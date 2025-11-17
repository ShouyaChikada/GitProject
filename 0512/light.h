//=================================================
//
//	light.h
// 
// Author:近田 尚也
//
//=================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

//マクロ
#define MAX_LIGHT (5)

class CLight
{
public:
	CLight();
	~CLight();
	//プロトタイプ宣言
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
private:
	static D3DLIGHT9 m_light[MAX_LIGHT];	//ライト情報
};
#endif
