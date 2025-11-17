//=================================================
//
//	Gauge.h
// 
//	Author:近田尚也
//
//=================================================
#ifndef _CGAUGE_H_
#define _CGAUGE_H_

#include "object2D.h"
#include "baseUI.h"

class CGauge : public CObject2D
{
public:
	CGauge(int nPriolity = 15);
	~CGauge();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	void SetGageLength(const int nMaxLife, const int nCurrentLife, float fValue, float Height); // 最大の長さ、今の長さ、倍率、高さ
	void FSetGageLength(float fMax, float fCurrent, float fMaxWidth, float fHeight);			// 最大値、現在の値、最大の横幅、高さ

	static CGauge* Create(D3DXVECTOR3 pos,const char* aTxt,D3DXCOLOR col);

private:
	CBaseUI* m_pBaseUI;
	int m_nIdx;
	float m_fCnt;
	float m_fCnt1;
	const char* m_aName;
	//D3DXCOLOR m_col;
};

#endif