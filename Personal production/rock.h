//=================================================
//
// [rock.h]
// Author:chikada shouya
//
//=================================================
#ifndef _ROCK_H_
#define _ROCK_H_

#include "main.h"
#include "objectx.h"
#include "shadows.h"
#include <string>

// マクロ定義
#define MAX_SPEED (15.0f)	// 移動の速さ
#define MAX_ROT (0.175f)	// クオータニオンの回転値
#define HALF (0.5f)			// 半分の値

// クラス
class CRock :public CObjectX
{
public:
	CRock(int nPriolty = 3);
	~CRock();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRock* Create(D3DXVECTOR3 pos, ROT Rot, CObjectX::ROT rotation, TYPE type);

	void Collision(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3* move, D3DXVECTOR3* size);
	void MoveInput(void);

	// ゲッター
	D3DXVECTOR3 GetMove(void) { return m_move; }

	// セッター
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

private:
	D3DXVECTOR3 m_move;			// 移動量
	D3DXVECTOR3 m_CollisionPos;	//　当たり判定用位置
	D3DXVECTOR3 m_CollisionSize;//	当たり判定用サイズ
};
#endif
