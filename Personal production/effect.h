//=================================================
//
//	effect.h
// 
// Author:近田 尚也
//
//=================================================
#ifndef EFFECT_H_
#define EFFECT_H_

#include "main.h"
#include "billboard.h"

#define MAX_EFFECT (128)

class CEffect :public CBillboard
{
public:
	CEffect();
	~CEffect();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffect* Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, std::string FilePath);

	// セッター
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

	// ゲッター
	D3DXVECTOR3 GetMove(void) { return m_move; }

private:
	D3DXVECTOR3 m_move;					//移動量
	int m_nLife;			//寿命

};
#endif