//=================================================
//
//	camera.cpp
// 
// Author:近田 尚也
//
//=================================================
#include "camera.h"
#include "input.h"
#include "manager.h"
#include "debugproc.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "pausemanager.h"
#include "tutorial.h"

#define MAX_ANGLE (3.0f)

CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f,0.0f,0.0f);		
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR2(0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_fDistance = NULL;
	m_bFlattery = false;
	m_bTPS = NULL;
}
CCamera::~CCamera()
{

}

//================================
//初期化処理
//================================
HRESULT CCamera::Init(void)
{
	m_bFlattery = false;
	m_bTPS = true;
	//視点・注視点・上方向を設定する
#if 0
	m_posV = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, -300.0f);
#else
	//視点
	m_posV = D3DXVECTOR3(0.0f, 330.0f, -60.0f);
#endif
	//注視点
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//上方向
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_rot = D3DXVECTOR3(D3DX_PI * 0.6f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//視点から注視点までの距離
	m_fDistance = sqrtf((m_posV.x - m_posR.x) * (m_posV.x - m_posR.x) + (m_posV.y - m_posR.y) * (m_posV.y - m_posR.y) + (m_posV.z - m_posR.z) * (m_posV.z - m_posR.z));

	//m_viewport.X = 0.0f;
	//m_viewport.Y = 0.0f;
	//m_viewport.Width = 640.0f;
	//m_viewport.Height = 720.0f;

	return S_OK;
}
//================================
//終了処理
//================================
void CCamera::Uninit(void)
{
	
}
//================================
//更新処理
//================================
void CCamera::Update(void)
{
//#ifndef _DEBUG
//#endif
	//	キーボード
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	// マウス
	CInputMouse* pInputMouse = CManager::GetMouse();
	
	// ゲームの終了の判定
	bool bGame = CGame::GetCheck();

	bool bTutorial = CTutorial::GetCheck();

	bool bCheck = CPauseManager::GetCheck();
	static int nCnt = 0;

	if (bTutorial == false)
	{
		if (bGame == true)
		{
			nCnt++;
			if (nCnt >= 90)
			{
				m_bFlattery = false;
				//視点
				m_posV = D3DXVECTOR3(0.0f, 330.0f, -60.0f);
				//注視点
				m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				//上方向
				m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				m_rot = D3DXVECTOR3(D3DX_PI * 0.6f, 0.0f, 0.0f);

				nCnt = 0;
			}
		}
	}

	if (bTutorial == false)
	{
		if (bCheck == true)
		{
			nCnt++;
			if (nCnt >= 30)
			{
				m_bFlattery = false;
				//視点
				m_posV = D3DXVECTOR3(0.0f, 330.0f, -110.0f);
				//注視点
				m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				//上方向
				m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				m_rot = D3DXVECTOR3(D3DX_PI * 0.6f, 0.0f, 0.0f);

				nCnt = 0;
			}
		}
	}

#if 0
	if (m_bFlattery == false)
	{
		if (pInputKeyboard->GetTrigger(DIK_F8) == true)
		{
			m_bFlattery = true;

		}
	}
	else if (m_bFlattery == true)
	{
		if (pInputKeyboard->GetTrigger(DIK_F8) == true)
		{
			m_bFlattery = false;
		}
	}
	
	// カメラのマウス操作
	if (m_bFlattery == false)
	{
		MouseView(pInputMouse);

		// 正規化
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= D3DX_PI * 2.0f;
		}
		else if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2.0f;
		}
		if (m_rot.x > D3DX_PI)
		{
			m_rot.x -= D3DX_PI * 2.0f;
		}
		else if (m_rot.x < -D3DX_PI)
		{
			m_rot.x += D3DX_PI * 2.0f;
		}

	}

	// プレイヤーの追従
	if (m_bFlattery == true)
	{

		//視点の旋回(左)
		if (pInputKeyboard->GetPress(DIK_Q) == true)
		{
			m_rot.y -= 0.05f;
			//角度の正規化
			// 正規化
			if (m_rot.y > D3DX_PI)
			{
				m_rot.y -= D3DX_PI * 2.0f;
			}
			else if (m_rot.y < -D3DX_PI)
			{
				m_rot.y += D3DX_PI * 2.0f;
			}
		}
		//視点の旋回(右)
		if (pInputKeyboard->GetPress(DIK_E) == true)
		{
			m_rot.y += 0.05f;
			// 正規化
			if (m_rot.y > D3DX_PI)
			{
				m_rot.y -= D3DX_PI * 2.0f;
			}
			else if (m_rot.y < -D3DX_PI)
			{
				m_rot.y += D3DX_PI * 2.0f;
			}
		}	

		m_posV.x = m_posR.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		m_posV.y = m_posR.y - cosf(m_rot.x) * m_fDistance;
		m_posV.z = m_posR.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;

		m_posR.x += (m_posRDest.x - m_posR.x) * 0.2f;
		m_posR.y += (m_posRDest.y - m_posR.y) * 0.2f;
		m_posR.z += (m_posRDest.z - m_posR.z) * 0.2f;

		m_posV.x += (m_posVDest.x - m_posV.x) * 0.2f;
		m_posV.z += (m_posVDest.z - m_posV.z) * 0.2f;

		
	}
