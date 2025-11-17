//=================================================
//
//	ObjectX.cpp
// 
// Author:近田 尚也
//
//=================================================
#include "objectx.h"
#include "manager.h"
#include "motion.h"
#include "texturemanager.h"

//静的メンバ変数
const char* CObjectX::m_txt = {};

// コンストラクタ
CObjectX::CObjectX(int nPriolty):CObject(nPriolty)
{
	m_pTexture = { nullptr };

	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		m_nIdx[nCnt] = NULL;
	}
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;
	m_dwNumMat = NULL;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_SetPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_txt = nullptr;
	m_pModel = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Quat = D3DXQUATERNION(1.0f, 1.0f, 1.0f, 1.0f);						// クォータニオン
	m_VecAxis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 回転軸
	m_VtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 最大値
	m_VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 最小値
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// サイズ

}

// デストラクタ
CObjectX::~CObjectX()
{

}

// 生成
CObjectX* CObjectX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* txt)
{
	CObjectX* pObjectX = nullptr;
	pObjectX = new CObjectX;

	if (pObjectX != nullptr)
	{
		pObjectX->m_pos = pos;
		pObjectX->m_rot = D3DXToRadian(rot);
		pObjectX->m_txt = txt;
		pObjectX->Init();
		return pObjectX;
	}
	else
	{
		return nullptr;
	}
}

//================================
// 初期化処理
//================================
HRESULT CObjectX::Init(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャマネージャーの取得
	CTextureManager* pTex = CManager::GetTexManager();

	//Xファイルの読み込み
	D3DXLoadMeshFromX(m_txt,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	D3DXMATERIAL *pMat = nullptr;	//マテリアルへのポインタ

	m_pTexture = new int[m_dwNumMat];

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != nullptr)
		{//テクスチャファイルが存在する
			// テクスチャポインタ取得
			CTextureManager* pTexture = CManager::GetTexManager();

			m_pTexture[nCntMat] = pTexture->Register(pMat[nCntMat].pTextureFilename);
		}
		else
		{
			m_pTexture[nCntMat] = -1;
		}
	}

	return S_OK;
}
//================================
// 終了処理
//================================
void CObjectX::Uninit(void)
{

	// テクスチャの破棄
	if (m_pTexture != nullptr)
	{
		delete[] m_pTexture;

		m_pTexture = nullptr;
	}

	//メッシュの破棄
	if (m_pMesh != nullptr)
	{	   
		m_pMesh->Release();
		m_pMesh = nullptr;
	}
	//マテリアルの破棄
	if (m_pBuffMat != nullptr)
	{	   
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	//自分の破棄
	CObject::Release();
}
//================================
// 更新処理
//================================
void CObjectX::Update(void)
{
	
}
//================================
// 描画処理
//================================
void CObjectX::Draw(void)
{
	CTextureManager* pTex = CManager::GetTexManager();

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//マルチターゲット
	LPDIRECT3DTEXTURE9 pTexMT;

	D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
	D3DMATERIAL9 matDef; //現在のマテリアル保存用
	D3DXMATERIAL* pMat;	//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.x, m_rot.y, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		if (m_pTexture[nCntMat] != -1)
		{
			pTexMT = CManager::GetRenderer()->GetTextureMT();

			//テクスチャの設定
			pDevice->SetTexture(0, pTex->GetAddress(m_pTexture[nCntMat]));
		}
		else
		{
			//テクスチャの設定
			pDevice->SetTexture(0, NULL);
		}

		//モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを隠す
	pDevice->SetMaterial(&matDef);


}

LPD3DXMESH CObjectX::GetMesh(void)
{
	return m_pMesh;
}