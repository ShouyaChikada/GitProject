//=================================================
//
//	human.cpp
// 
//	Author:近田尚也
//
//=================================================
#include "human.h"
#include "input.h"
#include "manager.h"
#include "camera.h"
#include "debugproc.h"
#include "blockmanager.h"
#include "game.h"
#include "gimmickmanager.h"
#include "time.h"
#include "tutorial.h"

//============================
// コンストラクタ
//============================
CHuman::CHuman(int nPriority) : CObject(nPriority)
{
	for (int nCnt = 0; nCnt < MAX_HMODEL; nCnt++)
	{
		m_apModel[nCnt] = nullptr;
	}
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_SetPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Diff = 0.0f;
	m_bJump = false;
	m_pMotion = nullptr;;
	m_bLeave = true;
	m_nCnt = 0;
	m_bCnt = false;
}

//============================
// デストラクタ
//============================
CHuman::~CHuman()
{

}

//============================
//  生成処理
//============================
CHuman* CHuman::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CHuman* pHuman = nullptr;
	pHuman = new CHuman;

	if (pHuman != nullptr)
	{
		pHuman->m_pos = pos;
		pHuman->m_rot = rot;
		pHuman->Init();
		return pHuman;
	}
	else
	{
		return nullptr;
	}
}

//============================
// 初期化処理
//============================
HRESULT CHuman::Init(void)
{
	CScene::MODE mode = CScene::GetMode();

	static CModel** pModel = nullptr;

	if (mode != CScene::MODE_TUTORIAL)
	{
		m_pMotion = CGame::GetMotion1();
		pModel = CGame::GetModel1();
	}
	else if (mode == CScene::MODE_TUTORIAL)
	{
		m_pMotion = CTutorial::GetMotion1();
		pModel = CTutorial::GetModel1();
	}

	if (pModel != nullptr)
	{
		for (int nCnt = 0; nCnt < MAX_HMODEL; nCnt++)
		{
			m_apModel[nCnt] = pModel[nCnt];
		}
	}

	m_size = CModel::GetSize();

	srand((unsigned int)time(NULL));

	return S_OK;
}

//============================
// 終了処理
//============================
void CHuman::Uninit(void)
{
	if (this == nullptr) return;

	m_bLeave = false;

	// モデルの破棄
	for (int nCnt = 0; nCnt < MAX_HMODEL; nCnt++)
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

//============================
// 更新処理
//============================
void CHuman::Update(void)
{
	m_pMotion->Update(&m_apModel[0]);

	//AutoWand(m_pos);

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

	m_move.y -= 0.4f;	//重力加算

	//重力
	if (m_pos.y < -600.0f)
	{
		m_pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
		m_move.y = 0.0f;
		m_bJump = false;
	}

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
void CHuman::Draw(void)
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
	for (int nCnt = 0; nCnt < MAX_HMODEL; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}

	//保存していたマテリアルを隠す
	pD3DDevice->SetMaterial(&matDef);

}

// 位置の設定
void CHuman::SetPosition(D3DXVECTOR3 pos)
{
	m_SetPosition = pos;
}

// 位置を取得
D3DXVECTOR3 CHuman::GetPosition(void)
{
	return m_SetPosition;
}

D3DXVECTOR3 CHuman::GetPos(void)
{
	return m_pos;
}

// 移動量を取得
D3DXVECTOR3 CHuman::GetMove(void)
{
	return m_move;
}

// 前回の位置を取得
D3DXVECTOR3 CHuman::GetPosOld(void)
{
	return m_posOld;
}

// サイズを取得
D3DXVECTOR3 CHuman::GetSize(void)
{
	return m_size;
}
// 目的の向きの取得
D3DXVECTOR3 CHuman::GetRotDest(void)
{
	return m_rotDest;
}

void CHuman::AutoWand(D3DXVECTOR3 pos)
{
	m_pMotion->Set(CMotion::MOTIONTYPE_MOVE);

	D3DXVECTOR3 Turn[MAX_RANDPOINT];

	float fAnglemove = 0.0f;

	static float fX = 0.0f;
	static float fZ = 0.0f;
	static float fMove = 0.0f;

	//徘徊ポイント用変数
	int nMax = 2000.0f;
	int nMin = -2000.0f;

	//人間のスピード用変数
	int nMaxS = 20.0f;
	int nMinS = 5.0f;

	if (m_bCnt == false)
	{
		fX = (float)(rand() % (nMax - nMin + 1) + nMin);
		fZ = (float)(rand() % (nMax - nMin + 1) + nMin);
		fMove = (float)(rand() % (nMaxS - nMinS + 1) + nMinS);

		m_bCnt = true;
	}

	Turn[0] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[1] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[2] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[3] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[4] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[5] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[6] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[7] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[8] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[9] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[10] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[11] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[12] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[13] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[14] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[15] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[16] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[17] = D3DXVECTOR3(fX, 0.0f, fZ);
	Turn[18] = D3DXVECTOR3(fX, 0.0f, fZ);

	// 距離用の変数
	float fDistance = (pos.x - Turn[m_nCnt].x) * (pos.x - Turn[m_nCnt].x) + (pos.y - Turn[m_nCnt].y) * (pos.y - Turn[m_nCnt].y) + (pos.z - Turn[m_nCnt].z) * (pos.z - Turn[m_nCnt].z);
	
	// 範囲用変数
	D3DXVECTOR3 fRadP(100.0f, 0.0f, 100.0f);
	D3DXVECTOR3 fRadE(100.0f, 0.0f, 100.0f);

	// 半径の式
	float fRadius = (fRadP.x + fRadE.x) * (fRadP.x + fRadE.x) + (fRadP.y + fRadE.y) * (fRadP.y + fRadE.y) + (fRadP.z + fRadE.z) * (fRadP.z + fRadE.z);


	if (fDistance <= fRadius)
	{//ターン地点まで来たら

		//次のターン地点を設定
		m_nCnt += 1;
		m_nCnt = m_nCnt % MAX_RANDPOINT;
		m_bCnt = false;

	}

	// 目的の角度
	m_rotDest.y = atan2f((Turn[m_nCnt].x - pos.x), (Turn[m_nCnt].z - pos.z)) + D3DX_PI;
	fAnglemove = atan2f((Turn[m_nCnt].x - pos.x), (Turn[m_nCnt].z - pos.z));

	m_move.x = sinf(fAnglemove) * fMove;
	m_move.z = cosf(fAnglemove) * fMove;

}