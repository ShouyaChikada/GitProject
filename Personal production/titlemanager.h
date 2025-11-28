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
#include <string>

class CTitleManager : public CObject2D
{
public:
	CTitleManager(int nPriolity = 19);
	~CTitleManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTxt(std::string aName) { m_aName = aName; }
	static CTitleManager* Create(D3DXVECTOR3 pos, std::string aName);

private:
	D3DXVECTOR3 m_pos;
	int m_nIdx;
	std::string m_aName;
};


#endif