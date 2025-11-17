//=================================================
//
//	block.h
// 
// Author:近田 尚也
//
//=================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"
#include "objectx.h"
#include "object.h"

//マクロ
#define HALF (0.5f)					// 半分の値

class CBlock :public CObjectX
{
public:
	//***************************
	// ブロックの種類の列挙型宣言
	//***************************
	typedef enum
	{
		TYPE_0 = 0,	//地面
		TYPE_1,		//ゴール 1
		TYPE_2,		//チュートリアル 2
		TYPE_3,		//チュートリアル1 3
		TYPE_4,		//鍵穴 4
		TYPE_MAX,
	}TYPE;

	CBlock(int nPriority = 7);
	~CBlock();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBlock* Create(const char* FileName,D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	bool Collision(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3* move, D3DXVECTOR3* size);
	//bool Collision(void);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	TYPE m_type;
	D3DXVECTOR3 m_Vtxmax;
	D3DXVECTOR3 m_Vtxmin;
	D3DXVECTOR3 m_size;
	bool m_bLanding;
	int m_nIdx;
};

#endif