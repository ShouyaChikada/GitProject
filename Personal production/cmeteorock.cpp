//=================================================
//
// [meteorock.cpp]	隕石(塵)の処理全般
// 
// Author:chikada shouya
//
//=================================================
#include "cmeteorock.h"
#include "player.h"
#include "input.h"
#include "manager.h"
#include "debugproc.h"
#include "particle.h"

//=================================================
// コンストラクタ
//=================================================
CMeteoRock::CMeteoRock()
{
	m_posOld = D3DX_VEC3;
	m_fCountFrame = NULL;
	m_fMaxFrame = NULL;
	m_fDistance = NULL;
	m_fRotValue = NULL;
	m_fDistanceValue = NULL;
	m_fAddValue = NULL;
	m_nCntValueTime = NULL;
	m_fPos = NULL;
	m_fDiffX = NULL;
	m_fDiffZ = NULL;
	m_bDeath = false;
	m_bTimeOut = false;

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_bSign[nCnt] = false;
		m_bRelease[nCnt] = false;
	}
}

//=================================================
// デストラクタ
//=================================================
CMeteoRock::~CMeteoRock()
{
	
}

//=================================================
// 生成
//=================================================
CMeteoRock* CMeteoRock::Create(D3DXVECTOR3 pos)
{
	CMeteoRock* pMeteoRock = nullptr;
	pMeteoRock = new CMeteoRock;

	if (pMeteoRock != nullptr)
	{
		pMeteoRock->SetPosition(pos);
		pMeteoRock->SetIdx("data\\MODEL\\inseki.x");	// inseki.x || earth000.x
		pMeteoRock->SetRotaiton(ROT::ROT_ON1);
		pMeteoRock->Init();

		return pMeteoRock;
	}
	else
	{
		return nullptr;
	}
}

//=================================================
// 初期化
//=================================================
HRESULT CMeteoRock::Init(void)
{
	CRock::Init();

	m_fDistanceValue = 100.0f;
	m_nCntValueTime = 0;
	m_fAddValue = 0.075f;
	m_bSign[0] = false;
	m_bSign[1] = false;
	m_bRelease[0] = false;
	m_bRelease[1] = false;
	m_bTimeOut = false;
	return S_OK;
}

//=================================================
// 破棄
//=================================================
void CMeteoRock::Uninit(void)
{
	CRock::Uninit();
}

//=================================================
// 更新
//=================================================
void CMeteoRock::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 move = GetMove();
	// プレイヤー座標の取得
	D3DXVECTOR3 PlayerPos = CPlayer::GetPos();

	//CParticle::Create(pos, move, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 120);
	
	UpdateObjectPos(pos, move);

	if (m_bSign[0] == false && m_bSign[1] == false)
	{
		move.z -= MAX_SPEED;

		SetPosition(pos);
		SetMove(move);

		m_fDiffX = pos.x - PlayerPos.x;
		m_fDiffZ = pos.z - PlayerPos.z;

		m_fPos = atan2f(m_fDiffX, m_fDiffZ);

		m_fRotValue = m_fPos;

		if (m_fRotValue > D3DX_PI)
		{
			m_fRotValue -= D3DX_PI * 2.0f;
		}
		else if (m_fRotValue < -D3DX_PI)
		{
			m_fRotValue += D3DX_PI * 2.0f;
		}
	}

	if (pos.x >= 1000.0f || pos.x <= -1000.0f ||
		pos.z >= 900.0f || pos.z <= -900.0f)
	{
		m_bDeath = true;
		m_bSign[0] = false;
		m_bSign[1] = false;
	}

	CRock::Update();
}

//=================================================
// 描画
//=================================================
void CMeteoRock::Draw(void)
{
	D3DXVECTOR3 pos = GetPosition();

	CRock::Draw();

	CDebugProc::Print("飛んでいく威力(m_fAddValue) : %.2f\n", m_fAddValue);

	CDebugProc::Print("隕石座標 : { %.2f,%.2f,%.2f }\n", pos.x, pos.y, pos.z);
}

