//=================================================
//
//	particle.cpp
// 
// Author:近田 尚也
//
//=================================================

#include "particle.h"

// コンストラクタ
CParticle::CParticle()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_nCnt = 0;
}

// デストラクタ
CParticle::~CParticle()
{

}

// 生成
CParticle* CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife)
{
	CParticle* pParticle = nullptr;
	pParticle = new CParticle;

	if (pParticle != nullptr)
	{

		pParticle->m_pos = pos;
		pParticle->m_move = move;
		pParticle->m_col = col;
		pParticle->m_nLife = nLife;
		pParticle->Init();
		return pParticle;
	}
	else
	{
		return nullptr;
	}

}

// 初期化
HRESULT CParticle::Init(void)
{
	return S_OK;
}

// 終了処理
void CParticle::Uninit(void)
{
	CObject::Release();
}

// 更新処理
void CParticle::Update(void)
{
	if (m_nCnt == 60)
	{
		int nLife = 0;

		if (m_nLife > 0)
		{
			nLife = rand() % m_nLife + 60;
		}

		//ライフの減少
		m_nLife--;

		if (m_nLife <= 0)
		{
			Uninit();
			return;
		}

		CEffect::Create(m_pos, m_col, m_move, nLife);

		m_nCnt = 0;
	}
	else
	{
		m_nCnt++;
	}
}

// 描画処理
void CParticle::Draw(void)
{

}

void CParticle::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}