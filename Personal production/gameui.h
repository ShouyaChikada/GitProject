//=================================================
//
// [GameUI.h]
// Author:chikada shouya
//
//=================================================
#ifndef _GAMEUI_H_
#define _GAMEUI_H_

#include "main.h"
#include "object2D.h"
#include "shadows.h"
#include <string>

// マクロ定義
#define MAX_SPEED (15.0f)	// 移動の速さ
#define MAX_ROT (0.175f)	// クオータニオンの回転値
#define HALF (0.5f)			// 半分の値

// クラス
class CGameUI :public CObject2D
{
public:

	CGameUI(int nPriolty = 3);
	~CGameUI();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGameUI* Create(D3DXVECTOR3 pos,int type);

private:
};
#endif
