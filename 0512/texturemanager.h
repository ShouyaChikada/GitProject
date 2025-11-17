//=================================================
//
//	TextureManager.h
// 
//	Author:近田尚也
//
//=================================================
#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include "main.h"

class CTextureManager
{
public:
	CTextureManager();
	~CTextureManager();
	HRESULT Load(void);
	void Unload(void);
	int Register(const char* pFilename);
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);
private:
	LPDIRECT3DTEXTURE9 m_apTex[MAX_TEXTURE];	// テクスチャのポインタ
	static int m_nNumAll;						// 総数
	const char* m_pName[MAX_TEXTURE];						// 名前
};
#endif