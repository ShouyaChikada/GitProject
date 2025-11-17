//=================================================
//
// [jimen.h]
// Author:chikada shouya
//
//=================================================

#ifndef _JIMEN_H_
#define _JIMEN_H_

#include "main.h"
#include "object.h"

//マクロ定義
#define GRAND_X_BLOCK (10)		//X方向のブロック数
#define GRAND_Z_BLOCK (10)		//Z方向のブロック数
#define GRAND_VERTEX_NUM ((GRAND_X_BLOCK + 1) * (GRAND_Z_BLOCK + 1))		//頂点数
#define GRAND_INDEX_NUM (GRAND_X_BLOCK * GRAND_Z_BLOCK * 2 + (GRAND_Z_BLOCK - 1) * 12)	//ポリゴン数
#define GRAND_PRIMITVE_NUM (GRAND_X_BLOCK * GRAND_Z_BLOCK * 2 + (GRAND_Z_BLOCK + (GRAND_Z_BLOCK - 1) * 4)		//インデックス数

class CGrand :public CObject
{
public:
	CGrand(int nPriolity = 2); 
	~CGrand();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static	CGrand* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);

private:
	D3DXVECTOR3 m_pos;							//位置
	D3DXVECTOR3 m_rot;							//向き
	D3DXMATRIX m_mtxWorld;						//ワールドマトリックス
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;			//インデックスバッファへのポインタ
	int m_nIdx;

};

#endif
