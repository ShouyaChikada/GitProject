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
	static CObject* getobject(void);
	static CTextureManager* GetTexManager(void);

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

};
#endif
