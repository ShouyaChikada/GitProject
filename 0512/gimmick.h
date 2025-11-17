//=================================================
//
//	gimmick.h
// 
//	Author:近田尚也
//
//=================================================
#ifndef GIMMICK_H_
#define GIMMICK_H_

#include "main.h"
#include "objectx.h"
#include "meshcylinder.h"
#include "gauge.h"
#include "baseUI.h"

class CGimmick :public CObjectX
{
public:

	//ギミックの種類
	typedef enum
	{
		TYPE_METEORITE,	// 隕石
		TYPE_THUNDER,	// 木
		TYPE_TREE,		// 雷
		TYPE_MAX,
	}TYPE;


	CGimmick(int nPriority = 6);
	~CGimmick();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGimmick* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type);
	bool Collision(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3* move, D3DXVECTOR3* size);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	static bool GetUse(void) { return m_bUse; }
	TYPE GetType(void) { return m_type; }
	static CMeshCylinder* GetMeshCylinder(void) { return m_pMeshCylinder; }
	static CGauge* GetGauge(void) { return m_pGauge; }
	static CBaseUI* GetBaseUI(void) { return m_pBaseUI; }
private:

	const char* GIMMICK_FILE[TYPE_MAX] =
	{
		"data\\MODEL\\GIMMICK\\inseki.x",		//通常
		"data\\MODEL\\GIMMICK\\kaminari.x",		//ゴール
		"data\\MODEL\\GIMMICK\\tutorial.x",		//チュートリアル
	};

	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_rot;		// 向き
	D3DXVECTOR3 m_move;
	TYPE m_type;			// タイプ
	D3DXVECTOR3 m_Vtxmax;	// 最頂点
	D3DXVECTOR3 m_Vtxmin;	// 一番小さい頂点
	D3DXVECTOR3 m_size;		// サイズ
	bool m_bLanding;		// 乗っているかどうか
	static bool m_bUse;			// 使っているかどうか

	static CMeshCylinder* m_pMeshCylinder;	// シリンダーのポインタ
	static CGauge* m_pGauge;	//ゲージへのポインタ
	static CBaseUI* m_pBaseUI;
	float m_fAddCharge;			// ゲージの加算量

};

#endif