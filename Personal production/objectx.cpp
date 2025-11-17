//=================================================
//
//	[ObjectX.cpp]
// Author:chikada shouya
//
//=================================================
#include "objectx.h"
#include "manager.h"
#include "texturemanager.h"
#include "modelmanager.h"

//================================================
// コンストラクタ
//================================================
CObjectX::CObjectX(int nPriolty):CObject(nPriolty)
{
	m_nIdx = NULL;
	m_pMesh = nullptr;
	m_pBuffMat = nullptr;
	m_dwNumMat = NULL;
	m_FilePath = {};
	m_fValueRot = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VecAxis = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Quat = D3DXQUATERNION(1.0f,1.0f,1.0f,1.0f);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&m_mtxRot);
}
//================================================
// デストラクタ
//================================================
CObjectX::~CObjectX()
{

}

//================================================
// 生成
//================================================
CObjectX* CObjectX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, std::string FilePath, float ValueRot)
{
	CObjectX* pObjectX = nullptr;
	pObjectX = new CObjectX;

	if (pObjectX != nullptr)
	{
		pObjectX->m_pos = pos;
		pObjectX->m_rot = rot;
		pObjectX->m_FilePath = FilePath;
		pObjectX->m_addRot = ValueRot;
		pObjectX->SetIdx(FilePath);
		pObjectX->Init();
		return pObjectX;
	}
	else
	{
		return nullptr;
	}
}

//================================================
// 初期化処理
//================================================
HRESULT CObjectX::Init(void)
{
	CModelManager* pModelTexManager = CModelManager::Instance();
	CModelManager::ModelInfo modelinfo = pModelTexManager->GetAddress(m_nIdx);

	// ローカル変数宣言-----------------------------
	int nNumVtx;		// 頂点数
	DWORD sizeFVF;		// 頂点フォーマットのサイズ
	BYTE* pVtxBuff;		// 頂点バッファのポインタ
	//----------------------------------------------
	LPD3DXMESH pMesh = modelinfo.pMesh;

	// 頂点数の取得
	nNumVtx = pMesh->GetNumVertices();

	// 頂点のサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(pMesh->GetFVF());

	// 頂点バッファをロック
	pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
	// 頂点数分回す
	for (int nCntBlock = 0; nCntBlock < nNumVtx; nCntBlock++)
	{
		// 頂点座標の代入
		D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

		// 頂点座標の比較
		if (Vtx.x > m_VtxMax.x)
		{// xが最大値より大きかったら
			// 代入
			m_VtxMax.x = Vtx.x;
		}
		if (Vtx.y > m_VtxMax.y)
		{// yが最大値より大きかったら
			// 代入
			m_VtxMax.y = Vtx.y;
		}
		if (Vtx.z > m_VtxMax.z)
		{// zが最大値より大きかったら
			// 代入
			m_VtxMax.z = Vtx.z;
		}

		if (Vtx.x < m_VtxMin.x)
		{// xが最小値より小さかったら
			// 代入
			m_VtxMin.x = Vtx.x;
		}
		if (Vtx.y < m_VtxMin.y)
		{// yが最小値より小さかったら
			// 代入
			m_VtxMin.y = Vtx.y;
		}
		if (Vtx.z < m_VtxMin.z)
		{// zが最小値より小さかったら
			// 代入
			m_VtxMin.z = Vtx.z;
		}

		// 頂点フォーマットのサイズ分進める
		pVtxBuff += sizeFVF;
	}

	// サイズを代入する
	m_Size.x = m_VtxMax.x - m_VtxMin.x;	// sizeのx
	m_Size.y = m_VtxMax.y - m_VtxMin.y;	// sizeのy
	m_Size.z = m_VtxMax.z - m_VtxMin.z;	// sizeのz

	// アンロック
	pMesh->UnlockVertexBuffer();

	return S_OK;
}
//================================================
// 終了処理
//================================================
void CObjectX::Uninit(void)
{
	//メッシュの破棄
	if (m_pMesh != NULL)
	{	   
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	//マテリアルの破棄
	if (m_pBuffMat != NULL)
	{	   
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
	
	//自分の破棄
	CObject::Release();
}
//================================================
// 更新処理
//================================================
void CObjectX::Update(void)
{
	static float fAngle = 0.0f;

	D3DXVECTOR3 Axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	fAngle += 0.05f;

	D3DXQuaternionRotationAxis(&m_Quat,&Axis,fAngle);
}
//================================================
// 描画処理
//================================================
void CObjectX::Draw(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CModelManager* pModelTexManager = CModelManager::Instance();
	CModelManager::ModelInfo modelinfo = pModelTexManager->GetAddress(m_nIdx);

	D3DXMATRIX mtxRot, mtxTrans;						// 計算用マトリックス
	D3DMATERIAL9 matDef;								// 現在のマテリアル保存用
	D3DXMATERIAL* pMat;									// マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転軸のおける指定の回転角からクォータニオンを作成
	D3DXQuaternionRotationAxis(&m_Quat, &m_VecAxis, m_fValueRot);

	// クォータニオンから回転マトリックスの作成
	D3DXMatrixRotationQuaternion(&mtxRot, &m_Quat);

	// 現在の回転量に次の回転量を加える
	D3DXMatrixMultiply(&m_mtxRot, &m_mtxRot, &mtxRot);
	
	// 次の回転量をワールドマトリックスの加える
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);

	// 位置のマトリックスの作成
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	// ワールドマトリックスに位置のマトリックスを加える
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)modelinfo.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)modelinfo.dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, CTextureManager::Instance()->GetAddress(modelinfo.pTexture[nCntMat]));

		//モデル(パーツ)の描画
		modelinfo.pMesh->DrawSubset(nCntMat);
	}
	
	//保存していたマテリアルを隠す
	pDevice->SetMaterial(&matDef);
}

//================================================
// インデックスを設定
//================================================
void CObjectX::SetIdx(std::string Path)
{
	m_nIdx = CModelManager::Instance()->Register(Path);
}