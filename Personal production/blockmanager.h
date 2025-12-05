//=================================================
//
//	blockmanager.h
// 
// Author:chikada shouya
//
//=================================================
#ifndef _BLOCKMANAGER_H_
#define _BLOCKMANAGER_H_

#include "main.h"
#include "block.h"

class CBlockManager
{
public:

	CBlockManager();
	~CBlockManager();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ÉQÉbÉ^Å[
	static CBlock** GetBlock(void) { return &m_pBlock[0]; }

private:
	static CBlock* m_pBlock[MAX_BLOCK];

};
#endif