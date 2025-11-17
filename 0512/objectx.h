//=================================================
//
// ObjectX.h
// 
// Author:近田 尚也
//
//=================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "main.h"
#include "object.h"
#include "model.h"

#define MAX_LOAD (128)
class CObjectX :public CObject
{
public:
	CObjectX(int nPriolty = 3);
	~CObjectX();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectX* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* txt);

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetXfile(const char* txt) { m_txt = txt; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	LPD3DXMESH GetMesh(void);

private:
	int* m_pTexture;								// テクスチャのポインタ
	LPD3DXMESH m_pMesh;		// メッシュのポインタ
	LPD3DXBUFFER m_pBuffMat;	// マテリアルのポインタ
	DWORD m_dwNumMat;			// マテリアル数
	D3DXMATRIX m_mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3 m_SetPosition;			//位置
	D3DXVECTOR3 m_rot;
    D3DXVECTOR3 m_pos;
	CModel* m_pModel;
	static const char* m_txt;
	int m_nIdx[MAX_LOAD];
	D3DXQUATERNION m_Quat;						// クォータニオン
	D3DXVECTOR3 m_VecAxis;						// 回転軸
	D3DXVECTOR3 m_VtxMax;						// 最大値
	D3DXVECTOR3 m_VtxMin;						// 最小値
	D3DXVECTOR3 m_Size;							// サイズ


};
#endif
