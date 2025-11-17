//=================================================
//
// [meshcylinder.cpp]
// Author:chikada shouya
//
//=================================================
#include "meshcylinder.h"
#include "manager.h"
#include "texturemanager.h"

// コンストラクタ
CMeshCylinder::CMeshCylinder(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = NULL;						//頂点バッファへのポインタ
	m_pIdxBuff = NULL;						//インデックスバッファへのポインタ
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_fRadius = 0.0f;
	m_nIdx = NULL;
}

// デストラクタ
CMeshCylinder::~CMeshCylinder()
{

}

// 生成
CMeshCylinder* CMeshCylinder::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius)
{
	CMeshCylinder* pMeshCylinder = nullptr;
	pMeshCylinder = new CMeshCylinder;

	if (pMeshCylinder != nullptr)
	{
		pMeshCylinder->m_pos = pos;
		pMeshCylinder->m_rot = rot;
		pMeshCylinder->m_fRadius = fRadius;
		pMeshCylinder->Init();
		return pMeshCylinder;
	}
	else
	{
		return nullptr;
	}
}

//=======================================
// 初期化処理
//=======================================
HRESULT CMeshCylinder::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CTextureManager* pTex = CManager::GetTexManager()->Instance();

	//m_nIdx = pTex->Register("data\\TEXTURE\\red1.png");

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHFIELD_MAX_VTX,
		D3DUSAGE_WRITEONLY,
		D3DFVF_VERTEX,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHFIELD_MAX_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;

	int index = 0;
	float fAngle = 0.0f;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の設定
	for (int nCntV = 0; nCntV < MESHFIELD_V_BLOCK + 1; nCntV++)
	{//Z方向の繰り返し

		for (int nCntH = 0; nCntH < MESHFIELD_H_BLOCK + 1; nCntH++)
		{//X方向の繰り返し
			fAngle = (D3DX_PI * 2) / MESHFIELD_H_BLOCK /*(D3DX_PI * 2) / (MESHFIELD_H_BLOCK - nCntH)*/;

			//頂点座標の設定
			pVtx[index].pos = D3DXVECTOR3(sinf((fAngle)*nCntH) * m_fRadius, 20.0f * (nCntV * 2), cosf((fAngle)*nCntH) * m_fRadius);

			//法線の設定
			D3DXVec3Normalize(&pVtx[index].nor, &pVtx[index].pos);

			//カラー設定
			pVtx[index].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ設定
			pVtx[index].tex = D3DXVECTOR2((1.0f / MESHFIELD_H_BLOCK) * nCntV, (1.0f / MESHFIELD_V_BLOCK) * nCntH);

			index++;

		}


	}
	//アンロック
	m_pVtxBuff->Unlock();

	//頂点情報の設定
	WORD* pIdx;
	int nCnt1 = 0;
	int nCnt2 = 0;
	int nCnt3 = 25;

	//インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntV = 0; nCntV < MESHFIELD_V_BLOCK; nCntV++)
	{//Z方向の繰り返し
		for (int nCntH = 0; nCntH < MESHFIELD_H_BLOCK + 1; nCntH++)
		{//X方向の繰り返し

		//インデックスの設定
			pIdx[nCnt1] = nCnt2;
			pIdx[nCnt1 + 1] = nCnt3;

			nCnt1 += 2;
			nCnt2++;
			nCnt3++;

		}
	}
	//インデックスバッファのアンロック
	m_pIdxBuff->Unlock();


	return S_OK;
}
//=======================================
//終了処理
//=======================================
void CMeshCylinder::Uninit(void)
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
void CMeshCylinder::Update(void)
{

}
//=======================================
//描画処理
//=======================================
void CMeshCylinder::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CTextureManager* pTex = CManager::GetTexManager();

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
	//pDevice->SetTexture(0, pTex->GetAddress(m_nIdx));

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0, 0, MESHFIELD_MAX_VTX, 0, MESHFIELD_MAX_POLYGON); //頂点情報構造体のサイズ
}

void CMeshCylinder::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
D3DXVECTOR3 CMeshCylinder::GetPosition(void)
{
	return m_pos;
}