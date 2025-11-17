//=================================================
//
//	time.h
// 
// Author:近田 尚也
//
//=================================================
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"
#include "object.h"
#include "number.h"


#define MAX_COUNTTIME (300)	//ゲーム中の時間
#define MAX_TIME (2)		//描画時の0の数
#define MAX_MIN (2)

class CTime :public CObject
{
public:
	CTime(int nPriolity = 13);
	~CTime();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);
	static CTime* Create(D3DXVECTOR3 pos);

	void SetTime(int ntime);
	void SubNs(int nValue);
	void SubMin(int nValue);
	int GetNs(void);
	int GetMin(void);
	bool GetbTime(void) { return m_bTime; };
	static int GetTime(void) { return m_nTime; };
private:
	static CNumber* m_pNumber1[MAX_TIME];	//ナンバーのポインタ(秒)
	static CNumber* m_pNumber2[MAX_TIME];	//ナンバーのポインタ(分)
	static CNumber* m_pNumber3;				//ナンバーのポインタ(：)
	D3DXVECTOR3 m_pos;						// タイマーの位置
	D3DXVECTOR3 m_SetPosition;				//位置
	int m_ntime;							// タイマーの値
	int m_ns;								// 秒
	int m_min;								// 分
	bool m_bTime;							// エンドかどうか確認
	static int m_nTime;
};

#endif