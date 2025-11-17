//=================================================
//
//	gimmickmanager.h
// 
//	Author:近田尚也
//
//=================================================
#ifndef GIMMICKMANAGER_H_
#define GIMMICKMANAGER_H_

#include "main.h"
#include "gimmick.h"
#include "particle.h"
#include "baseUI.h"
#include "gauge.h"

#define MAX_COUNT (2)
#define MAX_GIMMICK (128)

class CGimmickManager
{
public:

	CGimmickManager();
	~CGimmickManager();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGimmick** GetGimmick(void) { return &m_pGimmick[0]; }
	static bool GetRange(void) { return m_bRange; }
	static bool GetPush(void) { return m_bPush; }
	static CParticle* GetParticle(void) { return m_pParticle; }
	static int GetCntGimmick(void) { return m_nCntGimmick; }
	static bool GetbCheck(void) { return m_bCheck; }

private:
	static bool m_bRange;						// 範囲に入っているかどうか
	static bool m_bPush;						// ボタンを押しているかどうか
	static bool m_bCheck;						// 作業を終えているかどうか
	static CGimmick* m_pGimmick[MAX_GIMMICK];	// ギミックのポインタ
	static CParticle* m_pParticle;
	static int m_nCntGimmick;					// 直したor破壊したギミックのカウント
	bool m_bUse;
	bool m_bTime;
	int m_nCnt[MAX_COUNT];
	int m_nScore;								// スコア用の関数

};

#endif