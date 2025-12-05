//=================================================
//
// [enemy.cpp]
// Author:chikada shouya
//
//=================================================
#include "enemy.h"
#include "input.h"
#include "manager.h"
#include "camera.h"
#include "debugproc.h"
#include "bullet.h"

//=================================================
// コンストラクタ
//=================================================
CEnemy::CEnemy(int nPriority) : CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Diff = NULL;
	m_nCreate = NULL;

	m_bJump = false;
	m_bLeave = true;

	for (int nCnt = 0; nCnt < MAX_EMODEL; nCnt++)
	{
		m_apModel[nCnt] = nullptr;
	}
	m_pMotion = nullptr;
}

//=================================================
// デストラクタ
//=================================================
CEnemy::~CEnemy()
{

}

//=================================================
//  生成処理
//=================================================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy* pEnemy = nullptr;
	pEnemy = new CEnemy;

	if (pEnemy != nullptr)
	{
		pEnemy->m_pos = pos;
		pEnemy->m_rot = rot;
		pEnemy->Init();
		return pEnemy;
	}
	else
	{
		return nullptr;
	}
}

//=================================================
// 初期化処理
//=================================================
HRESULT CEnemy::Init(void)
{
	m_pMotion = CMotion::Create("data\\MOTION\\motion_robot.txt", &m_apModel[0], CModel::QUAT_NONE);	//whichMotion.txt || motion2.txt
	m_size = CModel::GetSize();

	return S_OK;
}

//=================================================
// 終了処理
//=================================================
void CEnemy::Uninit(void)
{
	// モデルの破棄
	for (int nCnt = 0; nCnt < MAX_EMODEL; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{
			m_apModel[nCnt]->Uninit();
			delete m_apModel[nCnt];
			m_apModel[nCnt] = nullptr;
		}
	}

	// モーションの破棄
	if (m_pMotion != nullptr)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	m_bLeave = false;

	CObject::Release();
}

//=================================================
// 更新処理
//=================================================
void CEnemy::Update(void)
{
	// モーションの更新
	m_pMotion->Update(&m_apModel[0]);

	m_nCreate++;

	if (m_nCreate >= 180)
	{
		CBullet::Create(m_pos, D3DXVECTOR3(0.0f,0.0f,-3.0f), 30.0f, "data\\TEXTURE\\bullet000.png");
		m_nCreate = 0;
	}

	// 移動
	//MoveInput();

	//角度の正規化
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = m_rot.y + D3DX_PI;
		m_rot.y = D3DX_PI + m_rot.y;
	}
	else if (m_rot.y > D3DX_PI)
	{
		m_rot.y = m_rot.y - D3DX_PI;
		m_rot.y = -D3DX_PI - m_rot.y;

	}

	//角度の調整
	m_Diff = m_rotDest.y - m_rot.y;

	if (m_Diff < -D3DX_PI)
	{
		m_Diff = m_Diff + (D3DX_PI * 2);
	}
	else if (m_Diff > D3DX_PI)
	{
		m_Diff = m_Diff - (D3DX_PI * 2);
	}

	//プレイヤーの向き
	m_rot.y += m_Diff * 0.25f;

	//移動量を更新
	m_move.x += (0.0f - m_move.x) * 0.5f;
	m_move.z += (0.0f - m_move.z) * 0.5f;

	//前回の位置を保存	位置更新の上で書く
	m_posOld = m_pos;

	// 位置を移動
	m_pos += m_move;

	// 位置の設定
	SetPosition(m_pos);
}

//=================================================
// 描画処理
//=================================================
void CEnemy::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DMATERIAL9 matDef; //現在のマテリアル保存用

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//モデルパーツを描画
	for (int nCnt = 0; nCnt < MAX_EMODEL; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}

	// 保存していたマテリアルを隠す
	pDevice->SetMaterial(&matDef);

	// デバッグフォントの表示
	CDebugProc::Print("EnemyPos : { %.2f,%.2f,%.2f }\n", m_pos.x, m_pos.y, m_pos.z);

}

//=================================================
// 移動用関数
//=================================================
void CEnemy::MoveInput(void)
{
	// キーボード
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	//カメラの情報取得
	CCamera* pCamera = CManager::GetCamera();
	D3DXVECTOR3 rot = pCamera->GetRotasion();

	pCamera->SetFollowing(m_pos, m_rotDest);


	//左移動
	if (pInputKeyboard->GetPress(DIK_A) == true)
	{
		// 移動のモーション
		m_pMotion->Set(CMotion::MOTIONTYPE_MOVE);

		//前移動
		if (pInputKeyboard->GetPress(DIK_W) == true)
		{
			m_rotDest.y = rot.y + D3DX_PI * 0.75f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;

			//m_rot.z = 0.19625f;

		}
		//後ろ移動
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{

			m_rotDest.y = rot.y + D3DX_PI * 0.25f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;

		}
		else
		{

			m_rotDest.y = rot.y + D3DX_PI * 0.5f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;

		}
	}
	//右移動
	if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		// 移動のモーション
		m_pMotion->Set(CMotion::MOTIONTYPE_MOVE);
		//前移動
		if (pInputKeyboard->GetPress(DIK_W) == true)
		{
			m_rotDest.y = rot.y - D3DX_PI * 0.75f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;
		}
		//後ろ移動
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{
			m_rotDest.y = rot.y - D3DX_PI * 0.25f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;
		}
		else
		{

			m_rotDest.y = rot.y - D3DX_PI * 0.5f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;
		}
	}
	//前移動
	if (pInputKeyboard->GetPress(DIK_W) == true)
	{
		// 移動のモーション
		m_pMotion->Set(CMotion::MOTIONTYPE_MOVE);

		if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;
		}
		//前移動
		else if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;
		}
		else
		{
			m_rotDest.y = rot.y + D3DX_PI;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;
		}
	}
	//後ろ移動
	if (pInputKeyboard->GetPress(DIK_S) == true)
	{
		// 移動のモーション
		m_pMotion->Set(CMotion::MOTIONTYPE_MOVE);

		if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;
		}
		//前移動
		else if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;
		}
		else
		{
			m_rotDest.y = rot.y;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * MAX_PSPEED;

		}
	}

}