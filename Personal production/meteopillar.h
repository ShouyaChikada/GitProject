//=================================================
//
// [meteopillar.h]	隕石(柱)のヘッダー
// Author:chikada shouya
//
//=================================================
#ifndef _CMETEOPILLAR_H_
#define _CMETEOPILLAR_H_

#include "rock.h"

class CMeteoPillar : public CRock
{
public:
	typedef enum
	{
		ROT_NONE = 0,
		ROT_X,
		ROT_Y,
		ROT_Z,
		ROT_MAX,
	}ROT;

	CMeteoPillar();
	~CMeteoPillar();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMeteoPillar* Create(D3DXVECTOR3 pos, ROT rot);

	void MovePillar(void);

	// セッター
	void SetRotSize(ROT Rot);

	// ゲッター
	bool GetDeath(void) { return m_bDeath; }

private:
	bool m_bChange[4];	// 柱の4方向
	bool m_bDeath;		// 死の判定
};

#endif

