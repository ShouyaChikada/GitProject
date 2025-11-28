//=================================================
//
//	resultmanager.cpp
// 
//	Author:近田尚也
//
//=================================================
#include "resultmanager.h"
#include "manager.h"
#include "texturemanager.h"

// コンストラクタ
CResultManager::CResultManager(int nPriolity) : CObject2D(nPriolity)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nIdx = NULL;
	m_aName = nullptr;
}

// デストラクタ
CResultManager::~CResultManager()
{

}

// 生成
CResultManager* CResultManager::Create(D3DXVECTOR3 pos, const char* aName)
{
	CResultManager* pResultManager = new CResultManager;

	if (pResultManager != nullptr)
	{
		pResultManager->SetPosition(pos);
		pResultManager->SetTxt(aName);
		pResultManager->Init();
		pResultManager->SetSize(640.0f, 360.0f);
		pResultManager->SetType(CObject2D::ANCHORTYPE_CENTER);

		return pResultManager;
	}
	else
	{
		return nullptr;
	}
}

// 初期化
HRESULT CResultManager::Init(void)
{
	m_nIdx = CTextureManager::Instance()->Register(m_aName);

	CObject2D::Init();

	return S_OK;
}

// 終了
void CResultManager::Uninit(void)
{
	CObject2D::Uninit();
}

// 更新
void CResultManager::Update(void)
{
	CObject2D::Update();
}

// 描画
void CResultManager::Draw(void)
{
	// FOGを消す
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの設定
	pDevice->SetTexture(0, CTextureManager::Instance()->GetAddress(m_nIdx));

	CObject2D::Draw();
}