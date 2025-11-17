//=================================================
//
//	fade.h
// 
// Author:近田 尚也
//
//=================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "object2D.h"
#include "scene.h"

class CFade
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;//頂点座標
		float rhw;		//座用変換用係数(1.0fで固定)
		D3DCOLOR col;	//頂点カラー
		D3DXVECTOR2 tex;//テクスチャ座標

	}VERTEX_2D;

	//フェードの状態
	typedef enum
	{
		FADE_NONE = 0,	//何もしていない状態
		FADE_IN,		//フェードイン状態
		FADE_OUT,		//フェードアウト状態
		FADE_MAX
	}FADE;

	CFade();
	~CFade();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetFade(CScene* pScene);
	FADE GetFadeState(void);

	static CFade* Create(void);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファ
	FADE m_Fade;						//フェイド
	D3DXCOLOR m_col;					//カラー
	CScene* m_pScene;
};

#endif