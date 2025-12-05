//=================================================
//
// [enemy.h]
// Author:chikada shouya
//
//=================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "object.h"
#include "objectx.h"
#include "shadows.h"
#include "model.h"
#include "motion.h"

//マクロ
#define PLAYER_WIDTH (100.0f)	//幅
#define PLAYER_HEIGHT (200.0f)	//高さ
#define MAX_PSPEED (15.0f)
#define MAX_EMODEL (8)

class CEnemy :public CObject
{
public:

	CEnemy(int nPriority = 5);
	~CEnemy();
	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void MoveInput(void);
	// ゲッター
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRotDest(void) { return m_rotDest; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
	D3DXVECTOR3 GetSize(void) { return m_size; }

private:
	D3DXVECTOR3 m_pos;				// 位置
	D3DXVECTOR3 m_posOld;			// 目的の位置
	D3DXVECTOR3 m_move;				// 移動
	D3DXVECTOR3 m_rot;				// 向き
	D3DXVECTOR3 m_rotDest;			// 目的の向き
	D3DXVECTOR3 m_size;				// サイズ
	D3DXMATRIX m_mtxWorld;			// ワールドマトリックス
	float m_Diff;					// 差分
	CModel* m_apModel[MAX_EMODEL];	//モデルのポインタ
	CMotion* m_pMotion;				// モーションポインタ
	bool m_bJump;					// ジャンプ判定
	bool m_bLeave;					// 生存確認
	int m_nCreate;
};

#endif