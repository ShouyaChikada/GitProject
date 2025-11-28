//=================================================
//
//	[manager.h]
//	Author:chikada shouya
//
//=================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "renderer.h"
#include "object.h"
#include "objectx.h"
#include "input.h"
#include "jimen.h"
#include "debugproc.h"
#include "camera.h"
#include "light.h"
#include "texturemanager.h"
#include "fade.h"
#include "scene.h"

class CManager
{
public:
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ゲッター
	static CCamera* GetCamera(void) { return m_pCamera; }
	static CLight* GetLight(void) { return m_pLight; }
	static CDebugProc* GetDebugProc(void) { return m_pDebugProc; }
	static CRenderer* GetRenderer(void) { return m_pRenderer; }
	static CInputKeyboard* GetKeyboard(void) { return m_pInputKeyboard; }
	static CInputJoypad* GetJoypad(void) { return m_pInputJoypad; }
	static CInputMouse* GetMouse(void) { return m_pInputMouse; }
	static CObject* getobject(void) { return m_pObject; }
	static CTextureManager* GetTexManager(void) { return m_pTexManager; }
	static CFade* GetFade(void) { return m_pFade; }
	static CScene* GetScene(void) { return m_pScene; }

	// セッター
	static void SetMode(CScene* pNewScene);

private:
	static CRenderer* m_pRenderer;				// レンダラーへのポインタ
	static CInputKeyboard* m_pInputKeyboard;	// キーボードへのポインタ
	static CInputJoypad* m_pInputJoypad;		// パッドへのポインタ
	static CInputMouse* m_pInputMouse;			// マウスのポインタ
	static CObject* m_pObject;					// オブジェクトのポインタ
	static CDebugProc* m_pDebugProc;			// デバッグフォントのポインタ
	static CCamera* m_pCamera;					// カメラのポインタ
	static CLight* m_pLight;					// ライトのポインタ
	static CTextureManager* m_pTexManager;		// テクスチャマネージャのポインタ
	static CFade* m_pFade;						// フェードへのポインタ
	static CScene* m_pScene;					// シーンへのポインタ

};
#endif
