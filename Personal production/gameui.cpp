//=================================================
//
//	[GamneUI.cpp]
// Author:chikada shouya
//
//=================================================
#include "gameui.h"
#include "manager.h"
#include "texturemanager.h"
#include "debugproc.h"

//=================================================
// コンストラクタ
//=================================================
CGameUI::CGameUI(int nPriolty) :CObject2D(nPriolty)
{

}

//=================================================
// デストラクタ
//=================================================
CGameUI::~CGameUI()
{

}

//=================================================
// 生成
//=================================================
CGameUI* CGameUI::Create(D3DXVECTOR3 pos, int type)
{
	CGameUI* pGameUI = nullptr;
	pGameUI = new CGameUI;

	if (pGameUI != nullptr)
	{
		pGameUI->SetPosition(pos);
		pGameUI->SetType(type);
		pGameUI->Init();
		return pGameUI;
	}
	else
	{
		return nullptr;
	}
}

//=================================================
// 初期化処理
//=================================================
HRESULT CGameUI::Init(void)
{
	CObject2D::Init();

	return S_OK;
}
//=================================================
// 終了処理
//=================================================
void CGameUI::Uninit(void)
{
	// 破棄
	CObject2D::Uninit();
}
//=================================================
// 更新処理
//=================================================
void CGameUI::Update(void)
{
	// 更新
	CObject2D::Update();

}
//=================================================
// 描画処理
//=================================================
void CGameUI::Draw(void)
{
	CObject2D::Draw();

	CDebugProc::Print("");
}