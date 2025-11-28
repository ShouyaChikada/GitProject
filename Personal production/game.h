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

class CGame :public CScene
{
public:
	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CObject3D* GetObject3D(void);
	static CObjectX* GetObjectX(void);
	static CMeshField* GetMeshField(void);
	static CPlayer* GetPlayer(void);
	static CShadowS* GetShadowS(void);
	static CGrand* GetGrand(void);
	static CTimer* GetTime(void);
	static CPauseManager* GetPauseManager(void) {return m_pPauseManager; }
	static bool GetCheck(void) { return m_bCheck; }
	static CModel** GetModel1(void);

private:
	static CPlayer* m_pPlayer;					// プレイヤーのポインタ
	static CObject3D* m_pObject3D;				// オブジェクト3Dのポインタ
	static CObjectX* m_pObjectX;				// オブジェクトXのポインタ
	static CMeshField* m_pMeshField;			// メッシュフィールドのポインタ
	static CShadowS* m_pShadowS;				// シャドウへのポインタ
	static CGrand* m_pGrand;					// 地面へのポインタ
	static CTimer* m_pTime;						// タイムのポインタ
	static CPauseManager* m_pPauseManager;
	static CModel* m_pModel1[MAX_HMODEL];		// モデルのポインタ
	static bool m_bCheck;
};

#endif

