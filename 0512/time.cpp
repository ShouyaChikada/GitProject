//=================================================
//
//	time.cpp
// 
// Author:近田 尚也
//
//=================================================
#include "time.h"
#include "manager.h"

// 静的メンバ変数
CNumber* CTime::m_pNumber1[MAX_TIME] = {};
CNumber* CTime::m_pNumber2[MAX_TIME] = {};
CNumber* CTime::m_pNumber3 = {};
int CTime::m_nTime = NULL;

// コンストラクタ
CTime::CTime(int nPriolity):CObject(nPriolity)
{
	m_SetPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);						
	m_ntime = 0;							
	m_ns = 0;
	m_min = 0;
	m_bTime = false;
}

// デストラクタ
CTime::~CTime()
{

}

// 生成
CTime* CTime::Create(D3DXVECTOR3 pos)
{
	CTime* pTime = nullptr;
	pTime = new CTime;

	if (pTime != nullptr)
	{
		pTime->m_pos = pos;
		pTime->Init();
		return pTime;
	}
	else
	{
		return nullptr;
	}
}

//=====================
// 初期化処理
//=====================
HRESULT CTime::Init(void)
{
	// 位置を初期化する
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 分
	m_min = 0;

	m_nTime = 0;

	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_pNumber1[nCnt] = new CNumber;
		m_pNumber1[nCnt]->Init(200.0f, 200.0f, nCnt,50.0f,50.0f, MAX_TIME,4, "data\\TEXTURE\\number005.png", 0.1f);

		m_pNumber2[nCnt] = new CNumber;
		m_pNumber2[nCnt]->Init(50.0f,50.0f, nCnt, 50.0f, 50.0f, MAX_TIME,4, "data\\TEXTURE\\number005.png",0.1f);
	}

	m_pNumber3 = new CNumber;
	m_pNumber3->Init(150.0f, 200.0f,0, 1.0f, 0.0f, 1,0, "data\\TEXTURE\\koron.png",1.0f);

	//CTime::SetTime(MAX_COUNTTIME);

	return S_OK;
}

//=============================================================================
// タイマーの終了処理
//=============================================================================
void CTime::Uninit(void)
{
	//ナンバーの破棄(秒)
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		if (m_pNumber1[nCnt] != NULL)
		{
			m_pNumber1[nCnt]->Uninit();
			delete m_pNumber1[nCnt];
			m_pNumber1[nCnt] = NULL;
		}
	}

	//ナンバーの破棄(分)
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		if (m_pNumber2[nCnt] != NULL)
		{
			m_pNumber2[nCnt]->Uninit();
			delete m_pNumber2[nCnt];
			m_pNumber2[nCnt] = NULL;
		}
	}

	//ナンバーの破棄(：)
	if (m_pNumber3 != NULL)
	{
		m_pNumber3->Uninit();
		delete m_pNumber3;
		m_pNumber3 = NULL;
	}
	
	// 自分自身の破棄
	CObject::Release();
}

//=============================================================================
// タイマーの更新処理
//=============================================================================
void CTime::Update(void)
{
	m_ns++;

	// 1秒経過
	if (m_ns > 60)
	{
		SubNs(1);

		m_ns = 0;
	}

	// 1分経過
	if (m_ntime >= 60)
	{
		SubNs(-60);
		SubMin(1);
		m_ntime = 0;
	}
	
	//m_nTime++;
}

//=============================================================================
// タイマーの描画処理
//=============================================================================
void CTime::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		m_pNumber1[nCnt]->Draw();
		m_pNumber2[nCnt]->Draw();
	}
	m_pNumber3->Draw();
}

//=============================================================================
// タイマーの設定処理
//=============================================================================
void CTime::SetTime(int ntime)
{
	// 秒数
	int aPosTexU[MAX_TIME] = {};	// 各桁の数字を格納
	int nData = 100;				// 3桁
	int nData1 = 10;				// 2桁

	m_ntime -= ntime;

	for (int nCnt1 = 0; nCnt1 < MAX_TIME; nCnt1++)
	{
		if (nCnt1 == 0)
		{
			// 0番目だったら
			aPosTexU[0] = m_ntime / nData;
		}
		else
		{
			// 0番目以外
			aPosTexU[nCnt1] = (m_ntime % nData) / nData1;
			nData = nData / 10;
			nData1 = nData1 / 10;
		}
		m_pNumber2[nCnt1]->SetNumber(aPosTexU[nCnt1],4);
	}

	int nData2 = 100;
	int nData3 =  10;

	for (int nCnt2 = 0; nCnt2 < MAX_TIME; nCnt2++)
	{
		if (nCnt2 == 0)
		{
			// 0番目だったら
			aPosTexU[0] = m_min / nData2;
		}
		else
		{
			// 0番目以外
			aPosTexU[nCnt2] = (m_min % nData2) / nData3;
			nData2 = nData2 / 10;
			nData3 = nData3 / 10;
		}
		m_pNumber1[nCnt2]->SetNumber(aPosTexU[nCnt2],4);
	}

}

//=============================================================================
// タイマーの秒算処理
//=============================================================================
void CTime::SubNs(int nValue)
{
	int aPosTexU[MAX_TIME] = {};	// 各桁の数字を格納
	int nData = 100;				// 3桁
	int nData1 = 10;				// 2桁

	m_ntime += nValue;

	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		// 0番目以外
		aPosTexU[nCnt] = (m_ntime % nData) / nData1;
		nData = nData / 10;
		nData1 = nData1 / 10;

		m_pNumber1[nCnt]->SetNumber(aPosTexU[nCnt],4);

	}
}

//=============================================================================
// タイマーの分減算処理
//=============================================================================
void CTime::SubMin(int nValue)
{
	int aPosTexU[MAX_TIME] = {};	// 各桁の数字を格納
	int nData = 100;				// 3桁
	int nData1 = 10;				// 2桁

	m_min += nValue;

	for (int nCnt = 0; nCnt < MAX_TIME; nCnt++)
	{
		// 0番目以外
		aPosTexU[nCnt] = (m_min % nData) / nData1;
		nData = nData / 10;
		nData1 = nData1 / 10;

		m_pNumber2[nCnt]->SetNumber(aPosTexU[nCnt],4);
	}
}

//=============================================================================
//タイマーの秒取得
//=============================================================================
int CTime::GetNs(void)
{
	return m_ntime;
}

//=============================================================================
//タイマーの分取得
//=============================================================================
int CTime::GetMin(void)
{
	return m_min;
}

//位置の設定
void CTime::SetPosition(D3DXVECTOR3 pos)
{
	m_SetPosition = pos;
}

// 位置を取得
D3DXVECTOR3 CTime::GetPosition(void)
{
	return m_SetPosition;
}
