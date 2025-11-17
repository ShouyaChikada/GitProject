//=================================================
//
//	UIManager.h
// 
//	Author:ãﬂìcèÆñÁ
//
//=================================================
#ifndef _UIMANAGER_H_
#define _UIMANAGER_H_

#include "main.h"

class CUIManager
{
public:
	CUIManager();
	~CUIManager();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
};

#endif