//=================================================
//
//	gauge.cpp
// 
// Author:近田 尚也
//
//=================================================
#include "gauge.h"
#include "manager.h"
#include "texturemanager.h"
#include "gimmickmanager.h"

//コンストラクタ
CGauge::CGauge(int nPriolity) : CObject2D(nPriolity)
{
	m_nIdx = 0;
	m_pBaseUI = nullptr;
	m_fCnt = 0.0f;
	m_fCnt1 = 0.0f;
	m_aName = nullptr;
}
//デストラクタ
CGauge::~CGauge()
{

}

// 生成
CGauge* CGauge::Create(D3DXVECTOR3 pos, const char* aTxt,D3DXCOLOR col)
{
	CGauge* pGauge = nullptr;
	pGauge = new CGauge;

	if (pGauge != nullptr)
	{
		pGauge->SetCol(col);
		pGauge->SetPosition(pos);
		pGauge->Init();
		pGauge->SetSize(0.0f, 55.0f);
		pGauge->SetType(CObject2D::ANCHORTYPE_LEFT);
		return pGauge;
	}
	else
	{
		return nullptr;
	}
}

// 初期化
HRESULT CGauge::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//	終了
void CGauge::Uninit(void)
{
	//自分自身の破棄
	CObject2D::Uninit();
}

//===================
//	更新処理
//===================
void CGauge::Update(void)
{
	// m_pBaseUI->Update();
	CObject2D::Update();
}

//===================
//	描画処理
//===================
void CGauge::Draw(void)
{

	bool bUse = CGimmickManager::GetRange();
	bool bPush = CGimmickManager::GetPush();

	// FOGの設定
	CManager::GetRenderer()->SetupVertexFog(D3DCOLOR_XRGB(255, 255, 255), D3DFOG_LINEAR, TRUE, 0.005f);

	// デバイスへのポインタ
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (bUse == true)
	{
		CObject2D::Draw();
	}

	// FOGを消す
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

}

//===============================
// ゲージの長さ設定処理
//===============================
void CGauge::SetGageLength(const int nMaxLife, const int nCurrentLife, float fValue, float Height)
{
	// 最大比率を出す
	float fRatio = 1.0f;

	// 0以上なら
	if (nMaxLife > NULL)
	{
		// 割合を計算する
		fRatio = static_cast<float>(nCurrentLife) / static_cast<float>(nMaxLife);
	}

	// 表示する体力バーの最大幅
	const float fMaxWidth = SCREEN_WIDTH * fValue;

	// サイズを比率で反映
	CObject2D::SetSize(fMaxWidth * fRatio, Height);
}
//===============================
// ゲージの長さ設定処理 ( float )
//===============================
void CGauge::FSetGageLength(float fMax, float fCurrent, float fMaxWidth, float fHeight)
{
	// 割合値
	float fRatio = 1.0f;

	// 0以上
	if (fMax > 0.0f)
	{
		// 割合計算
		fRatio = fCurrent / fMax;
	}

	// 最大幅 × 割合
	CObject2D::SetSize(fMaxWidth * fRatio, fHeight);
}
