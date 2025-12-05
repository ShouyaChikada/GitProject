//=================================================
//
//	bullet.cpp
// 
// Author:近田 尚也
//
//=================================================
#include "bullet.h"
#include "input.h"
#include "enemy.h"
#include "object.h"
#include "texturemanager.h"

//コンストラクタ
CBullet::CBullet()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_lifetime = NULL;
	m_nIdx = NULL;
}

///デストラクタ
CBullet::~CBullet() 
{

}

//弾の生成
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRadius, std::string Path)
{
	CBullet* pBullet = nullptr;
	pBullet = new CBullet;

	if (pBullet != nullptr)
	{
		pBullet->SetPosition(pos);
		pBullet->SetRadius(fRadius);
		pBullet->SetPath(Path);
		pBullet->SetType(TYPE_BULLET);
		pBullet->m_move = move;
		pBullet->Init();
		return pBullet;
	}
	else
	{
		return nullptr;
	}
}
HRESULT CBullet::Init(void)
{

	// オブジェクト2Dの初期化
	CBillboard::Init();

	// 弾の寿命を設定
	m_lifetime = 180;

	return S_OK;
}

//============================
//終了処理
//============================
void CBullet::Uninit(void)
{
	//終了
	CBillboard::Uninit();
}

//更新処理
void CBullet::Update(void)
{
	//更新
	CBillboard::Update();

	//ライフをデクリメント
	m_lifetime--;

	//ライフが0以下になったら
	if (m_lifetime <= 0)
	{
		//弾を破棄 
		CBullet::Uninit();
	}

	////弾の移動量
	//m_move.x = -10.0f;

	//位置を更新
	m_pos += m_move;

	//位置を代入
	SetPosition(m_pos);
}

//プレイヤーの描画処理
void CBullet::Draw(void)
{
	//描画
	CBillboard::Draw();
}

//当たり判定(敵)
bool CBullet::CollisionEnemy(D3DXVECTOR3 pos)
{
	//for (int nCntObj = 0; nCntObj < MAX_OBJECT;nCntObj++)
	//{
	//	CObject* pObj = NULL;

	//	//オブジェクトの取得
	//	pObj = Getobject(nCntObj);
	//	
	//	//pObjがNULLじゃなかったら
	//	if (pObj != NULL)
	//	{
	//		// 敵の位置
	//		D3DXVECTOR3 EnemyPos = pObj->GetPosition();
	//
	//		// タイプを取得
	//		TYPE type = TYPE_NONE;

	//		// 状態を取得
	//		STATE state = STATE_NONE;

	//		//種類の取得
	//		type = pObj->GetType();

	//		//種類が敵だったら
	//		if (type == TYPE_ENEMY)
	//		{
	//			//敵と重なったとき
	//			if (m_pos.x >= EnemyPos.x - 50.0f && m_pos.x <= EnemyPos.x + 50.0f
	//				&& m_pos.y >= EnemyPos.y - 50.0f && m_pos.y <= EnemyPos.y + 50.0f)
	//			{	
	//				//爆発を生成
	//				CExplosion::Create(m_pos, m_rot);

	//				//敵の終了
	//				pObj->Uninit();

	//				//弾を破棄
	//				CBullet::Uninit();

	//				CScore::Add(100);

	//				CEffect* pEffect = NULL;

	//				// NULLじゃなかったら
	//				if (pEffect != NULL)
	//				{
	//					// エフェクトの終了
	//					pEffect->Uninit();
	//				}
	//				
	//				return true;
	//			}
	//		}
	//	}
	//}
	return false;
}

void CBullet::CharngeMove(void)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 3.0f);
}