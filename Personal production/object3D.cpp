//=================================================
//
// [object3D.cpp]
// Author:chikada shouya
//
//=================================================
#include "object3D.h"
#include "renderer.h"
#include "manager.h"

//============================
//コンストラクタ
//============================
CObject3D::CObject3D()
{
	m_pVtxBuff = NULL;
	m_SetPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//============================
//デストラクタ
//============================
CObject3D::~CObject3D()
{

}

//============================
// オブジェクト3D生成
//============================
CObject3D* CObject3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 ros)
{
	//int nNumAll = Getobject();

	//if (nNumAll < MAX_OBJECT - 1)
	//{
		CObject3D* pObject3D = NULL;
		pObject3D = new CObject3D;
		pObject3D->Init();
		return pObject3D;
	//}
	//return NULL;
}
//============================
//初期化処理
//============================
HRESULT CObject3D::Init(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();
	
	//頂点バッファの生成
	pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);
	
	VERTEX_3D* pVtx = NULL;
	
	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-450.0f, 0.0f, 450.0f);
	pVtx[1].pos = D3DXVECTOR3(450.0f, 0.0f, 450.0f);
	pVtx[2].pos = D3DXVECTOR3(-450.0f, 0.0f, -450.0f);
	pVtx[3].pos = D3DXVECTOR3(450.0f, 0.0f, -450.0f);
	
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	//アンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//============================
//終了処理
//============================
void CObject3D::Uninit(void)
{
	//頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{			  
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	
	//自分の破棄
	CObject::Release();
}

//============================
//更新処理
//============================
void CObject3D::Update(void)
{
	
}

//============================
//描画処理
//============================
void CObject3D::Draw(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pD3DDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	
	//テクスチャの設定
	pD3DDevice->SetTexture(0, NULL);

	//頂点フォーマットの設定
	pD3DDevice->SetFVF(FVF_VERTEX_3D);

	//ポリゴンの描画
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,
		2); //頂点情報構造体のサイズ
}

//位置の設定
void CObject3D::SetPosition(D3DXVECTOR3 pos)
{
	m_SetPosition = pos;
}

//位置を取得
D3DXVECTOR3 CObject3D::GetPosition(void)
{
	return m_SetPosition;
}
