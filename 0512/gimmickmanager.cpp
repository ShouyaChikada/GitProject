//=================================================
//
//	gimmickmanager.cpp
// 
//	Author:近田尚也
//
//=================================================
#include "gimmickmanager.h"
#include "game.h"
#include "player.h"
#include "debugproc.h"
#include "input.h"
#include "manager.h"
#include "meshcylinder.h"
#include "gauge.h"
#include "time.h"
#include "scene.h"
#include "tutorial.h"

//静的メンバ変数
CParticle* CGimmickManager::m_pParticle = nullptr;
CGimmick* CGimmickManager::m_pGimmick[MAX_GIMMICK] = {};
bool CGimmickManager::m_bRange = false;
bool CGimmickManager::m_bPush = false;
int CGimmickManager::m_nCntGimmick = 0;
bool CGimmickManager::m_bCheck = false;

// コンストラクタ
CGimmickManager::CGimmickManager()
{
	for (int nCnt = 0; nCnt < MAX_COUNT; nCnt++)
	{
		m_nCnt[nCnt] = 0;
	}
	m_bTime = false;
	m_nScore = 0;
}

// デストラクタ
CGimmickManager::~CGimmickManager()
{

}

//=========================
//　ブロック初期化処理
//=========================
HRESULT CGimmickManager::Init(void)
{
	CScene::MODE mode = CScene::GetMode();

	if (mode != CScene::MODE_TUTORIAL)
	{
		m_bCheck = false;
		m_bRange = false;
		m_bPush = false;
		m_pGimmick[0] = CGimmick::Create(D3DXVECTOR3(-200.0f, 40.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CGimmick::TYPE_THUNDER);
		//m_pGimmick[1] = CGimmick::Create(D3DXVECTOR3(-200.0f, 700.0f, 0.0f), D3DXVECTOR3(90, 0.0f, 90), CGimmick::TYPE_METEORITE);

		//m_bUse = ;
	}
	if (mode == CScene::MODE_TUTORIAL)
	{
		m_bCheck = false;
		m_bRange = false;
		m_bPush = false;
		m_pGimmick[0] = CGimmick::Create(D3DXVECTOR3(-200.0f, 40.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CGimmick::TYPE_THUNDER);
	}
	return S_OK;
}
//=========================
//　ブロック終了処理
//=========================
void CGimmickManager::Uninit(void)
{

}
//=========================
//　ブロック更新処理
//=========================
void CGimmickManager::Update(void)
{
	CScene::MODE mode = CScene::GetMode();

	if (mode != CScene::MODE_TUTORIAL)
	{
		// キーボード
		CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

		// プレイヤー
		CPlayer* pPlayer = CGame::GetPlayer();

		// メッシュシリンダー
		CMeshCylinder* pMeshcylinder = CGimmick::GetMeshCylinder();

		// ゲージ
		CGauge* pGauge = CGimmick::GetGauge();

		// UI
		CBaseUI* pBaseUI = CGimmick::GetBaseUI();

		// 時間
		int nTime = CTime::GetTime();

		D3DXVECTOR3 GimmickPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		CGimmick::TYPE type = CGimmick::TYPE_METEORITE;
		bool bUse = false;

		for (int nCnt = 0; nCnt < MAX_GIMMICK; nCnt++)
		{
			if (m_pGimmick[nCnt] != nullptr)
			{
				// ギミック
				GimmickPos = m_pGimmick[nCnt]->GetPos();
				type = m_pGimmick[nCnt]->GetType();
				bUse = m_pGimmick[nCnt]->GetUse();
			}
		}
		// 使われている & ブロックのタイプが雷だったら
		if (bUse == true && type == CGimmick::TYPE_THUNDER)
		{
			//パーティクル角度
			float fAngleX = (float)(rand() % 628 - 314) * 0.01f;
			float fAngleY = (float)(rand() % 628 - 314) * 0.01f;
			float fAngleZ = (float)(rand() % 628 - 314) * 0.01f;

			//半径の算出変数
			float PRadiusPos = 55.0f;
			float GRadiusPos = 195.0f;

			//プレイヤーの位置の取得
			D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

			//範囲計算
			float fDisX = PlayerPos.x - GimmickPos.x;
			float fDisY = PlayerPos.y - GimmickPos.y;
			float fDisZ = PlayerPos.z - GimmickPos.z;

			//二つの半径を求める
			float fRadX = PRadiusPos + GRadiusPos;

			// プレイヤーが雷のギミックの範囲に入っていたら
			if ((fDisX * fDisX) + (fDisZ * fDisZ) <= (fRadX * fRadX))
			{
				m_bRange = true;

				// Fボタンを押していたら
				if (pInputKeyboard->GetPress(DIK_F) == true)
				{
					m_bPush = true;

					m_nCnt[0]++;

					if (m_nCnt[0] >= 480)
					{
						m_bCheck = true;

					}
				}
				else if (pInputKeyboard->GetPress(DIK_F) == false && m_bCheck == false)
				{
					m_bPush = false;
				}

			}
			else
			{
				if (m_bCheck == false)
				{
					m_bRange = false;
					m_bPush = false;
				}
			}

			// 解除できていたら
			if (m_bCheck == true)
			{
				m_nCnt[1]++;
				//m_bUse = true;
				if (m_nCnt[1] >= 120)
				{
					for (int nCnt = 0; nCnt < MAX_GIMMICK; nCnt++)
					{
						if (m_pGimmick[nCnt] != nullptr)
						{
							m_pGimmick[nCnt]->Uninit();
						}
					}

					if (pMeshcylinder != nullptr)
					{
						pMeshcylinder->Uninit();
					}

					if (pGauge != nullptr)
					{
						pGauge->Uninit();
					}

					if (pBaseUI != nullptr)
					{
						pBaseUI->Uninit();
					}

					m_nCnt[0] = 0;
					m_nCnt[1] = 0;

					CScore::Add(300);

					// 修復 or 破壊のカウント
					m_nCntGimmick++;
				}
			}
		}
		if (nTime == 5400 || nTime == 3600 || nTime == 1800)
		{
			m_bTime = true;
		}
		if (m_bTime == true)
		{
			m_bCheck = false;
			m_pGimmick[1] = CGimmick::Create(D3DXVECTOR3(-200.0f, 40.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CGimmick::TYPE_THUNDER);
			m_bTime = false;
		}
	}

	if (mode == CScene::MODE_TUTORIAL)
	{
		// キーボード
		CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

		// プレイヤー
		CPlayer* pPlayer = CTutorial::GetPlayer();

		// メッシュシリンダー
		CMeshCylinder* pMeshcylinder = CGimmick::GetMeshCylinder();

		// ゲージ
		CGauge* pGauge = CGimmick::GetGauge();

		// UI
		CBaseUI* pBaseUI = CGimmick::GetBaseUI();

		D3DXVECTOR3 GimmickPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		CGimmick::TYPE type = CGimmick::TYPE_METEORITE;
		bool bUse = false;

		if (m_pGimmick[0] != nullptr)
		{
			// ギミック
			GimmickPos = m_pGimmick[0]->GetPos();
			type = m_pGimmick[0]->GetType();
			bUse = m_pGimmick[0]->GetUse();
		}
		// 使われている & ブロックのタイプが雷だったら
		if (bUse == true && type == CGimmick::TYPE_THUNDER)
		{
			//パーティクル角度
			float fAngleX = (float)(rand() % 628 - 314) * 0.01f;
			float fAngleY = (float)(rand() % 628 - 314) * 0.01f;
			float fAngleZ = (float)(rand() % 628 - 314) * 0.01f;

			//半径の算出変数
			float PRadiusPos = 55.0f;
			float GRadiusPos = 195.0f;

			//プレイヤーの位置の取得
			D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

			//範囲計算
			float fDisX = PlayerPos.x - GimmickPos.x;
			float fDisY = PlayerPos.y - GimmickPos.y;
			float fDisZ = PlayerPos.z - GimmickPos.z;

			//二つの半径を求める
			float fRadX = PRadiusPos + GRadiusPos;

			// プレイヤーが雷のギミックの範囲に入っていたら
			if ((fDisX * fDisX) + (fDisZ * fDisZ) <= (fRadX * fRadX))
			{
				m_bRange = true;

				// Fボタンを押していたら
				if (pInputKeyboard->GetPress(DIK_F) == true)
				{
					m_bPush = true;

					m_nCnt[0]++;

					if (m_nCnt[0] >= 30) // 480
					{
						m_bCheck = true;

					}
				}
				else if (pInputKeyboard->GetPress(DIK_F) == false && m_bCheck == false)
				{
					m_bPush = false;
				}

			}
			else
			{
				if (m_bCheck == false)
				{
					m_bRange = false;
					m_bPush = false;
				}
			}

			if (m_bCheck == true)
			{
				m_nCnt[1]++;
				//m_bUse = true;
				if (m_nCnt[1] >= 120)
				{
					
					if (m_pGimmick[0] != nullptr)
					{
						m_pGimmick[0]->Uninit();
					}
					

					if (pMeshcylinder != nullptr)
					{
						pMeshcylinder->Uninit();
					}

					if (pGauge != nullptr)
					{
						pGauge->Uninit();
					}

					//if (pBaseUI != nullptr)
					//{
					//	pBaseUI->Uninit();
					//}

					m_nCnt[0] = 0;
					m_nCnt[1] = 0;

				}
			}
		}
	}

	
}
//=========================
//　ブロック描画処理
//=========================
void CGimmickManager::Draw(void)
{
	// 範囲に入っていたら
	if (m_bRange == true)
	{
		CDebugProc::Print("ギミック範囲 + [ F ] : オン\n");
	}
	// 範囲外だったら
	else if (m_bRange == false)
	{
		CDebugProc::Print("ギミック範囲 + [ F ] : オフ\n");
	}

	// 作業を終えていたら
	if (m_bCheck == true)
	{
		// 描画処理
		//m_pBaseUI->Draw();
	}
}