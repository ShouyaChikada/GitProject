//=================================================
//
//	score.cpp
// 
// Author:近田 尚也
//
//=================================================
#include "score.h"
#include "manager.h"

// 静的メンバ変数
CNumber* CScore::m_pNumber[MAX_SCORE] = {};
int CScore::m_Score = 0;

//コンストラクタ
CScore::CScore(int nPriority) : CObject(nPriority)
{	
	m_SetPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounter = 0;
}

//デストラクタ
CScore::~CScore()
{

}

//スコアの生成
CScore* CScore::Create(D3DXVECTOR3 pos)
{
	CScore* pScore = nullptr;
	pScore = new CScore;

	if (pScore != nullptr)
	{
		pScore->m_Pos = pos;
		pScore->Init();
		return pScore;
	}
	else
	{
		return nullptr;
	}
}
//*********************
// 初期化処理
//*********************
HRESULT CScore::Init(void)
{

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_pNumber[nCnt] = new CNumber;
		m_pNumber[nCnt]->Init(1000.0f, 1000.0f,nCnt,50.0f,50.0f,1,4, "data\\TEXTURE\\number005.png", 0.1f);
		//テクスチャを設定
		//m_pNumber[nCnt]->BindTexture(m_pTexture);
	}
	CScore::Set(0);

	
	return S_OK;
}

//*********************
// 終了処理
//*********************
void CScore::Uninit(void)
{
	//ナンバーの破棄
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		if (m_pNumber[nCnt] != NULL)
		{
			m_pNumber[nCnt]->Uninit();
			delete m_pNumber[nCnt];
			m_pNumber[nCnt] = NULL;
		}
	}
	// 自分自身の破棄
	CObject::Release();
}

//*********************
// 更新処理
//*********************
void CScore::Update(void)
{

}

//*********************
// 描画処理
//*********************
void CScore::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		m_pNumber[nCnt]->Draw();
	}
}

//*********************
// スコア設定処理
//*********************
void CScore::Set(int nScore)
{
	int aPosTexU[MAX_SCORE] = {};

	int nData = 1000;
	int aData = 100;	//各桁の数字を格納

	m_Score = nScore;
	
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		//桁ごとに分割する
		if (nCount == 0)
		{
			aPosTexU[0] = m_Score / nData;//8桁目
		}
		else
		{
			aPosTexU[nCount] = m_Score % nData / aData;//7桁目
			nData = nData / 10;
			aData = aData / 10;
		}
		m_pNumber[nCount]->SetNumber(aPosTexU[nCount],4);
	}
}

//*********************
// スコア加算処理
//*********************
void CScore::Add(int nValue)
{
	// 各桁の数字を格納
	int aPosTexU[MAX_SCORE] = {};

	int nData = 1000;
	int aData = 100;	//各桁の数字を格納

	m_Score += nValue;

	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		//桁ごとに分割する
		if (nCount == 0)
		{
			aPosTexU[nCount] = m_Score / nData;//8桁目
		}
		else
		{
			aPosTexU[nCount] = m_Score % nData / aData;//7桁目
			nData = nData / 10;
			aData = aData / 10;
		}
		m_pNumber[nCount]->SetNumber(aPosTexU[nCount],4);
	}

}

//=====================
// スコアの0をカウント
//=====================
int  CScore::Counter(int nScore)
{
	int nNum = nScore;	// スコアの０の部分をカウント
	int nKeepNum = 0;	// スコアの桁数

	while (nNum != 0)	// 割り切れなくなるまで繰り返す(０まで)
	{
		nNum /= 10;		// nNumを10で割っていく
		nKeepNum++;		// 桁数を加算

	}
	if (nScore == 0)
	{
		// 1桁目に0が入っているとき
		nKeepNum = 1;
	}
	return nKeepNum;	// スコアの桁数を返す
}

//=====================
// 現在のスコア
//=====================
int CScore::GetScore(void)
{
	return m_Score;
}

//位置の設定
void CScore::SetPosition(D3DXVECTOR3 pos)
{
	m_SetPosition = pos;
}

// 位置を取得
D3DXVECTOR3 CScore::GetPosition(void)
{
	return m_SetPosition;
}