//=================================================
//
//	particle.cpp
// 
// Author:chikada shouya
//
//=================================================
#include "particle.h"
#include <time.h>

//=================================================
// コンストラクタ
//=================================================
CParticle::CParticle()
{
	m_nCnt = 0;
}

//=================================================
// デストラクタ
//=================================================
CParticle::~CParticle()
{

}

//=================================================
// 生成
//=================================================
CParticle* CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife)
{
	CParticle* pParticle = nullptr;
	pParticle = new CParticle;

	if (pParticle != nullptr)
	{

		pParticle->SetPosition(pos);
		pParticle->SetMove(move);
		pParticle->SetColor(col);
		pParticle->SetLife(nLife);
		pParticle->Init();
		return pParticle;
	}
	else
	{
		return nullptr;
	}

}

//=================================================
// 初期化
//=================================================
HRESULT CParticle::Init(void)
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	return S_OK;
}

//=================================================
// 終了処理
//=================================================
void CParticle::Uninit(void)
{
	// 破棄
	CObject::Release();
}

//=================================================
// 更新処理
//=================================================
void CParticle::Update(void)
{
	// 0から99までの乱数を生成する
	//int nRand0 = (std::rand() % 500 + (-300));

	if (m_nCnt == 0)
	{
		int nLife = 0;

		if (m_nLife > 0)
		{
			nLife = std::rand() % m_nLife + 60;
		}

		//ライフの減少
		m_nLife--;

		if (m_nLife <= 0)
		{
			Uninit();
			return;
		}

		CEffect::Create(m_pos, m_col, m_move, nLife,"data\\TEXTURE\\effect000.jpg");

		m_nCnt = 60;
	}
	else
	{
		m_nCnt--;
	}
}

//=================================================
// 描画処理
//=================================================
void CParticle::Draw(void)
{

}