//=================================================
// オブジェクト回転
//=================================================
void CMeteoRock::UpdateObjectPos(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	// プレイヤー周りの円の判定
	bool bCheck0 = CPlayer::GetTamesi0();
	bool bCheck1 = CPlayer::GetTamesi1();
	bool bCheck2 = CPlayer::GetTamesi2();

	// プレイヤー座標の取得
	D3DXVECTOR3 PlayerPos = CPlayer::GetPos();

	D3DXVECTOR3 Rot = GetRot();

	// キーボードポインタ
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	// 距離の計算
	m_fDistance = sqrtf((PlayerPos.x - pos.x) * (PlayerPos.x - pos.x) + (PlayerPos.y - pos.y) * (PlayerPos.y - pos.y) + (PlayerPos.z - pos.z) * (PlayerPos.z - pos.z));

	if (m_bTimeOut == false)
	{
		// 時計回り
		if ((bCheck2 == true && bCheck1 == true) && pInputKeyboard->GetPress(DIK_SPACE) == true)
		{
			m_bSign[0] = true;

			if (m_nCntValueTime < 300)
			{
				m_fAddValue += 0.001f;
			}
			else
			{
				m_bTimeOut = true;
			}

			m_fRotValue += m_fAddValue;

			if (m_fRotValue > D3DX_PI)
			{
				m_fRotValue -= D3DX_PI * 2.0f;
			}
			else if (m_fRotValue < -D3DX_PI)
			{
				m_fRotValue += D3DX_PI * 2.0f;
			}

			pos.x = PlayerPos.x + sinf(m_fRotValue) * m_fDistanceValue;
			pos.z = PlayerPos.z + cosf(m_fRotValue) * m_fDistanceValue;

			CRock::SetPosition(pos);
			CRock::SetMove(move);

			if (m_fDistanceValue <= 300.0f)
			{
				m_fDistanceValue += 0.1f;
			}
			m_nCntValueTime++;
		}
		else
		{
			bCheck1 = false;
			CPlayer::SetTamesi1(bCheck1);
		}

		// 反時計回り
		if ((bCheck2 == true && bCheck0 == true) && pInputKeyboard->GetPress(DIK_SPACE) == true)
		{

			m_bSign[1] = true;

			if (m_nCntValueTime < 300)
			{
				m_fAddValue += 0.001f;
			}
			else
			{
				m_bTimeOut = true;
			}

			m_fRotValue -= m_fAddValue;

			if (m_fRotValue > D3DX_PI)
			{
				m_fRotValue -= D3DX_PI * 2.0f;
			}
			else if (m_fRotValue < -D3DX_PI)
			{
				m_fRotValue += D3DX_PI * 2.0f;
			}

			pos.x = PlayerPos.x + sinf(m_fRotValue) * m_fDistanceValue;
			pos.z = PlayerPos.z + cosf(m_fRotValue) * m_fDistanceValue;

			CRock::SetPosition(pos);
			CRock::SetMove(move);

			if (m_fDistanceValue <= 300.0f)
			{
				m_fDistanceValue += 0.1f;
			}

			m_nCntValueTime++;
		}
		else
		{
			bCheck0 = false;
			CPlayer::SetTamesi0(bCheck0);
		}

	}

	if (m_bSign[0] == true && (pInputKeyboard->GetRelease(DIK_SPACE) == true || m_bTimeOut == true))
	{
		m_bRelease[0] = true;
	}
	if (m_bSign[1] == true && (pInputKeyboard->GetRelease(DIK_SPACE) == true || m_bTimeOut == true))
	{
		m_bRelease[1] = true;
	}

	if (m_bRelease[0] == true)
	{
		move.x = sinf(m_fRotValue + (D3DX_PI * 0.5f)) * (MAX_SPEED * (m_fAddValue * 15.0f));
		move.z = cosf(m_fRotValue + (D3DX_PI * 0.5f)) * (MAX_SPEED * (m_fAddValue * 15.0f));

		CRock::SetPosition(pos);
		CRock::SetMove(move);
	}
	if (m_bRelease[1] == true)
	{
		move.x = sinf(m_fRotValue - (D3DX_PI * 0.5f)) * (MAX_SPEED * (m_fAddValue * 15.0f));
		move.z = cosf(m_fRotValue - (D3DX_PI * 0.5f)) * (MAX_SPEED * (m_fAddValue * 15.0f));

		CRock::SetPosition(pos);
		CRock::SetMove(move);
	}
}

