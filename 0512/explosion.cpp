//=================================================
//
//	explosion.cpp
// 
// Author:近田尚也
//
//=================================================
#include "explosion.h"
#include "manager.h"

//============================
// コンストラクタ
//============================
CExplosion::CExplosion()
{
	//位置のゼロクリア
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

//============================
// デストラクタ
//============================
CExplosion::~CExplosion()
{

}

//============================
// 生成処理
//============================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CExplosion* pExplosion = NULL;
	pExplosion = new CExplosion;

	if (pExplosion != nullptr)
	{
		// 初期化
		pExplosion->Init(pos);
		return pExplosion;
	}
	else
	{
		return nullptr;
	}
}

//============================
// 初期化処理
//============================
HRESULT CExplosion::Init(D3DXVECTOR3 Pos)
{
	// 爆発のサイズ
	CObject2D::SetSize(160.0f, 160.0f);

	// テクスチャ自体のサイズ
	CObject2D::SetTex(0.125f, 1.0f);

	// 位置
	CObject2D::SetPosition(Pos);

	// 初期化
	CObject2D::Init();

	//位置を代入
	m_pos = Pos;

	return S_OK;
}

//============================
// 終了処理
//============================
void CExplosion::Uninit(void)
{
	// 終了
	CObject2D::Uninit();
}

//============================
// 更新処理
//============================
void CExplosion::Update(void)
{
	CObject2D::Update();

	m_nCounterAnim++;

	if ((m_nCounterAnim % 4) == 0)
	{
		m_nCounterAnim = 0;

		m_nPatternAnim = (m_nPatternAnim + 1) % 8;

		CObject2D::SetAnim(D3DXVECTOR2((float)m_nPatternAnim, 1.0f), 0.125f, 1.0f);
	}

	if (m_nPatternAnim >= 7)
	{
		CExplosion::Uninit();
	}

}

//============================
// 描画処理
//============================
void CExplosion::Draw(void)
{
	// 描画
	CObject2D::Draw();
}