//=================================================
//
//	player.cpp
// 
//	Author:近田尚也
//
//=================================================
#include "player.h"
#include "input.h"
#include "manager.h"
#include "camera.h"
#include "debugproc.h"
#include "blockmanager.h"
#include "game.h"
#include "gimmickmanager.h"

// 静的メンバ変数
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//============================
// コンストラクタ
//============================
CPlayer::CPlayer(int nPriority) : CObject(nPriority)
{	
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < MAX_PMODEL; nCnt++)
	{
		m_apModel[nCnt] = nullptr;

	}
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_SetPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Diff = 0.0f;
	m_bJump = false;
	m_pMotion = NULL;
	m_bLeave = true;
	m_pShadowS = nullptr;
	m_pParticle = nullptr;
}

//CPlayer::CPlayer(int nPriority):CObject2D((int)nPriority)
//{
//	nPriority = 5;
//}

//============================
// デストラクタ
//============================
CPlayer::~CPlayer()
{

}

//============================
//  生成処理
//============================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer* pPlayer = nullptr;
	pPlayer = new CPlayer;

	if(pPlayer != nullptr)
	{
		pPlayer->m_pos = pos;
		pPlayer->m_rot = rot;
		pPlayer->Init();
		return pPlayer;
	}
	else
	{
		return nullptr;
	}
}

//============================
// 初期化処理
//============================
HRESULT CPlayer::Init(void)
{

	m_pShadowS = CShadowS::Create("data\\MODEL\\bou3.x",m_pos, m_rot);
	m_pMotion = CMotion::Create("data\\whichMotion.txt",&m_apModel[0]);	//whichMotion.txt || motion2.txt
	m_size = CModel::GetSize();

	return S_OK;
}

//============================
// 終了処理
//============================
void CPlayer::Uninit(void)
{
	m_bLeave = false;

	// モデルの破棄
	for (int nCnt = 0; nCnt < MAX_PMODEL; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->Uninit();
			delete m_apModel[nCnt];
			m_apModel[nCnt] = NULL;
		}
	}
	
	// モーションの破棄
	if (m_pMotion != NULL)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = NULL;
	}

	CObject::Release();
}

//============================
// 更新処理
//============================
void CPlayer::Update(void)
{
	m_pMotion->Update(&m_apModel[0]);

	//移動とモーションのセット
	SetInput();


	//fCirc = 2.0f * D3DX_PI * 5.0f;

	//m_move.y = (fValueRot / (2 * D3DX_PI)) * fCirc;
	//m_move.z = (fValueRot / (2 * D3DX_PI)) * fCirc;

	//m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

	CBlock** pBlock = CBlockManager::GetBlock();
	CGimmick** pGimmick = CGimmickManager::GetGimmick();

	m_pos += m_move;

	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		if (pBlock[nCnt] != nullptr)
		{
			//ブロックとの当たり判定
			if (pBlock[nCnt]->Collision(&m_pos, &m_posOld, &m_move, &m_size) == true)
			{
				m_move.y = 0.0f;
			}

		}
	}

	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		if (pGimmick[nCnt] != nullptr)
		{
			if (pGimmick[nCnt]->Collision(&m_pos, &m_posOld, &m_move, &m_size) == true)
			{
				m_move.y = 0.0f;
			}
		}
	}

	//m_move.y -= 0.4f;	//重力加算

	////重力
	//if (m_pos.y < -600.0f)
	//{
	//	m_pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	//	m_move.y = 0.0f;
	//	m_bJump = false;
	//}

	// 移動の制限
	if (m_pos.y > 800.0f || m_pos.x > 2500.0f || m_pos.z > 2500.0f)
	{
		m_pos = m_posOld;
	}
	else if (m_pos.y < -180.0f || m_pos.x < -2500.0f || m_pos.z < -2500.0f)
	{
		m_pos = m_posOld;
	}

	m_pShadowS->SetShadow(m_pos, m_rot);

	SetPosition(m_pos);
}

