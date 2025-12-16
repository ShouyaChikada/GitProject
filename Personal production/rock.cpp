//=================================================
//
//	[rock.cpp]
// Author:chikada shouya
//
//=================================================
#include "rock.h"
#include "input.h"
#include "manager.h"
#include "texturemanager.h"
#include "modelmanager.h"
#include "debugproc.h"
#include "player.h"
#include "easing.h"
#include <cmath>

//=================================================
// コンストラクタ
//=================================================
CRock::CRock(int nPriolty) :CObjectX(nPriolty)
{
	m_move = D3DX_VEC3;
	m_CollisionPos = D3DX_VEC3;
	m_CollisionSize = D3DX_VEC3;
}

//=================================================
// デストラクタ
//=================================================
CRock::~CRock()
{

}

//=================================================
// 生成
//=================================================
CRock* CRock::Create(D3DXVECTOR3 pos, ROT Rot, CObjectX::ROT rotation, TYPE type)
{
	CRock* pRock = nullptr;
	pRock = new CRock;

	if (pRock != nullptr)
	{
		pRock->SetPosition(pos);
		pRock->SetRotaiton(rotation);
		pRock->Init();
		return pRock;
	}
	else
	{
		return nullptr;
	}
}

//=================================================
// 初期化処理
//=================================================
HRESULT CRock::Init()
{
	CObjectX::Init();


	return S_OK;
}
//=================================================
// 終了処理
//=================================================
void CRock::Uninit(void)
{
	// 破棄
	CObjectX::Uninit();
}
//=================================================
// 更新処理
//=================================================
void CRock::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRot();

	// 更新
	CObjectX::Update();
	
	//移動量を更新
	m_move.x += (0.0f - m_move.x) * 0.5f;
	m_move.z += (0.0f - m_move.z) * 0.5f;

	pos += m_move;

	SetPosition(pos);


}
//=================================================
// 描画処理
//=================================================
void CRock::Draw(void)
{
	CObjectX::Draw();
}

//=================================================
//　隕石の当たり判定処理
//=================================================
void CRock::Collision(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3* move, D3DXVECTOR3* size)
{
	m_CollisionPos = GetPosition();
	m_CollisionSize = GetSize();

	if (m_CollisionPos != nullptr && m_CollisionSize != nullptr)
	{
		if (pos->y - (size->y * HALF) < m_CollisionPos.y + (m_CollisionSize.y * HALF) &&
			pos->y + (size->y * HALF) > m_CollisionPos.y - (m_CollisionSize.y * HALF))
		{
			// 左右の当たり判定----------------------
			if (posOld->z - (size->z * HALF) < m_CollisionPos.z + (m_CollisionSize.z * HALF) &&
				pos->z + (size->z * HALF) > m_CollisionPos.z - (m_CollisionSize.z * HALF))
			{
				// 左からめり込む
				if (posOld->x + (size->x * HALF) < m_CollisionPos.x - (m_CollisionSize.x * HALF) &&
					pos->x + (size->x * HALF) > m_CollisionPos.x - (m_CollisionSize.x * HALF))
				{
					pos->x = m_CollisionPos.x - m_CollisionSize.x * HALF - size->x * HALF - 0.1f;

				}
				// 右からめり込む
				else if (posOld->x - (size->x * HALF) > m_CollisionPos.x + (m_CollisionSize.x * HALF) &&
					pos->x - (size->x * HALF) < m_CollisionPos.x + (m_CollisionSize.x * HALF))
				{
					pos->x = m_CollisionPos.x + (m_CollisionSize.x * HALF) + (size->x * HALF) + 0.1f;
				}
			}

			// 前後の当たり判定------------------------------
			if (posOld->x - (size->x * HALF) < m_CollisionPos.x + (m_CollisionSize.x * HALF) &&
				pos->x + (size->x * HALF) > m_CollisionPos.x - (m_CollisionSize.x * HALF))
			{
				// 手前からめり込む
				if (posOld->z + (size->z * HALF) < m_CollisionPos.z - (m_CollisionSize.z * HALF) &&
					pos->z + (size->z * HALF) > m_CollisionPos.z - (m_CollisionSize.z * HALF))
				{
					pos->z = m_CollisionPos.z - (m_CollisionSize.z * HALF) - (size->z * HALF) - 0.3f;

				}
				// 奥からめり込む
				else if (posOld->z - (size->z * HALF) > m_CollisionPos.z + (m_CollisionSize.z * HALF) &&
					pos->z - (size->z * HALF) < m_CollisionPos.z + (m_CollisionSize.z * HALF))
				{
					pos->z = m_CollisionPos.z + (m_CollisionSize.z * HALF) + (size->z * HALF) + 0.3f;

				}
			}

		}
	}
}

