//=================================================
//
//	input.h
// 
//	Author:近田尚也
//
//=================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//マクロ定義
#define NUM_KEY_MAX (256)

class CInput
{
public:
	//======================
	// マウスの種類
	//======================
	typedef enum
	{
		MOUSE_L = 0, // マウス左
		MOUSE_R,     // マウス右
		MOUSE_WHEEL,     // マウスホイール
		MOUSE_MAX
	}MouseButton;

	
	
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void);

protected:

	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};


class CInputKeyboard :public CInput
{
public:

	CInputKeyboard();
	~CInputKeyboard();
	//キーボードのプロトタイプ宣言
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool GetPress(int nKey);
	bool GetTrigger(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aOldState[NUM_KEY_MAX];
};

class CInputJoypad :public CInput
{
public:
	//===================
//パッドの種類
//===================
	typedef enum
	{
		KEY_UP = 0,	//十字キー(上)
		KEY_DOWN,	//十字キー(下)
		KEY_LEFT,	//十字キー(左)
		KEY_RIGHT,	//十字キー(右)
		KEY_START,	//STARTキー
		KEY_BACK,
		KEY_L3,
		KEY_R3,
		KEY_L1,
		KEY_R1,
		KEY_L2,
		KEY_R2,
		KEY_A,
		KEY_B,
		KEY_X,
		KEY_Y,
		KEY_MAX

	}KEY;

	//ジョイパッドのプロトタイプ宣言

	CInputJoypad();
	~CInputJoypad();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	bool GetPress(KEY key);
	bool GetTrigger(KEY key);

private:
	XINPUT_STATE m_joykeyState; //ジョイパッドのプレス情報
	XINPUT_STATE m_joykeyStateTrigger; //ジョイパッドのプレス情報
};


class CInputMouse :public CInput
{
public:

	// マウス
	CInputMouse();
	~CInputMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool OnDown(MouseButton button_type);
	bool OnDownL(MouseButton button_type);
	bool OnDownR(MouseButton button_type);
	bool OnDownWheel(MouseButton button_type);
	bool OnUp(MouseButton button_type);
	bool OnUpL(MouseButton button_type);
	bool OnUpR(MouseButton button_type);
	D3DXVECTOR2 GetVelocity();
	D3DXVECTOR2 GetVelocityOld();
private:
	BYTE m_aMauseState;
	//BYTE m_aOldMauseState;
	DIMOUSESTATE m_CurrentMouseState;		                //!< マウスの現在の入力情報
	DIMOUSESTATE m_PrevMouseState;			                //!< マウスの一フレーム前の入力情報
	DIMOUSESTATE m_aOldMouseState;		                        //!< マウスの現在の入力情報

};



#endif


