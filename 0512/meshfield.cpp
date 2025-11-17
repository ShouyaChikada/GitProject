//=================================================
//
//	meshfield.cpp
// 
// Author:近田 尚也
//
//=================================================
#include "meshfield.h"
#include "manager.h"
#include "texturemanager.h"

// コンストラクタ
CMeshField::CMeshField(int nPriority) : CObject(nPriority)
{
	m_pVtxBuff = NULL;						//頂点バッファへのポインタ
	m_pIdxBuff = NULL;						//インデックスバッファへのポインタ
	m_rot = D3DXVECTOR3(0.0f,0.0f,0.0f);	//向き
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);	//位置
	m_fRadius = 0.0f;
	m_nIdx = NULL;
}

// デストラクタ
CMeshField::~CMeshField()
{

}

// 生成
CMeshField* CMeshField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius)
{
	CMeshField* pMeshField = nullptr;
	pMeshField = new CMeshField;

	if (pMeshField != nullptr)
	{
		pMeshField->m_pos = pos;
		pMeshField->m_rot = rot;
		pMeshField->m_fRadius = fRadius;
		pMeshField->Init();
		return pMeshField;
	}
	else
	{
		return nullptr;
	}
}

//=======================================
// 初期化処理
//=======================================
HRESULT CMeshField::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CTextureManager* pTex = CManager::GetTexManager();
	m_nIdx = pTex->Register("data\\TEXTURE\\sky000.jpg");

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MESHFIELD_MAX_VTX,
		D3DUSAGE_WRITEONLY,
		D3DFVF_VERTEX,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);


	return S_OK;
}
//=======================================
//終了処理
//=======================================
void CMeshField::Uninit(void)
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
void CMeshField::Update(void)
{


}
//=======================================
//描画処理
//=======================================
void CMeshField::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();


	// FOGの設定
	CManager::GetRenderer()->SetupVertexFog(D3DCOLOR_XRGB(55, 55, 255), D3DFOG_LINEAR, TRUE, 0.005f);

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	vector<Vertex> vertices;
	vector<Vertex> fan;

	GenerateSphereVertices(4000.0f, 6, 6, vertices);  // 半径1.0、20分割

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// スフィアの描画
	RenderSphere(pDevice,vertices, 6, 6);
	
	pDevice->Present(NULL, NULL, NULL, NULL);

	// FOGを消す
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);


}

void CMeshField::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
D3DXVECTOR3 CMeshField::GetPosition(void)
{
	return m_pos;
}

// スフィア用緯度と経度に基づいて頂点を計算
void CMeshField::GenerateSphereVertices(float radius, int slices, int stacks, vector<Vertex>& vertices)
{
	for (int i = 0; i <= stacks; ++i) 
	{
		float phi = D3DX_PI * i / stacks;  // 緯度
		for (int j = 0; j <= slices; ++j) 
		{
			float theta = 2.0f * D3DX_PI * j / slices;  // 経度

			Vertex v;
			v.x = radius * sinf(phi) * cosf(theta);
			v.y = radius * cosf(phi);
			v.z = radius * sinf(phi) * sinf(theta);
			v.color = 0xFFFFFFFF;  // 白色
			vertices.push_back(v);
		}
	}
}

// スフィアの描画
void CMeshField::RenderSphere(LPDIRECT3DDEVICE9 pDevice, const vector<Vertex>& vertices, int slices, int stacks)
{
	CTextureManager* pTex = CManager::GetTexManager();

	//vector<Vertex> fan;
	int index = 0;
	VERTEX_3D* pVtx = nullptr;

	for (int i = 0; i < stacks; ++i)
	{
		for (int j = 0; j < slices; ++j)
		{

			vector<Vertex> fan;

			// 三角形ファンの中心
			fan.push_back(vertices[i * (slices + 1) + j]);

			// 周囲の頂点
			fan.push_back(vertices[(i + 1) * (slices + 1) + j]);
			fan.push_back(vertices[(i + 1) * (slices + 1) + (j + 1)]);
			fan.push_back(vertices[i * (slices + 1) + (j + 1)]);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

			// 描画ループ
			pDevice->SetFVF(D3DFVF_VERTEX);

			//テクスチャの設定
			pDevice->SetTexture(0, pTex->GetAddress(m_nIdx));

			// 描画
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, fan.size() - 2, fan.data(), sizeof(Vertex));

		}
	}
	//アンロック
	m_pVtxBuff->Unlock();
}