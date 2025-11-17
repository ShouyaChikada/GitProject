//=================================================
//
//	particle.h
// 
// Author:近田 尚也
//
//=================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"
#include "object.h"
#include "effect.h"

//マクロ定義
#define MAX_PARTICLE (128)																//パーティクルの最大数

class CParticle :public CObject
{
public:

	CParticle();
	~CParticle();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CParticle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }


private:
	D3DXVECTOR3 m_pos;	//弾の位置
	D3DXVECTOR3 m_move;	//弾の移動
	D3DXCOLOR m_col;
	int m_nLife;
	int m_nCnt;
};
#endif