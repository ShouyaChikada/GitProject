//=================================================
//
//	bullet.cpp
// 
// Author:chikada shouya
//
//=================================================
#include "bullet.h"
#include "input.h"
#include "enemy.h"
#include "object.h"
#include "texturemanager.h"
#include "player.h"

//=================================================
// コンストラクタ
//=================================================
CBullet::CBullet()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSpeed = NULL;
	m_nLife = NULL;
	m_nMoveTime = NULL;
	m_nIdx = NULL;
}

//=================================================
// デストラクタ
//=================================================
CBullet::~CBullet()
{

}

//=================================================
// 弾の生成
//=================================================
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CBullet* pBullet = nullptr;
	pBullet = new CBullet;

	if (pBullet != nullptr)
	{
		pBullet->SetPosition(pos);
		pBullet->m_pos = pos;
		pBullet->SetRadius(30.0f);
		pBullet->SetPath("data\\TEXTURE\\bullet000.png");
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

//=================================================
// 初期化
//=================================================
HRESULT CBullet::Init(void)
{

	// オブジェクト2Dの初期化
	CBillboard::Init();

	// 弾の寿命を設定
	m_nLife = 240;

	// CT用の設定
	m_nMoveTime = 60;

	return S_OK;
}

//=================================================
// 終了処理
//=================================================
void CBullet::Uninit(void)
{
	//終了
	CBillboard::Uninit();
}

//=================================================
// 更新処理
//=================================================
void CBullet::Update(void)
{
	//更新
	CBillboard::Update();

	//ライフをデクリメント
	m_nLife--;

	//ライフが0以下になったら
	if (m_nLife <= 0)
	{
		//弾を破棄 
		CBullet::Uninit();
	}	

	//位置を更新
	m_pos += m_move;

	// 追従
	FollowingMove();

	//位置を代入
	SetPosition(m_pos);
}

//=================================================
// プレイヤーの描画処理
//=================================================
void CBullet::Draw(void)
{
	//描画
	CBillboard::Draw();
}

//=================================================
// 追従処理
//=================================================
void CBullet::FollowingMove(void)
{

	//半径の算出変数
	float PRadiusPos = 500.0f;
	float ERadiusPos = 500.0f;

	//プレイヤーの位置の取得
	D3DXVECTOR3 PlayerPos = CPlayer::GetPos();

	//弾とプレイヤーの距離の差
	D3DXVECTOR3 diff = PlayerPos - m_pos;

	//角度
	float fAngle = atan2f(diff.x, diff.z);

	m_nMoveTime--;

	// ゼロ以下になったら
	if (m_nMoveTime <= 0)
	{
		//速度計さん
		m_fSpeed += 0.075f;
	}

	//範囲計算
	float fDisX = PlayerPos.x - m_pos.x;
	float fDisY = PlayerPos.y - m_pos.y;
	float fDisZ = PlayerPos.z - m_pos.z;

	//二つの半径を求める
	float fRadX = PRadiusPos + ERadiusPos;

	//敵の角度
	m_rot.y = fAngle;

	if ((fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ) <= (fRadX * fRadX))
	{
		//移動量を更新
		m_move.x = sinf(m_rot.y) * m_fSpeed;	//敵の見てる方向
		m_move.z = cosf(m_rot.y) * m_fSpeed;
	}

}