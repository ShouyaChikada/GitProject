//=================================================
//
// [rockmanager.h]
// Author:chikada shouya
//
//=================================================
#ifndef _ROCKMANAGER_H_
#define _ROCKMANAGER_H_

#include "main.h"
#include "cmeteorock.h"
#include "meteopillar.h"

#define MAX_ROCK (32)

class CRockManager
{
public:
	CRockManager();
	~CRockManager();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ゲッター
	static CMeteoRock** GetRock(void) { return &m_pRock[0];}
	static CMeteoPillar** GetPillar(void) { return &m_pPillar[0]; }

private:
	static CMeteoRock* m_pRock[MAX_ROCK];		// 隕石(塵)のポインタ
	static CMeteoPillar* m_pPillar[MAX_ROCK];	// 隕石(柱)のポインタ
	bool m_bCreate;
	bool m_bLeave;
	bool m_bStop;
	int m_nCntCreate;
	int m_nCntTime;

};
#endif