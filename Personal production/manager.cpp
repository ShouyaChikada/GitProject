//=================================================
//
// [manager.cpp]
// Author:chikada shouya
//
//=================================================
#include "manager.h"
#include "object2D.h"
#include "time.h"
#include "modelmanager.h"
#include "rock.h"
#include "meshfield.h"
#include "title.h"

//静的メンバ変数
CDebugProc* CManager::m_pDebugProc = nullptr;
CCamera* CManager::m_pCamera = nullptr;
CLight* CManager::m_pLight = nullptr;
CRenderer* CManager::m_pRenderer = nullptr;
CInputKeyboard* CManager::m_pInputKeyboard = nullptr;
CInputJoypad* CManager::m_pInputJoypad = nullptr;
CInputMouse* CManager::m_pInputMouse = nullptr;
CObject* CManager::m_pObject = nullptr;
CTextureManager* CManager::m_pTexManager = nullptr;
CFade* CManager::m_pFade = nullptr;
CScene* CManager::m_pScene = nullptr;

//コンストラクタ
CManager::CManager()
{
	
}
//デストラクタ
CManager::~CManager()
{

}

//初期化処理
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//メモリ確保
	m_pRenderer = new CRenderer;
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{
		return E_FAIL;
	}

	//キーボードの初期化
	m_pInputKeyboard = new CInputKeyboard;
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//ジョイパッドの初期化処理
	m_pInputJoypad = new CInputJoypad;
	if (FAILED(m_pInputJoypad->Init()))
	{
		return E_FAIL;
	}

	// マウスの初期化
	m_pInputMouse = new CInputMouse;
	if (FAILED(m_pInputMouse->Init(hInstance,hWnd)))
	{
		return E_FAIL;
	}

	// カメラの初期化
	m_pCamera = new CCamera;
	if (m_pCamera != nullptr)
	{
		m_pCamera->Init();
	}

	// ライトの初期化
	m_pLight = new CLight;
	if (m_pLight != nullptr)
	{
		m_pLight->Init();
	}

	// デバッグフォントの初期化
	m_pDebugProc = new CDebugProc;
	if (m_pDebugProc != nullptr)
	{
		m_pDebugProc->Init();
	}


	// フェードの初期化
	m_pFade = new CFade;

	if (m_pFade != nullptr)
	{
		m_pFade->Init();
		m_pFade->SetFade(new CTitle());
	}

	return S_OK;
}

//終了処理
void CManager::Uninit(void)
{	
	//NULLチェック
	if (m_pInputKeyboard != NULL)
	{
		//キーボードの終了処理
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
	
	//NULLチェック
	if (m_pInputJoypad != NULL)
	{
		//ジョイパッドの終了処理
		m_pInputJoypad->Uninit();
		delete m_pInputJoypad;
		m_pInputJoypad = NULL;
	}

	//NULLチェック
	if (m_pInputMouse != nullptr)
	{
		//マウスの終了処理
		m_pInputMouse->Uninit();
		delete m_pInputMouse;
		m_pInputMouse = nullptr;
	}

	// NULLチェック
	if (m_pRenderer != nullptr)
	{
		// レンダラーの終了処理
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pDebugProc != nullptr)
	{
		// デバッグフォントの終了処理
		m_pDebugProc->Uninit();
		delete m_pDebugProc;
		m_pDebugProc = nullptr;
	}

	if (m_pCamera != nullptr)
	{
		// カメラの終了処理
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pLight != nullptr)
	{
		// ライトの終了処理
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}

	if (m_pFade != nullptr)
	{	
		// フェードの終了処理
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}

	// テクスチャマネージャーの破棄
	CTextureManager::Instance()->Unload();

	// モデルマネージャーの破棄
	CModelManager::Instance()->Unload();

	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}

	// すべてのオブジェクトの破棄
	CObject::ReleaseAll();

}

//更新処理
void CManager::Update(void)
{
	if (m_pInputKeyboard != nullptr)
	{
		// キーボードの更新
		m_pInputKeyboard->Update();
	}

	// ジョイパッドの更新
	if (m_pInputJoypad != nullptr)
	{
		m_pInputJoypad->Update();
	}

	if (m_pInputMouse != nullptr)
	{
		// マウスの更新
		m_pInputMouse->Update();
	}

	if (m_pCamera != nullptr)
	{
		// カメラの更新処理
		m_pCamera->Update();
	}

	if (m_pLight != nullptr)
	{
		// ライトの更新処理
		m_pLight->Update();
	}

	if (m_pFade != nullptr)
	{
		// フェードの更新処理
		m_pFade->Update();
	}

	// null チェック
	if (m_pScene != nullptr)
	{
		// シーンの更新処理
		m_pScene->Update();
	}

	if (m_pRenderer != nullptr)
	{
		// レンダラーの更新
		m_pRenderer->Update();
	}
}

// 描画処理
void CManager::Draw()
{
	CScene::MODE pMode;
	pMode = m_pScene->GetMode();

	CFade::FADE pFade;
	pFade = m_pFade->GetFadeState();

	if (m_pRenderer != nullptr)
	{
		//レンダラーの描画
		m_pRenderer->Draw();

		if (pMode == m_pScene->MODE_TITLE)
		{
			CDebugProc::Print("現在のシーン:タイトル\n");
		}
		if (pMode == m_pScene->MODE_GAME)
		{
			CDebugProc::Print("現在のシーン:ゲーム\n");
		}
		if (pMode == m_pScene->MODE_RESULT)
		{
			CDebugProc::Print("現在のシーン:リザルト\n");
		}

		if (pFade == m_pFade->FADE_IN)
		{
			CDebugProc::Print("現在のフェイド:フェイドイン\n");
		}

		if (pFade == m_pFade->FADE_OUT)
		{
			CDebugProc::Print("現在のフェイド:フェイドアウト\n");
		}
	}
}

// モード設定
void CManager::SetMode(CScene* pNewScene)
{
	// サウンドの停止
	
	// シーンの破棄
	if (m_pScene != nullptr)
	{
		// 現在のモードを破棄
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;

		// すべてのオブジェクトの破棄
		CObject::ReleaseAll();

	}

	if (m_pScene == nullptr)
	{
		m_pScene = pNewScene;
		m_pScene->Init();
	}

}