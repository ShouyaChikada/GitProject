//=================================================
//
//	game.h
// 
// Author:近田 尚也
//
//=================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "scene.h"
#include "player.h"
#include "bullet.h"
#include "score.h"
#include "object3D.h"
#include "billboard.h"
#include "objectx.h"
#include "motion.h"
#include "model.h"
#include "meshfield.h"
#include "object.h"
#include "block.h"
#include "blockmanager.h"
#include "shadows.h"
#include "scene.h"
#include "fade.h"
#include "jimen.h"
#include "gimmickmanager.h"
#include "humanmanager.h"
#include "time.h"
#include "pausemanager.h"

class CGame :public CScene
{
public:
	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScore* GetScore(void);
	static CObject3D* GetObject3D(void);
	static CBillboard* GetBillboard(void);
	static CObjectX* GetObjectX(void);
	static CMeshField* GetMeshField(void);
	static CBlockManager* GetBlockManager(void);
	static CPlayer* GetPlayer(void);
	static CShadowS* GetShadowS(void);
	static CGrand* GetGrand(void);
	static CGimmickManager* GetGimmickManager(void);
	static CHumManager* GetHumManamger(void);
	static CTime* GetTime(void);
	static CPauseManager* GetPauseManager(void) {return m_pPauseManager; }
	static bool GetCheck(void) { return m_bCheck; }
	static CModel** GetModel1(void);
	static CMotion* GetMotion1(void);

private:
	static CPlayer* m_pPlayer;					// プレイヤーのポインタ
	static CScore* m_pScore;					// スコアのポインタ
	static CObject3D* m_pObject3D;				// オブジェクト3Dのポインタ
	static CBillboard* m_pBillboard;			// ビルボードのポインタ
	static CObjectX* m_pObjectX;				// オブジェクトXのポインタ
	static CMeshField* m_pMeshField;			// メッシュフィールドのポインタ
	static CBlockManager* m_pBlockManager;		// ブロックマネージャーへのポインタ
	static CShadowS* m_pShadowS;				// シャドウへのポインタ
	static CGrand* m_pGrand;					// 地面へのポインタ
	static CGimmickManager* m_pGimmickManager;	// ギミックマネージャーのポインタ
	static CHumManager* m_pHumManager;			// ヒューマンマネージャーのポインタ
	static CTime* m_pTime;						// タイムのポインタ
	static CPauseManager* m_pPauseManager;
	static CMotion* m_pMotion1;					// モーションのポインタ
	static CModel* m_pModel1[MAX_HMODEL];		// モデルのポインタ
	static bool m_bCheck;
};

#endif