//============================
// 描画処理
//============================
void CPlayer::Draw(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DMATERIAL9 matDef; //現在のマテリアル保存用

	//D3DXMATRIX mtxRot;		// 回転マトリックス(保存用)
	D3DXQUATERNION quat;	// クォータニオン
	D3DXVECTOR3 vecAxis = m_rot;	// 回転軸
	float fValueRot = 0.0f;	// 回転角(回転量)
	float fCirc = 0.0f;		//円周(計算用)

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転軸のおける指定の回転角からクォータニオンを作成
	D3DXQuaternionRotationAxis(&quat, &vecAxis, fValueRot);
	// クォータニオンから回転マトリックスの作成
	D3DXMatrixRotationQuaternion(&mtxRot, &quat);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pD3DDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pD3DDevice->GetMaterial(&matDef);

	//モデルパーツを描画
	for (int nCnt = 0; nCnt < MAX_PMODEL; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}

	//保存していたマテリアルを隠す
	pD3DDevice->SetMaterial(&matDef);

	CDebugProc::Print("プレイヤー座標 : { %.2f,%.2f,%.2f }\n", m_pos.x, m_pos.y, m_pos.z);

}


//============================
// 移動処理
//============================
void CPlayer::SetInput(void)
{
	bool bUse = CGimmickManager::GetPush();
	bool bCheck = CGimmickManager::GetbCheck();

	// キーボード
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	//カメラの情報取得
	CCamera* pCamera = CManager::GetCamera();
	D3DXVECTOR3 rot = pCamera->GetRotasion();

	pCamera->SetFollowing(m_pos, m_rotDest);

	//if (pInputKeyboard->GetPress(DIK_F) == true)
	//{
	//	m_pParticle = CParticle::Create(D3DXVECTOR3(m_pos), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 30);
	//}


	if (bUse == false || bCheck == true)
	{
		//左移動
		if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			// 移動のモーション
			m_pMotion->Set(CMotion::MOTIONTYPE_MOVE);

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
			// 移動のモーション
			m_pMotion->Set(CMotion::MOTIONTYPE_MOVE);
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
			// 移動のモーション
			m_pMotion->Set(CMotion::MOTIONTYPE_MOVE);

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
			// 移動のモーション
			m_pMotion->Set(CMotion::MOTIONTYPE_MOVE);

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

		// 上昇
		if (pInputKeyboard->GetPress(DIK_UP) == true)
		{
			m_move.y = 2.5f;
		}

		// 降下
		else if (pInputKeyboard->GetPress(DIK_DOWN) == true)
		{
			m_move.y = -2.5f;
		}
		else
		{
			m_move.y = 0.0f;
		}

		// 動いてないときはニュートラルに
		if (pInputKeyboard->GetPress(DIK_W) == false &&
			pInputKeyboard->GetPress(DIK_S) == false &&
			pInputKeyboard->GetPress(DIK_A) == false &&
			pInputKeyboard->GetPress(DIK_D) == false &&
			m_bJump == false)
		{
			m_pMotion->Set(CMotion::MOTIONTYPE_NEUTRAL);
		}
	}
}

// 位置の設定
void CPlayer::SetPosition(D3DXVECTOR3 pos)
{
	m_SetPosition = pos;
}

// 位置を取得
D3DXVECTOR3 CPlayer::GetPosition(void)
{
	return m_SetPosition;
}

D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}

// 移動量を取得
D3DXVECTOR3 CPlayer::GetMove(void)
{
	return m_move;
}

// 前回の位置を取得
D3DXVECTOR3 CPlayer::GetPosOld(void)
{	
	return m_posOld;
}

// サイズを取得
D3DXVECTOR3 CPlayer::GetSize(void)
{
	return m_size;
}
// 目的の向きの取得
D3DXVECTOR3 CPlayer::GetRotDest(void)
{
	return m_rotDest;
}