//=================================================
//
//	explosion.h
// 
//	Author:ãﬂìcèÆñÁ
//
//=================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "object2D.h"

class CExplosion:public CObject2D
{
public:
	CExplosion();
	~CExplosion();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CExplosion* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	D3DXVECTOR3 m_pos;	//à íu
	int m_nCounterAnim;
	int m_nPatternAnim;
};

#endif
