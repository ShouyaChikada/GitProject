//=================================================
//
// [meshcylinder.h]
// Author:chikada shouya
//
//=================================================
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

#include "main.h"
#include "object.h"

#define MESHFIELD_V_BLOCK (1)		//X方向のブロック数
#define MESHFIELD_H_BLOCK (24)		//Z方向のブロック数
#define MESHFIELD_MAX_VTX ((MESHFIELD_V_BLOCK + 1) * (MESHFIELD_H_BLOCK + 1))		//頂点数
#define MESHFIELD_MAX_POLYGON (MESHFIELD_V_BLOCK * MESHFIELD_H_BLOCK * 2 + (MESHFIELD_H_BLOCK - 1) * 2)	//ポリゴン数
#define MESHFIELD_MAX_INDEX (MESHFIELD_MAX_POLYGON + 2/*(MESHFIELD_X_BLOCK + 1) * 2 * MESHFIELD_Z_BLOCK + (MESHFIELD_Z_BLOCK - 1) + 2*/)		//インデックス数

class CMeshCylinder :public CObject
{
public:
	CMeshCylinder(int nPriority = 1);
	~CMeshCylinder();
	//プロトタイプ宣言
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static	CMeshCylinder* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//インデックスバッファへのポインタ
	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_rot;					//向き
	D3DXMATRIX m_mtxWorld;				//ワールドマトリックス
	float m_fRadius;						//半径
	int m_nIdx;
};

#endif
