//=================================================
//
//	titlemanager.cpp
// 
//	Author:近田尚也
//
//=================================================
#include "titlemanager.h"
#include "manager.h"
#include "texturemanager.h"

// コンストラクタ
CTitleManager::CTitleManager(int nPriolity) : CObject2D(nPriolity)
{
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_nIdx = NULL;
	m_aName = nullptr;
}

// デストラクタ
CTitleManager::~CTitleManager()
{

}

// 生成
CTitleManager* CTitleManager::Create(D3DXVECTOR3 pos,const char* aName)
{
	CTitleManager* pTitleManager = new CTitleManager;

	if (pTitleManager != nullptr)
	{
		pTitleManager->SetPosition(pos);
		pTitleManager->SetTxt(aName);
		pTitleManager->Init();
		pTitleManager->SetSize(640.0f, 360.0f);
		pTitleManager->SetType(CObject2D::ANCHORTYPE_CENTER);

		return pTitleManager;
	}
	else
	{
		return nullptr;
	}
}

// 初期化
HRESULT CTitleManager::Init(void)
{
	CTextureManager* pTex = CManager::GetTexManager();
	m_nIdx = pTex->Register(m_aName);

	CObject2D::Init();

	return S_OK;
}

// 終了
void CTitleManager::Uninit(void)
{
	CObject2D::Uninit();
}

// 更新
void CTitleManager::Update(void)
{
	CObject2D::Update();
}

// 描画
void CTitleManager::Draw(void)
{
	// FOGを消す

	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CTextureManager* pTex = CManager::GetTexManager();

	// テクスチャの設定
	pDevice->SetTexture(0, pTex->GetAddress(m_nIdx));

	CObject2D::Draw();

	// FOGの設定
	CManager::GetRenderer()->SetupVertexFog(D3DCOLOR_XRGB(255, 255, 255), D3DFOG_LINEAR, TRUE, 0.005f);
}