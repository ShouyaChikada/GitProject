//=================================================
//
// [meteorock.h]	隕石(塵)のヘッダー
// Author:chikada shouya
//
//=================================================
#ifndef _CMETEOROCK_H_
#define _CMETEOROCK_H_

#include "rock.h"

class CMeteoRock :public CRock
{
public:

	CMeteoRock();
	~CMeteoRock();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMeteoRock* Create(D3DXVECTOR3 pos);

	void UpdateObjectPos(D3DXVECTOR3 pos ,D3DXVECTOR3 move);
	void MoveSphere(void);
	void FollowingMove(void);

	// ゲッター
	bool GetDeath(void) { return m_bDeath; }

private:
	D3DXVECTOR3 m_posOld;		// 前回の位置
	float m_fCountFrame;	// フレームカウント
	float m_fMaxFrame;		// マックスフレーム
	float m_fDistance;		// 距離
	float m_fRotValue;		// 回転値
	float m_fDistanceValue;	// 距離の加算
	float m_fAddValue;		// 回転する値の加算用変数
	float m_fPos;
	float m_fDiffX;
	float m_fDiffZ;
	int m_nCntValueTime;	// 加算する時間
	bool m_bDeath;			// 消すかの判定
	bool m_bSign[2];		// 飛ぶ判定
	bool m_bRelease[2];		// キーが離されているかどうか
	bool m_bTimeOut;

};

#endif