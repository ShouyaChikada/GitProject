//=================================================
//
//	shadowS.h
// 
//	Author:ãﬂìcèÆñÁ
//
//=================================================

#ifndef _SHADOWS_H_
#define _SHADOWS_H_

#include "main.h"
#include "objectx.h"
#include "object2D.h"

class CShadowS: public CObjectX
{
public:

	CShadowS(int nPriority = 19);
	~CShadowS();
	HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	static CShadowS* Create(const char* txt,D3DXVECTOR3 pos,D3DXVECTOR3 rot);
private:
	CObject2D* m_Obj2D;
	D3DXVECTOR3 m_pos;	//íeÇÃà íu
	D3DXVECTOR3 m_rot;	//íeÇÃå¸Ç´
	D3DXMATRIX m_mtxWorld;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	bool m_bLook;

};
#endif
