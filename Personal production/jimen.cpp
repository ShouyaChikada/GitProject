//=================================================
//
// [jimen.cpp]
// 
// Author:chikada shouya
//
//=================================================
#include "manager.h"
#include "jimen.h"
#include "texturemanager.h"

// コンストラクタ
CGrand::CGrand(int nPriolity) : CObject(nPriolity)
{
	m_rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_mtxWorld = {};
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;
	m_nIdx = NULL;
}

// デストラクタ
CGrand::~CGrand()
{

}

// 生成
CGrand* CGrand::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CGrand* pGrand = nullptr;
	pGrand = new CGrand;

	if (pGrand != nullptr)
	{
		pGrand->m_pos = pos;
		pGrand->m_rot = rot;
		pGrand->Init();
		return pGrand;
	}
	else
	{
		return nullptr;
	}
}

//=======================================
// 初期化処理
//=======================================
HRESULT CGrand::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CTextureManager* pTex = CManager::GetTexManager()->Instance();
	m_nIdx = pTex->Register("data\\TEXTURE\\bkg.jpg");

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * GRAND_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * GRAND_INDEX_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx = nullptr;

	int radius = 1500;	//半径
	int index = 0;
	float fAngle = 0.0f;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	float fxz = 1500.0f;

	//頂点の設定
	for (int nCntZ = 0; nCntZ < GRAND_Z_BLOCK; nCntZ++)
	{//Z方向の繰り返し

		for (int nCntX = 0; nCntX < GRAND_X_BLOCK; nCntX++)
		{//X方向の繰り返し

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-fxz, 0.0f, fxz);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, fxz);
			pVtx[2].pos = D3DXVECTOR3(fxz, 0.0f, fxz);
			pVtx[3].pos = D3DXVECTOR3(-fxz, 0.0f, 0.0f);
			pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[5].pos = D3DXVECTOR3(fxz, 0.0f, 0.0f);
			pVtx[6].pos = D3DXVECTOR3(-fxz, 0.0f, -fxz);
			pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -fxz);
			pVtx[8].pos = D3DXVECTOR3(fxz, 0.0f, -fxz);

			//法線の設定
			pVtx[nCntX].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//カラー設定
			pVtx[nCntX].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ設定
			//pVtx[nCntZ].tex = D3DXVECTOR2(nCntX * (0.25f / nCntX), nCntZ * (0.25f / nCntZ));
			//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
			pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
			pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
			pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
			pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
	}
	//アンロック
	m_pVtxBuff->Unlock();

	//頂点情報の設定
	WORD* pIdx;
	int nCnt1 = 0;
	int nCnt2 = 3;
	int nCnt3 = 0;
	//インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);


	//インデックスの設定

	pIdx[0] = 3;
	pIdx[1] = 0;

	pIdx[2] = 4;
	pIdx[3] = 1;

	pIdx[4] = 5;
	pIdx[5] = 2;

	pIdx[6] = 2;
	pIdx[7] = 6;

	pIdx[8] = 6;
	pIdx[9] = 3;

	pIdx[10] = 7;
	pIdx[11] = 4;

	pIdx[12] = 8;
	pIdx[13] = 5;

	pIdx[14] = 5;
	pIdx[15] = 3;

	//インデックスバッファのアンロック
	m_pIdxBuff->Unlock();

	return S_OK;
}
//=======================================
//終了処理
//=======================================
void CGrand::Uninit(void)
{
	//頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{	
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//インデックスバッファの開放
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	CObject::Release();
}
//=======================================
//更新処理
//=======================================
void CGrand::Update(void)
{

	VERTEX_3D* pVtx = nullptr;

	static float aPosTexU = 0.0f;

	aPosTexU += 0.0001f;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(aPosTexU, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(aPosTexU + 0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(aPosTexU + 1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(aPosTexU, 0.5f);
	pVtx[4].tex = D3DXVECTOR2(aPosTexU + 0.5f, 0.5f);
	pVtx[5].tex = D3DXVECTOR2(aPosTexU + 1.0f, 0.5f);
	pVtx[6].tex = D3DXVECTOR2(aPosTexU, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(aPosTexU + 0.5f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(aPosTexU + 1.0f, 1.0f);
	
	m_pVtxBuff->Unlock();
}
//=======================================
//描画処理
//=======================================
void CGrand::Draw(void)
{

	CTextureManager* pTex = CManager::GetTexManager()->Instance();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

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
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, CTextureManager::Instance()->GetAddress(m_nIdx));

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0, 0, GRAND_VERTEX_NUM, 0, GRAND_PRIMITVE_NUM)); //頂点情報構造体のサイズ
}

void CGrand::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
D3DXVECTOR3 CGrand::GetPosition(void)
{
	return m_pos;
}
