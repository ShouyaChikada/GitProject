//=================================================
//
//	effect.cpp
// 
// Author:近田 尚也
//
//=================================================
#include"effect.h"
#include "texturemanager.h"
#include "manager.h"

// コンストラクタ
CEffect::CEffect()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//移動量
	m_nLife = 0;			//寿命
	m_nIdx = 0;
	m_mtxWorld = {};

}

// デストラクタ
CEffect::~CEffect()
{
}

// エフェクトの生成
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife)
{
	CEffect* pEffect = nullptr;
	pEffect = new CEffect;

	if (pEffect != nullptr)
	{
		pEffect->m_pos = pos;
		pEffect->m_move = move;
		pEffect->m_nLife = nLife;
		pEffect->SetRadius(15.0f);
		pEffect->SetColor(col);
		pEffect->Init();
		return pEffect;
		
	}
	else
	{
		return nullptr;
	}
}
// 初期化
HRESULT CEffect::Init(void)
{

	CTextureManager* pTex = CManager::GetTexManager();
	m_nIdx = pTex->Register("data\\TEXTURE\\effect000.jpg");

	CBillboard::Init();
	return S_OK;
}

//=============================================================================
//エフェクトの終了処理
//=============================================================================
void CEffect::Uninit(void)
{
	CBillboard::Uninit();
}

//=============================================================================
//エフェクトの更新処理
//=============================================================================
void CEffect::Update(void)
{
	m_pos += m_move;

	m_nLife--;

	if (m_nLife <= 0)
	{
		Uninit();
	}

	SetPosition(m_pos);
}

//=============================================================================
//エフェクトの描画処理
//=============================================================================
void CEffect::Draw(void)
{
	// FOGを消す
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//αテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 加算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);



	// テクスチャの設定
	CTextureManager* pTex = CManager::GetTexManager();
	pDevice->SetTexture(0, pTex->GetAddress(m_nIdx));
	// 描画
	CBillboard::Draw();

	// 設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//αテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// FOGの設定
	CManager::GetRenderer()->SetupVertexFog(D3DCOLOR_XRGB(255, 255, 255), D3DFOG_LINEAR, TRUE, 0.005f);
}