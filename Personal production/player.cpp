//=================================================
//
// [player.cpp]
// Author:chikada shouya
//
//=================================================
#include "player.h"
#include "input.h"
#include "manager.h"
#include "camera.h"
#include "debugproc.h"
#include "blockmanager.h"
#include "bullet.h"
#include "rockmanager.h"

//=================================================
// 静的メンバ変数
//=================================================
D3DXVECTOR3 CPlayer::m_GetPos = {};
D3DXVECTOR3 CPlayer::m_GetRot = {};
D3DXVECTOR3 CPlayer::m_GetRotDest = {};
bool CPlayer::m_bTamesi0 = false;
bool CPlayer::m_bTamesi1 = false;
bool CPlayer::m_bTamesi2 = false;

//=================================================
// コンストラクタ
//=================================================
CPlayer::CPlayer(int nPriority) : CObject(nPriority)
{
	for (int nCnt = 0; nCnt < MAX_PMODEL; nCnt++)
	{
		m_apModel[nCnt] = nullptr;
	}
	m_pMotion = nullptr;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_GetRotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Diff = NULL;;
	m_fAddMove = NULL;
	m_fAddLR = NULL;
	m_fAddUD = NULL;

	m_bLeave = true;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
}

//=================================================
// デストラクタ
//=================================================
CPlayer::~CPlayer()
{

}

//=================================================
//  生成処理
//=================================================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer* pPlayer = nullptr;
	pPlayer = new CPlayer;

	if (pPlayer != nullptr)
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

//=================================================
// 初期化処理
//=================================================
HRESULT CPlayer::Init(void)
{

	m_GetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pMotion = CMotion::Create("data\\MOTION\\Human.txt", &m_apModel[0], CModel::QUAT_NONE);	//whichMotion.txt || motion2.txt
	m_size = CModel::GetSize();

	return S_OK;
}

//=================================================
// 終了処理
//=================================================
void CPlayer::Uninit(void)
{
	m_bLeave = false;

	// モデルの破棄
	for (int nCnt = 0; nCnt < MAX_PMODEL; nCnt++)
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

	CObject::Release();
}

//=================================================
// 更新処理
//=================================================
void CPlayer::Update(void)
{
	// モーションの更新
	m_pMotion->Update(&m_apModel[0]);

	//移動とモーションのセット
	MoveInput();
	
	CollisionBullet();

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

	// 左右
	if (m_rotDest.y >= -1.0f && m_rotDest.y <= 1.0f)
	{
		m_fAddLR = 50.0f;
		m_fAddUD = 0.0f;
	}
	else if (m_rotDest.y >= 3.13f && m_rotDest.y <= 3.15f)
	{
		m_fAddLR = -50.0f;
		m_fAddUD = 0.0f;
	}
	else if ((m_rotDest.y >= 1.56f && m_rotDest.y <= 1.58f))
	{
		m_fAddLR = 0.0f;
		m_fAddUD = -50.0f;
	}
	else if ((m_rotDest.y <= -1.56f && m_rotDest.y >= -1.58f))
	{
		m_fAddLR = 0.0f;
		m_fAddUD = 50.0f;
	}

	// 判定(試作品)
	VectorJudgeL();
	VectorJudgeR();
	VectorJudge();

	//プレイヤーの向き
	m_rot.y += m_Diff * 0.25f;

	m_GetRot = m_rot;

	//移動量を更新
	m_move.x += (0.0f - m_move.x) * 0.09f;
	m_move.z += (0.0f - m_move.z) * 0.09f;

	//前回の位置を保存	位置更新の上で書く
	m_posOld = m_pos;

	// 位置を更新
	m_pos += m_move;

	// ブロックと岩のポインタ
	CBlock** pBlock = CBlockManager::GetBlock();
	CMeteoRock** pRock = CRockManager::GetRock();
	CMeteoPillar** pPillar = CRockManager::GetPillar();

	// 当たり判定
	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		if (pBlock[nCnt] != nullptr)
		{
			//ブロックとの当たり判定
			pBlock[nCnt]->Collision(&m_pos, &m_posOld, &m_move, &m_size);
		}
	}

	for (int nCnt = 0; nCnt < MAX_ROCK; nCnt++)
	{
		if (pRock[nCnt] != nullptr)
		{
			//ロックとの当たり判定
			pRock[nCnt]->Collision(&m_pos, &m_posOld, &m_move, &m_size);
		}
		if (pPillar[nCnt] != nullptr)
		{
			//ロックとの当たり判定
 			pPillar[nCnt]->Collision(&m_pos, &m_posOld, &m_move, &m_size);

		}
	}

	// 取得関数に保存
	m_GetPos = m_pos;
	m_GetRotDest = m_rotDest;

	// 位置の設定
	SetPosition(m_pos);
}

