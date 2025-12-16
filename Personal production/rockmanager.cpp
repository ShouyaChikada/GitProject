//=================================================
//
// [rockmanager.cpp]
// Author:chikada shouya
//
//=================================================
#include "rockmanager.h"
#include "timer.h"
#include <random>
#include <ctime> 

//=================================================
// 静的メンバ変数
//=================================================
CMeteoRock* CRockManager::m_pRock[MAX_ROCK] = {};
CMeteoPillar* CRockManager::m_pPillar[MAX_ROCK] = {};

//=================================================
// コンストラクタ
//=================================================
CRockManager::CRockManager()
{
	m_bCreate = false;
	m_bLeave = false;
	m_bStop = false;
	m_nCntCreate = NULL;
	m_nCntTime = NULL;
}

//=================================================
// デストラクタ
//=================================================
CRockManager::~CRockManager()
{

}

//=================================================
// 初期化
//=================================================
HRESULT CRockManager::Init(void)
{
	float fRand[3] = {};

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		std::srand(static_cast<unsigned int>(std::time(nullptr)));

		// 0から99までの乱数を生成する
		fRand[nCnt] = (float)(std::rand() % (500 - ((nCnt + 1) *100)) + (-500 - (-(nCnt  + 1) * 100)));
	}

	m_pRock[0] = CMeteoRock::Create(D3DXVECTOR3(0.0f, 20.0f, 800.0f));

	m_nCntCreate = 0;
	m_nCntTime = 20;

	return S_OK;
}

//=================================================
// 破棄
//=================================================
void CRockManager::Uninit(void)
{

}

//=================================================
// 更新
//=================================================
void CRockManager::Update(void)
{
	int nSec = CTimer::GetSecond();
	int nMin = CTimer::GetMinute();
	//// 1. 乱数生成エンジンを初期化する
	//std::mt19937 engine(static_cast<unsigned int>(std::time(nullptr)));
	//std::mt19937 engine1(static_cast<unsigned int>(std::time(nullptr)));

	//// 2. 乱数分布を定義する (0から99までの整数)
	//std::uniform_int_distribution<int> dist(100, 400);
	//std::uniform_int_distribution<int> dist1(-200, 100);

	//// 3. 乱数を生成する
	//float fRand0 = dist(engine);
	//float fRand1 = dist1(engine1);

	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	// 0から99までの乱数を生成する
	float fRand0 = (float)(std::rand() % 500 + (-300));
	float fRand1 = (float)(std::rand() % 500 + (-300));

	if (m_nCntTime < 0)
	{
		m_nCntTime = 50;
	}

	if (nMin <= 0 && m_nCntTime <= 0)
	{
		m_bStop = true;
	}

	if (nSec == m_nCntTime)
	{
		for (int nCnt = 0; nCnt < MAX_ROCK; nCnt++)
		{
			if (m_bCreate == false)
			{
				if (m_pRock[nCnt] == nullptr)
				{
					if (m_bStop == false)
					{
						m_pPillar[nCnt] = CMeteoPillar::Create(D3DXVECTOR3(2100.0f, 20.0f, fRand0), (CMeteoPillar::ROT)3);
						m_pPillar[nCnt + 1] = CMeteoPillar::Create(D3DXVECTOR3(-2100.0f, 20.0f, fRand1), (CMeteoPillar::ROT)3);
						m_bCreate = true;
						m_nCntTime = m_nCntTime - 10;
					}
				}
			}
		}
	}

	for (int nCnt = 0; nCnt < MAX_ROCK; nCnt++)
	{
		if (m_pRock[nCnt] != nullptr)
		{
			bool bDeath = m_pRock[nCnt]->GetDeath();

			if (bDeath == true)
			{
				m_pRock[nCnt]->Uninit();
				m_pRock[nCnt] = nullptr;
				m_pRock[0] = CMeteoRock::Create(D3DXVECTOR3(0.0f, 20.0f, 800.0f));
			}
		}

		if (m_pPillar[nCnt] != nullptr)
		{
			bool bDeath = m_pPillar[nCnt]->GetDeath();

			if (bDeath == true)
			{

				m_pPillar[nCnt]->Uninit();
				m_pPillar[nCnt] = nullptr;
				m_bCreate = false;
			}
		}
	}

	if (m_bLeave == true)
	{
		//for (int nCnt = 0; nCnt < 3; nCnt++)
		//{
		//	float fRand[3] = {};

		//	for (int nCnt = 0; nCnt < 3; nCnt++)
		//	{
		//		std::srand(static_cast<unsigned int>(std::time(nullptr)));

		//		// 0から99までの乱数を生成する
		//		fRand[nCnt] = (float)(std::rand() % (500 - ((nCnt + 1) * 100)) + (-500 - (-(nCnt + 1) * 100)));
		//	}
		//	if (m_pRock[nCnt] == nullptr)
		//	{
		//		m_pRock[0] = CRock::Create(D3DXVECTOR3(fRand[nCnt], 20.0f, 800.0f), (CRock::ROT)2, (CObjectX::ROT)2, (CRock::TYPE)1);
		//	}
		//}
		m_bLeave = false;
	}
}

//=================================================
// 描画
//=================================================
void CRockManager::Draw(void)
{

}

