//=================================================
//
// [model.h]
// Author:chikada shouya
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
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CModel* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, std::string Path);

	// ゲッター
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }
	static D3DXVECTOR3 GetSize(void) { return m_Size; }

	// セッター
	void SetParent(CModel* pModel) { m_pParent = pModel; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void SetPosOld(D3DXVECTOR3 PosOld) { m_posOld = PosOld; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
	void SetMove(D3DXVECTOR3 Move) { m_move = Move; }
	void SetQuaternion(D3DXQUATERNION quat) { m_Quat = quat; }
	void SetVecAxis(D3DXVECTOR3 VecAxis) { m_VecAxis = VecAxis; }
	void SetValueRot(float fValueRot) { m_fValueRot = fValueRot; }
	void SetPosX(float posX) { m_pos.x = posX; };
	void SetIdx(std::string Path);

private:

	D3DXVECTOR3 m_pos;				// 位置
	D3DXVECTOR3 m_posOld;			// 前の位置
	D3DXVECTOR3 m_rot;				// 回転
	D3DXVECTOR3 m_move;				// 移動
	D3DXVECTOR3 m_VtxMax;			// 頂点最大値
	D3DXVECTOR3 m_VtxMin;			// 頂点最小値
	D3DXQUATERNION m_Quat;			// クォータニオン
	D3DXVECTOR3 m_VecAxis;			// 回転軸
	static D3DXVECTOR3 m_Size;		// サイズ
	D3DXMATRIX m_mtxWorld;			// ワールドマトリックス
	D3DXMATRIX m_mtxRot;			// ワールドマトリックス
	CModel* m_pParent;				//親モデルのポインタ
	float m_fValueRot;				// 回転角(回転量)
	int m_nIdx;						// モデルへのインデックス
};
#endif