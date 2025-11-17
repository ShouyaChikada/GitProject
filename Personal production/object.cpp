//=================================================
//
// [object.cpp]
// Author:chikada shouya
// 
//=================================================
#include "object.h"
#include "renderer.h"
#include "camera.h"
#include "manager.h"
//#include "game.h"

//静的メンバ変数
CObject* CObject::m_apTop[NUM_PRIORITY] = {};
CObject* CObject::m_apCur[NUM_PRIORITY] = {};
int CObject::m_nNumAll = 0;

//============================
//コンストラクタ
//============================
CObject::CObject(int nPriority)
{
	m_type = TYPE_NONE;			//タイプの初期化
	m_nPriority = nPriority;	// 描画優先順位の代入
 	m_bDeath = false;			// 死亡フラグをfalseにしておく

	// つなぎの初期化
	m_pNext = nullptr;
	m_pPrev = nullptr;

	m_pPrev = m_apCur[nPriority];	// 前の尾辺ジェクトとのつなぎ

	// 最後尾が入ってたら
	if (m_apCur[nPriority])
	{
		m_apCur[nPriority]->m_pNext = this;		// 最後尾の次に設定
	}
	else
	{
		m_apTop[nPriority] = this;	// 先頭の設定
	}

	m_apCur[nPriority] = this;		// 最後尾の設定
	m_nNumAll++;		//総数の加算
}

//============================
// デストラクタ
//============================
CObject::~CObject()
{

}

// すべてを破棄処理
void CObject::ReleaseAll(void)
{
	// 描画優先順位分まわす
	for (int nCnt = 0; nCnt < NUM_PRIORITY; nCnt++)
	{
		// 先頭のオブジェクトを代入
		CObject* pObject = m_apTop[nCnt];	

		// 情報が入っていたら
		while (pObject != nullptr)
		{ 
			// 次のオブジェクトを保存
			CObject* pObjectNext = pObject->m_pNext;	

			// オブジェクトの終了処理
			pObject->Uninit();

			// オブジェクトのリストから削除
			pObject->m_pNext = nullptr;
			pObject->m_pPrev = nullptr;

			// オブジェクトの破棄
			delete pObject;
			pObject = nullptr;

			// 次のオブジェクトを代入
			pObject = pObjectNext;	
		}

		// 先頭の初期化
		m_apTop[nCnt] = nullptr;

		// 最後尾の初期化
		m_apCur[nCnt] = nullptr;
	}

	// 総数の減算
	m_nNumAll = NULL;
	
}

// 自分自身の破棄
void CObject::Release(void)
{
	// 死亡フラグを立てる
	m_bDeath = true;
}

// すべての更新処理
void CObject::UpdateAll(void)
{
	// 描画優先順位分まわす
	for (int nCnt = 0; nCnt < NUM_PRIORITY; nCnt++)
	{
		// 先頭のオブジェクトを代入
		CObject* pObject = m_apTop[nCnt];

		// 情報が入っていたら
		while (pObject != nullptr)
		{
			// 次のオブジェクトを保存
			CObject* pObjectNext = pObject->m_pNext;

			//if (CPauseManager::GetPause())
			//{
			//	if (pObject->GetType() == TYPE_PAUSE)
			//	{
			//		// 更新処理
			//		pObject->Update();
			//	}
			//}
			//else
			//{
			//	// 死亡フラグが立っていたら
			//	if (pObject->m_bDeath == false)
			//	{
			//		// 更新処理
			//		pObject->Update();
			//	}
			//}

			 //死亡フラグが立っていたら
			if (pObject->m_bDeath == false)
			{
				// 更新処理
				pObject->Update();
			}

			//次のオブジェクトを代入
			pObject = pObjectNext;
		}

	}

	// 描画優先順位分まわす
	for (int nCnt = 0; nCnt < NUM_PRIORITY; nCnt++)
	{
		CObject* pObject = m_apTop[nCnt];	//先頭のオブジェクトを代入

		// 情報が入っていたら
		while (pObject != nullptr)
		{
			// 次のオブジェクトを保存
			CObject* pObjectNext = pObject->m_pNext;

			// 死亡フラグが立っていたら
			if (pObject->m_bDeath == true)
			{
				// 前にオブジェクトがあったら
				if (pObject->m_pPrev != nullptr)
				{
					// 前の次のオブジェクトとつなげる
					pObject->m_pPrev->m_pNext = pObject->m_pNext;
				}
				else
				{
					// 次のオブジェクトに引き継がす
					m_apTop[nCnt] = pObject->m_pNext;
				}

				// 後ろがあったら
				if (pObject->m_pNext != nullptr)
				{
					// 次の前のオブジェクトとつなげる
					pObject->m_pNext->m_pPrev = pObject->m_pPrev;
				}
				else
				{
					// 前のオブジェクトに引き継がす
					m_apCur[nCnt] = pObject->m_pPrev;
				}

				pObject->m_pNext = nullptr;
				pObject->m_pPrev = nullptr;

				m_nNumAll--;

				delete pObject;
			}
			pObject = pObjectNext;
		}

	}
	
}

