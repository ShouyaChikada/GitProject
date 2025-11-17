//=================================================
//
//	billboard.h
// 
//	Author:近田尚也
//
//=================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"
#include "object.h"

//マクロ
#define MAX_BILLBOARD (128)	//ビルボードの最大数

class CBillboard :public CObject
{
public:
	CBillboard(int nPriority = 13);
	~CBillboard();
	//プロトタイプ宣言
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBillboard* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//弾とか出したい場合
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);
	void SetColor(D3DXCOLOR col) { m_col = col; }
	void SetRadius(float fRadius) { m_fRadius = fRadius; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_SetPosition;			//位置
	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_rot;					//向き
	D3DXCOLOR m_col;
	D3DXVECTOR3 m_move;					//移動量
	D3DXVECTOR3 m_dir;					//向き格納
	D3DXMATRIX m_mtxWorld;				//ワールドマトリックス
	bool m_bTest;
	bool m_bUse;
	float m_fRadius;
};
#endif