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
#include "shadows.h"

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
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetInput(void);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetRotDest(void);
	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetMove(void);
	D3DXVECTOR3 GetPosOld(void);
	D3DXVECTOR3 GetSize(void);
	void SetPosition(D3DXVECTOR3 pos);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャのポインタ
	D3DXVECTOR3 m_pos;						//位置
	D3DXVECTOR3 m_posOld;
	D3DXVECTOR3 m_move;						//移動
	D3DXVECTOR3 m_rot;						//向き
	D3DXVECTOR3 m_rotDest;					//目的の向き
	D3DXVECTOR3 m_SetPosition;
	D3DXVECTOR3 m_size;
	D3DXMATRIX m_mtxWorld;					//マトリックス
	float m_Diff;
	CShadowS* m_pShadowS;
	bool m_bJump;
	bool m_bLeave;
};

#endif