#else
	//視点の旋回(左)
	if (pInputKeyboard->GetPress(DIK_Q) == true)
	{
		m_rot.y -= 0.05f;
		//角度の正規化
		// 正規化
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= D3DX_PI * 2.0f;
		}
		else if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2.0f;
		}
	}
	//視点の旋回(右)
	if (pInputKeyboard->GetPress(DIK_E) == true)
	{
		m_rot.y += 0.05f;
		// 正規化
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= D3DX_PI * 2.0f;
		}
		else if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2.0f;
		}
	}

	m_posV.x = m_posR.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
	m_posV.y = m_posR.y - cosf(m_rot.x) * m_fDistance;
	m_posV.z = m_posR.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;

	m_posR.x += (m_posRDest.x - m_posR.x) * 0.2f;
	m_posR.y += (m_posRDest.y - m_posR.y) * 0.2f;
	m_posR.z += (m_posRDest.z - m_posR.z) * 0.2f;

	m_posV.x += (m_posVDest.x - m_posV.x) * 0.2f;
	m_posV.z += (m_posVDest.z - m_posV.z) * 0.2f;

#endif

}
//================================
//設定処理
//================================
void CCamera::SetCamera(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//ビューマトリックスの設定
	pD3DDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		5000.0f);

	//プロジェクションマトリックスの設定
	pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	CDebugProc::Print("カメラ視点座標 : {(注視点) x:%.2f,y:%.2f,z:%.2f }{(視点)  x:%.2f,y:%.2f,z:%.2f }\n", m_posR.x, m_posR.y, m_posR.z, m_posV.x, m_posV.y, m_posV.z);

	if (m_bFlattery == true)
	{
		CDebugProc::Print("プレイヤーの追従 [ F8 ] : オン\n");
	}
	else if (m_bFlattery == false)
	{
		CDebugProc::Print("プレイヤーの追従 [ F8 ] : オフ\n");
	}


}

D3DXVECTOR3 CCamera::GetRotasion(void)
{
	return m_rot;
}

D3DXVECTOR3 CCamera::GetPosV(void)
{
	return m_posV;
}

D3DXVECTOR3 CCamera::GetPosR(void)
{
	return m_posR;
}

D3DXVECTOR3 CCamera::GetVecU(void)
{
	return m_vecU;
}

void CCamera::MouseView(CInputMouse* pMouse)
{
	// 右クリック
	if (pMouse->OnDownR(CInputMouse::MOUSE_R))
	{
		// マウスの移動量取得
		D3DXVECTOR2 Move = pMouse->GetVelocity();
		D3DXVECTOR2 MoveOld = pMouse->GetVelocityOld();

		// 現在の角度を計算
		D3DXVECTOR2 fAngle = Move - MoveOld;

		// 回転量を更新
		m_rot.y += fAngle.x * 0.005f;
		m_rot.x += fAngle.y * 0.005f;

		// 回転量を制限
		if (m_rot.x > MAX_ANGLE)
		{
			m_rot.x -= fAngle.x * 0.005f;
		}
		else if (m_rot.x < 0.1f)
		{
			m_rot.x += fAngle.x * 0.005f;
		}

		// カメラ座標を更新
		m_posR.x = m_posV.x + sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		m_posR.y = m_posV.y + cosf(m_rot.x) * m_fDistance;
		m_posR.z = m_posV.z + sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
	}
	// 左クリック
	else if (pMouse->OnDownL(CInputMouse::MOUSE_L))
	{
		D3DXVECTOR2 Move = pMouse->GetVelocity();
		D3DXVECTOR2 MoveOld = pMouse->GetVelocityOld();

		D3DXVECTOR2 fAngle = Move - MoveOld;

		// 回転量を更新
		m_rot.y += fAngle.x * 0.005f;
		m_rot.x += fAngle.y * 0.005f;

		// 回転量を制限
		if (m_rot.x > MAX_ANGLE)
		{
			m_rot.x -= fAngle.x * 0.005f;
		}
		else if (m_rot.x < 0.1f)
		{
			m_rot.x += fAngle.x * 0.005f;
		}

		// カメラの視点の情報
		m_posV.x = m_posR.x - sinf(m_rot.x) * sinf(m_rot.y) * m_fDistance;
		m_posV.y = m_posR.y - cosf(m_rot.x) * m_fDistance;
		m_posV.z = m_posR.z - sinf(m_rot.x) * cosf(m_rot.y) * m_fDistance;
	}
	
	// 正規化
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	if (m_rot.x > D3DX_PI)
	{
		m_rot.x -= D3DX_PI * 2.0f;
	}
	else if (m_rot.x < -D3DX_PI)
	{
		m_rot.x += D3DX_PI * 2.0f;
	}
}

// 追従の設定
void CCamera::SetFollowing(D3DXVECTOR3 pos, D3DXVECTOR3 rotDest)
{
	//注視点の目的
	m_posRDest.x = pos.x + sinf(rotDest.y) * MAX_SPEED;
	m_posRDest.y = pos.y + cosf(rotDest.y) * MAX_SPEED;
	m_posRDest.z = pos.z + cosf(rotDest.y) * MAX_SPEED;

	//視点の目的
	m_posVDest.x = pos.x - sinf(m_rot.y) * m_fDistance;
	m_posVDest.y = pos.y - cosf(m_rot.y) * m_fDistance;
	m_posVDest.z = pos.z - cosf(m_rot.y) * m_fDistance;
}