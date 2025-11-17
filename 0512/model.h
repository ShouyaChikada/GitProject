//=================================================
//
//	model.h
// 
// Author:近田 尚也
//
//=================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

class CModel
{
public:

	CModel();
	~CModel();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* txt);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CModel* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* txt);
	void SetParent(CModel* pModel);
	D3DXMATRIX GetMtxWorld(void);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetPosOld(D3DXVECTOR3 PosOld);
	void SetSize(D3DXVECTOR3 Size);
	void SetMove(D3DXVECTOR3 Move);
	//void SetX(const char* txt);
	void SetPosX(float posX) { m_pos.x = posX; };
	static D3DXVECTOR3 GetSize(void);

private:

	int*  m_pTexture;								// テクスチャのポインタ
	D3DXVECTOR3 m_pos;								// 位置
	D3DXVECTOR3 m_posOld;								// 前の位置
	D3DXVECTOR3 m_rot;								// 回転
	D3DXVECTOR3 m_move;								// 移動
	D3DXVECTOR3 m_VtxMax;							// 頂点最大値
	D3DXVECTOR3 m_VtxMin;							// 頂点最小値
	static D3DXVECTOR3 m_Size;						// サイズ
	LPD3DXMESH m_pMesh;								// メッシュのポインタ
	LPD3DXBUFFER m_pBuffMat;						// マテリアルのポインタ
	DWORD m_dwNumMat;								// マテリアル数
	D3DXMATRIX m_mtxWorld;							// ワールドマトリックス
	CModel* m_pParent;								//親モデルのポインタ
};
#endif