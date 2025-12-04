//=================================================
//
//	[modelmanager.h] 
//	Author:chikada shouya
//
//=================================================

// 二重インクルード防止
#ifndef _MODELMANAGER_H_
#define _MODELMANAGER_H_

#include "main.h"
#include <string>

class CModelManager
{
public:

	typedef struct
	{
		LPD3DXMESH pMesh;		// メッシュのポインタ
		LPD3DXBUFFER pBuffMat;	// マテリアルのポインタ
		DWORD dwNumMat;			// マテリアル数
		std::string sName;
		int* pTexture;		// テクスチャのポインタ

	}ModelInfo;

	CModelManager();
	~CModelManager();
	HRESULT Load(std::string sName);
	void Unload(void);
	int Register(std::string sName);
	static CModelManager* Instance(void);

	// ゲッター
	ModelInfo GetAddress(int nIdx);

private:
	std::vector<ModelInfo> m_vModel;					// テクスチャのポインタ
	D3DXVECTOR3 m_VtxMax;								// 頂点最大値
	D3DXVECTOR3 m_VtxMin;								// 頂点最小値
	D3DXVECTOR3 m_Size;									// サイズ
	static std::unique_ptr<CModelManager> m_Instance;	// シングルトン
};
#endif