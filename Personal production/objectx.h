//=================================================
//
// [ObjectX.h]
// Author:chikada shouya
//
//=================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "main.h"
#include "object.h"
#include <string>

class CObjectX :public CObject
{
public:
	CObjectX(int nPriolty = 3);
	~CObjectX();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CObjectX* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, std::string FilePath, float ValueRot);

	// ゲッター
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetVecAxis(void) { return m_VecAxis; }
	float GetValueRot(void) { return m_fValueRot; }

	// セッター
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetQuaternion(D3DXQUATERNION quat) { m_Quat = quat; }
	void SetVecAxis(D3DXVECTOR3 VecAxis) { m_VecAxis = VecAxis; }
	void SetValueRot(float fValueRot) { m_fValueRot = fValueRot; }
	void SetIdx(std::string Path);

private:
	LPD3DXMESH m_pMesh;							// メッシュのポインタ
	LPD3DXBUFFER m_pBuffMat;					// マテリアルのポインタ
	DWORD m_dwNumMat;							// マテリアル数
	D3DXMATRIX m_mtxWorld;						// ワールドマトリックス
	D3DXMATRIX m_mtxRot;						// ワールドマトリックス
	D3DXVECTOR3 m_rot;							// 向き
	D3DXVECTOR3 m_rotDest;						// 目的の向き
    D3DXVECTOR3 m_pos;							// 位置
	D3DXVECTOR3 m_posOld;						// 目的の位置
	D3DXQUATERNION m_Quat;						// クォータニオン
	D3DXVECTOR3 m_VecAxis;						// 回転軸
	D3DXVECTOR3 m_VtxMax;						// 最大値
	D3DXVECTOR3 m_VtxMin;						// 最小値
	D3DXVECTOR3 m_Size;							// サイズ
	std::string m_FilePath;						// テキスト
	float m_fValueRot;							// 回転角(回転量)
	float m_Diff;								// 差分
	int m_nIdx;									// モデルへのインデックス
	float m_addRot;
};
#endif
