//=================================================
//
// [rock.h]
// Author:chikada shouya
//
//=================================================
#ifndef _ROCK_H_
#define _ROCK_H_

#include "main.h"
#include "objectx.h"
#include "shadows.h"
#include <string>

// マクロ定義
#define MAX_SPEED (4.0f)
#define MAX_ROT (0.175f)

// クラス
class CRock :public CObjectX
{
public:
	CRock(int nPriolty = 3);
	~CRock();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetInput(D3DXVECTOR3 pos);

	static CRock* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, std::string Path, float fValue);

private:
	D3DXVECTOR3 m_rotDest;						// 目的の向き
	D3DXVECTOR3 m_posOld;						// 目的の位置
	D3DXVECTOR3 m_move;							// 移動量
	CShadowS* m_pShadowS;						// シャドウのポインタ
	float m_Diff;								// 差分

};
#endif
