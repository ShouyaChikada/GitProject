//=================================================
//
//	tutorial.h
// 
// Author:近田 尚也
//
//=================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "scene.h"
#include "player.h"
#include "blockmanager.h"
#include "gimmickmanager.h"
#include "meshfield.h"
#include "jimen.h"
#include "humanmanager.h"
#include "baseUI.h"

class CTutorial : public CScene
{
public:
	CTutorial();
	~CTutorial();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer* GetPlayer(void) { return m_pPlayer; }
	static CGrand* GetGrand(void) { return m_pGrand; }
	static CMeshField* GetMeshGrand(void) { return m_pMeshField; }
	static CGimmickManager* GetGimmickManager(void) { return m_pGimmickManager; }
	static CBlockManager* GetBlockManager(void) { return m_pBlockManager; }
	static CHumManager* GetHumanManager(void) { return m_pHumanManager; }
	static CBaseUI* GetBaseUI(void) { return m_pBaseUI; }
	static CMotion* GetMotion1(void);
	static CModel** GetModel1(void);
	static bool GetCheck(void) { return m_bCheck; }

private:
	static CPlayer* m_pPlayer;
	static CGrand* m_pGrand;
	static CMeshField* m_pMeshField;
	static CGimmickManager* m_pGimmickManager;
	static CBlockManager* m_pBlockManager;
	static CHumManager* m_pHumanManager;
	static CBaseUI* m_pBaseUI;
	static CModel* m_pModel1[MAX_HMODEL];		// モデルのポインタ
	static CMotion* m_pMotion1;					// モーションのポインタ
	static bool m_bCheck;
};
#endif