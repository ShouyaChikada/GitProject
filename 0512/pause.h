//=================================================
//
//	pause.cpp
// 
// Author:ãﬂìc èÆñÁ
//
//=================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"
#include "object2D.h"


class CPause :	public CObject2D
{
public:

	CPause(int nPriolity = 16);
	~CPause();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTex(float fX, float fY);
	static CPause* Create(D3DXVECTOR3 pos,D3DXCOLOR col,float fX,float fY, const char* aName);
private:
	int m_nIdx;
	const char* m_aName;
};

#endif