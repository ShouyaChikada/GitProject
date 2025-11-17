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

	void SetPosition(D3DXVECTOR3 pos);
	void SetTex(float aUV, float zUV);
	void SetAnim(D3DXVECTOR2 UV,float fSizeX,float fSizeY);
	void SetAnim(float aTex, float fAdd);
	void SetSize(float fWidth, float fHeight);
	void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius);
	void SetType(int nType) { m_nType = nType; }
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	static CObject2D* Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,float fWidth,float fHeight,D3DXCOLOR col);
	void Set2Dpolygon(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, D3DXCOLOR col);
	D3DXVECTOR3 GetPosition(void);

	void UpdateCenter(void);
	void UpdateLeft(void);
	//void UpdateCenter(void);

	void SetCol(D3DXCOLOR col) { m_col = col; }
	void Setcol(D3DXCOLOR col);

private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_pos;					// 位置
	D3DXCOLOR m_col;					// 頂点カラー
	float m_fAngle;						// 角度
	float m_fLength;					// 長さ
	float m_aUV;						// α値
	float m_zUV;						// ｚ値
	float m_Width;					// 横のサイズ
	float m_Height;					// 縦のサイズ
	int m_nType;						// 頂点生成の種類 
};
#endif
