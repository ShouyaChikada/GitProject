//=============================================
//
// [light.cpp]
// author chikada shouya
//
//=============================================

#include "light.h"
#include "manager.h"

//静的メンバ変数
D3DLIGHT9 CLight::m_light[MAX_LIGHT] = {};

// コンストラクタ
CLight::CLight()
{
	
}

// デストラクタ
CLight::~CLight()
{

}
//==================================
// 初期化処理
//==================================
HRESULT CLight::Init(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir[MAX_LIGHT];	//ライトの方向ベクトル

	//ライトをクリアする
	ZeroMemory(&m_light, sizeof(m_light));

	//ライトの方向を設定

#if 1
	vecDir[0] = D3DXVECTOR3(-0.59f, -0.79f, -0.16f);
	vecDir[1] = D3DXVECTOR3(0.49f, -0.55f, 0.67f);
	vecDir[2] = D3DXVECTOR3(0.55f, -0.67f, -0.48f);
	vecDir[3] = D3DXVECTOR3(0.57f, -0.49f, 0.16f);
	vecDir[4] = D3DXVECTOR3(-0.81f, -0.61f, -0.68f);

#else 
	vecDir[0] = D3DXVECTOR3(0.18f, -0.91f, 0.36f);
	vecDir[1] = D3DXVECTOR3(0.49f, -0.76f, 0.67f);
	vecDir[2] = D3DXVECTOR3(0.55f, 20.0f, -0.48f);
	vecDir[3] = D3DXVECTOR3(0.89f, -0.11f, 0.44f);
	vecDir[4] = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);

#endif

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		//ライトの種類を設定
		m_light[nCnt].Type = D3DLIGHT_DIRECTIONAL;

		//ライトの拡散光を設定
		m_light[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//正規化する(大きさ１のベクトルにする)
		for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
			D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);

		m_light[nCnt].Direction = vecDir[nCnt];

		//ライトを設定する
		pD3DDevice->SetLight(nCnt, &m_light[nCnt]);

		//ライトを有効にする
		pD3DDevice->LightEnable(nCnt, TRUE);
	}

	return S_OK;
}

//==================================
// 終了処理
//==================================
void CLight::Uninit(void)
{
	
}

//==================================
// 更新処理
//==================================
void CLight::Update(void)
{

}