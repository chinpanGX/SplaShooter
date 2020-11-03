/*------------------------------------------------------------

	[InputDevice.h]
	キーボード、ゲームパッド、マウスを管理
	Author : 出合翔太

-------------------------------------------------------------*/
#pragma once
#include <Windows.h>
#define DIRECTINPUT_VERSION (0x0800)	//	DirectInputのバージョン
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

// マクロ定義	
#define SAFE_RELEASE(p) do {if(p){(p)->Release(); (p) = NULL;} } while(0)	// DirectXデバイス解放マクロ
#define	NUM_KEY_MAX			(256)
// ゲームパッド用の設定値
#define DEADZONE	(2500)	// 各軸の25%を無効ゾーンとする
#define RANGE_MAX	(1000)	// 有効範囲の最大値
#define RANGE_MIN	(-1000)	// 有効範囲の最小値

//ゲームパッド（XboxとPS4）の入力のマクロ
#define LS_UP		(0x00000001l) // PS4	Xbox : 左スティック上(.IY<0)
#define LS_DOWN		(0x00000002l) // PS4	Xbox : 左スティック下(.IY>0)
#define LS_LEFT		(0x00000004l) // PS4	Xbox : 左スティック左(.IX<0)
#define LS_RIGHT	(0x00000008l) // PS4	Xbox : 左スティック右(.IX>0)
#define POV_UP		(0x00400000l) // PS4	Xbox : 方向キー上(rgdwPOV[0] = 0)
#define POV_DOWN	(0x00800000l) // PS4	Xbox : 方向キー下(.rgdwPOV[0] = 18000)
#define POV_LEFT	(0x01000000l) // PS4	Xbox : 方向キー左(.rgdwPOV[0] = 27000)
#define POV_RIGHT	(0x02000000l) // PS4	Xbox : 方向キー右(.rgdwPOV[0] = 9000)

#define BTN_1		(0x00008000l) // PS4 ： △ボタン	  Xbox : Ｙボタン(.rgbButtons[3]&0x80)
#define BTN_2		(0x00004000l) // PS4 ： 〇ボタン	  Xbox : Ｘボタン(.rgbButtons[2]&0x80)
#define BTN_3		(0x00002000l) // PS4 ： ×ボタン	  Xbox : Ｂボタン(.rgbButtons[1]&0x80)
#define BTN_4		(0x00001000l) // PS4 ： □ボタン	  Xbox : Ａボタン(.rgbButtons[0]&0x80)
#define BTN_L1		(0x00010000l) // PS4 ： L1ボタン	  Xbox : LBボタン(.rgbButtons[4]&0x80)
#define BTN_R1		(0x00020000l) // PS4 ： R1ボタン	  Xbox : RBボタン(.rgbButtons[5]&0x80)
#define BTN_L2		(0x00000400l) // PS4 : L2トリガー(.lRx>10000)
#define BTN_R2		(0x00000800l) // PS4 : R2トリガー(.lRy>10000)

#define BTN_OPTION	(0x00040000l) // PS4 ： OPTIONボタン  Xbox : BACKボタン(.rgbButtons[6]&0x80)
#define BTN_SHARE	(0x00080000l) // PS4 ： SHAREボタン	  Xbox : STARTボタン(.rgbButtons[7]&0x80)

#define RS_UP		(0x00000010l) // PS4 : 右スティック上(.lRz<16383)
#define RS_DOWN		(0x00000020l) // PS4 : 右スティック下(.lRz>49150)
#define RS_RIGHT	(0x00000040l) // PS4 : 右スティック右(.lZ<16383)
#define RS_LEFT		(0x00000080l) // PS4 : 右スティック左(.lZ>49150)

