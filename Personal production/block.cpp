//=================================================
//
//	block.cpp
// 
// Author:近田 尚也
//
//=================================================

//****************************
// インクルードファイル宣言
//****************************
#include "block.h"
#include "enemy.h"
#include "player.h"
#include "manager.h"
#include "game.h"

// コンストラクタ
CBlock::CBlock(int nPriority):CObjectX(nPriority)
{
	m_type = TYPE_0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Vtxmax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Vtxmin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bLanding = false;
	m_nIdx = NULL;
}

// デストラクタ
CBlock::~CBlock()
{

}

//=========================
// ブロックの生成
//=========================
CBlock* CBlock::Create(std::string FilePath,D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBlock* pBlock = nullptr;
	pBlock = new CBlock;
	if (pBlock != nullptr)
	{
		// オブジェクト設定
		pBlock->SetIdx(FilePath);
		pBlock->SetPosition(pos);
		pBlock->SetRot(D3DXToRadian(rot));	
		pBlock->Init(pos, rot);
		return pBlock;

	}
	else
	{
		return nullptr;
	}
}

//=========================
//　ブロック初期化処理
//=========================
HRESULT CBlock::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CObjectX::Init();

	m_pos = pos;
	m_rot = rot;
	m_size = GetSize();

	return S_OK;
}
//=========================
//　ブロック終了処理
//=========================
void CBlock::Uninit(void)
{
	CObjectX::Uninit();
}
//=========================
//　ブロック更新処理
//=========================
void CBlock::Update(void)
{
	// 一旦なし
	CObjectX::Update();
	
}
//=========================
//　ブロック描画処理
//=========================
void CBlock::Draw(void)
{
	CObjectX::Draw();
}

//=============================
//　ブロックの当たり判定処理
//=============================
void CBlock::Collision(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3* move, D3DXVECTOR3* size)
{

	if (pos->y - (size->y * HALF) < m_pos.y + (m_size.y * HALF) &&
		pos->y + (size->y * HALF) > m_pos.y - (m_size.y * HALF))
	{
		// 左右の当たり判定----------------------
		if (posOld->z - (size->z * HALF) < m_pos.z + (m_size.z * HALF) &&
			pos->z + (size->z * HALF) > m_pos.z - (m_size.z * HALF))
		{
			// 左からめり込む
			if (posOld->x + (size->x * HALF) < m_pos.x - (m_size.x * HALF) &&
				pos->x + (size->x * HALF) > m_pos.x - (m_size.x * HALF))
			{
				pos->x = m_pos.x - m_size.x * HALF - size->x * HALF - 0.1f;

			}
			// 右からめり込む
			else if (posOld->x - (size->x * HALF) > m_pos.x + (m_size.x * HALF) &&
				pos->x - (size->x * HALF) < m_pos.x + (m_size.x * HALF))
			{
				pos->x = m_pos.x + (m_size.x * HALF) + (size->x * HALF) + 0.1f;
			}
		}

		// 前後の当たり判定------------------------------
		if (posOld->x - (size->z * HALF) < m_pos.x + (m_size.z * HALF) &&
			pos->x + (size->z * HALF) > m_pos.x - (m_size.z * HALF))
		{
			// 手前からめり込む
			if (posOld->z + (size->z * HALF) < m_pos.z - (m_size.z * HALF) &&
				pos->z + (size->z * HALF) > m_pos.z - (m_size.z * HALF))
			{
				pos->z = m_pos.z - (m_size.z * HALF) - (size->z * HALF) - 0.3f;

			}
			// 奥からめり込む
			else if (posOld->z - (size->z * HALF) > m_pos.z + (m_size.z * HALF) &&
				pos->z - (size->z * HALF) < m_pos.z + (m_size.z * HALF))
			{
				pos->z = m_pos.z + (m_size.z * HALF) + (size->z * HALF) + 0.3f;

			}
		}

	}
}