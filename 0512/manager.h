//=================================================
//
//	manager.h
// 
//	Author:近田尚也
//
//=================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "renderer.h"
#include "input.h"
#include "scene.h"
#include "fade.h"
#include "debugproc.h"
#include "camera.h"
#include "light.h"
#include "title.h"
#include "texturemanager.h"
#include "motion.h"

class CManager
{
public:
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CCamera* GetCamera(void);
	static CLight* GetLight(void);
	static CDebugProc* GetDebugProc(void);
	static CRenderer* GetRenderer(void);
	static CInputKeyboard* GetKeyboard(void);
	static CInputJoypad* GetJoypad(void);
	static CInputMouse* GetMouse(void);
	static void SetMode(CScene* pNewScene);
	static CScene::MODE GetMode(void);
	static CObject* getobject(void);
	static CFade* GetFade(void);
	static CTextureManager* GetTexManager(void);
	static CScene* GetScene(void) { return m_pScene; }
	static CMotion* GetMotion(void);
	static CMotion* GetMotion1(void);
	static CModel** GetModel(void);
	static CModel** GetModel1(void);

private:
	static CRenderer* m_pRenderer;				// レンダラーへのポインタ
	static CInputKeyboard* m_pInputKeyboard;	// キーボードへのポインタ
	static CInputJoypad* m_pInputJoypad;		// パッドへのポインタ
	static CInputMouse* m_pInputMouse;			// マウスのポインタ
	static CObject* m_pObject;					// オブジェクトのポインタ
	static CScene* m_pScene;					// シーンへのポインタ
	static CFade* m_pFade;						// フェードへのポインタ
	static CDebugProc* m_pDebugProc;			// デバッグフォントのポインタ
	static CCamera* m_pCamera;					// カメラのポインタ
	static CLight* m_pLight;					// ライトのポインタ
	static CTextureManager* m_pTexManager;		// テクスチャマネージャのポインタ
	static CMotion* m_pMotion;					// モーションのポインタ
	static CMotion* m_pMotion1;					// モーションのポインタ
	static CModel* m_pModel[MAX_PMODEL];					// モデルのポインタ
	static CModel* m_pModel1[MAX_HMODEL];					// モデルのポインタ

};
#endif
