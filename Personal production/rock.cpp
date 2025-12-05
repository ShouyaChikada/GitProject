//=================================================
//
//	[rock.cpp]
// Author:chikada shouya
//
//=================================================
#include "rock.h"
#include "manager.h"
#include "texturemanager.h"
#include "modelmanager.h"
#include "debugproc.h"

//=================================================
// コンストラクタ
//=================================================
CRock::CRock(int nPriolty) :CObjectX(nPriolty)
{
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Diff = NULL;
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
CRock* CRock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, std::string FilePath, CObjectX::ROT rotation)
{
	CRock* pRock = nullptr;
	pRock = new CRock;

	if (pRock != nullptr)
	{
		pRock->SetPosition(pos);
		pRock->SetRot(D3DXToRadian(rot));
		pRock->SetIdx(FilePath);
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
HRESULT CRock::Init(void)
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

	//移動とモーションのセット
	//SetInput(pos);

	//角度の調整
	m_Diff = m_rotDest.y - rot.y;

	// 角度の正規化
	if (m_Diff < -D3DX_PI)
	{
		m_Diff = m_Diff + (D3DX_PI * 2);
	}
	else if (m_Diff > D3DX_PI)
	{
		m_Diff = m_Diff - (D3DX_PI * 2);
	}

	rot.y += m_Diff * 0.25f;
	SetRot(rot);

	//前回の位置を保存	位置更新の上で書く
	m_posOld = pos;
	pos += m_move;

	SetPosition(pos);

	//移動量を更新
	m_move.x += (0.0f - m_move.x) * 0.5f;
	m_move.z += (0.0f - m_move.z) * 0.5f;

	//m_pos = pos;
}
//=================================================
// 描画処理
//=================================================
void CRock::Draw(void)
{
	CObjectX::Draw();

	CDebugProc::Print("Rock : { %.2f,%.2f,%.2f }\n", m_pos.x, m_pos.y, m_pos.z);
}

//=================================================
// 移動処理
//=================================================
void CRock::SetInput(D3DXVECTOR3 pos)
{
	// キーボード
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXVECTOR3 vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXVECTOR3 VecAxis = GetVecAxis();

	float fValueRot = GetValueRot();

	//カメラの情報取得
	CCamera* pCamera = CManager::GetCamera();
	D3DXVECTOR3 rot = pCamera->GetRotasion();

	pCamera->SetFollowing(pos, m_rotDest);

	//左移動
	if (pInputKeyboard->GetPress(DIK_A) == true)
	{
		fValueRot = MAX_ROT;

		//前移動
		if (pInputKeyboard->GetPress(DIK_W) == true)
		{
			m_rotDest.y = rot.y + D3DX_PI * 0.75f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;

			//m_rot.z = 0.19625f;

		}
		//後ろ移動
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{

			m_rotDest.y = rot.y + D3DX_PI * 0.25f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;

		}
		else
		{
			m_rotDest.y = rot.y + D3DX_PI * 0.5f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;

		}
	}
	//右移動
	if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		fValueRot = MAX_ROT;

		//前移動
		if (pInputKeyboard->GetPress(DIK_W) == true)
		{
			m_rotDest.y = rot.y - D3DX_PI * 0.75f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
		}
		//後ろ移動
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{
			m_rotDest.y = rot.y - D3DX_PI * 0.25f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
		}
		else
		{

			m_rotDest.y = rot.y - D3DX_PI * 0.5f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
		}
	}
	//前移動
	if (pInputKeyboard->GetPress(DIK_W) == true)
	{
		fValueRot = MAX_ROT;

		if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
		}
		//前移動
		else if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
		}
		else
		{
			m_rotDest.y = rot.y + D3DX_PI;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
		}
	}
	//後ろ移動
	if (pInputKeyboard->GetPress(DIK_S) == true)
	{
		fValueRot = MAX_ROT;

		if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
		}
		//前移動
		else if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
		}
		else
		{
			m_rotDest.y = rot.y;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_SPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_SPEED;

		}
	}

	if ((pInputKeyboard->GetPress(DIK_W) == false) &&
		(pInputKeyboard->GetPress(DIK_A) == false) &&
		(pInputKeyboard->GetPress(DIK_S) == false) &&
		(pInputKeyboard->GetPress(DIK_D) == false))
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