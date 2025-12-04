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

//============================
// コンストラクタ
//============================
CEnemy::CEnemy(int nPriority) : CObject(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Diff = 0.0f;
	m_bJump = false;
	m_bLeave = true;

	for (int nCnt = 0; nCnt < MAX_EMODEL; nCnt++)
	{
		m_apModel[nCnt] = nullptr;

	}
	m_pMotion = nullptr;
}

//============================
// デストラクタ
//============================
CEnemy::~CEnemy()
{

}

//============================
//  生成処理
//============================
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy* pEnemy = nullptr;
	pEnemy = new CEnemy;

	if (pEnemy != nullptr)
	{
		pEnemy->SetPosition(pos);
		pEnemy->m_rot = rot;
		pEnemy->Init();
		return pEnemy;
	}
	else
	{
		return nullptr;
	}
}

//============================
// 初期化処理
//============================
HRESULT CEnemy::Init(void)
{
	m_pMotion = CMotion::Create("data\\MOTION\\motion_robot.txt", &m_apModel[0]);	//whichMotion.txt || motion2.txt
	m_size = CModel::GetSize();

	return S_OK;
}

//============================
// 終了処理
//============================
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

//============================
// 更新処理
//============================
void CEnemy::Update(void)
{
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


	m_pos += m_move;

	// 移動の制限
	if (m_pos.y > 800.0f || m_pos.x > 2500.0f || m_pos.z > 2500.0f)
	{
		m_pos = m_posOld;
	}
	else if (m_pos.y < -180.0f || m_pos.x < -2500.0f || m_pos.z < -2500.0f)
	{
		m_pos = m_posOld;
	}

	SetPosition(m_pos);
}

//============================
// 描画処理
//============================
void CEnemy::Draw(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DMATERIAL9 matDef; //現在のマテリアル保存用

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//モデルパーツを描画
	for (int nCnt = 0; nCnt < MAX_EMODEL; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}

	//保存していたマテリアルを隠す
	pDevice->SetMaterial(&matDef);

	CDebugProc::Print("EnemyPos : { %.2f,%.2f,%.2f }\n", m_pos.x, m_pos.y, m_pos.z);

}