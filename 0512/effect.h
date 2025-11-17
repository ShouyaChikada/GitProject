//=================================================
//
//	effect.h
// 
// Author:近田 尚也
//
//=================================================
#ifndef EFFECT_H_
#define EFFECT_H_

#include "main.h"
#include "billboard.h"

#define MAX_EFFECT (128)

class CEffect :public CBillboard
{
public:
	CEffect();
	~CEffect();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffect* Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife);

private:
	int m_nIdx;
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_move; //移動量
	D3DXCOLOR m_col;	//移動量
	int m_nLife;			//寿命
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;

};
#endif