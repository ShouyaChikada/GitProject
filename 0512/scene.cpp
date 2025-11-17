//=================================================
//
//	scene.cpp
// 
// Author:近田 尚也
//
//=================================================
#include "scene.h"
#include "title.h"
#include "game.h"
#include "result.h"

CScene::MODE CScene::m_Mode = MODE_NONE;

// コンストラクタ
CScene::CScene(MODE mode)
{
	m_mode = mode;
	m_Mode = mode;
}
// デストラクタ
CScene::~CScene()
{

}