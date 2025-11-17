//=================================================
//
//	bullet.cpp
// 
// Author:近田 尚也
//
//=================================================
#include "bullet.h"
#include "input.h"
#include "manager.h"
#include "explosion.h"
#include "enemy.h"
#include "object.h"
#include "effect.h"
#include "score.h"

//コンストラクタ
CBullet::CBullet()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_lifetime = 0;
}

///デストラクタ
CBullet::~CBullet() 
{

}

//弾の生成
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBullet* pBullet = nullptr;
	pBullet = new CBullet;

	if (pBullet != nullptr)
	{
		pBullet->Init(pos);
		//テクスチャを設定
		pBullet->SetType(TYPE_BULLET);
		return pBullet;
	}
	else
	{
		return nullptr;
	}
}
HRESULT CBullet::Init(D3DXVECTOR3 Pos)
{
	// 弾の縦横のサイズ指定
	CObject2D::SetSize(60.0f, 60.0f);

	// 弾のテクスチャの表示(横,縦)
	CObject2D::SetTex(1.0f, 1.0f);

	// 位置を設定
	CObject2D::SetPosition(Pos);

	// オブジェクト2Dの初期化
	CObject2D::Init();

	// 位置を代入
	m_pos = Pos;

	// 向きを初期化
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 移動地を初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 弾の寿命を設定
	m_lifetime = 60;

	return S_OK;
}

//============================
//終了処理
//============================
void CBullet::Uninit(void)
{
	//終了
	CObject2D::Uninit();
}

//更新処理
void CBullet::Update(void)
{
	//更新
	CObject2D::Update();

	//エフェクト
	//CEffect::Create(m_pos,D3DXCOLOR(1.0f,0.5f,0.0f,1.0f),40,15);

	//ライフをデクリメント
	m_lifetime--;

	//ライフが0以下になったら
	if (m_lifetime <= 0 || (m_pos.x > SCREEN_WIDTH || m_pos.x < 0.0f || m_pos.y > SCREEN_HEIGHT || m_pos.y < 0.0f))
	{
		//爆発を生成
  		CExplosion::Create(m_pos, m_rot);

		//弾を破棄 
		CBullet::Uninit();

		//エフェクトを破棄
		CEffect* pEffect = NULL;
		if (pEffect != NULL)
		{
			pEffect->Uninit();
		}
	}

	////キーボード
	//CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();
	//pInputKeyboard = CManager::GetKeyboard();

	//弾の移動量
	m_move.x = -10.0f;

	//位置を更新
	m_pos += m_move;

	//敵と弾の当たり判定
	//CollisionPlayer(m_pos);

	//プレイヤーと弾の当たり判定
	CollisionEnemy(m_pos);

	//位置を代入
	CObject2D::SetPosition(m_pos);
}

//プレイヤーの描画処理
void CBullet::Draw(void)
{

	//描画
	CObject2D::Draw();
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