//=================================================
// 描画処理
//=================================================
void CPlayer::Draw(void)
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
	for (int nCnt = 0; nCnt < MAX_PMODEL; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}

	// 保存していたマテリアルを隠す
	pDevice->SetMaterial(&matDef);

	// デバッグフォントの表示
	CDebugProc::Print("プレイヤー座標 : { %.2f,%.2f,%.2f }\n", m_pos.x, m_pos.y, m_pos.z);

	if (m_bTamesi0 == true || m_bTamesi1 == true)
	{
		CDebugProc::Print("判定に入っている\n");
	}
	else if (m_bTamesi0 == false || m_bTamesi1 == false)
	{
		CDebugProc::Print("判定に入っていない\n");
	}

	if (m_bTamesi2 == true)
	{
		CDebugProc::Print("全体判定に入っている\n");
	}
	else
	{
		CDebugProc::Print("全体判定に入っていない\n");
	}

	CDebugProc::Print("RotDest :{ %.2f,%.2f,%.2f }\n", m_rotDest.x, m_rotDest.y, m_rotDest.z);

}

//=================================================
// 移動処理
//=================================================
void CPlayer::MoveInput(void)
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
		if (m_fAddMove <= 10.0f)
		{
			m_fAddMove += 0.1f;
		}

		// 移動のモーション
		m_pMotion->Set(CMotion::MOTIONTYPE_MOVE);

		//前移動
		if (pInputKeyboard->GetPress(DIK_W) == true)
		{
			m_rotDest.y = rot.y + D3DX_PI * 0.75f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * m_fAddMove;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * m_fAddMove;

			//m_rot.z = 0.19625f;

		}
		//後ろ移動
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{

			m_rotDest.y = rot.y + D3DX_PI * 0.25f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * m_fAddMove;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * m_fAddMove;

		}
		else
		{
			m_rotDest.y = rot.y + D3DX_PI * 0.5f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * m_fAddMove;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * m_fAddMove;

		}
	}
	//右移動
	if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		if (m_fAddMove <= 10.0f)
		{
			m_fAddMove += 0.1f;
		}

		// 移動のモーション
		m_pMotion->Set(CMotion::MOTIONTYPE_MOVE);
		//前移動
		if (pInputKeyboard->GetPress(DIK_W) == true)
		{
			m_rotDest.y = rot.y - D3DX_PI * 0.75f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * m_fAddMove;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * m_fAddMove;
		}
		//後ろ移動
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{
			m_rotDest.y = rot.y - D3DX_PI * 0.25f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * m_fAddMove;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * m_fAddMove;
		}
		else
		{
			m_rotDest.y = rot.y - D3DX_PI * 0.5f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * m_fAddMove;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * m_fAddMove;
		}
	}
	//前移動
	if (pInputKeyboard->GetPress(DIK_W) == true)
	{

		if (m_fAddMove <= 10.0f)
		{
			m_fAddMove += 0.1f;
		}

		// 移動のモーション
		m_pMotion->Set(CMotion::MOTIONTYPE_MOVE);

		if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			m_rotDest.y = rot.y - D3DX_PI * 0.75f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * m_fAddMove;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * m_fAddMove;
		}
		//前移動
		else if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			m_rotDest.y = rot.y + D3DX_PI * 0.75f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * m_fAddMove;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * m_fAddMove;
		}
		else
		{
			m_rotDest.y = rot.y + D3DX_PI;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * m_fAddMove;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * m_fAddMove;
		}
	}
	//後ろ移動
	if (pInputKeyboard->GetPress(DIK_S) == true)
	{
		if (m_fAddMove <= 10.0f)
		{
			m_fAddMove += 0.1f;
		}

		// 移動のモーション
		m_pMotion->Set(CMotion::MOTIONTYPE_MOVE);

		if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			m_rotDest.y = rot.y - D3DX_PI * 0.25f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * m_fAddMove;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * m_fAddMove;
		}
		//前移動
		else if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			m_rotDest.y = rot.y + D3DX_PI * 0.25f;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * m_fAddMove;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * m_fAddMove;
		}
		else
		{
			m_rotDest.y = rot.y;
			m_move.x = sinf(m_rotDest.y + D3DX_PI) * m_fAddMove;
			m_move.z = cosf(m_rotDest.y + D3DX_PI) * m_fAddMove;

		}
	}

	// 動いてないときはニュートラルに
	if (pInputKeyboard->GetPress(DIK_W) == false &&
		pInputKeyboard->GetPress(DIK_S) == false &&
		pInputKeyboard->GetPress(DIK_A) == false &&
		pInputKeyboard->GetPress(DIK_D) == false)
	{
		m_pMotion->Set(CMotion::MOTIONTYPE_NEUTRAL);
		
		m_fAddMove = 0.0f;
	}
}

