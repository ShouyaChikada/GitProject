////==============================================================
////
//// [number.h]
//// Author: Irisawa Kazan
////
////==============================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"

#define MAX_TIMENUM (2)

class CNumber
{
public:

	typedef enum
	{
		NUM_NONE = 0,
		NUM_TIME,
		NUM_SCORE,
		NUM_MAX,
	}NUM;

	CNumber();
	~CNumber();
	HRESULT Init(float fX1, int nCnt, float fAdd, std::string aName, NUM NumType);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CNumber* Create(D3DXVECTOR3 pos);

	// セッター
	void SetNumber(int nNumber);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void ColAnim(void);

	void InitTimeNum(float fX1, int nCnt, float fAdd, std::string aName);
	void InitScoreNum(float fX1, std::string aName);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファ
	D3DXVECTOR3 m_pos;						// 位置
	bool m_bChange;							// カラー判定用
	int m_nColTime;							// カラー用の計算
	int m_nIdx;								// インデックス番号
	NUM m_Num;								// ナンバー
};
#endif