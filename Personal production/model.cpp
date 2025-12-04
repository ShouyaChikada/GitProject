//=================================================
//
// [model.cpp]
// Author:chikada shouya
//
//=================================================
#include "model.h"
#include "manager.h"
#include "object.h"
#include "texturemanager.h"
#include "modelmanager.h"

D3DXVECTOR3 CModel::m_Size = {};
// コンストラクタ
CModel::CModel()
{
	m_nIdx = NULL;
	m_pParent = NULL;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&m_mtxRot);

}

// デストラクタ
CModel::~CModel()
{

}

// 生成
CModel* CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, std::string Path)
{
	CModel* pModel = nullptr;
	pModel = new CModel;
	if (pModel != nullptr)
	{
		pModel->Init(pos, rot);
		pModel->SetIdx(Path);
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
HRESULT CModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
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
//================================
// 終了処理
//================================
void CModel::Uninit(void)
{

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
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CModelManager* pModelTexManager = CModelManager::Instance();
	CModelManager::ModelInfo modelinfo = pModelTexManager->GetAddress(m_nIdx);

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL* pMat;				//マテリアルデータへのポインタ
	D3DXMATRIX mtxParent;			//親のマトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ワールドマトリックスの初期化

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


	//パーツの「親のマトリックス」を設定
	if (m_pParent != NULL)
	{//親のモデルがある場合
		mtxParent = m_pParent->GetMtxWorld();//親モデルのインデックスを指定
	}
	else
	{//親モデルがない場合
		//パーツのワールドマトリックスの設定
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//算出した「パーツのマトリックス」と「親のマトリックス」をかけ合わせる
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld ,&mtxParent);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)modelinfo.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)modelinfo.dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャインデックスがあるとき
		if (modelinfo.pTexture[nCntMat] != -1)
		{				
			//テクスチャ割り当て
			pDevice->SetTexture(0, CTextureManager::Instance()->GetAddress(modelinfo.pTexture[nCntMat]));
		}
		else
		{
			//テクスチャの設定
			pDevice->SetTexture(0, NULL);
		}

		//モデル(パーツ)の描画
		modelinfo.pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを隠す
	pDevice->SetMaterial(&matDef);

}

//================================================
// インデックスを設定
//================================================
void CModel::SetIdx(std::string Path)
{
	m_nIdx = CModelManager::Instance()->Register(Path);
}