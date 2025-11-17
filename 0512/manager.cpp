//=================================================
//
//	manager.cpp
// 
// Author:近田尚也
//
//=================================================
#include "manager.h"
#include "object2D.h"
#include "explosion.h"
#include "bg.h"
#include "enemy.h"
#include <stdlib.h>
#include "effect.h"
#include "number.h"
#include "time.h"

//静的メンバ変数
CMotion* CManager::m_pMotion = nullptr;
CMotion* CManager::m_pMotion1 = nullptr;
CModel* CManager::m_pModel[MAX_PMODEL] = {};
CModel* CManager::m_pModel1[MAX_HMODEL] = {};
CDebugProc* CManager::m_pDebugProc = nullptr;
CCamera* CManager::m_pCamera = nullptr;
CLight* CManager::m_pLight = nullptr;
CRenderer* CManager::m_pRenderer = nullptr;
CInputKeyboard* CManager::m_pInputKeyboard = nullptr;
CInputJoypad* CManager::m_pInputJoypad = nullptr;
CInputMouse* CManager::m_pInputMouse = nullptr;
CObject* CManager::m_pObject = nullptr;
CScene* CManager::m_pScene = nullptr;
CFade* CManager::m_pFade = nullptr;
CTextureManager* CManager::m_pTexManager = nullptr;

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
	m_pRenderer->Init(hWnd, TRUE);

	m_pInputKeyboard = new CInputKeyboard;
	//キーボードの初期化
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	m_pInputJoypad = new CInputJoypad;
	//ジョイパッドの初期化処理
	if (FAILED(m_pInputJoypad->Init()))
	{
		return E_FAIL;
	}

	m_pInputMouse = new CInputMouse;
	if (FAILED(m_pInputMouse->Init(hInstance,hWnd)))
	{
		return E_FAIL;
	}

	// テクスチャマネージャーのロード
	m_pTexManager = new CTextureManager;
	if (FAILED(m_pTexManager->Load()))
	{
		return E_FAIL;
	}

	m_pCamera = new CCamera;
	m_pCamera->Init();

	m_pLight = new CLight;
	m_pLight->Init();

	m_pDebugProc = new CDebugProc;
	m_pDebugProc->Init();

	// フェードの生成
	m_pFade = new CFade;
	m_pFade->Init();

	m_pFade->SetFade(new CTitle());

	//m_pMotion1 = CMotion::Create("data\\human.txt", &m_pModel1[0]);	//whichMotion.txt || motion2.txt

	return S_OK;
}

//終了処理
void CManager::Uninit(void)
{	
	//NULLチェック
	if (m_pInputKeyboard != nullptr)
	{
		//キーボードの終了処理
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}
	
	//NULLチェック
	if (m_pInputJoypad != nullptr)
	{
		//ジョイパッドの終了処理
		m_pInputJoypad->Uninit();
		delete m_pInputJoypad;
		m_pInputJoypad = nullptr;
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

	if (m_pTexManager != nullptr)
	{
		// 終了処理
		m_pTexManager->Unload();
		delete m_pTexManager;
		m_pTexManager = nullptr;
	}

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

//レンダラーの初期化
CRenderer* CManager::GetRenderer(void) 
{
	return m_pRenderer;
}

//キーボードの取得
CInputKeyboard* CManager::GetKeyboard(void)
{
	return m_pInputKeyboard;
}

//パッドの取得
CInputJoypad* CManager::GetJoypad(void)
{
	return m_pInputJoypad;
}

//マウスの取得
CInputMouse* CManager::GetMouse(void)
{
	return m_pInputMouse;
}

// オブジェクトの取得
CObject* CManager::getobject(void)
{
	return m_pObject;
}

CFade* CManager::GetFade()
{
	return m_pFade;
}

// デバッグフォントの取得
CDebugProc* CManager::GetDebugProc(void)
{
	return m_pDebugProc;
}

// カメラの取得
CCamera* CManager::GetCamera(void)
{
	return m_pCamera;
}

// ライトの取得
CLight* CManager::GetLight(void)
{
	return m_pLight;
}

// テクスチャマネージャーの取得
CTextureManager* CManager::GetTexManager(void)
{
	return m_pTexManager;
}

// モーションの取得
CMotion* CManager::GetMotion(void)
{
	return m_pMotion;
}
// モーションの取得1
CMotion* CManager::GetMotion1(void)
{
	return m_pMotion1;
}

CModel** CManager::GetModel(void)
{
	return &m_pModel[0];
}

CModel** CManager::GetModel1(void)
{
	return &m_pModel1[0];
}