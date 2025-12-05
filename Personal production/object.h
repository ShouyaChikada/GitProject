//=================================================
//
// [object.h]
// Author:chikada shouya
//
//=================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"

// マクロ
#define MAX_OBJECT (256)
#define NUM_PRIORITY (20)

// クラス
class CObject
{
public:

	// タイプ
	typedef enum
	{
		TYPE_NONE = 0,	// 何もない
		TYPE_PLAYER,	// プレイヤー
		TYPE_ENEMY,		// 敵
		TYPE_BULLET,	// 弾
		TYPE_BLOCK,		//ブロック
		TYPE_PAUSE,		// ポーズ
		TYPE_MAX		// 最大数

	}TYPE;

	CObject(int nPriority = 3);
	virtual ~CObject();

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void SetPosition(D3DXVECTOR3 pos) = 0;
	virtual D3DXVECTOR3 GetPosition(void) = 0;

	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	// ゲッター
	static int Getobject(void);
	TYPE GetType(void);
	CObject* GetNext(void) { return m_pNext; }
	static CObject* Getobject(int nIdx);
	static CObject* GetTop(int nPriority);

	// セッター
	D3DXVECTOR3 SetSize(D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin, int nNumVtx, DWORD sizeFVF, BYTE* pVtxBuff);
	void SetType(TYPE type);

protected:

	void Release(void);

private:
	static CObject* m_apTop[NUM_PRIORITY];		//先頭オブジェクトへのポインタ
	static CObject* m_apCur[NUM_PRIORITY];		//最後尾オブジェクトへのポインタ
	CObject* m_pPrev;							//前のオブジェクトへのポインタ
	CObject* m_pNext;							//次のオブジェクトへのポインタ
	static int m_nNumAll;						//最大数
	//int m_nID;									//自分の配列を保存
	TYPE m_type;								//変更点の調整がしやすいため
	int m_nPriority;							//郵政順位の総数
	bool m_bDeath;								//死亡フラグ
};
#endif
