//=================================================
//
// [object2D.cpp]
// Author:chikada shouya
//
//=================================================
#include "object2D.h"
#include "renderer.h"
#include "manager.h"

//============================
//コンストラクタ
//============================
CObject2D::CObject2D(int nPriolity): CObject(nPriolity)
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fAngle = 0.0f;
	m_fLength = 0.0f;
	m_aUV = 0.0f;
	m_zUV = 0.0f;
	m_Width = 0.0f;
	m_Height = 0.0f;
	m_nType = 0;
}

//============================
//デストラクタ
//============================
CObject2D::~CObject2D()
{

}

//============================
// オブジェクト2D生成
//============================
CObject2D* CObject2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, D3DXCOLOR col)
{
	CObject2D* pObject2D = nullptr;
	pObject2D = new CObject2D;

	if (pObject2D != nullptr)
	{
		pObject2D->Init();
		return pObject2D;
	}
	else
	{
		return NULL;
	}
	
}
//============================
//初期化処理
//============================
HRESULT CObject2D::Init(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);

	VERTEX_2D* pVtx = nullptr;

	// 頂点バッファのロック、頂点データへのポインタ取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();
	return S_OK;
}

//============================
//終了処理
//============================
void CObject2D::Uninit(void)
{
	//バッファの破棄==========================
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//========================================

	//自分自身の破棄
	CObject::Release();
}

//============================
//更新処理
//============================
void CObject2D::Update(void)
{
	switch (m_nType)
	{
	case ANCHORTYPE_CENTER:
		UpdateCenter();
		break;
	case ANCHORTYPE_LEFT:
		UpdateLeft();
		break;
	default:
		UpdateCenter();
		break;
	}
}

//============================
//描画処理
//============================
void CObject2D::Draw(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0, 2); //頂点情報構造体のサイズ

	//テクスチャの設定
	//pDevice->SetTexture(0, NULL);
}

//位置の設定
void CObject2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//テクスチャのサイズ
void CObject2D::SetTex(float aUV, float zUV)
{
	m_aUV = aUV;
	m_zUV = zUV;
}

//アニメーションの設定
void CObject2D::SetAnim(D3DXVECTOR2 UV, float fSizeX, float fSizeY)
{
	VERTEX_2D* pVtx;

	//ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(UV.x * fSizeX, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((UV.x * fSizeX) + fSizeX, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(UV.x * fSizeX, fSizeY);
	pVtx[3].tex = D3DXVECTOR2((UV.x * fSizeX) + fSizeX, fSizeY);

	//アンロック
	m_pVtxBuff->Unlock();
}

//	アニメーション
void CObject2D::SetAnim(float aTex, float fAdd)
{
	VERTEX_2D* pVtx;

	//ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(aTex, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(aTex +fAdd, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(aTex, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(aTex + fAdd, 1.0f);

	//アンロック
	m_pVtxBuff->Unlock();

}

void CObject2D::SetSize(float fWidth, float fHeight)
{
	m_Width = fWidth;
	m_Height = fHeight;
}

//位置を取得
D3DXVECTOR3 CObject2D::GetPosition(void)
{
	return m_pos;
}

void CObject2D::UpdateLeft(void)
{
	// 頂点情報のポインタ
	VERTEX_2D* pVtx;
	// 頂点バッファをロックし,頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Width, m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_Height, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Width, m_pos.y + m_Height, 0.0f);

	// rhwの設定( 1.0fで固定 )
	pVtx[0].rhw =
	pVtx[1].rhw =
	pVtx[2].rhw =
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = D3DXCOLOR(m_col);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// アンロック
	m_pVtxBuff->Unlock();

}

void CObject2D::UpdateCenter(void)
{
	VERTEX_2D* pVtx = nullptr;

	//ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//========================================
	//頂点座標の設定

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Width, m_pos.y - m_Height, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Width, m_pos.y - m_Height, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Width, m_pos.y + m_Height, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Width, m_pos.y + m_Height, 0.0f);
	//========================================

	//アンロック
	m_pVtxBuff->Unlock();

}


//エフェクト
void CObject2D::SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius)
{
	VERTEX_2D* pVtx;

	//ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(pos.x - fRadius, pos.y - fRadius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fRadius, pos.y - fRadius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fRadius, pos.y + fRadius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fRadius, pos.y + fRadius, 0.0f);

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//アンロック
	m_pVtxBuff->Unlock();
}


void CObject2D::Set2Dpolygon(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, D3DXCOLOR col)
{
	VERTEX_2D* pVtx;

	//ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//========================================
	//頂点座標の設定
	pVtx[0].pos.x = 0.0f;
	pVtx[0].pos.y = 0.0f;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = fWidth;
	pVtx[1].pos.y = 0.0f;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = 0.0f;
	pVtx[2].pos.y = fHeight;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = fWidth;
	pVtx[3].pos.y = fHeight;
	pVtx[3].pos.z = 0.0f;
	//========================================


	//========================================
	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//========================================

	//========================================
	//頂点カラーの設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;
	//========================================

	//========================================
	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//========================================

	//アンロック
	m_pVtxBuff->Unlock();


}

void CObject2D::Setcol(D3DXCOLOR col)
{
	VERTEX_2D* pVtx;

	//ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//アンロック
	m_pVtxBuff->Unlock();


}