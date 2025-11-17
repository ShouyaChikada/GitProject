//=================================================
//
//	gimmick.cpp
// 
//	Author:近田尚也
//
//=================================================

//****************************
// インクルードファイル宣言
//****************************
#include "gimmick.h"
#include "enemy.h"
#include "player.h"
#include "manager.h"
#include "game.h"
#include "gimmickmanager.h"
#include "scene.h"

// 静的メンバ変数
bool CGimmick::m_bUse = false;
CMeshCylinder* CGimmick::m_pMeshCylinder = nullptr;
CGauge* CGimmick::m_pGauge = nullptr;
CBaseUI* CGimmick::m_pBaseUI = nullptr;

// コンストラクタ
CGimmick::CGimmick(int nPriority) :CObjectX(nPriority)
{
	m_type = TYPE_METEORITE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Vtxmax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Vtxmin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bLanding = false;
	m_fAddCharge = 0.0f;
	m_bUse = false;

}

// デストラクタ
CGimmick::~CGimmick()
{

}

//=========================
// ブロックの生成
//=========================
CGimmick* CGimmick::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type)
{
	CGimmick* pGimmick = nullptr;
	pGimmick = new CGimmick;

	if (pGimmick != nullptr)
	{
		// オブジェクト設定
		pGimmick->SetXfile(pGimmick->GIMMICK_FILE[type]);
		pGimmick->SetPosition(pos);
		pGimmick->SetRot(D3DXToRadian(rot));
		pGimmick->Init(pos, rot, type);
		pGimmick->m_bUse = true;
		return pGimmick;

	}
	else
	{
		return nullptr;
	}
}

//=========================
//　ブロック初期化処理
//=========================
HRESULT CGimmick::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type)
{
	CScene::MODE mode = CScene::GetMode();

	CObjectX::Init();

	m_pMeshCylinder = CMeshCylinder::Create(D3DXVECTOR3(pos.x,-20.0f,pos.z), D3DXVECTOR3(0.0f,0.0f,0.0f), 250.0f);
	m_pGauge = CGauge::Create(D3DXVECTOR3(315.0f,335.0f,0.0f),nullptr,D3DXCOLOR(1.0f,1.0f,0.0f,1.0f));

	if (mode == CScene::MODE_TUTORIAL)
	{
		m_pBaseUI = CBaseUI::Create(D3DXVECTOR3(250.0f, 360.0f, 0.0f), "data\\TEXTURE\\Tumbase.png");
	}

	if (mode != CScene::MODE_TUTORIAL)
	{
		m_pBaseUI = CBaseUI::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), "data\\TEXTURE\\Tumbase.png");
	}

	m_pos = pos;
	m_rot = rot;
	m_type = type;
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
void CGimmick::Uninit(void)
{
	m_bUse = false;

	CObjectX::Uninit();

}
//=========================
//　ブロック更新処理
//=========================
void CGimmick::Update(void)
{
	bool bUse = CGimmickManager::GetPush();

	if (bUse == true)
	{
		m_fAddCharge += 0.5f;

		if (m_fAddCharge < 260.0f)
		{
			m_pGauge->FSetGageLength(200.0f, m_fAddCharge, 500.0f, 50.0f);
		}


	}

	m_pos += m_move;

	if (m_type == TYPE_METEORITE)
	{
		m_move.y = -0.05f;
		m_rot.y += 0.5f;
		if (m_pos.y <= 0.0f)
		{
			Uninit();
		}
	}	

	SetPosition(m_pos);
}
//=========================
//　ブロック描画処理
//=========================
void CGimmick::Draw(void)
{

	CObjectX::Draw();
}

//=============================
//　当たり判定処理
//=============================
bool CGimmick::Collision(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3* move, D3DXVECTOR3* size)
{
	bool bLanding = false;

	CPlayer* pPlayer = CGame::GetPlayer();

	if (m_bUse == true)
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
		}
	}
	return bLanding;
}