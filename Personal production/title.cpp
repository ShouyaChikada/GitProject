//=================================================
//
//	title.cpp
// 
// Author:近田 尚也
//
//=================================================

#include "title.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "texturemanager.h"
#include "game.h"
//#include "tutorial.h"

// コンストラクタ
CTitle::CTitle():CScene(CScene::MODE_TITLE)
{
	for (int nCnt = 0; nCnt < MAX_TITLE; nCnt++)
	{
		m_pTitleManager[nCnt] = nullptr;
		m_aPosTexU[nCnt] = NULL;
	}

}

// デストラクタ
CTitle::~CTitle()
{

}

// 初期化
HRESULT CTitle::Init(void)
{

	m_pTitleManager[0] = CTitleManager::Create(D3DXVECTOR3(640.0f,360.0f,0.0f), "data\\TEXTURE\\title.jpg");
	m_pTitleManager[1] = CTitleManager::Create(D3DXVECTOR3(640.0f,360.0f,0.0f), "data\\TEXTURE\\title5.png");
	m_pTitleManager[2] = CTitleManager::Create(D3DXVECTOR3(640.0f,360.0f,0.0f), "data\\TEXTURE\\title1.png");

	return S_OK;
}

//終了
void CTitle::Uninit(void)
{
	
}

// 更新
void CTitle::Update(void)
{
	// キーボード
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();
	CInputJoypad* pInputJoypad = CManager::GetJoypad();

	m_aPosTexU[0] += 0.0001f;
	m_aPosTexU[2] += 0.001f;

	for (int nCntBG = 0; nCntBG < MAX_TITLE; nCntBG++)
	{
		m_pTitleManager[nCntBG]->SetAnim(m_aPosTexU[nCntBG], 1.0f);
		//m_pTitleManager[nCntBG]->SetAnim(m_aPosTexU[nCntBG], 1.0f);
	}

	// フェード
	CFade* pFade = CManager::GetFade();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoypad->GetTrigger(CInputJoypad::KEY_START) == true)
	{//決定キー(ENTERキー)が押された
		//モード設定(ゲーム画面に移行)
		pFade->SetFade(new CGame());
	}
}

// 描画
void CTitle::Draw(void)
{

}