//================================================
// 
// MultipleBackGround.h
// 
// Author:近田 尚也
//
//================================================
#ifndef _MBG_H_
#define _MBG_H_

#include "main.h"
#include "object.h"
#include "object2D.h"

class CMbg :public CObject
{
public:
	CMbg();
	~CMbg();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	CMbg* Create(D3DXVECTOR3 pos);
	static CObject2D* GetObject2D(void);

private:
	static CObject2D* pObject2D;	//オブジェクト2Dのポインタ
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_rot;	//回転
};

#endif