//=================================================
//
//	result.h
// 
// Author:ãﬂìc èÆñÁ
//
//=================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "scene.h"
#include "resultmanager.h"

class CResult : public CScene
{
public:
	CResult();
	~CResult();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static bool GetCheck(void) { return m_bCheck; }

private:
	CResultManager* m_pResultManager;
	static bool m_bCheck;

};

#endif

