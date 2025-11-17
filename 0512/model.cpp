//=================================================
//
//	model.cpp
// 
// Author:近田 尚也
//
//=================================================
#include "model.h"
#include "manager.h"
#include "object.h"
#include "texturemanager.h"

D3DXVECTOR3 CModel::m_Size = {};
// コンストラクタ
CModel::CModel()
{
	m_pTexture = { nullptr };

	m_pParent = NULL;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = NULL;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

// デストラクタ
CModel::~CModel()
{

}

// 生成
CModel* CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* txt)
{
	//int nNumAll = CObject::Getobject();

	//if (nNumAll < MAX_OBJECT - 1)
	//{
	CModel* pModel = nullptr;
	pModel = new CModel;
	if (pModel != nullptr)
	{
		pModel->Init(pos, rot, txt);
		return pModel;
	}
	else
	{
		return nullptr;
	}
		//}
	//return NULL;
}

//================================
// 初期化処理
//================================
HRESULT CModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* txt)
{
	
	//デバイス取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	CObject* pObject = CManager::getobject();

	//Xファイルの読み込み(全パーツ)2
	D3DXLoadMeshFromX(txt,
		D3DXMESH_SYSTEMMEM,
		pD3DDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	m_pos = pos;
	m_rot = rot;

	// ローカル変数宣言-----------------------------
	int nNumVtx;		// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE* pVtxBuff;		// 頂点バッファのポインタ
	//----------------------------------------------

	// 頂点数の取得
	nNumVtx = m_pMesh->GetNumVertices();

	// 頂点のサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	// 頂点バッファをロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	m_Size = pObject->SetSize(m_VtxMax, m_VtxMin, nNumVtx, sizeFVF, pVtxBuff);

	// アンロック
	m_pMesh->UnlockVertexBuffer();

	D3DXMATERIAL* pMat;	//マテリアルへのポインタ

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
void CModel::Uninit(void)
{
	// もしnullptrだったら
	if (this == nullptr) return;

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
}
//================================
// 更新処理
//================================
void CModel::Update(void)
{
	//前回の位置を保存	位置更新の上で書く
	m_posOld = m_pos;

}
//================================
// 描画処理
//================================
void CModel::Draw(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL* pMat;				//マテリアルデータへのポインタ
	D3DXMATRIX mtxParent;			//親のマトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//現在のマテリアルを取得
	pD3DDevice->GetMaterial(&matDef);

	//パーツの「親のマトリックス」を設定
	if (m_pParent != NULL)
	{//親のモデルがある場合
		mtxParent = m_pParent->GetMtxWorld();//親モデルのインデックスを指定
	}
	else
	{//親モデルがない場合
		//パーツのワールドマトリックスの設定
		pD3DDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//算出した「パーツのマトリックス」と「親のマトリックス」をかけ合わせる
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld ,&mtxParent);

	//ワールドマトリックスの設定
	pD3DDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pD3DDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャインデックスがあるとき
		if (m_pTexture[nCntMat] != -1)
		{
			// テクスチャポインタ取得
			CTextureManager* pTexture = CManager::GetTexManager();
				
			//テクスチャ割り当て
			pD3DDevice->SetTexture(0, pTexture->GetAddress(m_pTexture[nCntMat]));
		}
		else
		{
			//テクスチャの設定
			pD3DDevice->SetTexture(0, NULL);
		}

		//モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを隠す
	pD3DDevice->SetMaterial(&matDef);

}

// ワールドマトリックスの取得
D3DXMATRIX CModel::GetMtxWorld(void)
{
	return m_mtxWorld;
}

// パーツのペアレント設定
void CModel::SetParent(CModel* pModel)
{
	m_pParent = pModel;
}
// 位置の設定
void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
	
}

// 向きの設定
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

// 前の位置の設定
void CModel::SetPosOld(D3DXVECTOR3 PosOld)
{
	m_posOld = PosOld;
}

// サイズの設定
void CModel::SetSize(D3DXVECTOR3 Size)
{
	m_Size = Size;
}

// 移動量の設定
void CModel::SetMove(D3DXVECTOR3 Move)
{
	m_move = Move;
}

D3DXVECTOR3 CModel::GetSize(void)
{
	return m_Size;
}