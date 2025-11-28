//=================================================
//
// [renderer.h]
// Author:chikada shouya
//
//=================================================

#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

//マクロ
#define NUM_TEXTURE (2)

class CRenderer
{
public:

	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	void SetupVertexFog(DWORD Color, DWORD Mode, BOOL UseRange, FLOAT Density);

	// ゲッター
	LPDIRECT3DDEVICE9 GetDevice(void);
	LPDIRECT3DTEXTURE9 GetTextureMT(void);

	// ワイヤーフレーム用関数
	void onWireFrame(void);
	void offWireFrame(void);

	// ターゲットチェンジ
	void ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU);


private:
	LPDIRECT3D9 m_pD3D;								//Direct3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 m_pD3DDevice;					//Direct3Dデバイスへのポインタ
	static int m_nCountFPS;							//FPSの描画用変数
	LPDIRECT3DTEXTURE9 m_apTextureMT[NUM_TEXTURE];	//レンダリング用テクスチャ
	LPDIRECT3DSURFACE9 m_apRenderMT[NUM_TEXTURE];	//テクスチャレンダリング用インターフェース
	LPDIRECT3DSURFACE9 m_pZBuffMT;					//テクスチャレンダリング用Zバッファ
	D3DVIEWPORT9 m_pViewportMT;						//テクスチャレンダリング用ビューポート
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMT;			//フィードバック用ポリゴンの頂点バッファ
};
#endif