//すべての描画処理
void CObject::DrawAll(void)
{
	CCamera* pCamera = CManager::GetCamera();
	pCamera->SetCamera();
	
	// 描画優先順位分まわす
	for (int nCnt = 0; nCnt < NUM_PRIORITY; nCnt++)
	{
		// 先頭のオブジェクトを代入
		CObject* pObject = m_apTop[nCnt];	

		// 情報が入っていたら
		while (pObject != nullptr)
		{
			// 次のオブジェクトを保存
			CObject* pObjectNext = pObject->m_pNext;

			// 描画処理
			pObject->Draw();

			// 次のオブジェクトを代入
			pObject = pObjectNext;

		}
		

	}
}

// 最大数の取得
int CObject::Getobject(void)
{
	return m_nNumAll;
}

// タイプの代入
void CObject::SetType(TYPE type)
{
	m_type = type;
}

// タイプの取得
CObject::TYPE CObject::GetType(void)
{
	return m_type;
}
// サイズの取得
D3DXVECTOR3 CObject::SetSize(D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin, int nNumVtx, DWORD sizeFVF, BYTE* pVtxBuff)
{
	D3DXVECTOR3 Size;

	// 頂点数分回す
	for (int nCntBlock = 0; nCntBlock < nNumVtx; nCntBlock++)
	{
		// 頂点座標の代入
		D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;

		// 頂点座標の比較
		if (Vtx.x > VtxMax.x)
		{// xが最大値より大きかったら
			// 代入
			VtxMax.x = Vtx.x;
		}
		if (Vtx.y > VtxMax.y)
		{// yが最大値より大きかったら
			// 代入
			VtxMax.y = Vtx.y;
		}
		if (Vtx.z > VtxMax.z)
		{// zが最大値より大きかったら
			// 代入
			VtxMax.z = Vtx.z;
		}

		if (Vtx.x < VtxMin.x)
		{// xが最小値より小さかったら
			// 代入
			VtxMin.x = Vtx.x;
		}
		if (Vtx.y < VtxMin.y)
		{// yが最小値より小さかったら
			// 代入
			VtxMin.y = Vtx.y;
		}
		if (Vtx.z < VtxMin.z)
		{// zが最小値より小さかったら
			// 代入
			VtxMin.z = Vtx.z;
		}

		// 頂点フォーマットのサイズ分進める
		pVtxBuff += sizeFVF;
	}

	// サイズを代入する
	Size.x = VtxMax.x - VtxMin.x;	// sizeのx
	Size.y = VtxMax.y - VtxMin.y;	// sizeのy
	Size.z = VtxMax.z - VtxMin.z;	// sizeのz

	return Size;
}

//先頭アドレスの取得
CObject* CObject::GetTop(int nPriority)
{
	return m_apTop[nPriority];
}