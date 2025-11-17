//=================================================
//
//	titlemanager.h
// 
//	Author:ãﬂìcèÆñÁ
//
//=================================================
#ifndef _TITLEMANAGER_H_
#define _TITLEMANAGER_H_

#include "object2D.h"

class CTitleManager : public CObject2D
{
public:
	CTitleManager(int nPriolity = 19);
	~CTitleManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTxt(const char* aName) { m_aName = aName; }
	static CTitleManager* Create(D3DXVECTOR3 pos,const char* aName);

private:
	D3DXVECTOR3 m_pos;
	int m_nIdx;
	const char* m_aName;
};


#endif