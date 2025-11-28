//=================================================
//
//	ResultManager.h
// 
//	Author:ãﬂìcèÆñÁ
//
//=================================================
#ifndef _RESULTMANAGER_H_
#define _RESULTMANAGER_H_

#include "object2D.h"
class CResultManager : public CObject2D
{
public:
	CResultManager(int nPriolity = 13);
	~CResultManager();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CResultManager* Create(D3DXVECTOR3 pos, const char* aName);
	void SetTxt(const char* aName) { m_aName = aName; }
private:
	D3DXVECTOR3 m_pos;
	int m_nIdx;
	const char* m_aName;
};

#endif