#define XboxRIGHTSTICK_UP	 (0x04000000l) // Xbox : 右スティック上(.lRz<16383)
#define XboxRIGHTSTICK_DOWN	 (0x10000000l) // Xbox : 右スティック下(.lRz>49150)
#define XboxRIGHTSTICK_LEFT	 (0x20000000l) // Xbox : 右スティック右(.lZ<16383)
#define XboxRIGHTSTICK_RIGHT (0x40000000l) // Xbox : 右スティック左(.lZ>49150
#define TRIGGER_LT			 (0x00000100l) // Xbox : LTトリガー(.lZ>49150)
#define TRIGGER_RT			 (0x00000200l) // Xbox : RTトリガー(.lZ<16383)
#define BUTTON_L3			 (0x00100000l) // Xbox : L3ボタン(.rgbButtons[8]&0x80)
#define BUTTON_R3			 (0x00200000l) // Xbox : R3ボタン(.rgbButtons[9]&0x80)

#define GAMEPADMAX (4) // 同時に接続するジョイパッドの最大数をセット

class InputDevice
{
protected:
	static LPDIRECTINPUT8 m_Input;
public:
	static bool Init(HINSTANCE hInstance, HWND hWnd);
	static void Uninit();
	static void Update();
};

/* キーボードの入力を管理 */
class KeyBoard : public InputDevice
{
private:
	static LPDIRECTINPUTDEVICE8	m_DevKeyboard;						//	キーボードデバイス
	static BYTE					m_aKeyState[NUM_KEY_MAX];			//	キーボード情報(押しているとき)
	static BYTE					m_aKeyStateTrigger[NUM_KEY_MAX];	//	キーボード情報(押した瞬間)
	static BYTE					m_aKeyStateRelease[NUM_KEY_MAX];	//	キーボード情報(離した瞬間)
public:
	static HRESULT Init(HINSTANCE hInstance, HWND hWnd);			//	初期化処理
	static void Uninit();											//	終了処理
	static void Update();											//	更新処理
	static bool IsPress(int nKey);									//	押している間
	static bool IsTrigger(int nKey);								//	押した瞬間
	static bool IsRelease(int nKey);								//	離した瞬間
};

/* ゲームパッドコントローラの入力を管理 */
class GamePad : public InputDevice
{
private:
	static LPDIRECTINPUTDEVICE8	m_GamePad[GAMEPADMAX];								//　パッドデバイス
	static DWORD				m_padState[GAMEPADMAX];								//	パッド情報(押しているとき)
	static DWORD				m_padTrigger[GAMEPADMAX];							//	パッド情報(押した瞬間)
	static int					m_padCount;											//　検出したパッドの数
public:
	static BOOL CALLBACK SearchGamePadCallback(LPDIDEVICEINSTANCE lpddi, LPVOID);	//	コールバック関数
	static HRESULT Init(HINSTANCE hInstance, HWND hWnd);							//	初期化
	static void Uninit();															//	終了処理
	static void Update();															//	更新処理
	static BOOL IsPress(int padNo, DWORD button);									//	ボタンを押している間
	static BOOL IsTrigger(int padNo, DWORD button);									//	ボタンを押した瞬間
};

/* マウスの入力を管理 */
class Mouse : public InputDevice
{
private:
	static LPDIRECTINPUTDEVICE8 m_Mouse;		// マウスデバイス
	static DIMOUSESTATE2		m_mouseState;	// マウスのダイレクトな状態
	static DIMOUSESTATE2		m_mouseTrigger;	// 押された瞬間だけON
public:
	static HRESULT	Init(HINSTANCE hInst, HWND hWnd, bool bShaw); //	初期化
	static void		Uninit();									 // 終了処理
	static HRESULT	Update();									 // 更新処理
	static BOOL		LeftPress();								 // 左クリックした状態
	static BOOL		LeftTrigger();								 // 左クリックした瞬間
	static BOOL		RightPress();								 // 右クリックした状態
	static BOOL		RightTrigger();								 // 右クリックした瞬間
	static BOOL		CenterPress();								 // 中央クリックした状態
	static BOOL		CenterTrigger();							 // 中央クリックした瞬間
	static long		GetMouseX();								 // マウスがX方向に動いた相対値
	static long		GetMouseY();								 // マウスがY方向に動いた相対値
	static long		GetMouseZ();								 // マウスホイールが動いた相対値
};




