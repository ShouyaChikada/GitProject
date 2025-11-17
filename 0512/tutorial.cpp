//=================================================
//
//	tutorial.h
// 
// Author:近田 尚也
//
//=================================================
#include "tutorial.h"
#include "input.h"
#include "manager.h"
#include "game.h"

CPlayer* CTutorial::m_pPlayer = nullptr;
CGrand* CTutorial::m_pGrand = nullptr;
CMeshField* CTutorial::m_pMeshField = nullptr;
CGimmickManager* CTutorial::m_pGimmickManager = nullptr;
CBlockManager* CTutorial::m_pBlockManager = nullptr;
CHumManager* CTutorial::m_pHumanManager = nullptr;
CBaseUI* CTutorial::m_pBaseUI = nullptr;
CModel* CTutorial::m_pModel1[MAX_HMODEL] = {};
CMotion* CTutorial::m_pMotion1 = nullptr;
bool CTutorial::m_bCheck = false;
// コンストラクタ
CTutorial::CTutorial() : CScene(CScene::MODE_TUTORIAL)
{

}

// デストラクタ
CTutorial::~CTutorial()
{

}

// 初期化
HRESULT CTutorial::Init(void)
{
	m_bCheck = true;

	m_pMotion1 = CMotion::Create("data\\human.txt", &m_pModel1[0]);	//whichMotion.txt || motion2.txt

	m_pGimmickManager = new CGimmickManager;
	if (FAILED(m_pGimmickManager->Init()))
	{
		return E_FAIL;
	}

	m_pHumanManager = new CHumManager;
	if (FAILED(m_pHumanManager->Init()))
	{
		return E_FAIL;
	}

	m_pBlockManager = new CBlockManager;
	if (FAILED(m_pBlockManager->Init()))
	{
		return E_FAIL;
	}


	m_pPlayer = CPlayer::Create(D3DXVECTOR3(300.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pMeshField = CMeshField::Create(D3DXVECTOR3(200.0f, -1100.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 500.0f);

	m_pGrand = CGrand::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
	return S_OK;
}

// 終了処理
void CTutorial::Uninit(void)
{
	if (m_pGimmickManager != nullptr)
	{
		// ギミックマネージャーの終了処理
		m_pGimmickManager->Uninit();
		delete m_pGimmickManager;
		m_pGimmickManager = nullptr;
	}

	if (m_pBlockManager != nullptr)
	{
		// ブロックマネージャーの終了処理
		m_pBlockManager->Uninit();
		delete m_pBlockManager;
		m_pBlockManager = nullptr;
	}

	if (m_pHumanManager != nullptr)
	{
		//	ヒューマンマネージャーの終了処理
		m_pHumanManager->Uninit();
		delete m_pHumanManager;
		m_pHumanManager = nullptr;
	}

}

// 更新処理
void CTutorial::Update(void)
{
	static int nCnt = 0;

	// キーボード
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	// パッド
	CInputJoypad* pInputJoypad = CManager::GetJoypad();

	// フェード
	CFade* pFade = CManager::GetFade();

	bool bUse = CGimmickManager::GetbCheck();

	// ブロックマネージャーの更新処理
	m_pBlockManager->Update();

	// ヒューマンマネージャーの更新処理
	m_pHumanManager->Update();

	// ギミックマネージャーの更新処理
	m_pGimmickManager->Update();

	if (bUse == true)
	{
		nCnt++;
		if (nCnt > 120)
		{
			//モード設定(ゲーム画面に移行)
			pFade->SetFade(new CGame());
			m_bCheck = false;
		}
	}
}

// 描画処理
void CTutorial::Draw(void)
{
	// ギミックマネージャーの描画処理
	m_pGimmickManager->Draw();
}

// モーションの取得1
CMotion* CTutorial::GetMotion1(void)
{
	return m_pMotion1;
}

CModel** CTutorial::GetModel1(void)
{
	return &m_pModel1[0];
}