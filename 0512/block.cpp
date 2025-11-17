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
CBlock* CBlock::Create(const char * FileName,D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBlock* pBlock = nullptr;
	pBlock = new CBlock;
	if (pBlock != nullptr)
	{
		// オブジェクト設定
		pBlock->SetType(TYPE_BLOCK);
		pBlock->SetXfile(FileName);
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

	LPD3DXMESH pMesh = CObjectX::GetMesh();

	// ローカル変数宣言-----------------------------
	int nNumVtx;		// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE* pVtxBuff;		// 頂点バッファのポインタ
	//----------------------------------------------

	// 頂点数の取得
	nNumVtx = pMesh->GetNumVertices();

	// 頂点のサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(pMesh->GetFVF());

	// 頂点バッファをロック
	pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	m_size = CObject::SetSize(m_Vtxmax, m_Vtxmin, nNumVtx, sizeFVF, pVtxBuff);

	// アンロック
	pMesh->UnlockVertexBuffer();

	return S_OK;
}
//=========================
//　ブロック終了処理
//=========================
void CBlock::Uninit(void)
{
	CObjectX::Uninit();

	// CBlock::Release();
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
	// FOGの設定
	//CManager::GetRenderer()->SetupVertexFog(D3DCOLOR_XRGB(255, 255, 255), D3DFOG_LINEAR, TRUE, 0.00005f);

	CObjectX::Draw();

	// FOGを消す
	//CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

}

//=============================
//　ブロックの当たり判定処理
//=============================
bool CBlock::Collision(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3* move, D3DXVECTOR3* size)
{
	bool bLanding = false;	

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

		// 縦の当たり判定--------------------------
		if (pos->x - (size->x * HALF) < m_pos.x + (m_size.x * HALF) &&
			pos->x + (size->x * HALF) > m_pos.x - (m_size.x * HALF))
		{
			if (posOld->z - (size->z * HALF) < m_pos.z + (m_size.z * HALF) &&
				pos->z + (size->z * HALF) > m_pos.z - (m_size.z * HALF))
			{
				// 上からめり込んだ時
				if (posOld->y - (size->y * HALF) >= m_pos.y + (m_size.y * HALF) &&
					pos->y - (size->y * HALF) < m_pos.y + (m_size.y * HALF))
				{
					bLanding = true;	// ジャンプ
					pos->y = posOld->y;
					move->y = 0.0f;

				}
				// 下からめり込んだ時
				else if (posOld->y + size->y <= m_pos.y - (m_size.y * HALF) &&
					pos->y + size->y > m_pos.y - (m_size.y * HALF))
				{
					pos->y = m_pos.y - (m_size.y * HALF);
					move->y = 0.0f;
				}
			}
		}
		//// 縦の当たり判定--------------------------
		//if (pos->x - size->x * HALF < m_pos.x + m_size.x * HALF &&
		//	pos->x + size->x * HALF > m_pos.x - m_size.x * HALF)
		//{
		//	if (posOld->z - size->z * HALF < m_pos.z + m_size.z * HALF &&
		//		pos->z + size->z * HALF > m_pos.z - m_size.z * HALF)
		//	{
		//		// 上からめり込んだ時
		//		if (posOld->y >= m_pos.y + m_size.y * HALF &&
		//			pos->y < m_pos.y + m_size.y * HALF)
		//		{
		//			bLanding = true;	// ジャンプ
		//			pos->y = posOld->y;
		//			move->y = 0.0f;
		//		}
		//		// 下からめり込んだ時
		//		else if (posOld->y + size->y <= m_pos.y - m_size.y * HALF &&
		//			pos->y + size->y > m_pos.y - m_size.y * HALF)
		//		{
		//			pos->y = (m_pos.y - m_size.y) - size->y * HALF;
		//			move->y = 0.0f;
		//		}
		//	}
		//}
	}

	//if ((pos->x - PlayerSize.x * 0.5f) < (m_pos.x + m_size.x * 0.5f)
	//	&& (pos->x + PlayerSize.x * 0.5f) > (m_pos.x - m_size.x * 0.5f)
	//	&& (pos->z - PlayerSize.z * 0.5f) < (m_pos.z + m_size.z * 0.5f)
	//	&& (pos->z + PlayerSize.z * 0.5f) > (m_pos.z - m_size.z * 0.5f))
	//{
	//	if ((posOld->y >= m_pos.y + m_size.y)
	//		&& (pos->y < m_pos.y + m_size.y))
	//	{
	//		bLanding = true;
	//		pos->y = posOld->y;
	//	}
	//}
	//if ((pos->x + PlayerSize.x * 0.5f) < (m_pos.x - m_size.x * 0.5f)
	//	&& (pos->x - PlayerSize.x * 0.5f) > (m_pos.x + m_size.x * 0.5f)
	//	&& (pos->z + PlayerSize.z * 0.5f) < (m_pos.z - m_size.z * 0.5f)
	//	&& (pos->z - PlayerSize.z * 0.5f) > (m_pos.z + m_size.z * 0.5f))
	//{
	//	if ((posOld->y <= m_pos.y - m_size.y)
	//		&& (pos->y > m_pos.y - m_size.y))
	//	{
	//		bLanding = true;
	//		pos->y = posOld->y;
	//	}
	//}

	return bLanding;
}