//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 近田 尚也
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

class CSound
{
public:
	//*****************************************************************************
	// サウンド一覧
	//*****************************************************************************
	typedef enum
	{
		SOUND_LABEL_BGM = 0,
		//SOUND_LABEL_SHOT01,
		SOUND_LABEL_GUN,
		SOUND_LABEL_RESULT,
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//*****************************************************************************
	// サウンド情報の構造体定義
	//*****************************************************************************
	typedef struct
	{
		const char* pFilename;	// ファイル名
		int nCntLoop;			// ループカウント
	} SOUNDINFO;

	//*****************************************************************************
	// プロトタイプ宣言
	//*****************************************************************************
	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

	//*****************************************************************************
	// プロトタイプ宣言
	//*****************************************************************************
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:

	//*****************************************************************************
	// グローバル変数
	//*****************************************************************************
	IXAudio2* m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE* m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ

	// サウンドの情報
	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX] =
	{
		{"data/SOUND/BGM.wav",0},		//BGM GAME
		{"data/SE/gun.wav",0},			//SE GUN
		{"data/SOUND/result.wav",0},	//BGM RESULT
	};
	
};


#endif
