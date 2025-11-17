//=================================================
//
// [shadowS.h]
// Author:chikada shouya
//
//=================================================

#ifndef _SHADOWS_H_
#define _SHADOWS_H_

#include "main.h"
#include "objectx.h"

class CShadowS: public CObjectX
{
public:

	CShadowS(int nPriority = 19);
	~CShadowS();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	static CShadowS* Create(std::string FilePath);
private:
	D3DXMATRIX m_mtxWorld;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	bool m_bLook;

};
#endif
