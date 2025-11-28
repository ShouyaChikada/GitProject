//=================================================
//
//	pause.cpp
// 
// Author:近田 尚也
//
//=================================================
#include "pause.h"
#include "texturemanager.h"
#include "manager.h"
#include "pausemanager.h"

// コンストラクタ
CPause::CPause(int nPriolity): CObject2D(nPriolity)
{
	m_nIdx = NULL;
	m_aName = {};
}

// デストラクタ
CPause::~CPause()
{

}

// 生成
CPause* CPause::Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fX, float fY, std::string aName)
{
	CPause* pPause = nullptr;
	pPause = new CPause;

	if (pPause != nullptr)
	{
		pPause->m_aName = aName;
		pPause->SetCol(col);
		pPause->Init();
		pPause->SetPosition(pos);
		pPause->SetSize(fX, fY);
		pPause->SetType(CObject2D::ANCHORTYPE_CENTER);
		return pPause;

	}
	else
	{
		return nullptr;
	}
}

// 初期化
HRESULT CPause::Init(void)
{
	CTextureManager* pTex = CManager::GetTexManager();
	m_nIdx = CTextureManager::Instance()->Register(m_aName);

	CObject::SetType(TYPE_PAUSE);

	CObject2D::Init();

	return S_OK;
}

// 終了
void CPause::Uninit(void)
{
	CObject2D::Uninit();
}

// 更新処理
void CPause::Update(void)
{
	CObject2D::Update();
}

// 描画
void CPause::Draw(void)
{
	// FOGを消す
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

	if (CPauseManager::GetPause() == true)
	{
		//デバイス取得
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// テクスチャの設定
		pDevice->SetTexture(0, CTextureManager::Instance()->GetAddress(m_nIdx));

		CObject2D::Draw();
	}
}