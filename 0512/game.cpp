//=================================================
//
//	game.cpp
// 
// Author:近田 尚也
//
//=================================================
#include "game.h"
#include "manager.h"
#include "result.h"

// 静的メンバ変数
CPlayer* CGame::m_pPlayer = nullptr;
CScore* CGame::m_pScore = nullptr;
CObject3D* CGame::m_pObject3D = nullptr;
CBillboard* CGame::m_pBillboard = nullptr;
CObjectX* CGame::m_pObjectX = nullptr;
CMeshField* CGame::m_pMeshField = nullptr;
CBlockManager* CGame::m_pBlockManager = nullptr;
CShadowS* CGame::m_pShadowS = nullptr;
CGrand* CGame::m_pGrand = nullptr;
CGimmickManager* CGame::m_pGimmickManager = nullptr;
CHumManager* CGame::m_pHumManager = nullptr;
CTime* CGame::m_pTime = nullptr;
CPauseManager* CGame::m_pPauseManager = nullptr;
CModel* CGame::m_pModel1[MAX_HMODEL] = {};
CMotion* CGame::m_pMotion1 = nullptr;
bool CGame::m_bCheck = false;

// コンストラクタ
CGame::CGame() : CScene(CScene::MODE_GAME)
{

}

// デストラクタ
CGame::~CGame()
{

}

// 初期化
HRESULT CGame::Init(void)
{
	m_pMotion1 = CMotion::Create("data\\human.txt", &m_pModel1[0]);	//whichMotion.txt || motion2.txt

	m_bCheck = false;

	m_pBlockManager = new CBlockManager;
	if (FAILED(m_pBlockManager->Init()))
	{
		return E_FAIL;
	}

	m_pGimmickManager = new CGimmickManager;
	if (FAILED(m_pGimmickManager->Init()))
	{
		return E_FAIL;
	}

	m_pHumManager = new CHumManager;
	if (FAILED(m_pHumManager->Init()))
	{
		return E_FAIL;
	}

	m_pPauseManager = new CPauseManager;
	if (FAILED(m_pPauseManager->Init()))
	{
		return E_FAIL;
	}

	m_pPlayer = CPlayer::Create(D3DXVECTOR3(300.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pScore = CScore::Create(D3DXVECTOR3(1000.0f, 50.0f, 0.0f));

	m_pMeshField = CMeshField::Create(D3DXVECTOR3(200.0f, -1100.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 500.0f);

	m_pGrand = CGrand::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pTime = CTime::Create(D3DXVECTOR3(100.0f, 50.0f, 0.0f));

	return S_OK;
}

// 終了処理
void CGame::Uninit(void)
{
	if (m_pBlockManager != nullptr)
	{
		// ブロックマネージャーの終了処理
		m_pBlockManager->Uninit();
		delete m_pBlockManager;
		m_pBlockManager = nullptr;
	}

	if (m_pGimmickManager != nullptr)
	{
		// ギミックマネージャーの終了処理
		m_pGimmickManager->Uninit();
		delete m_pGimmickManager;
		m_pGimmickManager = nullptr;
	}

	if (m_pHumManager != nullptr)
	{
		// ヒューマンマネージャーの終了処理
		m_pHumManager->Uninit();
		delete m_pHumManager;
		m_pHumManager = nullptr;
	}

	if (m_pPauseManager != nullptr)
	{
		// ポーズマネージャーの終了処理
		m_pPauseManager->Uninit();
		delete m_pPauseManager;
		m_pPauseManager = nullptr;
	}

}

// 更新処理
void CGame::Update(void)
{
	// キーボード
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	// ポーズの押下確認関数
	m_pPauseManager->SetEnablePause();

	// ポーズの更新処理
	m_pPauseManager->Update();
	

	//// パッド
	//CInputJoypad* pInputJoypad = nullptr;
	//pInputJoypad = CManager::GetJoypad();

	// フェード
	CFade* pFade = CManager::GetFade();


	if (m_pPauseManager->GetPause() == false)
	{
		// ブロックマネージャーの更新処理
		m_pBlockManager->Update();

		// ギミックマネージャーの更新処理
		m_pGimmickManager->Update();

		// ヒューマンマネージャーの更新処理
		m_pHumManager->Update();

		bool bFinish = m_pTime->GetbTime();

		if (bFinish == true || pInputKeyboard->GetTrigger(DIK_M) == true)
		{//決定キー(ENTERキー)が押された
			//モード設定(ゲーム画面に移行)
			pFade->SetFade(new CResult());
			m_bCheck = true;
		}
	}
}

// 描画処理
void CGame::Draw(void)
{
	// ギミックマネージャーの描画処理
	m_pGimmickManager->Draw();
}

// プレイヤーの取得
CPlayer* CGame::GetPlayer(void)
{
	return m_pPlayer;
}

// スコアの取得
CScore* CGame::GetScore(void)
{
	return m_pScore;
}

// ライトの取得
CObject3D* CGame::GetObject3D(void)
{
	return m_pObject3D;
}

// ライトの取得
CBillboard* CGame::GetBillboard(void)
{
	return m_pBillboard;
}

// オブジェクトXの取得
CObjectX* CGame::GetObjectX(void)
{
	return m_pObjectX;
}

// メッシュフィールドの取得
CMeshField* CGame::GetMeshField(void)
{
	return m_pMeshField;
}

// オブジェクトの取得
CBlockManager* CGame::GetBlockManager(void)
{
	return m_pBlockManager;
}

// 影の取得
CShadowS* CGame::GetShadowS(void)
{
	return m_pShadowS;
}

// 地面の取得
CGrand* CGame::GetGrand(void)
{
	return m_pGrand;
}

// ギミックマネージャーの取得
CGimmickManager* CGame::GetGimmickManager(void)
{
	return m_pGimmickManager;
}

// ヒューマンマネージャーの取得
CHumManager* CGame::GetHumManamger(void)
{
	return m_pHumManager;
}

// タイムの取得
CTime* CGame::GetTime(void)
{
	return m_pTime;
}

// モーションの取得1
CMotion* CGame::GetMotion1(void)
{
	return m_pMotion1;
}

CModel** CGame::GetModel1(void)
{
	return &m_pModel1[0];
}
