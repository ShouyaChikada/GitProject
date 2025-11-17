//=================================================
//
//	bg.h
// 
// Author:‹ß“c ®–ç
//
//=================================================
#ifndef _BG_H_
#define _BG_H_

#include "main.h"
#include "object2D.h"

class CBg :public CObject2D
{
public:

	CBg();
	~CBg();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBg* create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

	D3DXVECTOR3 m_pos;	//’e‚ÌˆÊ’u
	D3DXVECTOR3 m_rot;	//’e‚ÌŒü‚«
	D3DXVECTOR3 m_move;	//’e‚ÌˆÚ“®
};
#endif