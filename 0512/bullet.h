//=================================================
//
//	bullet.h
// 
// Author:近田 尚也
//
//=================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "object2D.h"

//マクロ
#define BULLET_WIDTH (60.0f)	//弾の横のサイズ
#define BULLET_HEIGHT (60.0f)	//弾の縦のサイズ
#define MAX_BULLET (128)

//クラス設計
class CBullet:public CObject2D 
{
public:

	CBullet();
	~CBullet();
	HRESULT Init(D3DXVECTOR3 Pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	bool CollisionEnemy(D3DXVECTOR3 pos);

private:

	D3DXVECTOR3 m_pos;						// 弾の位置
	D3DXVECTOR3 m_rot;						// 弾の向き
	D3DXVECTOR3 m_move;						// 弾の移動
	int m_lifetime;							// 弾の寿命
};

#endif