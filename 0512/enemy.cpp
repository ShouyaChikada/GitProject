//=================================================
//
//	enemy.cpp
// 
// Author:近田 尚也
//
//=================================================
#include "enemy.h"
#include "manager.h"

// 静的メンバ変数
float CEnemy::m_SizeX = 0.0f;
float CEnemy::m_SizeY = 0.0f;

// コンストラクタ
CEnemy::CEnemy()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCnt = 0;
}

// デストラクタ
CEnemy::~CEnemy()
{

}

// 敵生成
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float SizeX,float SizeY,TYPE type)
{
	CEnemy* pEnemy = NULL;
	pEnemy = new CEnemy;

	if (pEnemy != nullptr)
	{
		m_SizeX = SizeX;
		m_SizeY = SizeY;
		pEnemy->Init(pos);
		//テクスチャを設定
		pEnemy->SetType(TYPE_ENEMY);
		return pEnemy;
	}
	else
	{
		return nullptr;
	}
}

// 初期化処理
HRESULT CEnemy::Init(D3DXVECTOR3 Pos)
{
	//弾の縦横のサイズ指定
	CObject2D::SetSize(m_SizeX, m_SizeY);

	//弾のテクスチャの表示(横,縦)
	CObject2D::SetTex(1.0f, 1.0f);

	//位置を設定
	CObject2D::SetPosition(Pos);

	//オブジェクト2Dの初期化
	CObject2D::Init();

	//位置を代入
	m_pos = Pos;

	//向きを初期化
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//移動地を初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nCnt = 0;

	return S_OK;
}

//============================
//終了処理
//============================
void CEnemy::Uninit(void)
{
	CObject2D::Uninit();
}

// 更新処理
void CEnemy::Update(void)
{
	m_nCnt++;

	CObject2D::Update();

	/*if (m_nCnt >= 120)
	{
		CBullet::Create(m_pos, m_rot);
		m_nCnt = 0;
	}*/
	
	m_pos += m_move;

	CObject2D::SetPosition(m_pos);
}

// 敵の描画処理
void CEnemy::Draw(void)
{
	CObject2D::Draw();
}
