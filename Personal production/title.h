//=================================================
//
//	title.h
// 
// Author:ãﬂìc èÆñÁ
//
//=================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "titlemanager.h"
#include "scene.h"

#define MAX_TITLE (3)
class CTitle : public CScene
{
public:
	CTitle();
	~CTitle();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CTitleManager* m_pTitleManager[3];
	float m_aPosTexU[MAX_TITLE];
};

#endif
