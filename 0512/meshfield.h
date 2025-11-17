//=================================================
//
//	meshfield.h
// 
// Author:近田 尚也
//
//=================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"
#include "object.h"

#define MESHFIELD_V_BLOCK (1)		//X方向のブロック数
#define MESHFIELD_H_BLOCK (24)		//Z方向のブロック数
#define MESHFIELD_MAX_VTX ((MESHFIELD_V_BLOCK + 1) * (MESHFIELD_H_BLOCK + 1))		//頂点数

class CMeshField :public CObject
{
public:
	struct Vertex 
	{
		float x, y, z;  // 座標
		DWORD color;    // 色
	};

	CMeshField(int nPriority = 1);
	~CMeshField();
	//プロトタイプ宣言
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static	CMeshField* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);
	void GenerateSphereVertices(float radius, int slices, int stacks, vector<Vertex>& vertices);
	void RenderSphere(LPDIRECT3DDEVICE9 pDevice,const vector<Vertex>& vertices,int slices, int stacks);

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
