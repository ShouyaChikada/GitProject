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
#include "object3D.h"
#include "objectx.h"
#include "model.h"
#include "meshfield.h"
#include "object.h"
#include "shadows.h"
#include "scene.h"
#include "fade.h"
#include "jimen.h"
#include "timer.h"
#include "pausemanager.h"
#include "blockmanager.h"

class CGame :public CScene
{
public:
	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ゲッター
	static CObject3D* GetObj3D(void) { return m_pObj3D; }
	static CObjectX* GetObjX(void) { return m_pObjX; }
	static CMeshField* GetMeshField(void) { return m_pMeshField; }
	static CPlayer* GetPlayer(void) { return m_pPlayer;}
	static CShadowS* GetShadowS(void) { return m_pShadowS; }
	static CGrand* GetGrand(void) { return m_pGrand; }
	static CTimer* GetTime(void) { return m_pTime; }
	static CPauseManager* GetPauseManager(void) {return m_pPauseManager; }
	static bool GetCheck(void) { return m_bCheck; }
	static CModel** GetModel1(void) { return &m_pModel1[0]; }
	static CBlockManager* GetBlockManager(void){ return m_pBlockManager; }

private:
	static CPlayer* m_pPlayer;					// プレイヤーのポインタ
	static CObject3D* m_pObj3D;					// オブジェクト3Dのポインタ
	static CObjectX* m_pObjX;					// オブジェクトXのポインタ
	static CMeshField* m_pMeshField;			// メッシュフィールドのポインタ
	static CShadowS* m_pShadowS;				// シャドウへのポインタ
	static CGrand* m_pGrand;					// 地面へのポインタ
	static CTimer* m_pTime;						// タイムのポインタ
	static CPauseManager* m_pPauseManager;		// ポーズマネージャーのポインタ
	static CModel* m_pModel1[MAX_HMODEL];		// モデルのポインタ
	static CBlockManager* m_pBlockManager;		// ブロックマネージャーのポインタ
	static bool m_bCheck;						// ゴール判定
};

#endif

