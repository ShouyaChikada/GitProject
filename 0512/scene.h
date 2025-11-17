//=================================================
//
//	scene.h
// 
// Author:ãﬂìc èÆñÁ
//
//=================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"
#include "object.h"

class CScene
{
public:
	typedef enum
	{
		MODE_NONE = 0,
		MODE_TITLE,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	}MODE;

	CScene(MODE mode);
	virtual ~CScene();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static MODE GetMode(void) { return m_Mode; }
private:
	MODE m_mode;
	static MODE m_Mode;
};

#endif

