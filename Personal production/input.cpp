//=================================================
//
// [input.cpp]
// Author:chikada shouya
//
//=================================================
#include"input.h"

//静的メンバ変数
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{}
//コンストラクタ
CInput::CInput()
{
	m_pDevice = NULL;
}

//デストラクタ
CInput::~CInput()
{

}

//キーボードの初期化処理
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		//DirectInput
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}
//キーボードの終了処理
void CInput::Uninit(void)
{
	//入力デバイス
	if (m_pDevice != NULL)
	{
		//アクセス権の破棄
		m_pDevice->Unacquire();

		//デバイスの破棄
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	//Direct
	if (m_pInput != NULL)
	{
		//オブジェクトの破棄
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//更新処理
void CInput::Update(void)
{

}
//{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//コンストラクタ
CInputKeyboard::CInputKeyboard()
{
	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
	{
		m_aKeyState[nCnt] = NULL;
		m_aOldState[nCnt] = NULL;
	}
}

//デストラクタ
CInputKeyboard::~CInputKeyboard()
{

}

HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	//デバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モード
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}
//キーボードの更新処理
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;
	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		m_aOldState[nCntKey] = m_aKeyState[nCntKey];
	}
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDevice->Acquire();
	}

}
//キーボードのプレス情報
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//キーボードトリガー
bool CInputKeyboard::GetTrigger(int nKey)
{
	bool Trigger = false;
	if ((m_aKeyState[nKey] & 0x80) && !(m_aOldState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//===================================================================================
//コンストラクタ
CInputJoypad::CInputJoypad()
{
	m_joykeyState;
	m_joykeyStateTrigger;
}

//デストラクタ
CInputJoypad::~CInputJoypad()
{

}

//ジョイパッドの初期化
HRESULT CInputJoypad::Init(void)
{
	//メモリのクリア
	memset(&m_joykeyState, 0, sizeof(XINPUT_STATE));
	memset(&m_joykeyStateTrigger, 0, sizeof(XINPUT_STATE));

	//Xinputのステートを設定(有効にする)
	XInputEnable(true);

	return S_OK;
}

//ジョイパッドの終了処理
void CInputJoypad::Uninit(void)
{
	//XInputのステート設定(無効にする)
	XInputEnable(false);
}

//ジョイパッドの更新処理
void CInputJoypad::Update(void)
{
	XINPUT_STATE joykeyState;	//ジョイパッドの入力情報

	//ジョイパッドの状態を取得
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		WORD Button = joykeyState.Gamepad.wButtons;
		WORD OldButton = m_joykeyState.Gamepad.wButtons;

		m_joykeyStateTrigger.Gamepad.wButtons = Button & ~OldButton;
		m_joykeyState = joykeyState;	//ジョイパッドのプレス情報の保存
	}
}

//ジョイパッドのプレス情報を保存
bool CInputJoypad::GetPress(KEY key)
{
	return (m_joykeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//ジョイパッドのトリガー
bool CInputJoypad::GetTrigger(KEY key)
{
	return (m_joykeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}
//==========================================================================================

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//コンストラクタ
CInputMouse::CInputMouse()
{
	m_CurrentMouseState = {};
	m_PrevMouseState = {};
	m_aOldMouseState = {};
}

//デストラクタ
CInputMouse::~CInputMouse()
{

}

//=====================================
// マウスの初期化処理
//=====================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// 入力デバイスの生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットの設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// 協調モード
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}
//=====================================
// マウスの終了処理
//=====================================
void CInputMouse::Uninit(void)
{
	CInput::Uninit();
}
//=====================================
// マウスの更新処理
//=====================================
void CInputMouse::Update(void)
{
	m_aOldMouseState.lX = m_CurrentMouseState.lX;
	m_aOldMouseState.lY = m_CurrentMouseState.lY;

	// 更新前に最新マウス情報を保存する
	m_PrevMouseState = m_CurrentMouseState;

	// 最新のマウスの状態を更新
	HRESULT	hr = m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurrentMouseState);

	if (FAILED(hr))
	{
		m_pDevice->Acquire();
	}

	// マウス座標を取得する
	POINT p;
	GetCursorPos(&p);

	// スクリーン座標をクライアント座標に変換する
	ScreenToClient(FindWindowA(CLASS_NAME, WINDOW_NAME), &p);

	m_CurrentMouseState.lX = p.x;
	m_CurrentMouseState.lY = p.y;

#if 0
	m_aOldMouseState.lX = m_CurrentMouseState.lX;
	m_aOldMouseState.lY = m_CurrentMouseState.lY;

	// 更新前に最新マウス情報を保存する
	m_PrevMouseState = m_CurrentMouseState;

	// 最新のマウスの状態を更新
	HRESULT	hr1 = m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurrentMouseState);

	if (FAILED(hr1))
	{
		m_pDevice->Acquire();
	}

	POINT p;
	GetCursorPos(&p);

	// スクリーン座標をクライアント座標に変換する
	ScreenToClient(FindWindowA(CLASS_NAME, nullptr), &p);

	m_CurrentMouseState.lX = p.x;
	m_CurrentMouseState.lY = p.y;
#endif
}
//=====================================
// マウスが押された処理
//=====================================
bool CInputMouse::OnDown(MouseButton button_type)
{
	if (!(m_PrevMouseState.rgbButtons[button_type] & 0x80) &&
		m_CurrentMouseState.rgbButtons[button_type] & 0x80)
	{
		return true;
	}

	return false;
}
bool CInputMouse::OnDownL(MouseButton button_type)
{
	if (m_CurrentMouseState.rgbButtons[button_type] & (0x80))
	{
		// 左クリック中
		return true;
	}
	return false;
}
bool CInputMouse::OnDownR(MouseButton button_type)
{
	if (m_CurrentMouseState.rgbButtons[button_type] & (0x80))
	{
		// 右クリック中
		return true;
	}
	return false;
}
bool CInputMouse::OnDownWheel(MouseButton button_type)
{
	if (m_CurrentMouseState.rgbButtons[button_type] & (0x80))
	{
		// 右クリック中
		return true;
	}
	return false;
}
//=====================================
// マウスが離された処理
//=====================================
bool CInputMouse::OnUp(MouseButton button_type)
{
	if (m_PrevMouseState.rgbButtons[button_type] & 0x80 &&
		!(m_CurrentMouseState.rgbButtons[button_type] & 0x80))
	{
		return true;
	}

	return false;
}
bool CInputMouse::OnUpL(MouseButton button_type)
{
	//if (!m_CurrentMouseState.rgbButtons[0] & (0x80))
	//{
	//	return true;
	//}

	return false;
}
bool CInputMouse::OnUpR(MouseButton button_type)
{
	//if (!m_CurrentMouseState.rgbButtons[1] & (0x80))
	//{
	//	return true;
	//}

	return false;
}

D3DXVECTOR2 CInputMouse::GetVelocity()
{
	return D3DXVECTOR2((float)m_CurrentMouseState.lX, (float)m_CurrentMouseState.lY);
}

D3DXVECTOR2 CInputMouse::GetVelocityOld()
{
	return D3DXVECTOR2((float)m_aOldMouseState.lX, (float)m_aOldMouseState.lY);
}
