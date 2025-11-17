//=================================================
//
//	HumanMnager.h
// 
//	Author:ãﬂìcèÆñÁ
//
//=================================================
#ifndef _HUMANMANAGER_H_
#define _HUMANMANAGER_H_

#include "main.h"
#include "human.h"
#define MAX_HUMAN (2)
class CHumManager
{
public:

	CHumManager();
	~CHumManager();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	CHuman* m_pHuman[MAX_HUMAN];
};

#endif
