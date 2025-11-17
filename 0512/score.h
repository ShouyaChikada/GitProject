//=================================================
//
//	score.h
// 
// Author:近田 尚也
//
//=================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "object.h"
#include "number.h"
#include "object2D.h"

#define MAX_SCORE (4)

class CScore :public CObject
{
public:
	CScore(int nPriority = 13);
	~CScore();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);
	static CScore* Create(D3DXVECTOR3 pos);
	void Set(int nScore);
	static void Add(int nValue);
	int  Counter(int nScore);
	int GetScore(void);

private:
	D3DXVECTOR3 m_Pos;						// スコアの位置
	D3DXVECTOR3 m_SetPosition;				// 位置
	static CNumber* m_pNumber[MAX_SCORE];	// ナンバーのポインタ
	int m_nCounter;							// 0のカウント
	static int m_Score;						// 最終スコア
};


#endif 