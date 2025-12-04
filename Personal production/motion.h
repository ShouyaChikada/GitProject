//=================================================
//
//	motion.h
// 
//	Author:近田尚也
//
//=================================================
#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"
#include "model.h"

#define MAX_MOTIONINFO (6)
#define NUM_MOTION (32)
#define MAX_WORD (256)
#define MAX_OMIT (3)
class CMotion
{
public:
	//モーションの種類
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,	//待機
		MOTIONTYPE_MOVE,		//移動
		MOTIONTYPE_ACTION,		//アクション
		MOTIONTYPE_JUMP,		//ジャンプ
		MOTIONTYPE_LANDING,		//着地
		MOTIONTYPE_MAX
	}MOTIONTYPE;

	//モーションの状態
	typedef enum
	{
		MOTIONSTATE_NEUTRAL = 0,	//待機
		MOTIONSTATE_MOVE,			//移動
		MOTIONSTATE_ACTION,			//アクション
		MOTIONSTATE_JUMP,			//ジャンプ
		MOTIONSTATE_LANDING,		//着地
		MOTIONSTATE_MAX
	}MOTIONSTATE;

	//キーの構造体
	typedef struct
	{
		float m_fPosX;	//位置X
		float m_fPosY;	//位置Y
		float m_fPosZ;	//位置Z
		float m_fRotX;	//向きX
		float m_fRotY;	//向きY
		float m_fRotZ;	//向きZ
	}KEY;

	//キー情報の構造体
	typedef struct
	{
		int m_nFrame;		//再生フレーム
		KEY m_aKey[NUM_MOTION];	//各パーツのキー要素
	}KEY_INFO;

	//モーション情報の構造体
	typedef struct
	{
		bool m_bLoop;				//ループするかどうか
		int m_nNumKey;			//キー総数
		KEY_INFO m_aKeyInfo[NUM_MOTION];	//キー情報
	}INFO;

	CMotion();
	~CMotion();
	HRESULT Init(const char* txt,CModel **ppModel);
	void Uninit(void);
	void Update(CModel** ppModel);
	static CMotion* Create(const char* txt, CModel** ppModel);

	// ゲッター
	int GetType(void) { return m_nType; }
	
	// セッター
	void Set(MOTIONTYPE nType) { MotionType = nType; }

private:
	D3DXVECTOR3 pos;
	int nCounterState;
	bool bJump;						//ジャンプしているかどうか
	bool bUse;

	INFO m_aInfo[NUM_MOTION];	//モーション情報1
	int nNumAll;					//モーション総数1
	MOTIONTYPE MotionType;			//モーションの種類
	//bool bLoopMotion;				//るーぷするかどうか
	int m_nCounterMotion;				//モーションカウンター
	int m_nNext;						//次のキー
	int m_nType;
	MOTIONSTATE MotionState;		//モーションの状態

	int m_PartsCount;
	int m_nFrame;
	int m_nNumKey;
	int m_Loop;
	int m_nMotion;
	int m_nKey;
	int m_nCount;
	bool m_aMotionLoop[MAX_MOTIONINFO];
	CModel** m_ppModel;	//モデルのポインタ
	int m_nNumModel;	//モデルの総数
};
#endif