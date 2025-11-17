//=================================================
//
// [camera.h]
// Author:chikada shouya
//
//=================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
//#include "player.h"

class CInputMouse;

class CCamera
{
public:
	CCamera();
	~CCamera();
	//プロトタイプ宣言
	HRESULT  Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	D3DXVECTOR3 GetRotasion(void);
	D3DXVECTOR3 GetPosV(void);
	D3DXVECTOR3 GetPosR(void);
	D3DXVECTOR3 GetVecU(void);
	void SetFollowing(D3DXVECTOR3 pos,D3DXVECTOR3 rotDest);

	void MouseView(CInputMouse * pMouse);

private:
	D3DXVECTOR3 m_posV;			// 視点
	D3DXVECTOR3 m_posR;			// 注視点
	D3DXVECTOR3 m_vecU;			// 上方向ベクトル
	D3DXVECTOR3 m_rot;			// 向き
	D3DXVECTOR3 m_rotDest;		// 目的の向き
	D3DXVECTOR3 m_posVDest;		// 視点の目的
	D3DXVECTOR3 m_posRDest;		// 注視点の目的
	D3DXVECTOR2 m_move;			// 移動量

	D3DXMATRIX m_mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX m_mtxView;		// ビューマトリックス

	D3DVIEWPORT9 m_viewport;

	float m_fDistance;			// 視点から注視点の距離
	bool m_bFlattery;			// 追従のON/OFF
	bool m_bTPS;				

	//static CPlayer* m_pPlayer;
};

#endif