//=================================================
// 飛んでくる隕石の処理(線形補間)
//=================================================
void CMeteoRock::MoveSphere(void)
{
	D3DXVECTOR3 startPos = D3DX_VEC3;
	D3DXVECTOR3 endPos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 currentPos = D3DX_VEC3;
	float s = 0.5f; // 中間点

	// 線形補間を実行
	D3DXVec3Lerp(&currentPos, &startPos, &endPos, s);

	pos = currentPos;
}

//=================================================
// 追従処理
//=================================================
void CMeteoRock::FollowingMove(void)
{
	//D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//D3DXVECTOR3 vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//D3DXVECTOR3 VecAxis = GetVecAxis();
	//float fValueRot = GetValueRot();

	////半径の算出変数
	//float PRadiusPos = 500.0f;
	//float PradPos = 30.0f;

	//float ERadiusPos = 500.0f;
	//float ERadPos = 5.0f;

	////プレイヤーの位置の取得
	//D3DXVECTOR3 PlayerPos = CPlayer::GetPos();
	//D3DXVECTOR3 PlayerRot = CPlayer::GetRot();

	////弾とプレイヤーの距離の差
	//D3DXVECTOR3 diff = PlayerPos - m_pos;
	//D3DXVECTOR3 diff1 = PlayerPos - m_pos;

	////角度
	//float fAngle = atan2f(diff.x, diff.z);
	//float fAngle1 = atan2f(diff1.x, diff1.z);

	//m_nMoveTime--;

	//// ゼロ以下になったら
	//if (m_nMoveTime <= 0)
	//{
	//	if (m_fSpeed <= 12.5f)
	//	{
	//		//速度計算
	//		m_fSpeed += 0.075f;
	//	}
	//}

	////範囲計算
	//float fDisX = PlayerPos.x - m_pos.x;
	//float fDisY = PlayerPos.y - m_pos.y;
	//float fDisZ = PlayerPos.z - m_pos.z;

	////二つの半径を求める
	//float fRadX = PRadiusPos + ERadiusPos;
	//float fRadX1 = PradPos + ERadPos;

	////敵の角度
	//m_rot.y = fAngle;

	//
	//if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
	//{
	//	if (m_bCheck != true)
	//	{
	//		fValueRot += 0.0015f;
	//	}

	//	//移動量を更新
	//	m_move.x = sinf(m_rot.y) * m_fSpeed;	//敵の見てる方向
	//	m_move.z = cosf(m_rot.y) * m_fSpeed;

	//	if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX1 * fRadX1))
	//	{
	//		//m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//		m_bCheck = true;

	//		//移動量を更新
	//		m_move.x = sinf(PlayerRot.y + D3DX_PI) * 200.0f;	//敵の見てる方向
	//		m_move.z = cosf(PlayerRot.y + D3DX_PI) * 200.0f;
	//	}
	//}
	//
	//// 進行ベクトルの正規化
	//D3DXVec3Normalize(&move, &m_move);

	//// 外積
	//D3DXVec3Cross(&VecAxis, &vecU, &move);

	//// 回転量のセット
	//SetValueRot(fValueRot);

	//// 回転軸のセット
	//SetVecAxis(VecAxis);
}
