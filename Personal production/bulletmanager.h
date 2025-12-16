//=================================================
//
// [bulletmanager.h]
// Author:chikada shouya
//
//=================================================
#ifndef _BULLETMANAGER_H_
#define _BULLETMANAGER_H_

#include "main.h"
#include "bullet.h"

#define MAX_BULLET (128)

class CBulletManager
{
public:
	CBulletManager();
	~CBulletManager();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ゲッター
	static CBullet** GetBullet(void) { return &m_pBullet[0]; }

private:
	static CBullet* m_pBullet[MAX_BULLET];	// ブレットのポインタ
};

#endif