//=================================================
// 移動処理
//=================================================
void CRock::MoveInput(void)
{
	CObjectX::Update();

	// キーボード
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	D3DXVECTOR3 move = D3DX_VEC3;
	D3DXVECTOR3 rotDest = GetRotDest();

	D3DXVECTOR3 vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXVECTOR3 VecAxis = GetVecAxis();

	float fValueRot = GetValueRot();

	//カメラの情報取得
	CCamera* pCamera = CManager::GetCamera();
	D3DXVECTOR3 rot = pCamera->GetRotasion();

	//pCamera->SetFollowing(pos, m_rotDest);

	//左移動
	if (pInputKeyboard->GetPress(DIK_LEFT) == true)
	{
		fValueRot = MAX_ROT;

		//前移動
		if (pInputKeyboard->GetPress(DIK_UP) == true)
		{
			rotDest.y = rot.y + D3DX_PI * 0.75f;
			m_move.x = sinf(rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(rotDest.y + D3DX_PI) * MAX_SPEED;

			//m_rot.z = 0.19625f;

		}
		//後ろ移動
		else if (pInputKeyboard->GetPress(DIK_DOWN) == true)
		{

			rotDest.y = rot.y + D3DX_PI * 0.25f;
			m_move.x = sinf(rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(rotDest.y + D3DX_PI) * MAX_SPEED;

		}
		else
		{
			rotDest.y = rot.y + D3DX_PI * 0.5f;
			m_move.x = sinf(rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(rotDest.y + D3DX_PI) * MAX_SPEED;

		}
	}
	//右移動
	if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
	{
		fValueRot = MAX_ROT;

		//前移動
		if (pInputKeyboard->GetPress(DIK_UP) == true)
		{
			rotDest.y = rot.y - D3DX_PI * 0.75f;
			m_move.x = sinf(rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(rotDest.y + D3DX_PI) * MAX_SPEED;
		}
		//後ろ移動
		else if (pInputKeyboard->GetPress(DIK_DOWN) == true)
		{
			rotDest.y = rot.y - D3DX_PI * 0.25f;
			m_move.x = sinf(rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(rotDest.y + D3DX_PI) * MAX_SPEED;
		}
		else
		{

			rotDest.y = rot.y - D3DX_PI * 0.5f;
			m_move.x = sinf(rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(rotDest.y + D3DX_PI) * MAX_SPEED;
		}
	}
	//前移動
	if (pInputKeyboard->GetPress(DIK_UP) == true)
	{
		fValueRot = MAX_ROT;

		if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
		{
			m_move.x = sinf(rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(rotDest.y + D3DX_PI) * MAX_SPEED;
		}
		//前移動
		else if (pInputKeyboard->GetPress(DIK_LEFT) == true)
		{
			m_move.x = sinf(rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(rotDest.y + D3DX_PI) * MAX_SPEED;
		}
		else
		{
			rotDest.y = rot.y + D3DX_PI;
			m_move.x = sinf(rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(rotDest.y + D3DX_PI) * MAX_SPEED;
		}
	}
	//後ろ移動
	if (pInputKeyboard->GetPress(DIK_DOWN) == true)
	{
		fValueRot = MAX_ROT;

		if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			m_move.x = sinf(rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(rotDest.y + D3DX_PI) * MAX_SPEED;
		}
		//前移動
		else if (pInputKeyboard->GetPress(DIK_LEFT) == true)
		{
			m_move.x = sinf(rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(rotDest.y + D3DX_PI) * MAX_SPEED;
		}
		else
		{
			rotDest.y = rot.y;
			m_move.x = sinf(rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(rotDest.y + D3DX_PI) * MAX_SPEED;

		}
	}

	if ((pInputKeyboard->GetPress(DIK_UP) == false) &&
		(pInputKeyboard->GetPress(DIK_LEFT) == false) &&
		(pInputKeyboard->GetPress(DIK_DOWN) == false) &&
		(pInputKeyboard->GetPress(DIK_RIGHT) == false))
	{
		fValueRot = 0.0f;
	}

	// 進行ベクトルの正規化
	D3DXVec3Normalize(&move, &m_move);

	// 外積
	D3DXVec3Cross(&VecAxis, &vecU, &move);

	// 回転量のセット
	SetValueRot(fValueRot);

	// 回転軸のセット
	SetVecAxis(VecAxis);
}