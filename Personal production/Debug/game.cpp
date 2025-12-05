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
#include "rock.h"
#include "timer.h"
#include "enemy.h"

//=================================================
// 静的メンバ変数
//=================================================
CPlayer* CGame::m_pPlayer = nullptr;
CObject3D* CGame::m_pObject3D = nullptr;
CObjectX* CGame::m_pObjectX = nullptr;
CMeshField* CGame::m_pMeshField = nullptr;
CShadowS* CGame::m_pShadowS = nullptr;
CGrand* CGame::m_pGrand = nullptr;
CTimer* CGame::m_pTime = nullptr;
CPauseManager* CGame::m_pPauseManager = nullptr;
CModel* CGame::m_pModel1[MAX_HMODEL] = {};
bool CGame::m_bCheck = false;

//=================================================
// コンストラクタ
//=================================================
CGame::CGame() : CScene(CScene::MODE_GAME)
{

}

//=================================================
// デストラクタ
//=================================================
CGame::~CGame()
{

}

//=================================================
// 初期化
//=================================================
HRESULT CGame::Init(void)
{
	//m_pMotion1 = CMotion::Create("data\\human.txt", &m_pModel1[0]);	//whichMotion.txt || motion2.txt

	m_bCheck = false;

	m_pPauseManager = new CPauseManager;
	if (FAILED(m_pPauseManager->Init()))
	{
		return E_FAIL;
	}

	// 地球
	CRock::Create(D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\earth000.x", CObjectX::ROT_OFF);

	// 床
	CGrand::Create(D3DXVECTOR3(0.0f, -500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 月
	CObjectX::Create(D3DXVECTOR3(0.0f, -1900.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\moon.x", CObjectX::ROT_ON);

	// メッシュドーム
	//CMeshField::Create(D3DXVECTOR3(200.0f, -1100.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f);

	// タイム
	CTimer::Create(D3DXVECTOR3(100.0f, 100.0f, 0.0f));

	// 敵
	CEnemy::Create(D3DXVECTOR3(0.0f, 10.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// プレイヤー
	CPlayer::Create(D3DXVECTOR3(0.0f, 10.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//=================================================
// 終了処理
//=================================================
void CGame::Uninit(void)
{
	if (m_pPauseManager != nullptr)
	{
		// ポーズマネージャーの終了処理
		m_pPauseManager->Uninit();
		delete m_pPauseManager;
		m_pPauseManager = nullptr;
	}

}

//=================================================
// 更新処理
//=================================================
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

		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{//決定キー(ENTERキー)が押された
			//モード設定(ゲーム画面に移行)
			pFade->SetFade(new CResult());
			m_bCheck = true;
		}
	}
}

//=================================================
// 描画処理
//=================================================
void CGame::Draw(void)
{

}