//=================================================
//
//	bg.cpp
// 
// Author:近田 尚也
//
//=================================================
#include "bg.h"
#include "manager.h"

//コンストラクタ
CBg::CBg()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//デストラクタ
CBg::~CBg()
{

}

CBg* CBg::create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBg* pBg = nullptr;
	pBg = new CBg;

	if (pBg != nullptr)
	{
		pBg->Init(pos);
		return pBg;
	}
	else
	{
		return nullptr;
	}
}

HRESULT CBg::Init(D3DXVECTOR3 Pos)
{
	CObject2D::SetSize(1280.0f, 720.0f);
	CObject2D::SetTex(1.0f, 1.0f);
	CObject2D::Init();
	CObject2D::SetPosition(Pos);
	m_pos = Pos;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//============================
//終了処理
//============================
void CBg::Uninit(void)
{
	CObject2D::Uninit();
}

//プレイヤーの更新処理
void CBg::Update(void)
{
	CObject2D::Update();
}

//プレイヤーの描画処理
void CBg::Draw(void)
{
	CObject2D::Draw();
}