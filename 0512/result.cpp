//=================================================
//
//	result.cpp
// 
// Author:近田 尚也
//
//=================================================
#include "result.h"
#include "fade.h"
#include "manager.h"
#include "title.h"
#include "game.h"

// 静的メンバ変数
bool CResult::m_bCheck = false;

// コンストラクタ
CResult::CResult() :CScene(CScene::MODE_RESULT)
{
	m_pResultManager = nullptr;
}

// デストラクタ
CResult::~CResult()
{

}

//タイトル画面の初期化処理
HRESULT CResult::Init(void)
{
	m_bCheck = false;

	m_pResultManager = CResultManager::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f),"data\\TEXTURE\\result.jpg");
	return S_OK;
}
//リザルトの終了処理
void CResult::Uninit(void)
{

}
//タイトル画面の更新処理
void CResult::Update(void)
{
	// ゲームの終了の判定
	bool bUse = CGame::GetCheck();

	if (bUse == true)
	{
		m_bCheck = true;
	}

	// キーボード
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	// フェード
	CFade* pFade = CManager::GetFade();
	CFade::FADE mFade;
	mFade = pFade->GetFadeState();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true && mFade == CFade::FADE_NONE)
	{//決定キー(ENTERキー)が押された
		//モード設定(ゲーム画面に移行)
		pFade->SetFade(new CTitle());
	}
}
//タイトル画面の描画処理
void CResult::Draw(void)
{

}