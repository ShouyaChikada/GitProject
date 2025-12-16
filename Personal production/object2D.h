//=================================================
//
// [object2D.h]
// Author:chikada shouya
//
//=================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

#include "main.h"
#include "object.h"

//派生クラス
class CObject2D:public CObject
{
public:
	//状態
	typedef enum
	{
		STATE_NONE = 0,
		STATE_NORMAL,
		STATE_DAMAGE,
		STATE_MAX
	}STATE;

	// 頂点生成の種類
	enum ANCHORTYPE
	{
		ANCHORTYPE_CENTER,
		ANCHORTYPE_LEFT,
		ANCHORTYPE_RIGHT,
		ANCHORTYPE_UP,
		ANCHORTYPE_DOWN,
		ANCHORTYPE_MAX
	};

	CObject2D(int nPriolty = 3);
	~CObject2D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CObject2D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, D3DXCOLOR col);

	void UpdateCenter(void);
	void UpdateLeft(void);

	// セッター
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetSize(float fWidth, float fHeight) { m_Width = fWidth; m_Height = fHeight; }
	void SetType(int nType) { m_nType = nType; }
	void SetCol(D3DXCOLOR col);
	void SetAnim(D3DXVECTOR2 UV,float fSizeX,float fSizeY);
	void SetAnim(float aTex, float fAdd);
	void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius);
	void Set2Dpolygon(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, D3DXCOLOR col);
	void SetAlpha(void);

	// ゲッター
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// 頂点バッファ
	D3DXVECTOR3 m_pos;					// 位置
	D3DXCOLOR m_col;					// 頂点カラー
	float m_fAngle;						// 角度
	float m_fLength;					// 長さ
	float m_Width;						// 横のサイズ
	float m_Height;						// 縦のサイズ
	int m_nType;						// 頂点生成の種類 
	bool m_bAlpha;						// α値の判定
	int m_nIdx;							// テクスチャ設定用変数
};
#endif
