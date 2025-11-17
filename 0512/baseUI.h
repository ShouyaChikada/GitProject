//=================================================
//
//	BaseUI.h
// 
//	Author:近田尚也
//
//=================================================
#ifndef _BASEUI_H_
#define _BASEUI_H_

#include "main.h"
#include "object2D.h"
// クラス
class CBaseUI : public CObject2D
{
public:
	CBaseUI(int nPriolity = 14);
	~CBaseUI();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }

	static CBaseUI* Create(D3DXVECTOR3 pos, const char* aTxt);
	void SetUse(bool bUse) { bUse = m_bUse; }
private:

	D3DXVECTOR3 m_pos;			//位置
	int m_nIdx;
	int m_nIndx;
	const char* m_aName;
	const char* m_Name;

	bool m_bUse;
	bool m_bTutorial;
};
#endif