//=================================================
// 弾との当たり判定
//=================================================
void CPlayer::CollisionBullet(void)
{
	// キーボード
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	// ステージモデルのみ調べる
	CObject* pObj = CObject::GetTop(13);
	while (pObj != NULL)
	{
		CObject* pObjNext = pObj->GetNext();
		CObject::TYPE type = pObj->GetType();

		if (type == TYPE_BULLET)
		{
			CBullet* pBullet = (CBullet*)pObj;
			D3DXVECTOR3 BulletPos = pBullet->GetPosition();

			//半径の算出変数
			float PRadiusPos = 55.0f;
			float BRadiusPos = 30.0f;

			//範囲計算
			float fDisX = m_pos.x - BulletPos.x;
			float fDisY = m_pos.y - BulletPos.y;
			float fDisZ = m_pos.z - BulletPos.z;

			//二つの半径を求める
			float fRadX = PRadiusPos + BRadiusPos;

			// プレイヤーが雷のギミックの範囲に入っていたら
			if ((fDisX * fDisX) + (fDisZ * fDisZ) <= (fRadX * fRadX))
			{
				if (pInputKeyboard->GetPress(DIK_SPACE) == true)
				{
					//pBullet->CharngeMove();
				}
			}
		}
		pObj = pObjNext;
	}
}

//=================================================
// 右＆後ろの判定
//=================================================

void CPlayer::VectorJudgeR(void)
{
	//半径の算出変数
	float PRadius = 15.0f;
	float RRadius = 15.0f;

	//弾とプレイヤーの距離の差
	D3DXVECTOR3 diff = {};
	D3DXVECTOR3 RockPos[MAX_ROCK] = {};

	// ロックのポインタを取得
	CMeteoRock** pRock = CRockManager::GetRock();

	if (m_bTamesi1 == false)
	{
		for (int nCnt = 0; nCnt < MAX_ROCK; nCnt++)
		{
			if (pRock[nCnt] != nullptr)
			{
				//岩の位置の取得
				RockPos[nCnt] = pRock[nCnt]->GetPosition();

				//範囲計算
				float fDisX = (RockPos[nCnt].x - m_fAddLR) - m_pos.x;
				float fDisY = RockPos[nCnt].y - m_pos.y;
				float fDisZ = (RockPos[nCnt].z - m_fAddUD) - m_pos.z;

				//二つの半径を求める
				float fRadX = PRadius + RRadius;

				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
				{
					m_bTamesi0 = true;
				}
			}

		}
	}
}

//=================================================
// 左＆前の判定
//=================================================
void CPlayer::VectorJudgeL(void)
{
	//半径の算出変数
	float PRadius = 15.0f;
	float RRadius = 15.0f;

	//弾とプレイヤーの距離の差
	D3DXVECTOR3 diff = {};
	D3DXVECTOR3 RockPos[MAX_ROCK] = {};

	// ロックのポインタを取得
	CMeteoRock** pRock = CRockManager::GetRock();

	if (m_bTamesi0 == false)
	{
		for (int nCnt = 0; nCnt < MAX_ROCK; nCnt++)
		{
			if (pRock[nCnt] != nullptr)
			{
				//岩の位置の取得
				RockPos[nCnt] = pRock[nCnt]->GetPosition();

				//範囲計算
				float fDisX = (RockPos[nCnt].x + m_fAddLR) - m_pos.x;
				float fDisY = RockPos[nCnt].y - m_pos.y;
				float fDisZ = (RockPos[nCnt].z + m_fAddUD) - m_pos.z;

				//二つの半径を求める
				float fRadX = PRadius + RRadius;

				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
				{
					m_bTamesi1 = true;
				}
			}

		}
	}
}

void CPlayer::VectorJudge(void)
{
	//半径の算出変数
	float PRadius = 200.0f;
	float RRadius = 15.0f;

	//弾とプレイヤーの距離の差
	D3DXVECTOR3 diff = {};
	D3DXVECTOR3 RockPos[MAX_ROCK] = {};

	// ロックのポインタを取得
	CMeteoRock** pRock = CRockManager::GetRock();

	if (m_bTamesi0 == false)
	{
		for (int nCnt = 0; nCnt < MAX_ROCK; nCnt++)
		{
			if (pRock[nCnt] != nullptr)
			{
				//岩の位置の取得
				RockPos[nCnt] = pRock[nCnt]->GetPosition();

				//範囲計算
				float fDisX = RockPos[nCnt].x - m_pos.x;
				float fDisY = RockPos[nCnt].y - m_pos.y;
				float fDisZ = RockPos[nCnt].z - m_pos.z;

				//二つの半径を求める
				float fRadX = PRadius + RRadius;

				if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
				{
					m_bTamesi2 = true;
				}
				else
				{
					m_bTamesi2 = false;
				}
			}

		}
	}
}