//=================================================
//
// [meteopillar.cpp]	隕石(柱)の処理全般
// 
// Author:chikada shouya
//
//=================================================
#include "meteopillar.h"

//=================================================
// コンストラクタ
//=================================================
CMeteoPillar::CMeteoPillar()
{
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_bChange[nCnt] = false;
	}
	m_bDeath = false;
}

//=================================================
// デストラクタ
//=================================================
CMeteoPillar::~CMeteoPillar()
{

}

//=================================================
// 生成
//=================================================
CMeteoPillar* CMeteoPillar::Create(D3DXVECTOR3 pos, ROT rot)
{
	CMeteoPillar* pMeteoPillar = nullptr;
	pMeteoPillar = new CMeteoPillar;

	if (pMeteoPillar != nullptr)
	{
		pMeteoPillar->SetPosition(pos);
		pMeteoPillar->SetIdx("data\\MODEL\\hasira.x");
		pMeteoPillar->SetRotaiton(CObjectX::ROT::ROT_OFF);
		pMeteoPillar->Init();
		pMeteoPillar->SetRotSize(rot);

		return pMeteoPillar;
	}
	else
	{
		return nullptr;
	}
}

//=================================================
// 初期化
//=================================================
HRESULT CMeteoPillar::Init(void)
{
	CRock::Init();

	return S_OK;
}

//=================================================
// 破棄
//=================================================
void CMeteoPillar::Uninit(void)
{
	CRock::Uninit();
}

//=================================================
// 更新
//=================================================
void CMeteoPillar::Update(void)
{
	CRock::Update();

	MovePillar();	//外側から飛んでくる隕石
}

//=================================================
// 描画
//=================================================
void CMeteoPillar::Draw(void)
{
	CRock::Draw();
}

//=================================================
// 向きの変更
//=================================================
void CMeteoPillar::SetRotSize(ROT Rot)
{
	D3DXVECTOR3 rot = D3DX_VEC3;
	D3DXVECTOR3 size = GetSize();
	switch (Rot)
	{
	case ROT_NONE:
		rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		size = D3DXVECTOR3(size.x, size.y, size.z);
		break;

	case ROT_X:
		rot = D3DXVECTOR3(1.57f, 0.0f, 0.0f);
		size = D3DXVECTOR3(size.x, size.z, size.y);
		break;

	case ROT_Y:
		rot = D3DXVECTOR3(0.0f, 1.57f, 0.0f);
		size = D3DXVECTOR3(size.x, size.y, size.z);
		break;

	case ROT_Z:
		rot = D3DXVECTOR3(0.0f, 0.0f, 1.57f);
		size = D3DXVECTOR3(size.y, size.x, size.z);
		break;

	case ROT_MAX:
		break;

	default:
		break;
	}

	SetRot(rot);
	SetSize(size);
}

//=================================================
// 柱の移動設定
//=================================================
void CMeteoPillar::MovePillar(void)
{
	//if (m_Type != TYPE_HASIRA)return;

	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMove();

	if (pos.x >= 2100.0f)
	{
		m_bChange[0] = true;
	}
	if (pos.x <= -2100.0f)
	{
		m_bChange[1] = true;
	}
	if (pos.z >= 1600.0f)
	{
		m_bChange[2] = true;
	}
	if (pos.z <= -1600.0f)
	{
		m_bChange[3] = true;
	}
	

	// 右から左 or みだりから右
	if (m_bChange[0] == true)
	{
		move.x -= (MAX_SPEED * 2.5f);

		if (pos.x <= -2100.0f)
		{
			m_bDeath = true;
		}
	}
	if (m_bChange[1] == true)
	{
		move.x += (MAX_SPEED * 2.5f);

		if (pos.x >= 2100.0f)
		{
			m_bDeath = true;
		}
	}

	// 上から下 or 下から上
	if (m_bChange[2] == true)
	{
		move.z -= (MAX_SPEED * 2.5f);

		if (pos.z <= -1600.0f)
		{
			m_bDeath = true;
		}
	}
	if (m_bChange[3] == true)
	{
		move.z += (MAX_SPEED * 2.5f);

		if (pos.z >= 1600.0f)
		{
			m_bDeath = true;
		}
	}

	SetPosition(pos);
	SetMove(move);
}
