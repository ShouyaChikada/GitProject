//=================================================
//
//	blockmanager.cpp
// 
// Author:chikada shouya
//
//=================================================
#include "blockmanager.h"

CBlock* CBlockManager::m_pBlock[MAX_BLOCK] = {};
//=================================================
// コンストラクタ
//=================================================
CBlockManager::CBlockManager()
{

}

//=================================================
// デストラクタ
//=================================================
CBlockManager::~CBlockManager()
{

}

//=================================================
// 初期化
//=================================================
HRESULT CBlockManager::Init(void)
{
	//m_pBlock[0] = CBlock::Create("data\\MODEL\\wall.x", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//m_pBlock[1] = CBlock::Create("data\\MODEL\\wall.x", D3DXVECTOR3(10.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//m_pBlock[2] = CBlock::Create("data\\MODEL\\wall.x", D3DXVECTOR3(20.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//m_pBlock[3] = CBlock::Create("data\\MODEL\\wall.x", D3DXVECTOR3(30.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//=================================================
// 破棄
//=================================================
void CBlockManager::Uninit(void)
{
	
}
//=================================================
// 更新
//=================================================
void CBlockManager::Update(void)
{

}

//=================================================
// 描画
//=================================================
void CBlockManager::Draw(void)
{

}