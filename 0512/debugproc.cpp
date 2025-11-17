//=================================================
//
//	debugproc.cpp
// 
// Author:近田 尚也
//
//=================================================
#include "debugproc.h"
#include "manager.h"

//静的メンバ変数
LPD3DXFONT CDebugProc::m_pFont = NULL;
char CDebugProc::m_aStr[1024] = {};
int CDebugProc::m_nCountFPS = 0;
int CDebugProc::m_nowIndx = 0;
bool CDebugProc::m_Enable = true;

// コンストラクタ
CDebugProc::CDebugProc()
{
	
}

// デストラクタ
CDebugProc::~CDebugProc()
{

}

// 初期化
void CDebugProc::Init(void)
{
	m_nowIndx = 0;

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
		
	//デバッグ表示用フォントの生成
	D3DXCreateFont(pDevice, 20, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &m_pFont);
		
	memset(m_aStr, NULL, sizeof(m_aStr));
}

// 終了
void CDebugProc::Uninit(void)
{
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}

// 追加
void CDebugProc::Print(const char* fmt, ...)
{
#if 1
	va_list args;//va_listマクロを使用

	va_start(args, fmt);

	if (m_nowIndx > 1024)
	{
		m_nowIndx = 0;
		return;
	}
	m_nowIndx  += vsprintf(&m_aStr[m_nowIndx], fmt, args);//vsprintfを使用する場合は　　#define _CRT_SECURE_WARNINGS
	
	va_end(args);

#endif
}

// 描画
void CDebugProc::Draw(int aWidth,int aHeight)
{
#if 1
	if (m_Enable == true)
	{
		RECT rect = { aWidth,aHeight, SCREEN_WIDTH,SCREEN_HEIGHT };

		//テキストの描画
		m_pFont->DrawText(NULL, &m_aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 255, 0, 255));

		// バッファをクリア
		memset(&m_aStr[0], NULL, sizeof(m_aStr));
	}

#endif
}