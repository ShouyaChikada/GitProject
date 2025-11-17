//=================================================
//
//	enemy.h
// 
// Author:近田 尚也
//
//=================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "object2D.h"

//マクロ
#define NUM_ENEMY (10)				//敵の最大数

//クラス
class CEnemy :public CObject2D
{
public:
	// 敵を種類
	typedef enum
	{
		TYPE_BOSS = 0,
		TYPE_CAT,
		TYPE_RED,
		TYPE_YELLOW,
		TYPE_NYORO,
		TYPE_MAX
	}TYPE;

	CEnemy();
	~CEnemy();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float SizeX,float SizeY, TYPE type);

private:

	D3DXVECTOR3 m_pos;									//位置
	D3DXVECTOR3 m_move;									//移動
	D3DXVECTOR3 m_rot;									//向き
	static float m_SizeX;								//横
	static float m_SizeY;								//縦
	int m_nCnt;
};
#endif