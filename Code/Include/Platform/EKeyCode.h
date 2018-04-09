#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Platform)

enum EKeyCode
{
	EKeyCode_None = 0x00, // No key was pressed
	EKeyCode_LButton = 0x01, // Left mouse button
	EKeyCode_RButton = 0x02, // Right mouse button
	EKeyCode_Cancel = 0x03, // Cancel key
	EKeyCode_MButton = 0x04, // Middle mouse button
	EKeyCode_XButton1 = 0x05, // X1 mouse button
	EKeyCode_XButton2 = 0x06, // X2 mouse button
	// 0x07 is undefined
	EKeyCode_Back = 0x08,
	EKeyCode_Tab = 0x09,
	// 0x0A-0B are reserved
	EKeyCode_Clear = 0x0c, // The CLEAR key
	EKeyCode_Enter = 0x0d, // The Enter key
	// 0x0E-0F are undefined
	EKeyCode_ShiftKey = 0x10, // The Shift key
	EKeyCode_ControlKey = 0x11, // The Ctrl key
	EKeyCode_AltKey = 0x12, // The Alt key
	EKeyCode_Pause = 0x13, // The Pause key
	EKeyCode_Capital = 0x14, // The Caps Lock key
	EKeyCode_CapsLock = 0x14, // The Caps Lock key
	EKeyCode_KanaMode = 0x15, // IMI Kana mode
	EKeyCode_HanguelMode = 0x15, // IMI Hanguel mode (Use HangulMode)
	EKeyCode_HangulMode = 0x15, // IMI Hangul mode
	// 0x16 is undefined
	EKeyCode_JunjaMode = 0x17, // IMI Janja mode
	EKeyCode_FinalMode = 0x18, // IMI Final mode
	EKeyCode_HanjaMode = 0x19, // IMI Hanja mode
	EKeyCode_KanjiMode = 0x19, // IMI Kanji mode
	// 0x1A is undefined
	EKeyCode_Escape = 0x1b, // The ESC key
	EKeyCode_IMEConvert = 0x1c, // IMI convert key
	EKeyCode_IMINoConvert = 0x1d, // IMI noconvert key
	EKeyCode_IMEAccept = 0x1e, // IMI accept key
	EKeyCode_IMIModeChange = 0x1f, // IMI mode change key
	EKeyCode_Space = 0x20, // The Space key
	EKeyCode_Prior = 0x21, // The Page Up key
	EKeyCode_PageUp = 0x21, // The Page Up key
	EKeyCode_Next = 0x22, // The Page Down key
	EKeyCode_PageDown = 0x22, // The Page Down key
	EKeyCode_End = 0x23, // The End key
	EKeyCode_Home = 0x24, // The Home key
	EKeyCode_Left = 0x25, // The Left arrow key
	EKeyCode_Up = 0x26, // The Up arrow key
	EKeyCode_Right = 0x27, // The Right arrow key
	EKeyCode_Down = 0x28, // The Down arrow key
	EKeyCode_Select = 0x29, // The Select key
	EKeyCode_Print = 0x2a, // The Print key
	EKeyCode_Execute = 0x2b, // The Execute key
	EKeyCode_PrintScreen = 0x2c, // The Print Screen key
	EKeyCode_Snapshot = 0x2c, // The Print Screen key
	EKeyCode_Insert = 0x2d, // The Insert key
	EKeyCode_Delete = 0x2e, // The Delete key
	EKeyCode_Help = 0x2f, // The Help key
	EKeyCode_D0 = 0x30, // 0
	EKeyCode_D1 = 0x31, // 1
	EKeyCode_D2 = 0x32, // 2
	EKeyCode_D3 = 0x33, // 3
	EKeyCode_D4 = 0x34, // 4
	EKeyCode_D5 = 0x35, // 5
	EKeyCode_D6 = 0x36, // 6
	EKeyCode_D7 = 0x37, // 7
	EKeyCode_D8 = 0x38, // 8
	EKeyCode_D9 = 0x39, // 9
	// 0x3A - 40 are undefined
	EKeyCode_A = 0x41, // A
	EKeyCode_B = 0x42, // B
	EKeyCode_C = 0x43, // C
	EKeyCode_D = 0x44, // D
	EKeyCode_E = 0x45, // E
	EKeyCode_F = 0x46, // F
	EKeyCode_G = 0x47, // G
	EKeyCode_H = 0x48, // H
	EKeyCode_I = 0x49, // I
	EKeyCode_J = 0x4a, // J
	EKeyCode_K = 0x4b, // K
	EKeyCode_L = 0x4c, // L
	EKeyCode_M = 0x4d, // M
	EKeyCode_N = 0x4e, // N
	EKeyCode_O = 0x4f, // O
	EKeyCode_P = 0x50, // P
	EKeyCode_Q = 0x51, // Q
	EKeyCode_R = 0x52, // R
	EKeyCode_S = 0x53, // S
	EKeyCode_T = 0x54, // T
	EKeyCode_U = 0x55, // U
	EKeyCode_V = 0x56, // V
	EKeyCode_W = 0x57, // W
	EKeyCode_X = 0x58, // X
	EKeyCode_Y = 0x59, // Y
	EKeyCode_Z = 0x5a, // Z
	EKeyCode_LWin = 0x5b, // Left Windows key
	EKeyCode_RWin = 0x5c, // Right Windows key
	EKeyCode_Apps = 0x5d, // Apps key
	// 0x5E is reserved
	EKeyCode_Sleep = 0x5f, // The Sleep key
	EKeyCode_NumPad0 = 0x60, // The Numeric keypad 0 key
	EKeyCode_NumPad1 = 0x61, // The Numeric keypad 1 key
	EKeyCode_NumPad2 = 0x62, // The Numeric keypad 2 key
	EKeyCode_NumPad3 = 0x63, // The Numeric keypad 3 key
	EKeyCode_NumPad4 = 0x64, // The Numeric keypad 4 key
	EKeyCode_NumPad5 = 0x65, // The Numeric keypad 5 key
	EKeyCode_NumPad6 = 0x66, // The Numeric keypad 6 key
	EKeyCode_NumPad7 = 0x67, // The Numeric keypad 7 key
	EKeyCode_NumPad8 = 0x68, // The Numeric keypad 8 key
	EKeyCode_NumPad9 = 0x69, // The Numeric keypad 9 key
	EKeyCode_Multiply = 0x6a, // The Multiply key
	EKeyCode_Add = 0x6b, // The Add key
	EKeyCode_Separator = 0x6c, // The Separator key
	EKeyCode_Subtract = 0x6d, // The Subtract key
	EKeyCode_Decimal = 0x6e, // The Decimal key
	EKeyCode_Divide = 0x6f, // The Divide key
	EKeyCode_F1 = 0x70, // The F1 key
	EKeyCode_F2 = 0x71, // The F2 key
	EKeyCode_F3 = 0x72, // The F3 key
	EKeyCode_F4 = 0x73, // The F4 key
	EKeyCode_F5 = 0x74, // The F5 key
	EKeyCode_F6 = 0x75, // The F6 key
	EKeyCode_F7 = 0x76, // The F7 key
	EKeyCode_F8 = 0x77, // The F8 key
	EKeyCode_F9 = 0x78, // The F9 key
	EKeyCode_F10 = 0x79, // The F10 key
	EKeyCode_F11 = 0x7a, // The F11 key
	EKeyCode_F12 = 0x7b, // The F12 key
	EKeyCode_F13 = 0x7c, // The F13 key
	EKeyCode_F14 = 0x7d, // The F14 key
	EKeyCode_F15 = 0x7e, // The F15 key
	EKeyCode_F16 = 0x7f, // The F16 key
	EKeyCode_F17 = 0x80, // The F17 key
	EKeyCode_F18 = 0x81, // The F18 key
	EKeyCode_F19 = 0x82, // The F19 key
	EKeyCode_F20 = 0x83, // The F20 key
	EKeyCode_F21 = 0x84, // The F21 key
	EKeyCode_F22 = 0x85, // The F22 key
	EKeyCode_F23 = 0x86, // The F23 key
	EKeyCode_F24 = 0x87, // The F24 key
	// 0x88 - 0x8f are unassigned
	EKeyCode_NumLock = 0x90, // The Num Lock key
	EKeyCode_Scroll = 0x91, // The Scroll Lock key
	// 0x92 - 96 are OEM specific
	// 0x97 - 9f are unassigned
	EKeyCode_LShiftKey = 0xa0, // The Left Shift key
	EKeyCode_RShiftKey = 0xa1, // The Right Shift key
	EKeyCode_LControlKey = 0xa2, // The Left Control key
	EKeyCode_RControlKey = 0xa3, // The Right Control key
	EKeyCode_LMenu = 0xa4, // The Left Alt key
	EKeyCode_RMenu = 0xa5, // The Right Alt key
	EKeyCode_BrowserBack = 0xa6, // The Browser Back key
	EKeyCode_BrowserForward = 0xa7, // The Browser Forward key
	EKeyCode_BrowserRefresh = 0xa8, // The Browser Refresh key
	EKeyCode_BrowserStop = 0xa9, // The Browser Stop key
	EKeyCode_BrowserSearch = 0xaa, // The Browser Search key
	EKeyCode_BrowserFavorites = 0xab, // The Browser Favorites key
	EKeyCode_BrowserHome = 0xac, // The Browser Home key
	EKeyCode_VolumeMute = 0xad, // The Volume Mute key
	EKeyCode_VolumeDown = 0xae, // The Volume Down key
	EKeyCode_VolumeUp = 0xaf, // The Volume Up key
	EKeyCode_MediaNextTrack = 0xb0, // The Next Track key
	EKeyCode_MediaPreviousTrack = 0xb1, // The Previous Track key
	EKeyCode_MediaStop = 0xb2, // The Stop Media key
	EKeyCode_MediaPlayPause = 0xb3, // The Play/Pause Media key
	EKeyCode_LaunchMail = 0xb4, // The Start Mail key
	EKeyCode_SelectMedia = 0xb5, // The Select Media key
	EKeyCode_LaunchApplication1 = 0xb6, // The Launch Application 1 key.
	EKeyCode_LaunchApplication2 = 0xb7, // The Launch Application 2 key.
	// 0xB8 - B9 are reserved
	EKeyCode_OemSemicolon = 0xba, // Used for miscellaneous characters; it can vary by keyboard.  For the US standard keyboard, the ';:' key
	EKeyCode_Oem1 = 0xba, // Used for miscellaneous characters; it can vary by keyboard.  For the US standard keyboard, the ';:' key
	EKeyCode_OemPlus = 0xbb, // For any country/region, the '+' key
	EKeyCode_OemComma = 0xbc, // For any country/region, the ',' key
	EKeyCode_OemMinus = 0xbd, // For any country/region, the '-' key
	EKeyCode_OemPeriod = 0xbe, // For any country/region, the '.' key
	EKeyCode_OemQuestion = 0xbf, // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '/?' key
	EKeyCode_Oem2 = 0xbf, // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '/?' key
	EKeyCode_OemTilde = 0xc0, // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '`~' key
	EKeyCode_Oem3 = 0xc0, // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '`~' key
	// 0xC1 - D7 are reserved
	// 0xD8 - DA are unassigned
	EKeyCode_OemOpenBrackets = 0xdb, // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '[{' key
	EKeyCode_Oem4 = 0xdb, // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '[{' key
	EKeyCode_OemPipe = 0xdc, // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '\|' key
	EKeyCode_Oem5 = 0xdc, // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '\|' key
	EKeyCode_OemCloseBrackets = 0xdd, // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the ']}' key
	EKeyCode_Oem6 = 0xdd, // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the ']}' key
	EKeyCode_OemQuotes = 0xde, // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the 'single-quote/double-quote' key
	EKeyCode_Oem7 = 0xde, // Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the 'single-quote/double-quote' key
	EKeyCode_Oem8 = 0xdf, // Used for miscellaneous characters; it can vary by keyboard.
	// 0xE0 is reserved
	// 0xE1 is OEM specific
	EKeyCode_OemBackslash = 0xe2, // Either the angle bracket key or the backslash key on the RT 102-key keyboard
	EKeyCode_Oem102 = 0xe2, // Either the angle bracket key or the backslash key on the RT 102-key keyboard
	// 0xE3 - E4 OEM specific
	EKeyCode_ProcessKey = 0xe5, // IME Process key
	// 0xE6 is OEM specific
	EKeyCode_Packet = 0xe7, // Used to pass Unicode characters as if they were keystrokes. The Packet key value is the low word of a 32-bit virtual-key value used for non-keyboard input methods.
	// 0xE8 is unassigned
	// 0xE9 - F5 OEM specific
	EKeyCode_Attn = 0xf6, // The Attn key
	EKeyCode_CrSel = 0xf7, // The CrSel key
	EKeyCode_ExSel = 0xf8, // The ExSel key
	EKeyCode_EraseEof = 0xf9, // The Erase EOF key
	EKeyCode_Play = 0xfa, // The Play key
	EKeyCode_Zoom = 0xfb, // The Zoom key
	EKeyCode_NoName = 0xfc, // Reserved
	EKeyCode_Pa1 = 0xfd, // The PA1 key
	EKeyCode_OemClear = 0xfe, // The Clear key
};

END_NAMESPACE(Platform)
