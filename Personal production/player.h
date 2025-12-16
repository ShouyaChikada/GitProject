//=================================================
//
// [player.h]
// Author:chikada shouya
//
//=================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "object.h"
#include "objectx.h"
#include "model.h"
#include "motion.h"

//マクロ
#define PLAYER_WIDTH (100.0f)	//幅
#define PLAYER_HEIGHT (200.0f)	//高さ
#define MAX_PSPEED (15.0f)

class CPlayer :public CObject
{
public:
	typedef enum
	{
		TYPE_MONE = 0,
		TYPE_EXPROSION,
		TYPE_THUMDER,
		TYPE_WINDOW,
		TYPE_WATER,
		TYPE_MAX,
	}TYPE;

	CPlayer(int nPriority = 5);
	~CPlayer();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	void MoveInput(void);
	void CollisionBullet(void);

	// 右左の範囲
	void VectorJudgeR(void);
	void VectorJudgeL(void);
	void VectorJudge(void);

	// セッター
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }

	// 静的関数(セッター)
	static void SetTamesi0(bool bTamesi0) { m_bTamesi0 = bTamesi0; }
	static void SetTamesi1(bool bTamesi1) { m_bTamesi1 = bTamesi1; }

	// ゲッター
	D3DXVECTOR3 GetRotDest(void) { return m_rotDest; }
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
	D3DXVECTOR3 GetSize(void) { return m_size; }

	// 静的関数(ゲッター)
	static D3DXVECTOR3 GetPos(void) { return m_GetPos; }
	static D3DXVECTOR3 GetRot(void) { return m_GetRot; }
	static D3DXVECTOR3 GetRotDestS(void) { return m_GetRotDest; }
	static bool GetTamesi0(void) { return m_bTamesi0; }
	static bool GetTamesi1(void) { return m_bTamesi1; }
	static bool GetTamesi2(void) { return m_bTamesi2; }

private:
	static D3DXVECTOR3 m_GetPos;			// 位置情報の取得用変数
	static D3DXVECTOR3 m_GetRotDest;
	D3DXVECTOR3 m_pos;						// 位置
	D3DXVECTOR3 m_posOld;					// 目的の位置
	D3DXVECTOR3 m_move;						// 移動
	D3DXVECTOR3 m_rot;						// 向き
	static D3DXVECTOR3 m_GetRot;			// 向き情報の取得用変数
	D3DXVECTOR3 m_rotDest;					// 目的の向き
	D3DXVECTOR3 m_size;						// サイズ
	D3DXMATRIX m_mtxWorld;					// ワールドマトリックス
	float m_Diff;							// 差分
	bool m_bLeave;							// 生存フラグ

	CModel* m_apModel[MAX_PMODEL];			// モデルのポインタ
	CMotion* m_pMotion;						// モーションポインタ
	float m_fAddMove;
	float m_fAddLR;
	float m_fAddUD;
	static bool m_bTamesi0;
	static bool m_bTamesi1;
	static bool m_bTamesi2;
};

#endif