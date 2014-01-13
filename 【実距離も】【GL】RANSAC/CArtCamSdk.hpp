//==========================================================
//	ARTRAY Camera / Capture Module Software Developer Kit
//
//						Version 1.20		2003.9.4
//						Version 1.21		2003.9.18
//						Version 1.22		2003.10.10
//						Version 1.23		2004.1.21
//						Version 1.235		2004.3.19
//						Version 1.24		2004.7.9
//						Version 1.245		2004.8.17
//						Version 1.25		2004.9.1
//						Version 1.26		2004.10.28
//						Version 1.27		2005.3.8
//						Version 1.275		2005.4.18
//						Version 1.276		2005.9.5
//						Version 1.277		2005.12.22
//						Version 1.280		2007.4.4
//						Version 1.283		2008.10.07
//						Version 1.300		2009.4.24
//									(C) 2002-2009 Artray
//==========================================================


#ifndef _CARTCAMSDK_
#define _CARTCAMSDK_

#if _MSC_VER > 1000
	#pragma once
#endif


#include <windows.h>



#define WM_GRAPHNOTIFY  WM_APP + 1		// 本バージョンでは使用しません
#define WM_GRAPHPAINT	WM_APP + 2		// 映像が更新された時にアプリケーションに送られます
#define WM_ERROR		WM_APP + 3		// エラーが発生した時にアプリケーションに送られます


#define  HACAM  DWORD

enum ARTCAM_CAMERATYPE {
	// USB2シリーズ
	ARTCAM_CAMERATYPE_DS			= 1,	// DirectShow Camera
	ARTCAM_CAMERATYPE_DISABLE1		= 2,	// 無効
	ARTCAM_CAMERATYPE_USTC			= 3,	// ARTUST
	ARTCAM_CAMERATYPE_CNV			= 4,	// ARTCNV
	ARTCAM_CAMERATYPE_DISABLE2		= 5,	// 無効
	ARTCAM_CAMERATYPE_130MI			= 6,	// ARTCAM-130MI
	ARTCAM_CAMERATYPE_DISABLE3		= 7,	// 無効
	ARTCAM_CAMERATYPE_200MI			= 8,	// ARTCAM-200MI
	ARTCAM_CAMERATYPE_300MI			= 9,	// ARTCAM-300MI
	ARTCAM_CAMERATYPE_150P			= 10,	// ARTCAM-150P
	ARTCAM_CAMERATYPE_320P			= 11,	// ARTCAM-320P
	ARTCAM_CAMERATYPE_DISABLE4		= 12,	// 無効
	ARTCAM_CAMERATYPE_200SH			= 13,	// ARTCAM-200SH
	ARTCAM_CAMERATYPE_098			= 14,	// ARTCAM-098
	ARTCAM_CAMERATYPE_036MI			= 15,	// ARTCAM-036MI
	ARTCAM_CAMERATYPE_500P			= 16,	// ARTCAM-500P
	ARTCAM_CAMERATYPE_150P2			= 17,	// ARTCAM-150PⅡ
	ARTCAM_CAMERATYPE_036MIST		= 18,	// ARTCAM-036MIST
	ARTCAM_CAMERATYPE_500MI			= 19,	// ARTCAM-500MI
	ARTCAM_CAMERATYPE_DISABLE5		= 20,	// 無効
	ARTCAM_CAMERATYPE_DISABLE6		= 21,	// 無効
	ARTCAM_CAMERATYPE_150P3			= 22,	// ARTCAM-150PⅢ
	ARTCAM_CAMERATYPE_130MI_MOUT	= 23,	// ARTCAM-130MI MOUT
	ARTCAM_CAMERATYPE_150P3_MOUT	= 24,	// ARTCAM-150PⅢ MOUT
	ARTCAM_CAMERATYPE_267KY			= 25,	// ARTCAM-267KY
	ARTCAM_CAMERATYPE_274KY			= 26,	// ARTCAM-274KY
	ARTCAM_CAMERATYPE_625KY			= 27,	// ARTCAM-274KY
	ARTCAM_CAMERATYPE_V135MI		= 28,	// ARTCAM-V135MI
	ARTCAM_CAMERATYPE_445KY			= 29,	// ARTCAM-445KY
	ARTCAM_CAMERATYPE_098II			= 30,	// ARTCAM-098II
	ARTCAM_CAMERATYPE_MV413			= 31,	// ARTCAM-MV413USB
	ARTCAM_CAMERATYPE_OV210			= 32,	// ARTCAM-OV210
	ARTCAM_CAMERATYPE_850SH			= 33,	// ARTCAM-850SH
	ARTCAM_CAMERATYPE_1251SH		= 34,	// ARTCAM-1252SH
	ARTCAM_CAMERATYPE_D131			= 35,	// ARTCAM-D131
	ARTCAM_CAMERATYPE_900MI			= 36,	// ARTCAM-900MI
	ARTCAM_CAMERATYPE_1000MI		= 37,	// ARTCAM-1000MI
	ARTCAM_CAMERATYPE_500P2			= 38,	// ARTCAM-500P2
	


	// SATA シリーズ
	ARTCAM_CAMERATYPE_SATA			= 201,	// SATA CAMERA
};

// SATA カメラタイプ
enum ARTCAM_CAMERATYPE_SATA {
	ARTCAM_CAMERATYPE_SATA_LVDS		= 0,
	ARTCAM_CAMERATYPE_SATA_300MI	= 1,
	ARTCAM_CAMERATYPE_SATA_500MI	= 2,
	ARTCAM_CAMERATYPE_SATA_MV413	= 3,
	ARTCAM_CAMERATYPE_SATA_800MI	= 4,
	ARTCAM_CAMERATYPE_SATA_036MI	= 5,
	ARTCAM_CAMERATYPE_SATA_150P		= 6,
	ARTCAM_CAMERATYPE_SATA_267KY	= 6,
	ARTCAM_CAMERATYPE_SATA_274KY	= 7,
	ARTCAM_CAMERATYPE_SATA_625KY	= 8,
	ARTCAM_CAMERATYPE_SATA_130MI	= 9,
	ARTCAM_CAMERATYPE_SATA_200MI	=10,
};


// エラーコード
enum ARTCAMSDK_ERROR {
	ARTCAMSDK_NOERROR = 0,			// 正常
	ARTCAMSDK_NOT_INITIALIZE,		// 初期化されてません
	ARTCAMSDK_DISABLEDDEVICE,		// 利用不可能なデバイスにアクセスしようとしました
	ARTCAMSDK_CREATETHREAD,			// 画像取り込み用スレッド作成に失敗
	ARTCAMSDK_CREATEWINDOW,			// ウィンドウ作成に失敗
	ARTCAMSDK_OUTOFMEMORY,			// イメージ転送に十分なメモリを確保していない　又は　メモリの確保に失敗
	ARTCAMSDK_CAMERASET,			// カメラ（デバイス）の設定でエラー
	ARTCAMSDK_CAMERASIZE,			// カメラ（デバイス）のサイズ設定でエラー
	ARTCAMSDK_CAPTURE,				// 映像取り込みで失敗
	ARTCAMSDK_PARAM,				// 引数が間違ってます
	ARTCAMSDK_DIRECTSHOW,			// DirectShow 初期化エラー
	ARTCAMSDK_UNSUPPORTED,			// この機能はサポートされていません
	ARTCAMSDK_UNKNOWN,				// 不明のエラー
	ARTCAMSDK_CAPTURELOST,			// デバイスが消失
	ARTCAMSDK_FILENOTFOUND,			// 指定ファイルが見つからない
	ARTCAMSDK_FPGASET,				// FPGAの設定でエラー
	ARTCAMSDK_TRANSIMAGEFAILED,		// 画像転送に失敗
};

// 転送する情報
typedef struct GP_INFO {
	LONG	lSize;			// 構造体のサイズ sizeof(GP_INFO)
	LONG	lWidth;			// 画像の幅
	LONG	lHeight;		// 画像の高さ
	LONG	lBpp;			// 画像のビット震度
	LONG	lFps;			// フレームレート（実際の10倍の値）
	LPBYTE	pImage;			// CallBackPreview等で指定した画像のポインタ
} *LPGP_INFO;

// カメラの情報
typedef struct CAMERAINFO {
	LONG	lSize;				// 構造体のサイズ
	LONG	lWidth;				// カメラの有効最大幅
	LONG	lHeight;			// カメラの有効最大高さ
	LONG	lGlobalGainMin;		// グローバルゲインの最低値（使用不可能のカメラは－１）
	LONG	lGlobalGainMax;		// グローバルゲインの最低値（使用不可能のカメラは－１）
	LONG	lColorGainMin;		// カラーゲインの最低値（使用不可能のカメラは－１）
	LONG	lColorGainMax;		// カラーゲインの最低値（使用不可能のカメラは－１）
	LONG	lExposureMin;		// 露光時間の最低値（使用不可能のカメラは－１）
	LONG	lExposureMax;		// 露光時間の最低値（使用不可能のカメラは－１）
} *LPCAMERAINFO;


// 画像フィルターの種別
enum ARTCAM_FILTERTYPE {
	ARTCAM_FILTERTYPE_RESERVE = 0,			// 予約されてます
	ARTCAM_FILTERTYPE_BRIGHTNESS,			// 明るさ
	ARTCAM_FILTERTYPE_CONTRAST,				// コントラスト
	ARTCAM_FILTERTYPE_HUE,					// 色相
	ARTCAM_FILTERTYPE_SATURATION,			// 彩度
	ARTCAM_FILTERTYPE_SHARPNESS,			// 鮮明さ
	ARTCAM_FILTERTYPE_BAYER_GAIN_RGB,		// ベイヤー変換のカラーゲイン
	ARTCAM_FILTERTYPE_BAYER_GAIN_R,			// ベイヤー変換のカラーゲイン（赤のみ）
	ARTCAM_FILTERTYPE_BAYER_GAIN_G,			// ベイヤー変換のカラーゲイン（緑のみ）
	ARTCAM_FILTERTYPE_BAYER_GAIN_B,			// ベイヤー変換のカラーゲイン（青のみ）
	ARTCAM_FILTERTYPE_BAYER_GAIN_AUTO,		// 自動ホワイトバランス調整
	ARTCAM_FILTERTYPE_GAMMA,				// ガンマ
	ARTCAM_FILTERTYPE_BAYERMODE,			// ベイヤー変換モード
	ARTCAM_FILTERTYPE_GLOBAL_GAIN,			// カメラのグローバルゲイン
	ARTCAM_FILTERTYPE_COLOR_GAIN_R,			// カメラのカラーゲイン（赤）
	ARTCAM_FILTERTYPE_COLOR_GAIN_G1,		// カメラのカラーゲイン（緑１）
	ARTCAM_FILTERTYPE_COLOR_GAIN_G2,		// カメラのカラーゲイン（緑２）
	ARTCAM_FILTERTYPE_COLOR_GAIN_B,			// カメラのカラーゲイン（青）
	ARTCAM_FILTERTYPE_EXPOSURETIME,			// 露光時間（シャッタースピード）
	ARTCAM_FILTERTYPE_GRAY_MODE,			// グレースケール化　処理モード
	ARTCAM_FILTERTYPE_GRAY_GAIN_R,			// グレースケール化　ゲイン（赤）
	ARTCAM_FILTERTYPE_GRAY_GAIN_G1,			// グレースケール化　ゲイン（緑１）
	ARTCAM_FILTERTYPE_GRAY_GAIN_G2,			// グレースケール化　ゲイン（緑２）
	ARTCAM_FILTERTYPE_GRAY_GAIN_B,			// グレースケール化　ゲイン（青）
	ARTCAM_FILTERTYPE_GRAY_OFFSET_R,		// グレースケール化　オフセット（赤）
	ARTCAM_FILTERTYPE_GRAY_OFFSET_G1,		// グレースケール化　オフセット（緑１）
	ARTCAM_FILTERTYPE_GRAY_OFFSET_G2,		// グレースケール化　オフセット（緑２）
	ARTCAM_FILTERTYPE_GRAY_OFFSET_B,		// グレースケール化　オフセット（青）
};

// 過去のバージョンとの互換
#define ARTCAM_FILTERTYPE_RGB_GAIN		ARTCAM_FILTERTYPE_BAYER_GAIN_RGB
#define ARTCAM_FILTERTYPE_R_GAIN		ARTCAM_FILTERTYPE_BAYER_GAIN_R
#define ARTCAM_FILTERTYPE_G_GAIN		ARTCAM_FILTERTYPE_BAYER_GAIN_G
#define ARTCAM_FILTERTYPE_B_GAIN		ARTCAM_FILTERTYPE_BAYER_GAIN_B
#define ARTCAM_FILTERTYPE_AUTO_GAIN		ARTCAM_FILTERTYPE_BAYER_GAIN_AUTO


// 間引き転送モード
enum {
	SUBSAMPLE_1 = 0,	// フルサイズ
	SUBSAMPLE_2,		// １／２
	SUBSAMPLE_4,		// １／４
	SUBSAMPLE_8,		// １／８
	BINNING_2   = 0x10,
	BINNING_4	= 0x11,
};


// オートアイリスモード
enum AI_TYPE {
	AI_NONE = 0,		// 無効
	AI_EXPOSURE,		// 露出時間
	AI_GAIN,			// ゲイン
	AI_BOTH,			// 露光時間 + ゲイン
};


// グレースケール処理モード
enum GRAY_TYPE {
	GRAY_NONE = 0,		// 無効　ベイヤー配列のまま
	GRAY_BAYERCONVERT,	// ベイヤー配列に GRAY GAIN と GRAY OFFSET で演算を加える
	GRAY_GRAYSCALE,		// カラー変換した後、輝度情報のみにする
};


// ビデオフォーマット
enum VIDEOFORMAT {
	VIDEOFORMAT_NTSC = 0,	// NTSC
	VIDEOFORMAT_PAL,		// PAL
	VIDEOFORMAT_PALM,		// PALM
	VIDEOFORMAT_SECAM,		// SECAM
};

// サンプリングレート
enum SAMPLING_RATE {
	WIDE_HISPEED = 0,	// 
	WIDE_LOWSPEED,		// 
	NORMAL_HISPEED,		// 
	NORMAL_LOWSPEED,	// 
};


// 画像保存形式
enum FILETYPE {
	FILETYPE_BITMAP = 0,	// ビットマップで保存します。サイズ大
	FILETYPE_RAW,			// データ部分のみを保存します。サイズ大
	FILETYPE_JPEG_HIGH,		// 高品質のJPEGで保存します。文字やラインは崩れます。サイズ中
	FILETYPE_JPEG_NOMAL,	// 標準品質のJPEGで保存します。細かいパターン等は崩れます。サイズ低
	FILETYPE_JPEG_LOW,		// 低品質のJPEGで保存します。ブロックノイズが目立ちます。サイズ低
	FILETYPE_PNG,			// PNGで保存します。16ビット画像も正確に保存できます。サイズ中
	FILETYPE_TIFF,			// TIFFで保存します。16ビット画像も正確に保存できます。サイズ大
};


/*
　※注意※
　16ビット画像は全ての環境、画像ソフトウェアで読み込めるものではありません。
　本SDKで保存できる16ビットPNG,TIFFに関しては
　弊社製のビューアソフトウェア version 2.0以降、Adobe Photoshop 6で正常に読み込めることを確認しています。
　未対応のソフト等で読み込むと、画像が乱れて表示されたり、不正終了やファイルのロック等の症状が出ることがあります。
　ご注意ください
　
　16ビットビットマップで保存した場合は16ビットのグレースケール画像として保存しているので
　カラーパレット等は保存していません。ソフト側で16ビットのパレットを用意するか、
　グレースケールのデバイスコンテキストを用意する必要があります
　16ビットで保存する際はTIFF、もしくはPNGで保存する事をお勧めします。
　
　JPEGではカラー画像以外は保存できません。
　８ビット16ビット画像はモノクロのカラー画像として保存されます。
　特に16ビット画像に関しては下位８ビットのデータが切り捨てられて保存されます。
*/






typedef DWORD		(*GETDLLVERSION)		(void);
typedef LONG		(*GETLASTERROR)			(HACAM hACam);

typedef HACAM		(*INITIALIZE)			(HWND hWnd);
typedef BOOL		(*RELEASE)				(HACAM hACam);

typedef BOOL		(*PREVIEW)				(HACAM hACam);
typedef BOOL		(*RECORD)				(HACAM hACam, LPCTSTR lpAviName, UINT RecTime, BOOL fShow);
typedef BOOL		(*CALLBACKPREVIEW)		(HACAM hACam, HWND hWnd, LPBYTE lpImage, LONG Size, BOOL TopDown);
typedef BOOL		(*SNAPSHOT)				(HACAM hACam, LPBYTE lpImage, LONG Size, BOOL TopDown);
typedef BOOL		(*CLOSE)				(HACAM hACam);
typedef BOOL		(*CAPTURE)				(HACAM hACam);
typedef BOOL		(*TRIGGER)				(HACAM hACam, HWND hWnd, LPBYTE lpImage, LONG Size, BOOL TopDown);
typedef BOOL		(*SAVEIMAGE)			(HACAM hACam, LPCTSTR lpSaveName, LONG FileType);

typedef BOOL		(*SETPREVIEWWINDOW)		(HACAM hACam, HWND hWnd, LONG Left, LONG Top, LONG Right, LONG Bottom);
typedef BOOL		(*SETCAPTUREWINDOW)		(HACAM hACam, LONG Width, LONG Height, LONG Fps);
typedef BOOL		(*SETCAPTUREWINDOWEX)	(HACAM hACam, LONG HTotal, LONG HStart, LONG HEffective, LONG VTotal, LONG VStart, LONG VEffective);
typedef BOOL		(*GETCAPTUREWINDOWEX)	(HACAM hACam, LONG* HTotal, LONG* HStart, LONG* HEffective, LONG* VTotal, LONG* VStart, LONG* VEffective);

typedef BOOL		(*SETCOLORMODE)			(HACAM hACam, LONG ColorMode);
typedef LONG		(*GETCOLORMODE)			(HACAM hACam);

typedef BOOL		(*SETCROSSBAR)			(HACAM hACam, LONG Output, LONG Input);
typedef BOOL		(*SETDEVICENUMBER)		(HACAM hACam, LONG Number);
typedef LONG		(*ENUMDEVICE)			(HACAM hACam, TCHAR szDeviceName[10][256]);
typedef BOOL		(*GETDEVICENAME)		(HACAM hACam, LONG index, LPSTR szDeviceName, LONG nSize);

typedef BOOL		(*STARTPREVIEW)			(HACAM hACam);
typedef BOOL		(*STOPPREVIEW)			(HACAM hACam);
typedef BOOL		(*GETIMAGE)				(HACAM hACam, LPBYTE lpImage, LONG Size, BOOL TopDown);

typedef LONG		(*WIDTH)				(HACAM hACam);
typedef LONG		(*HEIGHT)				(HACAM hACam);
typedef LONG		(*FPS)					(HACAM hACam);

typedef BOOL		(*SETCAMERADLG)			(HACAM hACam, HWND hWnd);
typedef BOOL		(*SETIMAGEDLG)			(HACAM hACam, HWND hWnd);
typedef BOOL		(*SETANALOGDLG)			(HACAM hACam, HWND hWnd);

typedef BOOL		(*SETIOPORT)			(HACAM hACam, BYTE byteData, LONG longData, DWORD Reserve);
typedef BOOL		(*GETIOPORT)			(HACAM hACam, LPBYTE byteData, LPLONG longData, DWORD Reserve);
typedef BOOL		(*SETFILTERVALUE)		(HACAM hACam, LONG FilterType, LONG Value);
typedef LONG		(*GETFILTERVALUE)		(HACAM hACam, LONG FilterType, LPBOOL Error);

typedef BOOL		(*SETSUBSAMPLE)			(HACAM hACam, LONG SubSampleMode);
typedef LONG		(*GETSUBSAMPLE)			(HACAM hACam);
typedef BOOL		(*SETWAITTIME)			(HACAM hACam, LONG WaitTime);
typedef LONG		(*GETWAITTIME)			(HACAM hACam);


typedef BOOL		(*SETMIRRORV)			(HACAM hACam, BOOL Flg);
typedef BOOL		(*GETMIRRORV)			(HACAM hACam);
typedef BOOL		(*SETMIRRORH)			(HACAM hACam, BOOL Flg);
typedef BOOL		(*GETMIRRORH)			(HACAM hACam);

typedef BOOL		(*SETBRIGHTNESS)		(HACAM hACam, LONG Value);
typedef LONG		(*GETBRIGHTNESS)		(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETCONTRAST)			(HACAM hACam, LONG Value);
typedef LONG		(*GETCONTRAST)			(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETHUE)				(HACAM hACam, LONG Value);
typedef LONG		(*GETHUE)				(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETSATURATION)		(HACAM hACam, LONG Value);
typedef LONG		(*GETSATURATION)		(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETSHARPNESS)			(HACAM hACam, LONG Value);
typedef LONG		(*GETSHARPNESS)			(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETBAYERGAINRGB)		(HACAM hACam, LONG Value);
typedef LONG		(*GETBAYERGAINRGB)		(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETBAYERGAINRED)		(HACAM hACam, LONG Value);
typedef LONG		(*GETBAYERGAINRED)		(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETBAYERGAINGREEN)	(HACAM hACam, LONG Value);
typedef LONG		(*GETBAYERGAINGREEN)	(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETBAYERGAINBLUE)		(HACAM hACam, LONG Value);
typedef LONG		(*GETBAYERGAINBLUE)		(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETBAYERGAINAUTO)		(HACAM hACam, LONG Value);
typedef LONG		(*GETBAYERGAINAUTO)		(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETGAMMA)				(HACAM hACam, LONG Value);
typedef LONG		(*GETGAMMA)				(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETBAYERMODE)			(HACAM hACam, LONG Value);
typedef LONG		(*GETBAYERMODE)			(HACAM hACam, LPBOOL Error);

typedef BOOL		(*SETGLOBALGAIN)		(HACAM hACam, LONG Value);
typedef LONG		(*GETGLOBALGAIN)		(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETCOLORGAINRED)		(HACAM hACam, LONG Value);
typedef LONG		(*GETCOLORGAINRED)		(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETCOLORGAINGREEN1)	(HACAM hACam, LONG Value);
typedef LONG		(*GETCOLORGAINGREEN1)	(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETCOLORGAINGREEN2)	(HACAM hACam, LONG Value);
typedef LONG		(*GETCOLORGAINGREEN2)	(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETCOLORGAINBLUE)		(HACAM hACam, LONG Value);
typedef LONG		(*GETCOLORGAINBLUE)		(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETEXPOSURETIME)		(HACAM hACam, LONG Value);
typedef LONG		(*GETEXPOSURETIME)		(HACAM hACam, LPBOOL Error);

typedef BOOL		(*SETHALFCLOCK)			(HACAM hACam, LONG Value);
typedef LONG		(*GETHALFCLOCK)			(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETAUTOIRIS)			(HACAM hACam, LONG Value);
typedef LONG		(*GETAUTOIRIS)			(HACAM hACam, LPBOOL Error);

typedef BOOL		(*SETSAMPLINGRATE)		(HACAM hACam, LONG Value);
typedef LONG		(*GETSAMPLINGRATE)		(HACAM hACam, LPBOOL Error);
typedef LONG		(*GETVIDEOFORMAT)		(HACAM hACam, LPBOOL Error);

typedef BOOL		(*WRITESROMID)			(HACAM hACam, LONG Address, LONG Value);
typedef LONG		(*READSROMID)			(HACAM hACam, LONG Address, LPBOOL Error);

typedef BOOL		(*GETCAMERAINFO)		(HACAM hACam, LPCAMERAINFO pInfo);
typedef LONG		(*GETSTATUS)			(HACAM hACam, LPBOOL Error);

typedef BOOL		(*WRITEREGISTER)		(HACAM hACam, BYTE Address, DWORD Value);
typedef DWORD		(*READREGISTER)			(HACAM hACam, BYTE Address, LPBOOL Error);

typedef BOOL		(*WRITEREGISTEREX)		(HACAM hACam, DWORD Address, DWORD Value);
typedef DWORD		(*READREGISTEREX)		(HACAM hACam, DWORD Address, LPBOOL Error);


typedef BOOL		(*SETGRAYMODE)			(HACAM hACam, LONG Value);
typedef LONG		(*GETGRAYMODE)			(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETGRAYGAINR)			(HACAM hACam, LONG Value);
typedef LONG		(*GETGRAYGAINR)			(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETGRAYGAING1)		(HACAM hACam, LONG Value);
typedef LONG		(*GETGRAYGAING1)		(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETGRAYGAING2)		(HACAM hACam, LONG Value);
typedef LONG		(*GETGRAYGAING2)		(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETGRAYGAINB)			(HACAM hACam, LONG Value);
typedef LONG		(*GETGRAYGAINB)			(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETGRAYOFFSETR)		(HACAM hACam, LONG Value);
typedef LONG		(*GETGRAYOFFSETR)		(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETGRAYOFFSETG1)		(HACAM hACam, LONG Value);
typedef LONG		(*GETGRAYOFFSETG1)		(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETGRAYOFFSETG2)		(HACAM hACam, LONG Value);
typedef LONG		(*GETGRAYOFFSETG2)		(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETGRAYOFFSETB)		(HACAM hACam, LONG Value);
typedef LONG		(*GETGRAYOFFSETB)		(HACAM hACam, LPBOOL Error);

typedef BOOL		(*SETCAMERATYPE)		(HACAM hACam, LONG Flg);
typedef LONG		(*GETCAMERATYPE)		(HACAM hACam, LPBOOL Error);

typedef BOOL		(*SETSYNCV)				(HACAM hACam, LONG Flg);
typedef LONG		(*GETSYNCV)				(HACAM hACam, LPBOOL Error);
typedef BOOL		(*SETSYNCH)				(HACAM hACam, LONG Flg);
typedef LONG		(*GETSYNCH)				(HACAM hACam, LPBOOL Error);

typedef BOOL		(*FPGA_WRITEREGISTER)	(HACAM hACam, BYTE Address, DWORD Value);
typedef DWORD		(*FPGA_READREGISTER)	(HACAM hACam, BYTE Address, LPBOOL Error);

typedef BOOL		(*MONITOR_SETPREVIEWMODE)		(HACAM hACam, BOOL Preview);
typedef BOOL		(*MONITOR_GETPREVIEWMODE)		(HACAM hACam, LPBOOL Error);
typedef BOOL		(*MONITOR_SETPREVIEWSIZE)		(HACAM hACam, LONG Width, LONG Height);
typedef BOOL		(*MONITOR_GETPREVIEWSIZE)		(HACAM hACam, LONG* Width, LONG* Height);
typedef BOOL		(*MONITOR_SETCOLORMODE)			(HACAM hACam, BOOL ColorMode);
typedef BOOL		(*MONITOR_GETCOLORMODE)			(HACAM hACam, LPBOOL Error);
typedef BOOL		(*MONITOR_SETCAMERACLOCK)		(HACAM hACam, LONG Value);
typedef LONG		(*MONITOR_GETCAMERACLOCK)		(HACAM hACam, LPBOOL Error);
typedef BOOL		(*MONITOR_SETBAYERGAINAUTO)		(HACAM hACam, LONG Value);
typedef LONG		(*MONITOR_GETBAYERGAINAUTO)		(HACAM hACam, LPBOOL Error);
typedef BOOL		(*MONITOR_SETBAYERGAINLOCK)		(HACAM hACam, LONG Value);
typedef LONG		(*MONITOR_GETBAYERGAINLOCK)		(HACAM hACam, LPBOOL Error);
typedef BOOL		(*MONITOR_SETBAYERGAINRED)		(HACAM hACam, LONG Value);
typedef LONG		(*MONITOR_GETBAYERGAINRED)		(HACAM hACam, LPBOOL Error);
typedef BOOL		(*MONITOR_SETBAYERGAINGREEN)	(HACAM hACam, LONG Value);
typedef LONG		(*MONITOR_GETBAYERGAINGREEN)	(HACAM hACam, LPBOOL Error);
typedef BOOL		(*MONITOR_SETBAYERGAINBLUE)		(HACAM hACam, LONG Value);
typedef LONG		(*MONITOR_GETBAYERGAINBLUE)		(HACAM hACam, LPBOOL Error);


typedef BOOL		(*MONITOR_SAVECURRENTSETTINGS)		(HACAM hACam);
typedef BOOL		(*MONITOR_INITREGISTERSETTINGS)		(HACAM hACam, LONG Flg);

typedef BOOL		(*MONITOR_SETCROSSCURSORMODE)		(HACAM hACam, LONG CursorNum, LONG Value);
typedef LONG		(*MONITOR_GETCROSSCURSORMODE)		(HACAM hACam, LONG CursorNum, LPBOOL Error);
typedef BOOL		(*MONITOR_SETCROSSCURSORCOLORR)		(HACAM hACam, LONG CursorNum, LONG Value);
typedef LONG		(*MONITOR_GETCROSSCURSORCOLORR)		(HACAM hACam, LONG CursorNum, LPBOOL Error);
typedef BOOL		(*MONITOR_SETCROSSCURSORCOLORG)		(HACAM hACam, LONG CursorNum, LONG Value);
typedef LONG		(*MONITOR_GETCROSSCURSORCOLORG)		(HACAM hACam, LONG CursorNum, LPBOOL Error);
typedef BOOL		(*MONITOR_SETCROSSCURSORCOLORB)		(HACAM hACam, LONG CursorNum, LONG Value);
typedef LONG		(*MONITOR_GETCROSSCURSORCOLORB)		(HACAM hACam, LONG CursorNum, LPBOOL Error);
typedef BOOL		(*MONITOR_SETCROSSCURSORCOLORRGB)	(HACAM hACam, LONG CursorNum, LONG Value);
typedef LONG		(*MONITOR_GETCROSSCURSORCOLORRGB)	(HACAM hACam, LONG CursorNum, LPBOOL Error);
typedef BOOL		(*MONITOR_SETCROSSCURSORPOS)		(HACAM hACam, LONG CursorNum, LONG  ValueX, LONG  ValueY);
typedef BOOL		(*MONITOR_GETCROSSCURSORPOS)		(HACAM hACam, LONG CursorNum, LONG* ValueX, LONG* ValueY);
typedef BOOL		(*MONITOR_SETCROSSCURSORSIZE)		(HACAM hACam, LONG CursorNum, LONG  ValueX, LONG  ValueY);
typedef BOOL		(*MONITOR_GETCROSSCURSORSIZE)		(HACAM hACam, LONG CursorNum, LONG* ValueX, LONG* ValueY);

typedef BOOL		(*MONITOR_SETAUTOIRISMODE)			(HACAM hACam, LONG Value);
typedef LONG		(*MONITOR_GETAUTOIRISMODE)			(HACAM hACam, LPBOOL Error);
typedef BOOL		(*MONITOR_SETAUTOIRISRANGE)			(HACAM hACam, LONG  Min, LONG  Max);
typedef BOOL		(*MONITOR_GETAUTOIRISRANGE)			(HACAM hACam, LONG* Min, LONG* Max);
typedef BOOL		(*MONITOR_LOADFIRMWARE)				(HACAM hACam, LPCTSTR szFileName);

typedef LONG		(*GETREALEXPOSURETIME)				(HACAM hACam);


class CArtCamSdk{
private:
	HINSTANCE	m_hArtCamSdk;
	HACAM		m_hACam;


	GETDLLVERSION		m_GetDllVersion;
	GETLASTERROR		m_GetLastError;

	INITIALIZE			m_Initialize;
	RELEASE				m_Release;

	PREVIEW				m_Preview;
	RECORD				m_Record;
	CALLBACKPREVIEW		m_CallBackPreview;
	SNAPSHOT			m_SnapShot;
	CLOSE				m_Close;
	CAPTURE				m_Capture;
	TRIGGER				m_Trigger;
	SAVEIMAGE			m_SaveImage;

	SETPREVIEWWINDOW	m_SetPreviewWindow;
	SETCAPTUREWINDOW	m_SetCaptureWindow;
	SETCAPTUREWINDOWEX	m_SetCaptureWindowEx;
	GETCAPTUREWINDOWEX	m_GetCaptureWindowEx;

	SETCOLORMODE		m_SetColorMode;
	GETCOLORMODE		m_GetColorMode;

	SETCROSSBAR			m_SetCrossbar;
	SETDEVICENUMBER		m_SetDeviceNumber;
	ENUMDEVICE			m_EnumDevice;
	GETDEVICENAME		m_GetDeviceName;

	STARTPREVIEW		m_StartPreview;
	STOPPREVIEW			m_StopPreview;
	GETIMAGE			m_GetImage;

	WIDTH				m_Width;
	HEIGHT				m_Height;
	FPS					m_Fps;

	SETCAMERADLG		m_SetCameraDlg;
	SETIMAGEDLG			m_SetImageDlg;
	SETANALOGDLG		m_SetAnalogDlg;

	SETIOPORT			m_SetIOPort;
	GETIOPORT			m_GetIOPort;
	SETFILTERVALUE		m_SetFilterValue;
	GETFILTERVALUE		m_GetFilterValue;

	SETSUBSAMPLE		m_SetSubSample;
	GETSUBSAMPLE		m_GetSubSample;
	SETWAITTIME			m_SetWaitTime;
	GETWAITTIME			m_GetWaitTime;

	SETMIRRORV			m_SetMirrorV;
	GETMIRRORV			m_GetMirrorV;
	SETMIRRORH			m_SetMirrorH;
	GETMIRRORH			m_GetMirrorH;

	SETBRIGHTNESS		m_SetBrightness;
	GETBRIGHTNESS		m_GetBrightness;
	SETCONTRAST			m_SetContrast;
	GETCONTRAST			m_GetContrast;
	SETHUE				m_SetHue;
	GETHUE				m_GetHue;
	SETSATURATION		m_SetSaturation;
	GETSATURATION		m_GetSaturation;
	SETSHARPNESS		m_SetSharpness;
	GETSHARPNESS		m_GetSharpness;
	SETBAYERGAINRGB		m_SetBayerGainRGB;
	GETBAYERGAINRGB		m_GetBayerGainRGB;
	SETBAYERGAINRED		m_SetBayerGainRed;
	GETBAYERGAINRED		m_GetBayerGainRed;
	SETBAYERGAINGREEN	m_SetBayerGainGreen;
	GETBAYERGAINGREEN	m_GetBayerGainGreen;
	SETBAYERGAINBLUE	m_SetBayerGainBlue;
	GETBAYERGAINBLUE	m_GetBayerGainBlue;
	SETBAYERGAINAUTO	m_SetBayerGainAuto;
	GETBAYERGAINAUTO	m_GetBayerGainAuto;
	SETGAMMA			m_SetGamma;
	GETGAMMA			m_GetGamma;
	SETBAYERMODE		m_SetBayerMode;
	GETBAYERMODE		m_GetBayerMode;

	SETGLOBALGAIN		m_SetGlobalGain;
	GETGLOBALGAIN		m_GetGlobalGain;
	SETCOLORGAINRED		m_SetColorGainRed;
	GETCOLORGAINRED		m_GetColorGainRed;
	SETCOLORGAINGREEN1	m_SetColorGainGreen1;
	GETCOLORGAINGREEN1	m_GetColorGainGreen1;
	SETCOLORGAINGREEN2	m_SetColorGainGreen2;
	GETCOLORGAINGREEN2	m_GetColorGainGreen2;
	SETCOLORGAINBLUE	m_SetColorGainBlue;
	GETCOLORGAINBLUE	m_GetColorGainBlue;
	SETEXPOSURETIME		m_SetExposureTime;
	GETEXPOSURETIME		m_GetExposureTime;

	SETHALFCLOCK		m_SetHalfClock;
	GETHALFCLOCK		m_GetHalfClock;
	SETAUTOIRIS			m_SetAutoIris;
	GETAUTOIRIS			m_GetAutoIris;

	SETSAMPLINGRATE		m_SetSamplingRate;
	GETSAMPLINGRATE		m_GetSamplingRate;
	GETVIDEOFORMAT		m_GetVideoFormat;

	WRITESROMID			m_WriteSromID;
	READSROMID			m_ReadSromID;

	GETCAMERAINFO		m_GetCameraInfo;
	GETSTATUS			m_GetStatus;

	WRITEREGISTER		m_WriteRegister;
	READREGISTER		m_ReadRegister;

	WRITEREGISTEREX		m_WriteRegisterEx;
	READREGISTEREX		m_ReadRegisterEx;

	SETGRAYMODE			m_SetGrayMode;
	GETGRAYMODE			m_GetGrayMode;
	SETGRAYGAINR		m_SetGrayGainR;
	GETGRAYGAINR		m_GetGrayGainR;
	SETGRAYGAING1		m_SetGrayGainG1;
	GETGRAYGAING1		m_GetGrayGainG1;
	SETGRAYGAING2		m_SetGrayGainG2;
	GETGRAYGAING2		m_GetGrayGainG2;
	SETGRAYGAINB		m_SetGrayGainB;
	GETGRAYGAINB		m_GetGrayGainB;
	SETGRAYOFFSETR		m_SetGrayOffsetR;
	GETGRAYOFFSETR		m_GetGrayOffsetR;
	SETGRAYOFFSETG1		m_SetGrayOffsetG1;
	GETGRAYOFFSETG1		m_GetGrayOffsetG1;
	SETGRAYOFFSETG2		m_SetGrayOffsetG2;
	GETGRAYOFFSETG2		m_GetGrayOffsetG2;
	SETGRAYOFFSETB		m_SetGrayOffsetB;
	GETGRAYOFFSETB		m_GetGrayOffsetB;

	SETCAMERATYPE		m_SetCameraType;
	GETCAMERATYPE		m_GetCameraType;

	SETSYNCV			m_SetSyncV;
	GETSYNCV			m_GetSyncV;
	SETSYNCH			m_SetSyncH;
	GETSYNCH			m_GetSyncH;

	FPGA_WRITEREGISTER	m_Fpga_WriteRegister;
	FPGA_READREGISTER	m_Fpga_ReadRegister;

	MONITOR_SETPREVIEWMODE		m_Monitor_SetPreviewMode;
	MONITOR_GETPREVIEWMODE		m_Monitor_GetPreviewMode;
	MONITOR_SETPREVIEWSIZE		m_Monitor_SetPreviewSize;
	MONITOR_GETPREVIEWSIZE		m_Monitor_GetPreviewSize;
	MONITOR_SETCOLORMODE		m_Monitor_SetColorMode;
	MONITOR_GETCOLORMODE		m_Monitor_GetColorMode;
	MONITOR_SETCAMERACLOCK		m_Monitor_SetCameraClock;
	MONITOR_GETCAMERACLOCK		m_Monitor_GetCameraClock;
	MONITOR_SETBAYERGAINAUTO	m_Monitor_SetBayerGainAuto;
	MONITOR_GETBAYERGAINAUTO	m_Monitor_GetBayerGainAuto;
	MONITOR_SETBAYERGAINLOCK	m_Monitor_SetBayerGainLock;
	MONITOR_GETBAYERGAINLOCK	m_Monitor_GetBayerGainLock;
	MONITOR_SETBAYERGAINRED		m_Monitor_SetBayerGainRed;
	MONITOR_GETBAYERGAINRED		m_Monitor_GetBayerGainRed;
	MONITOR_SETBAYERGAINGREEN	m_Monitor_SetBayerGainGreen;
	MONITOR_GETBAYERGAINGREEN	m_Monitor_GetBayerGainGreen;
	MONITOR_SETBAYERGAINBLUE	m_Monitor_SetBayerGainBlue;
	MONITOR_GETBAYERGAINBLUE	m_Monitor_GetBayerGainBlue;

	MONITOR_SAVECURRENTSETTINGS		m_Monitor_SaveCurrentSettings;
	MONITOR_INITREGISTERSETTINGS	m_Monitor_InitRegisterSettings;
	MONITOR_SETCROSSCURSORMODE		m_Monitor_SetCrossCursorMode;
	MONITOR_GETCROSSCURSORMODE		m_Monitor_GetCrossCursorMode;
	MONITOR_SETCROSSCURSORCOLORR	m_Monitor_SetCrossCursorColorR;
	MONITOR_GETCROSSCURSORCOLORR	m_Monitor_GetCrossCursorColorR;
	MONITOR_SETCROSSCURSORCOLORG	m_Monitor_SetCrossCursorColorG;
	MONITOR_GETCROSSCURSORCOLORG	m_Monitor_GetCrossCursorColorG;
	MONITOR_SETCROSSCURSORCOLORB	m_Monitor_SetCrossCursorColorB;
	MONITOR_GETCROSSCURSORCOLORB	m_Monitor_GetCrossCursorColorB;
	MONITOR_SETCROSSCURSORCOLORRGB	m_Monitor_SetCrossCursorColorRGB;
	MONITOR_GETCROSSCURSORCOLORRGB	m_Monitor_GetCrossCursorColorRGB;
	MONITOR_SETCROSSCURSORPOS		m_Monitor_SetCrossCursorPos;
	MONITOR_GETCROSSCURSORPOS		m_Monitor_GetCrossCursorPos;
	MONITOR_SETCROSSCURSORSIZE		m_Monitor_SetCrossCursorSize;
	MONITOR_GETCROSSCURSORSIZE		m_Monitor_GetCrossCursorSize;	

	MONITOR_SETAUTOIRISMODE			m_Monitor_SetAutoIrisMode;		
	MONITOR_GETAUTOIRISMODE			m_Monitor_GetAutoIrisMode;		
	MONITOR_SETAUTOIRISRANGE		m_Monitor_SetAutoIrisRange;		
	MONITOR_GETAUTOIRISRANGE		m_Monitor_GetAutoIrisRange;
	MONITOR_LOADFIRMWARE			m_Monitor_LoadFirmware;

	GETREALEXPOSURETIME				m_GetRealExposureTime;

public:

	DWORD		GetDllVersion		(void);
	LONG		GetLastError		(void);

	BOOL		Initialize			(HWND hWnd);
	BOOL		Release				(void);

	BOOL		Preview				(void);
	BOOL		Record				(LPCTSTR lpAviName, UINT RecTime, BOOL fShow);
	BOOL		CallBackPreview		(HWND hWnd, LPBYTE lpImage, LONG Size, BOOL TopDown);
	BOOL		SnapShot			(LPBYTE lpImage, LONG Size, BOOL TopDown);		// 1230
	BOOL		Close				(void);

	// 1250
	BOOL		Capture				(void);

	// 1260
	BOOL		Trigger				(HWND hWnd, LPBYTE lpImage, LONG Size, BOOL TopDown);
	BOOL		SaveImage			(LPCTSTR lpSaveName, LONG FileType);

	BOOL		SetPreviewWindow	(HWND hWnd, LONG Left, LONG Top, LONG Right, LONG Bottom);
	BOOL		SetCaptureWindow	(LONG Width, LONG Height, LONG Fps);
	BOOL		SetCaptureWindowEx	(LONG HTotal, LONG HStart, LONG HEffective, LONG VTotal, LONG VStart, LONG VEffective);
	BOOL		GetCaptureWindowEx	(LONG* HTotal, LONG* HStart, LONG* HEffective, LONG* VTotal, LONG* VStart, LONG* VEffective);

	BOOL		SetColorMode		(LONG ColorMode);
	LONG		GetColorMode		(void);

	BOOL		SetCrossbar			(LONG Output, LONG Input);
	BOOL		SetDeviceNumber		(LONG Number);
	LONG		EnumDevice			(TCHAR szDeviceName[10][256]);
	BOOL		GetDeviceName		(LONG index, LPSTR szDeviceName, LONG nSize);

	BOOL		StartPreview		(void);
	BOOL		StopPreview			(void);
	BOOL		GetImage			(LPBYTE lpImage, LONG Size, BOOL TopDown);

	LONG		Width				(void);
	LONG		Height				(void);
	LONG		Fps					(void);

	BOOL		SetCameraDlg		(HWND hWnd);
	BOOL		SetImageDlg			(HWND hWnd);
	BOOL		SetAnalogDlg		(HWND hWnd);

	// 1230
	BOOL		SetIOPort			(BYTE byteData, LONG longData, DWORD Reserve=0);
	BOOL		GetIOPort			(LPBYTE byteData, LPLONG longData, DWORD Reserve=0);
	BOOL		SetFilterValue		(LONG FilterType, LONG Value);
	LONG		GetFilterValue		(LONG FilterType, LPBOOL Error=NULL);

	BOOL		SetSubSample		(LONG SubSampleMode);
	LONG		GetSubSample		(void);
	BOOL		SetWaitTime			(LONG WaitTime);
	LONG		GetWaitTime			(void);

	// 1240
	BOOL		SetMirrorV			(BOOL Flg);
	BOOL		GetMirrorV			(void);
	BOOL		SetMirrorH			(BOOL Flg);
	BOOL		GetMirrorH			(void);

	BOOL		SetBrightness		(LONG Value);
	LONG		GetBrightness		(LPBOOL Error=NULL);
	BOOL		SetContrast			(LONG Value);
	LONG		GetContrast			(LPBOOL Error=NULL);
	BOOL		SetHue				(LONG Value);
	LONG		GetHue				(LPBOOL Error=NULL);
	BOOL		SetSaturation		(LONG Value);
	LONG		GetSaturation		(LPBOOL Error=NULL);
	BOOL		SetSharpness		(LONG Value);
	LONG		GetSharpness		(LPBOOL Error=NULL);
	BOOL		SetBayerGainRGB		(LONG Value);
	LONG		GetBayerGainRGB		(LPBOOL Error=NULL);
	BOOL		SetBayerGainRed		(LONG Value);
	LONG		GetBayerGainRed		(LPBOOL Error=NULL);
	BOOL		SetBayerGainGreen	(LONG Value);
	LONG		GetBayerGainGreen	(LPBOOL Error=NULL);
	BOOL		SetBayerGainBlue	(LONG Value);
	LONG		GetBayerGainBlue	(LPBOOL Error=NULL);
	BOOL		SetBayerGainAuto	(LONG Value);
	LONG		GetBayerGainAuto	(LPBOOL Error=NULL);
	BOOL		SetGamma			(LONG Value);
	LONG		GetGamma			(LPBOOL Error=NULL);
	BOOL		SetBayerMode		(LONG Value);
	LONG		GetBayerMode		(LPBOOL Error=NULL);

	BOOL		SetGlobalGain		(LONG Value);
	LONG		GetGlobalGain		(LPBOOL Error=NULL);
	BOOL		SetColorGainRed		(LONG Value);
	LONG		GetColorGainRed		(LPBOOL Error=NULL);
	BOOL		SetColorGainGreen1	(LONG Value);
	LONG		GetColorGainGreen1	(LPBOOL Error=NULL);
	BOOL		SetColorGainGreen2	(LONG Value);
	LONG		GetColorGainGreen2	(LPBOOL Error=NULL);
	BOOL		SetColorGainBlue	(LONG Value);
	LONG		GetColorGainBlue	(LPBOOL Error=NULL);
	BOOL		SetExposureTime		(LONG Value);
	LONG		GetExposureTime		(LPBOOL Error=NULL);

	// 1260
	BOOL		SetHalfClock		(LONG Value);
	LONG		GetHalfClock		(LPBOOL Error=NULL);
	BOOL		SetAutoIris			(LONG Value);
	LONG		GetAutoIris			(LPBOOL Error=NULL);

	// 1275
	BOOL		SetSamplingRate		(LONG Value);
	LONG		GetSamplingRate		(LPBOOL Error=NULL);
	LONG		GetVideoFormat		(LPBOOL Error=NULL);

	// 1276
	BOOL		WriteSromID			(LONG Address, LONG Value);
	LONG		ReadSromID			(LONG Address, LPBOOL Error=NULL);

	// 1280
	BOOL		GetCameraInfo		(LPCAMERAINFO pInfo);
	LONG		GetStatus			(LPBOOL Error=NULL);

	BOOL		WriteRegister		(BYTE Address, DWORD Value);
	DWORD		ReadRegister		(BYTE Address, LPBOOL Error=NULL);

	BOOL		WriteRegisterEx		(DWORD Address, DWORD Value);
	DWORD		ReadRegisterEx		(DWORD Address, LPBOOL Error=NULL);

	BOOL		SetGrayMode			(LONG Value);
	LONG		GetGrayMode			(LPBOOL Error=NULL);
	BOOL		SetGrayGainR		(LONG Value);
	LONG		GetGrayGainR		(LPBOOL Error=NULL);
	BOOL		SetGrayGainG1		(LONG Value);
	LONG		GetGrayGainG1		(LPBOOL Error=NULL);
	BOOL		SetGrayGainG2		(LONG Value);
	LONG		GetGrayGainG2		(LPBOOL Error=NULL);
	BOOL		SetGrayGainB		(LONG Value);
	LONG		GetGrayGainB		(LPBOOL Error=NULL);
	BOOL		SetGrayOffsetR		(LONG Value);
	LONG		GetGrayOffsetR		(LPBOOL Error=NULL);
	BOOL		SetGrayOffsetG1		(LONG Value);
	LONG		GetGrayOffsetG1		(LPBOOL Error=NULL);
	BOOL		SetGrayOffsetG2		(LONG Value);
	LONG		GetGrayOffsetG2		(LPBOOL Error=NULL);
	BOOL		SetGrayOffsetB		(LONG Value);
	LONG		GetGrayOffsetB		(LPBOOL Error=NULL);

	// SATA
	BOOL		SetCameraType		(LONG Flg);
	LONG		GetCameraType		(LPBOOL Error=NULL);

	BOOL		SetSyncV			(LONG Flg);
	LONG		GetSyncV			(LPBOOL Error);
	BOOL		SetSyncH			(LONG Flg);
	LONG		GetSyncH			(LPBOOL Error);


	// MOUT
	BOOL		Fpga_WriteRegister	(BYTE Address, DWORD Value);
	DWORD		Fpga_ReadRegister	(BYTE Address, LPBOOL Error=NULL);

	BOOL		Monitor_SetPreviewMode		(BOOL Preview);
	BOOL		Monitor_GetPreviewMode		(LPBOOL Error=NULL);
	BOOL		Monitor_SetPreviewSize		(LONG Width, LONG Height);
	BOOL		Monitor_GetPreviewSize		(LONG* Width, LONG* Height);
	BOOL		Monitor_SetColorMode		(BOOL ColorMode);
	BOOL		Monitor_GetColorMode		(LPBOOL Error=NULL);
	BOOL		Monitor_SetCameraClock		(LONG Value);
	LONG		Monitor_GetCameraClock		(LPBOOL Error=NULL);
	BOOL		Monitor_SetBayerGainAuto	(LONG Value);
	LONG		Monitor_GetBayerGainAuto	(LPBOOL Error=NULL);
	BOOL		Monitor_SetBayerGainLock	(LONG Value);
	LONG		Monitor_GetBayerGainLock	(LPBOOL Error=NULL);
	BOOL		Monitor_SetBayerGainRed		(LONG Value);
	LONG		Monitor_GetBayerGainRed		(LPBOOL Error=NULL);
	BOOL		Monitor_SetBayerGainGreen	(LONG Value);
	LONG		Monitor_GetBayerGainGreen	(LPBOOL Error=NULL);
	BOOL		Monitor_SetBayerGainBlue	(LONG Value);
	LONG		Monitor_GetBayerGainBlue	(LPBOOL Error=NULL);

	BOOL		Monitor_SaveCurrentSettings		(void);
	BOOL		Monitor_InitRegisterSettings	(LONG Flg=0);

	BOOL		Monitor_SetCrossCursorMode		(LONG CursorNum, LONG Value);
	LONG		Monitor_GetCrossCursorMode		(LONG CursorNum, LPBOOL Error=NULL);
	BOOL		Monitor_SetCrossCursorColorR	(LONG CursorNum, LONG Value);
	LONG		Monitor_GetCrossCursorColorR	(LONG CursorNum, LPBOOL Error=NULL);
	BOOL		Monitor_SetCrossCursorColorG	(LONG CursorNum, LONG Value);
	LONG		Monitor_GetCrossCursorColorG	(LONG CursorNum, LPBOOL Error=NULL);
	BOOL		Monitor_SetCrossCursorColorB	(LONG CursorNum, LONG Value);
	LONG		Monitor_GetCrossCursorColorB	(LONG CursorNum, LPBOOL Error=NULL);
	BOOL		Monitor_SetCrossCursorColorRGB	(LONG CursorNum, LONG Value);
	LONG		Monitor_GetCrossCursorColorRGB	(LONG CursorNum, LPBOOL Error=NULL);
	BOOL		Monitor_SetCrossCursorPos		(LONG CursorNum, LONG  ValueX, LONG  ValueY);
	BOOL		Monitor_GetCrossCursorPos		(LONG CursorNum, LONG *ValueX, LONG *ValueY);
	BOOL		Monitor_SetCrossCursorSize		(LONG CursorNum, LONG  ValueX, LONG  ValueY);
	BOOL		Monitor_GetCrossCursorSize		(LONG CursorNum, LONG *ValueX, LONG *ValueY);

	BOOL		Monitor_SetAutoIrisMode			(LONG ColorMode);
	LONG		Monitor_GetAutoIrisMode			(LPBOOL Error=NULL);
	BOOL		Monitor_SetAutoIrisRange		(LONG  Min, LONG  Max);
	BOOL		Monitor_GetAutoIrisRange		(LONG* Min, LONG* Max);

	BOOL		Monitor_LoadFirmware			(LPCTSTR	szFileName);

	//900MI
	LONG		GetRealExposureTime				(void);

public:
	CArtCamSdk(){
		NullSet();
	}

	~CArtCamSdk(){
		FreeLibrary();
	}

	BOOL	LoadLibrary	(LPSTR szDllName);
	void	FreeLibrary	(void);

	BOOL	IsInit		(void) { return m_hArtCamSdk ? TRUE : FALSE; }

protected:
	void	NullSet		(void);
};

inline void CArtCamSdk::NullSet(void)
{
	m_hArtCamSdk				= NULL;
	m_hACam						= NULL;

	m_GetDllVersion				= NULL;
	m_GetLastError				= NULL;
	m_Initialize				= NULL;
	m_Release					= NULL;
	m_Preview					= NULL;
	m_Record					= NULL;
	m_CallBackPreview			= NULL;
	m_SnapShot					= NULL;
	m_Close						= NULL;
	m_Capture					= NULL;
	m_Trigger					= NULL;
	m_SaveImage					= NULL;
	m_SetPreviewWindow			= NULL;
	m_SetCaptureWindow			= NULL;
	m_SetCaptureWindowEx		= NULL;
	m_GetCaptureWindowEx		= NULL;
	m_SetColorMode				= NULL;
	m_GetColorMode				= NULL;
	m_SetCrossbar				= NULL;
	m_SetDeviceNumber			= NULL;
	m_EnumDevice				= NULL;
	m_GetDeviceName				= NULL;
	m_StartPreview				= NULL;
	m_StopPreview				= NULL;
	m_GetImage					= NULL;
	m_Width						= NULL;
	m_Height					= NULL;
	m_Fps						= NULL;
	m_SetCameraDlg				= NULL;
	m_SetImageDlg				= NULL;
	m_SetAnalogDlg				= NULL;
	m_SetIOPort					= NULL;
	m_GetIOPort					= NULL;
	m_SetFilterValue			= NULL;
	m_GetFilterValue			= NULL;
	m_SetSubSample				= NULL;
	m_GetSubSample				= NULL;
	m_SetWaitTime				= NULL;
	m_GetWaitTime				= NULL;
	m_SetMirrorV				= NULL;
	m_GetMirrorV				= NULL;
	m_SetMirrorH				= NULL;
	m_GetMirrorH				= NULL;
	m_SetBrightness				= NULL;
	m_GetBrightness				= NULL;
	m_SetContrast				= NULL;
	m_GetContrast				= NULL;
	m_SetHue					= NULL;
	m_GetHue					= NULL;
	m_SetSaturation				= NULL;
	m_GetSaturation				= NULL;
	m_SetSharpness				= NULL;
	m_GetSharpness				= NULL;
	m_SetBayerGainRGB			= NULL;
	m_GetBayerGainRGB			= NULL;
	m_SetBayerGainRed			= NULL;
	m_GetBayerGainRed			= NULL;
	m_SetBayerGainGreen			= NULL;
	m_GetBayerGainGreen			= NULL;
	m_SetBayerGainBlue			= NULL;
	m_GetBayerGainBlue			= NULL;
	m_SetBayerGainAuto			= NULL;
	m_GetBayerGainAuto			= NULL;
	m_SetGamma					= NULL;
	m_GetGamma					= NULL;
	m_SetBayerMode				= NULL;
	m_GetBayerMode				= NULL;
	m_SetGlobalGain				= NULL;
	m_GetGlobalGain				= NULL;
	m_SetColorGainRed			= NULL;
	m_GetColorGainRed			= NULL;
	m_SetColorGainGreen1		= NULL;
	m_GetColorGainGreen1		= NULL;
	m_SetColorGainGreen2		= NULL;
	m_GetColorGainGreen2		= NULL;
	m_SetColorGainBlue			= NULL;
	m_GetColorGainBlue			= NULL;
	m_SetExposureTime			= NULL;
	m_GetExposureTime			= NULL;
	m_SetHalfClock				= NULL;
	m_GetHalfClock				= NULL;
	m_SetAutoIris				= NULL;
	m_GetAutoIris				= NULL;
	m_SetSamplingRate			= NULL;
	m_GetSamplingRate			= NULL;
	m_GetVideoFormat			= NULL;
	m_WriteSromID				= NULL;
	m_ReadSromID				= NULL;
	m_GetCameraInfo				= NULL;
	m_GetStatus					= NULL;
	m_WriteRegister				= NULL;
	m_ReadRegister				= NULL;
	m_WriteRegisterEx			= NULL;
	m_ReadRegisterEx			= NULL;
	m_SetGrayMode				= NULL;
	m_GetGrayMode				= NULL;
	m_SetGrayGainR				= NULL;
	m_GetGrayGainR				= NULL;
	m_SetGrayGainG1				= NULL;
	m_GetGrayGainG1				= NULL;
	m_SetGrayGainG2				= NULL;
	m_GetGrayGainG2				= NULL;
	m_SetGrayGainB				= NULL;
	m_GetGrayGainB				= NULL;
	m_SetGrayOffsetR			= NULL;
	m_GetGrayOffsetR			= NULL;
	m_SetGrayOffsetG1			= NULL;
	m_GetGrayOffsetG1			= NULL;
	m_SetGrayOffsetG2			= NULL;
	m_GetGrayOffsetG2			= NULL;
	m_SetGrayOffsetB			= NULL;
	m_GetGrayOffsetB			= NULL;
	m_SetCameraType				= NULL;
	m_GetCameraType				= NULL;
	m_SetSyncV					= NULL;
	m_GetSyncV					= NULL;
	m_SetSyncH					= NULL;
	m_GetSyncH					= NULL;
	m_Fpga_WriteRegister		= NULL;
	m_Fpga_ReadRegister			= NULL;
	m_Monitor_SetPreviewMode	= NULL;
	m_Monitor_GetPreviewMode	= NULL;
	m_Monitor_SetPreviewSize	= NULL;
	m_Monitor_GetPreviewSize	= NULL;
	m_Monitor_SetColorMode		= NULL;
	m_Monitor_GetColorMode		= NULL;
	m_Monitor_SetCameraClock	= NULL;
	m_Monitor_GetCameraClock	= NULL;
	m_Monitor_SetBayerGainAuto	= NULL;
	m_Monitor_GetBayerGainAuto	= NULL;
	m_Monitor_SetBayerGainLock	= NULL;
	m_Monitor_GetBayerGainLock	= NULL;
	m_Monitor_SetBayerGainRed	= NULL;
	m_Monitor_GetBayerGainRed	= NULL;
	m_Monitor_SetBayerGainGreen	= NULL;
	m_Monitor_GetBayerGainGreen	= NULL;
	m_Monitor_SetBayerGainBlue	= NULL;
	m_Monitor_GetBayerGainBlue	= NULL;
	m_Monitor_SaveCurrentSettings		= NULL;
	m_Monitor_InitRegisterSettings		= NULL;
	m_Monitor_SetCrossCursorMode		= NULL;
	m_Monitor_GetCrossCursorMode		= NULL;
	m_Monitor_SetCrossCursorColorR		= NULL;
	m_Monitor_GetCrossCursorColorR		= NULL;
	m_Monitor_SetCrossCursorColorG		= NULL;
	m_Monitor_GetCrossCursorColorG		= NULL;
	m_Monitor_SetCrossCursorColorB		= NULL;
	m_Monitor_GetCrossCursorColorB		= NULL;
	m_Monitor_SetCrossCursorColorRGB	= NULL;
	m_Monitor_GetCrossCursorColorRGB	= NULL;
	m_Monitor_SetCrossCursorPos			= NULL;
	m_Monitor_GetCrossCursorPos			= NULL;
	m_Monitor_SetCrossCursorSize		= NULL;
	m_Monitor_GetCrossCursorSize		= NULL;
	m_Monitor_SetAutoIrisMode			= NULL;
	m_Monitor_GetAutoIrisMode			= NULL;
	m_Monitor_SetAutoIrisRange			= NULL;
	m_Monitor_GetAutoIrisRange			= NULL;
	m_Monitor_LoadFirmware				= NULL;

	m_GetRealExposureTime				= NULL;
}

inline BOOL CArtCamSdk::LoadLibrary(LPSTR szDllName)
{
	if(m_hArtCamSdk)
		return TRUE;

	m_hArtCamSdk = ::LoadLibrary(szDllName);

	DWORD error = ::GetLastError();

	if(NULL == m_hArtCamSdk){
		return FALSE;
	}


	// DLLのバージョンチェック
	m_GetDllVersion				= (GETDLLVERSION)		::GetProcAddress(m_hArtCamSdk, "ArtCam_GetDllVersion");
	if(!m_GetDllVersion){
		FreeLibrary();
		return FALSE;
	}


	// バージョン取得
	WORD Version = LOWORD(GetDllVersion());
	WORD DllType = HIWORD(GetDllVersion());

	// 標準の関数
	if(1000 <= Version){
		m_GetLastError				= (GETLASTERROR)		::GetProcAddress(m_hArtCamSdk, "ArtCam_GetLastError");
		m_Initialize				= (INITIALIZE)			::GetProcAddress(m_hArtCamSdk, "ArtCam_Initialize");
		m_Release					= (RELEASE)				::GetProcAddress(m_hArtCamSdk, "ArtCam_Release");
		m_Preview					= (PREVIEW)				::GetProcAddress(m_hArtCamSdk, "ArtCam_Preview");
		m_Record					= (RECORD)				::GetProcAddress(m_hArtCamSdk, "ArtCam_Record");
		m_CallBackPreview			= (CALLBACKPREVIEW)		::GetProcAddress(m_hArtCamSdk, "ArtCam_CallBackPreview");
		m_Close						= (CLOSE)				::GetProcAddress(m_hArtCamSdk, "ArtCam_Close");
		m_SetPreviewWindow			= (SETPREVIEWWINDOW)	::GetProcAddress(m_hArtCamSdk, "ArtCam_SetPreviewWindow");
		m_SetCaptureWindow			= (SETCAPTUREWINDOW)	::GetProcAddress(m_hArtCamSdk, "ArtCam_SetCaptureWindow");
		m_SetCaptureWindowEx		= (SETCAPTUREWINDOWEX)	::GetProcAddress(m_hArtCamSdk, "ArtCam_SetCaptureWindowEx");
		m_GetCaptureWindowEx		= (GETCAPTUREWINDOWEX)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetCaptureWindowEx");
		m_SetColorMode				= (SETCOLORMODE)		::GetProcAddress(m_hArtCamSdk, "ArtCam_SetColorMode");
		m_GetColorMode				= (GETCOLORMODE)		::GetProcAddress(m_hArtCamSdk, "ArtCam_GetColorMode");
		m_SetCrossbar				= (SETCROSSBAR)			::GetProcAddress(m_hArtCamSdk, "ArtCam_SetCrossbar");
		m_SetDeviceNumber			= (SETDEVICENUMBER)		::GetProcAddress(m_hArtCamSdk, "ArtCam_SetDeviceNumber");
		m_EnumDevice				= (ENUMDEVICE)			::GetProcAddress(m_hArtCamSdk, "ArtCam_EnumDevice");
		m_GetDeviceName				= (GETDEVICENAME)		::GetProcAddress(m_hArtCamSdk, "ArtCam_GetDeviceName");
		m_StartPreview				= (STARTPREVIEW)		::GetProcAddress(m_hArtCamSdk, "ArtCam_StartPreview");
		m_StopPreview				= (STOPPREVIEW)			::GetProcAddress(m_hArtCamSdk, "ArtCam_StopPreview");
		m_GetImage					= (GETIMAGE)			::GetProcAddress(m_hArtCamSdk, "ArtCam_GetImage");
		m_Width						= (WIDTH)				::GetProcAddress(m_hArtCamSdk, "ArtCam_Width");
		m_Height					= (HEIGHT)				::GetProcAddress(m_hArtCamSdk, "ArtCam_Height");
		m_Fps						= (FPS)					::GetProcAddress(m_hArtCamSdk, "ArtCam_Fps");
		m_SetCameraDlg				= (SETCAMERADLG)		::GetProcAddress(m_hArtCamSdk, "ArtCam_SetCameraDlg");
		m_SetImageDlg				= (SETIMAGEDLG)			::GetProcAddress(m_hArtCamSdk, "ArtCam_SetImageDlg");
		m_SetAnalogDlg				= (SETANALOGDLG)		::GetProcAddress(m_hArtCamSdk, "ArtCam_SetAnalogDlg");


		if(	!m_GetLastError || !m_Initialize || !m_Release || !m_Preview || !m_Record || !m_CallBackPreview || !m_Close || 
			!m_SetPreviewWindow || !m_SetCaptureWindow || !m_SetCaptureWindowEx || !m_GetCaptureWindowEx || !m_SetColorMode || !m_GetColorMode || 
			!m_SetCrossbar || !m_SetDeviceNumber || !m_EnumDevice || !m_GetDeviceName || !m_StartPreview || !m_StopPreview || !m_GetImage ||
			!m_Width || !m_Height || !m_Fps || !m_SetCameraDlg || !m_SetImageDlg || !m_SetAnalogDlg)
		{
			FreeLibrary();
			return FALSE;
		}
	}


	// 1.23 以降で使える関数取得
	if(1230 <= Version){
		m_SetIOPort			= (SETIOPORT)		::GetProcAddress(m_hArtCamSdk, "ArtCam_SetIOPort");
		m_GetIOPort			= (GETIOPORT)		::GetProcAddress(m_hArtCamSdk, "ArtCam_GetIOPort");
		m_SetFilterValue	= (SETFILTERVALUE)	::GetProcAddress(m_hArtCamSdk, "ArtCam_SetFilterValue");
		m_GetFilterValue	= (GETFILTERVALUE)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetFilterValue");
		m_SnapShot			= (SNAPSHOT)		::GetProcAddress(m_hArtCamSdk, "ArtCam_SnapShot");
		m_SetSubSample		= (SETSUBSAMPLE)	::GetProcAddress(m_hArtCamSdk, "ArtCam_SetSubSample");
		m_GetSubSample		= (GETSUBSAMPLE)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetSubSample");
		m_SetWaitTime		= (SETWAITTIME)		::GetProcAddress(m_hArtCamSdk, "ArtCam_SetWaitTime");
		m_GetWaitTime		= (GETWAITTIME)		::GetProcAddress(m_hArtCamSdk, "ArtCam_GetWaitTime");

		if(	!m_SetIOPort || !m_GetIOPort || !m_SetFilterValue || !m_GetFilterValue || !m_SnapShot ||
			!m_SetSubSample || !m_GetSubSample || !m_SetWaitTime || !m_GetWaitTime	)
		{
			FreeLibrary();
			return FALSE;
		}
	}


	// 1.24 以降で使える関数取得
	if(1240 <= Version){
		m_SetMirrorV			= (SETMIRRORV)			::GetProcAddress(m_hArtCamSdk, "ArtCam_SetMirrorV");
		m_GetMirrorV			= (GETMIRRORV)			::GetProcAddress(m_hArtCamSdk, "ArtCam_GetMirrorV");
		m_SetMirrorH			= (SETMIRRORH)			::GetProcAddress(m_hArtCamSdk, "ArtCam_SetMirrorH");
		m_GetMirrorH			= (GETMIRRORH)			::GetProcAddress(m_hArtCamSdk, "ArtCam_GetMirrorH");
		m_SetBrightness			= (SETBRIGHTNESS)		::GetProcAddress(m_hArtCamSdk, "ArtCam_SetBrightness");
		m_GetBrightness			= (GETBRIGHTNESS)		::GetProcAddress(m_hArtCamSdk, "ArtCam_GetBrightness");
		m_SetContrast			= (SETCONTRAST)			::GetProcAddress(m_hArtCamSdk, "ArtCam_SetContrast");
		m_GetContrast			= (GETCONTRAST)			::GetProcAddress(m_hArtCamSdk, "ArtCam_GetContrast");
		m_SetHue				= (SETHUE)				::GetProcAddress(m_hArtCamSdk, "ArtCam_SetHue");
		m_GetHue				= (GETHUE)				::GetProcAddress(m_hArtCamSdk, "ArtCam_GetHue");
		m_SetSaturation			= (SETSATURATION)		::GetProcAddress(m_hArtCamSdk, "ArtCam_SetSaturation");
		m_GetSaturation			= (GETSATURATION)		::GetProcAddress(m_hArtCamSdk, "ArtCam_GetSaturation");
		m_SetSharpness			= (SETSHARPNESS)		::GetProcAddress(m_hArtCamSdk, "ArtCam_SetSharpness");
		m_GetSharpness			= (GETSHARPNESS)		::GetProcAddress(m_hArtCamSdk, "ArtCam_GetSharpness");
		m_SetBayerGainRGB		= (SETBAYERGAINRGB)		::GetProcAddress(m_hArtCamSdk, "ArtCam_SetBayerGainRGB");
		m_GetBayerGainRGB		= (GETBAYERGAINRGB)		::GetProcAddress(m_hArtCamSdk, "ArtCam_GetBayerGainRGB");
		m_SetBayerGainRed		= (SETBAYERGAINRED)		::GetProcAddress(m_hArtCamSdk, "ArtCam_SetBayerGainRed");
		m_GetBayerGainRed		= (GETBAYERGAINRED)		::GetProcAddress(m_hArtCamSdk, "ArtCam_GetBayerGainRed");
		m_SetBayerGainGreen		= (SETBAYERGAINGREEN)	::GetProcAddress(m_hArtCamSdk, "ArtCam_SetBayerGainGreen");
		m_GetBayerGainGreen		= (GETBAYERGAINGREEN)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetBayerGainGreen");
		m_SetBayerGainBlue		= (SETBAYERGAINBLUE)	::GetProcAddress(m_hArtCamSdk, "ArtCam_SetBayerGainBlue");
		m_GetBayerGainBlue		= (GETBAYERGAINBLUE)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetBayerGainBlue");
		m_SetBayerGainAuto		= (SETBAYERGAINAUTO)	::GetProcAddress(m_hArtCamSdk, "ArtCam_SetBayerGainAuto");
		m_GetBayerGainAuto		= (GETBAYERGAINAUTO)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetBayerGainAuto");
		m_SetGamma				= (SETGAMMA)			::GetProcAddress(m_hArtCamSdk, "ArtCam_SetGamma");
		m_GetGamma				= (GETGAMMA)			::GetProcAddress(m_hArtCamSdk, "ArtCam_GetGamma");
		m_SetBayerMode			= (SETBAYERMODE)		::GetProcAddress(m_hArtCamSdk, "ArtCam_SetBayerMode");
		m_GetBayerMode			= (GETBAYERMODE)		::GetProcAddress(m_hArtCamSdk, "ArtCam_GetBayerMode");
		m_SetGlobalGain			= (SETGLOBALGAIN)		::GetProcAddress(m_hArtCamSdk, "ArtCam_SetGlobalGain");
		m_GetGlobalGain			= (GETGLOBALGAIN)		::GetProcAddress(m_hArtCamSdk, "ArtCam_GetGlobalGain");
		m_SetColorGainRed		= (SETCOLORGAINRED)		::GetProcAddress(m_hArtCamSdk, "ArtCam_SetColorGainRed");
		m_GetColorGainRed		= (GETCOLORGAINRED)		::GetProcAddress(m_hArtCamSdk, "ArtCam_GetColorGainRed");
		m_SetColorGainGreen1	= (SETCOLORGAINGREEN1)	::GetProcAddress(m_hArtCamSdk, "ArtCam_SetColorGainGreen1");
		m_GetColorGainGreen1	= (GETCOLORGAINGREEN1)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetColorGainGreen1");
		m_SetColorGainGreen2	= (SETCOLORGAINGREEN2)	::GetProcAddress(m_hArtCamSdk, "ArtCam_SetColorGainGreen2");
		m_GetColorGainGreen2	= (GETCOLORGAINGREEN2)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetColorGainGreen2");
		m_SetColorGainBlue		= (SETCOLORGAINBLUE)	::GetProcAddress(m_hArtCamSdk, "ArtCam_SetColorGainBlue");
		m_GetColorGainBlue		= (GETCOLORGAINBLUE)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetColorGainBlue");
		m_SetExposureTime		= (SETEXPOSURETIME)		::GetProcAddress(m_hArtCamSdk, "ArtCam_SetExposureTime");
		m_GetExposureTime		= (GETEXPOSURETIME)		::GetProcAddress(m_hArtCamSdk, "ArtCam_GetExposureTime");

		if(	!m_SetMirrorV || !m_GetMirrorV || !m_SetMirrorH || !m_GetMirrorH || 
			!m_SetBrightness || !m_GetBrightness || !m_SetContrast || !m_GetContrast || 
			!m_SetHue || !m_GetHue || !m_SetSaturation || !m_GetSaturation || 
			!m_SetSharpness || !m_GetSharpness || !m_SetBayerGainRGB || !m_GetBayerGainRGB || 
			!m_SetBayerGainRed || !m_GetBayerGainRed || !m_SetBayerGainGreen || !m_GetBayerGainGreen || 
			!m_SetBayerGainBlue || !m_GetBayerGainBlue || !m_SetBayerGainAuto || !m_GetBayerGainAuto || 
			!m_SetGamma || !m_GetGamma || !m_SetBayerMode || !m_GetBayerMode || 
			!m_SetGlobalGain || !m_GetGlobalGain || !m_SetColorGainRed || !m_GetColorGainRed || 
			!m_SetColorGainGreen1 || !m_GetColorGainGreen1 || !m_SetColorGainGreen2 || !m_GetColorGainGreen2 || 
			!m_SetColorGainBlue || !m_GetColorGainBlue || !m_SetExposureTime || !m_GetExposureTime)
		{
			FreeLibrary();
			return FALSE;
		}
	}


	// 1.25 以降で使える関数取得
	if(1250 <= Version){
		m_Capture = (CAPTURE) ::GetProcAddress(m_hArtCamSdk, "ArtCam_Capture");
		if(!m_Capture){
			FreeLibrary();
			return FALSE;
		}
	}



	// 1.26 以降で使える関数取得
	if(1260 <= Version){
		m_Trigger		= (TRIGGER)			::GetProcAddress(m_hArtCamSdk, "ArtCam_Trigger");
		m_SaveImage		= (SAVEIMAGE)		::GetProcAddress(m_hArtCamSdk, "ArtCam_SaveImage");
		m_SetHalfClock	= (SETHALFCLOCK)	::GetProcAddress(m_hArtCamSdk, "ArtCam_SetHalfClock");
		m_GetHalfClock	= (GETHALFCLOCK)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetHalfClock");
		m_SetAutoIris	= (SETAUTOIRIS)		::GetProcAddress(m_hArtCamSdk, "ArtCam_SetAutoIris");
		m_GetAutoIris	= (GETAUTOIRIS)		::GetProcAddress(m_hArtCamSdk, "ArtCam_GetAutoIris");

		if(!m_Trigger || !m_SaveImage || !m_SetHalfClock || !m_GetHalfClock || !m_SetAutoIris || !m_GetAutoIris){
			FreeLibrary();
			return FALSE;
		}
	}


	// 1.275 以降で使える関数取得
	if(1275 <= Version){
		m_SetSamplingRate	= (SETSAMPLINGRATE)	::GetProcAddress(m_hArtCamSdk, "ArtCam_SetSamplingRate");
		m_GetSamplingRate	= (GETSAMPLINGRATE)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetSamplingRate");
		m_GetVideoFormat	= (GETVIDEOFORMAT)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetVideoFormat");

		if(!m_SetSamplingRate || !m_GetSamplingRate || !m_GetVideoFormat){
			FreeLibrary();
			return FALSE;
		}
	}


	// 1.276 以降で使える関数取得
	if(1276 <= Version){
		m_WriteSromID	= (WRITESROMID)	::GetProcAddress(m_hArtCamSdk, "ArtCam_WriteSromID");
		m_ReadSromID	= (READSROMID)	::GetProcAddress(m_hArtCamSdk, "ArtCam_ReadSromID");

		if(!m_WriteSromID || !m_ReadSromID){
			FreeLibrary();
			return FALSE;
		}
	}


	// 1280 以降で使える関数取得
	if(1280 <= Version){
		m_GetCameraInfo		= (GETCAMERAINFO)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetCameraInfo");
		m_GetStatus			= (GETSTATUS)		::GetProcAddress(m_hArtCamSdk, "ArtCam_GetStatus");

		m_WriteRegister		= (WRITEREGISTER)	::GetProcAddress(m_hArtCamSdk, "ArtCam_WriteRegister");
		m_ReadRegister		= (READREGISTER)	::GetProcAddress(m_hArtCamSdk, "ArtCam_ReadRegister");

		m_SetGrayMode		= (SETGRAYMODE)		::GetProcAddress(m_hArtCamSdk, "ArtCam_SetGrayMode");
		m_GetGrayMode		= (GETGRAYMODE)		::GetProcAddress(m_hArtCamSdk, "ArtCam_GetGrayMode");
		m_SetGrayGainR		= (SETGRAYGAINR)	::GetProcAddress(m_hArtCamSdk, "ArtCam_SetGrayGainR");
		m_GetGrayGainR		= (GETGRAYGAINR)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetGrayGainR");
		m_SetGrayGainG1		= (SETGRAYGAING1)	::GetProcAddress(m_hArtCamSdk, "ArtCam_SetGrayGainG1");
		m_GetGrayGainG1		= (GETGRAYGAING1)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetGrayGainG1");
		m_SetGrayGainG2		= (SETGRAYGAING2)	::GetProcAddress(m_hArtCamSdk, "ArtCam_SetGrayGainG2");
		m_GetGrayGainG2		= (GETGRAYGAING2)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetGrayGainG2");
		m_SetGrayGainB		= (SETGRAYGAINB)	::GetProcAddress(m_hArtCamSdk, "ArtCam_SetGrayGainB");
		m_GetGrayGainB		= (GETGRAYGAINB)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetGrayGainB");
		m_SetGrayOffsetR	= (SETGRAYOFFSETR)	::GetProcAddress(m_hArtCamSdk, "ArtCam_SetGrayOffsetR");
		m_GetGrayOffsetR	= (GETGRAYOFFSETR)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetGrayOffsetR");
		m_SetGrayOffsetG1	= (SETGRAYOFFSETG1)	::GetProcAddress(m_hArtCamSdk, "ArtCam_SetGrayOffsetG1");
		m_GetGrayOffsetG1	= (GETGRAYOFFSETG1)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetGrayOffsetG1");
		m_SetGrayOffsetG2	= (SETGRAYOFFSETG2)	::GetProcAddress(m_hArtCamSdk, "ArtCam_SetGrayOffsetG2");
		m_GetGrayOffsetG2	= (GETGRAYOFFSETG2)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetGrayOffsetG2");
		m_SetGrayOffsetB	= (SETGRAYOFFSETB)	::GetProcAddress(m_hArtCamSdk, "ArtCam_SetGrayOffsetB");
		m_GetGrayOffsetB	= (GETGRAYOFFSETB)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetGrayOffsetB");

		if(	!m_GetCameraInfo || !m_GetStatus || !m_WriteRegister || !m_ReadRegister || !m_SetGrayMode || !m_GetGrayMode || 
			!m_SetGrayGainR || !m_GetGrayGainR || !m_SetGrayGainG1 || !m_GetGrayGainG1 || 
			!m_SetGrayGainG2 || !m_GetGrayGainG2 || !m_SetGrayGainB || !m_GetGrayGainB || 
			!m_SetGrayOffsetR || !m_GetGrayOffsetR || !m_SetGrayOffsetG1 || !m_GetGrayOffsetG1 || 
			!m_SetGrayOffsetG2 || !m_GetGrayOffsetG2 || !m_SetGrayOffsetB || !m_GetGrayOffsetB)
		{
			FreeLibrary();
			return FALSE;
		}


		//900MI
		if(ARTCAM_CAMERATYPE_900MI == DllType){
			m_WriteRegisterEx		= (WRITEREGISTEREX)		::GetProcAddress(m_hArtCamSdk, "ArtCam_WriteRegisterEx");
			m_ReadRegisterEx		= (READREGISTEREX)		::GetProcAddress(m_hArtCamSdk, "ArtCam_ReadRegisterEx");
			m_GetRealExposureTime	= (GETREALEXPOSURETIME)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetRealExposureTime");

			if(	!m_WriteRegisterEx || !m_ReadRegisterEx || !m_GetRealExposureTime){
				FreeLibrary();
				return FALSE;
			}
		}

		// SATA
		if(ARTCAM_CAMERATYPE_SATA == DllType){
			m_SetCameraType		= (SETCAMERATYPE)	::GetProcAddress(m_hArtCamSdk, "ArtCam_SetCameraType");
			m_GetCameraType		= (GETCAMERATYPE)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetCameraType");

			if(	!m_SetCameraType || !m_GetCameraType){
				FreeLibrary();
				return FALSE;
			}
		}

		// MOUT
		if(ARTCAM_CAMERATYPE_130MI_MOUT == DllType || ARTCAM_CAMERATYPE_150P3_MOUT == DllType ){
			m_Fpga_WriteRegister		= (FPGA_WRITEREGISTER)	::GetProcAddress(m_hArtCamSdk, "ArtCam_Fpga_WriteRegister");
			m_Fpga_ReadRegister			= (FPGA_READREGISTER)	::GetProcAddress(m_hArtCamSdk, "ArtCam_Fpga_ReadRegister");

			m_Monitor_SetPreviewMode	= (MONITOR_SETPREVIEWMODE)		::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_SetPreviewMode");
			m_Monitor_GetPreviewMode	= (MONITOR_GETPREVIEWMODE)		::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_GetPreviewMode");
			m_Monitor_SetPreviewSize	= (MONITOR_SETPREVIEWSIZE)		::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_SetPreviewSize");
			m_Monitor_GetPreviewSize	= (MONITOR_GETPREVIEWSIZE)		::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_GetPreviewSize");
			m_Monitor_SetColorMode		= (MONITOR_SETCOLORMODE)		::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_SetColorMode");
			m_Monitor_GetColorMode		= (MONITOR_GETCOLORMODE)		::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_GetColorMode");
			m_Monitor_SetCameraClock	= (MONITOR_SETCAMERACLOCK)		::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_SetCameraClock");
			m_Monitor_GetCameraClock	= (MONITOR_GETCAMERACLOCK)		::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_GetCameraClock");
			m_Monitor_SetBayerGainAuto	= (MONITOR_SETBAYERGAINAUTO)	::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_SetBayerGainAuto");
			m_Monitor_GetBayerGainAuto	= (MONITOR_GETBAYERGAINAUTO)	::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_GetBayerGainAuto");
			m_Monitor_SetBayerGainLock	= (MONITOR_SETBAYERGAINLOCK)	::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_SetBayerGainLock");
			m_Monitor_GetBayerGainLock	= (MONITOR_GETBAYERGAINLOCK)	::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_GetBayerGainLock");
			m_Monitor_SetBayerGainRed	= (MONITOR_SETBAYERGAINRED)		::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_SetBayerGainRed");
			m_Monitor_GetBayerGainRed	= (MONITOR_GETBAYERGAINRED)		::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_GetBayerGainRed");
			m_Monitor_SetBayerGainGreen	= (MONITOR_SETBAYERGAINGREEN)	::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_SetBayerGainGreen");
			m_Monitor_GetBayerGainGreen	= (MONITOR_GETBAYERGAINGREEN)	::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_GetBayerGainGreen");
			m_Monitor_SetBayerGainBlue	= (MONITOR_SETBAYERGAINBLUE)	::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_SetBayerGainBlue");
			m_Monitor_GetBayerGainBlue	= (MONITOR_GETBAYERGAINBLUE)	::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_GetBayerGainBlue");


			if(	!m_Fpga_WriteRegister || !m_Fpga_ReadRegister || 
				!m_Monitor_SetPreviewMode || !m_Monitor_GetPreviewMode || !m_Monitor_SetPreviewSize || !m_Monitor_GetPreviewSize || 
				!m_Monitor_SetColorMode || !m_Monitor_GetColorMode || !m_Monitor_SetCameraClock || !m_Monitor_GetCameraClock || 
				!m_Monitor_SetBayerGainAuto || !m_Monitor_GetBayerGainAuto || !m_Monitor_SetBayerGainRed || !m_Monitor_GetBayerGainRed || 
				!m_Monitor_SetBayerGainGreen || !m_Monitor_GetBayerGainGreen || !m_Monitor_SetBayerGainBlue || !m_Monitor_GetBayerGainBlue
				)
			{
				FreeLibrary();
				return FALSE;
			}
		}

	}
	
	if(1282 <= Version){
		// SATA
		if(ARTCAM_CAMERATYPE_SATA == DllType){
			m_SetSyncV			= (SETSYNCV)		::GetProcAddress(m_hArtCamSdk, "ArtCam_SetSyncV");
			m_GetSyncV			= (GETSYNCV)		::GetProcAddress(m_hArtCamSdk, "ArtCam_GetSyncV");
			m_SetSyncH			= (SETSYNCH)		::GetProcAddress(m_hArtCamSdk, "ArtCam_SetSyncH");
			m_GetSyncH			= (GETSYNCH)		::GetProcAddress(m_hArtCamSdk, "ArtCam_GetSyncH");

			if(	!m_SetSyncV || !m_GetSyncV || !m_SetSyncH || !m_GetSyncH){
				FreeLibrary();
				return FALSE;
			}
		}

		// MOUT
		if(ARTCAM_CAMERATYPE_130MI_MOUT == DllType || ARTCAM_CAMERATYPE_150P3_MOUT == DllType ){
			m_Monitor_SaveCurrentSettings	 =	(MONITOR_SAVECURRENTSETTINGS)		::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_SaveCurrentSettings");
			m_Monitor_InitRegisterSettings	 =	(MONITOR_INITREGISTERSETTINGS)		::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_InitRegisterSettings");
			m_Monitor_SetCrossCursorMode	 = 	(MONITOR_SETCROSSCURSORMODE)		::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_SetCrossCursorMode");
			m_Monitor_GetCrossCursorMode	 = 	(MONITOR_GETCROSSCURSORMODE)		::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_GetCrossCursorMode");
			m_Monitor_SetCrossCursorColorR	 = 	(MONITOR_SETCROSSCURSORCOLORR)		::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_SetCrossCursorColorR");
			m_Monitor_GetCrossCursorColorR	 = 	(MONITOR_GETCROSSCURSORCOLORR)		::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_GetCrossCursorColorR");
			m_Monitor_SetCrossCursorColorG	 = 	(MONITOR_SETCROSSCURSORCOLORG)		::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_SetCrossCursorColorG");
			m_Monitor_GetCrossCursorColorG	 = 	(MONITOR_GETCROSSCURSORCOLORG)		::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_GetCrossCursorColorG");
			m_Monitor_SetCrossCursorColorB	 = 	(MONITOR_SETCROSSCURSORCOLORB)		::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_SetCrossCursorColorB");
			m_Monitor_GetCrossCursorColorB	 = 	(MONITOR_GETCROSSCURSORCOLORB)		::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_GetCrossCursorColorB");
			m_Monitor_SetCrossCursorColorRGB = 	(MONITOR_SETCROSSCURSORCOLORRGB)	::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_SetCrossCursorColorRGB");
			m_Monitor_GetCrossCursorColorRGB = 	(MONITOR_GETCROSSCURSORCOLORRGB)	::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_GetCrossCursorColorRGB");
			m_Monitor_SetCrossCursorPos		 = 	(MONITOR_SETCROSSCURSORPOS)			::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_SetCrossCursorPos");
			m_Monitor_GetCrossCursorPos		 = 	(MONITOR_GETCROSSCURSORPOS)			::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_GetCrossCursorPos");
			m_Monitor_SetCrossCursorSize	 = 	(MONITOR_SETCROSSCURSORSIZE)		::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_SetCrossCursorSize");	
			m_Monitor_GetCrossCursorSize	 = 	(MONITOR_GETCROSSCURSORSIZE)		::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_GetCrossCursorSize");	
			m_Monitor_SetAutoIrisMode		 = 	(MONITOR_SETAUTOIRISMODE)			::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_SetAutoIrisMode");	
			m_Monitor_GetAutoIrisMode		 = 	(MONITOR_GETAUTOIRISMODE)			::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_GetAutoIrisMode");	
			m_Monitor_SetAutoIrisRange		 = 	(MONITOR_SETAUTOIRISRANGE)			::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_SetAutoIrisRange");	
			m_Monitor_GetAutoIrisRange		 = 	(MONITOR_GETAUTOIRISRANGE)			::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_GetAutoIrisRange");	
			m_Monitor_LoadFirmware			 =  (MONITOR_LOADFIRMWARE)				::GetProcAddress(m_hArtCamSdk, "ArtCam_Monitor_LoadFirmware");


			if(	!m_Monitor_SaveCurrentSettings   || !m_Monitor_InitRegisterSettings  || !m_Monitor_SetCrossCursorMode  || !m_Monitor_GetCrossCursorMode || 
				!m_Monitor_SetCrossCursorColorR  || !m_Monitor_GetCrossCursorColorR  || !m_Monitor_SetCrossCursorColorG|| 
				!m_Monitor_GetCrossCursorColorG  || !m_Monitor_SetCrossCursorColorB  || !m_Monitor_GetCrossCursorColorB|| 
				!m_Monitor_SetCrossCursorColorRGB|| !m_Monitor_GetCrossCursorColorRGB|| !m_Monitor_SetCrossCursorPos   || 
				!m_Monitor_GetCrossCursorPos	 || !m_Monitor_SetCrossCursorSize    || !m_Monitor_GetCrossCursorSize  || 
				!m_Monitor_SetAutoIrisMode		 || !m_Monitor_GetAutoIrisMode	     || 
				!m_Monitor_SetAutoIrisRange		 || !m_Monitor_GetAutoIrisRange		 /*|| !m_Monitor_LoadFirmware	*/
				)
			{
				FreeLibrary();
				return FALSE;
			}
		}

	}
	
	
	// 1300 以降で使える関数取得
	if(1300 <= Version){
		m_GetRealExposureTime	= (GETREALEXPOSURETIME)	::GetProcAddress(m_hArtCamSdk, "ArtCam_GetRealExposureTime");
		if(!m_GetRealExposureTime){
			FreeLibrary();
			return FALSE;
		}
	}
	
	
	return TRUE;
}

inline void CArtCamSdk::FreeLibrary()
{
	if(m_hACam && m_Release)
		m_Release(m_hACam);

	if(m_hArtCamSdk)
		::FreeLibrary(m_hArtCamSdk);

	NullSet();
}

inline DWORD CArtCamSdk::GetDllVersion(void)
{
	if(m_GetDllVersion){
		return m_GetDllVersion();
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetLastError(void)
{
	if(m_GetLastError){
		return m_GetLastError(m_hACam);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::Initialize(HWND hWnd)
{
	if(m_Initialize){
		m_hACam = m_Initialize(hWnd);
		if(m_hACam)
			return TRUE;
	}
	return FALSE;
}

inline BOOL CArtCamSdk::Release(void)
{
	if(m_Release){
		return m_Release(m_hACam);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::Preview(void)
{
	if(m_Preview){
		return m_Preview(m_hACam);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::Record(LPCTSTR lpAviName, UINT RecTime, BOOL fShow)
{
	if(m_Record){
		return m_Record(m_hACam, lpAviName, RecTime, fShow);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::CallBackPreview(HWND hWnd, LPBYTE lpImage, LONG Size, BOOL TopDown)
{
	if(m_CallBackPreview){
		return m_CallBackPreview(m_hACam, hWnd, lpImage, Size, TopDown);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SnapShot(LPBYTE lpImage, LONG Size, BOOL TopDown)
{
	if(m_SnapShot){
		return m_SnapShot(m_hACam, lpImage, Size, TopDown);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::Close(void)
{
	if(m_Close){
		return m_Close(m_hACam);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::Capture(void)
{
	if(m_Capture){
		return m_Capture(m_hACam);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::Trigger(HWND hWnd, LPBYTE lpImage, LONG Size, BOOL TopDown)
{
	if(m_Trigger){
		return m_Trigger(m_hACam, hWnd, lpImage, Size, TopDown);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SaveImage(LPCTSTR lpSaveName, LONG FileType)
{
	if(m_SaveImage){
		return m_SaveImage(m_hACam, lpSaveName, FileType);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetPreviewWindow(HWND hWnd, LONG Left, LONG Top, LONG Right, LONG Bottom)
{
	if(m_SetPreviewWindow){
		return m_SetPreviewWindow(m_hACam, hWnd, Left, Top, Right, Bottom);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetCaptureWindow(LONG Width, LONG Height, LONG Fps)
{
	if(m_SetCaptureWindow){
		return m_SetCaptureWindow(m_hACam, Width, Height, Fps);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetCaptureWindowEx(LONG HTotal, LONG HStart, LONG HEffective, LONG VTotal, LONG VStart, LONG VEffective)
{
	if(m_SetCaptureWindowEx){
		return m_SetCaptureWindowEx(m_hACam, HTotal, HStart, HEffective, VTotal, VStart, VEffective);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::GetCaptureWindowEx(LONG* HTotal, LONG* HStart, LONG* HEffective, LONG* VTotal, LONG* VStart, LONG* VEffective)
{
	if(m_GetCaptureWindowEx){
		return m_GetCaptureWindowEx(m_hACam, HTotal, HStart, HEffective, VTotal, VStart, VEffective);
	}
	return FALSE;
}


inline BOOL CArtCamSdk::SetColorMode(LONG ColorMode)
{
	if(m_SetColorMode){
		return m_SetColorMode(m_hACam, ColorMode);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetColorMode(void)
{
	if(m_GetColorMode){
		return m_GetColorMode(m_hACam);
	}
	return -1;
}


inline BOOL CArtCamSdk::SetCrossbar(LONG Output, LONG Input)
{
	if(m_SetCrossbar){
		return m_SetCrossbar(m_hACam, Output, Input);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetDeviceNumber(LONG Number)
{
	if(m_SetDeviceNumber){
		return m_SetDeviceNumber(m_hACam, Number);
	}
	return FALSE;
}

inline LONG CArtCamSdk::EnumDevice(TCHAR szDeviceName[10][256])
{
	if(m_EnumDevice){
		return m_EnumDevice(m_hACam, szDeviceName);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::GetDeviceName(LONG index, LPSTR szDeviceName, LONG nSize)
{
	if(m_GetDeviceName){
		return m_GetDeviceName(m_hACam, index, szDeviceName, nSize);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::StartPreview(void)
{
	if(m_StartPreview){
		return m_StartPreview(m_hACam);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::StopPreview(void)
{
	if(m_StopPreview){
		return m_StopPreview(m_hACam);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::GetImage(LPBYTE lpImage, LONG Size, BOOL TopDown)
{
	if(m_GetImage){
		return m_GetImage(m_hACam, lpImage, Size, TopDown);
	}
	return FALSE;
}

inline LONG CArtCamSdk::Width(void)
{
	if(m_Width){
		return m_Width(m_hACam);
	}
	return FALSE;
}

inline LONG CArtCamSdk::Height(void)
{
	if(m_Height){
		return m_Height(m_hACam);
	}
	return FALSE;
}

inline LONG CArtCamSdk::Fps(void)
{
	if(m_Fps){
		return m_Fps(m_hACam);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetCameraDlg(HWND hWnd)
{
	if(m_SetCameraDlg){
		return m_SetCameraDlg(m_hACam, hWnd);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetImageDlg(HWND hWnd)
{
	if(m_SetImageDlg){
		return m_SetImageDlg(m_hACam, hWnd);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetAnalogDlg(HWND hWnd)
{
	if(m_SetAnalogDlg){
		return m_SetAnalogDlg(m_hACam, hWnd);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetIOPort(BYTE byteData, LONG longData, DWORD Reserve)
{
	if(m_SetIOPort){
		return m_SetIOPort(m_hACam, byteData, longData, Reserve);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::GetIOPort(LPBYTE byteData, LPLONG longData, DWORD Reserve)
{
	if(m_GetIOPort){
		return m_GetIOPort(m_hACam, byteData, longData, Reserve);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetFilterValue(LONG FilterType, LONG Value)
{
	if(m_SetFilterValue){
		return m_SetFilterValue(m_hACam, FilterType, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetFilterValue(LONG FilterType, LPBOOL Error)
{
	if(m_GetFilterValue){
		return m_GetFilterValue(m_hACam, FilterType, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetSubSample(LONG SubSampleMode)
{
	if(m_SetSubSample){
		return m_SetSubSample(m_hACam, SubSampleMode);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetSubSample(void)
{
	if(m_GetSubSample){
		return m_GetSubSample(m_hACam);
	}
	return -1;
}

inline BOOL CArtCamSdk::SetWaitTime(LONG WaitTime)
{
	if(m_SetWaitTime){
		return m_SetWaitTime(m_hACam, WaitTime);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetWaitTime(void)
{
	if(m_GetWaitTime){
		return m_GetWaitTime(m_hACam);
	}
	return -1;
}

inline BOOL CArtCamSdk::SetMirrorV(BOOL Flg)
{
	if(m_SetMirrorV){
		return m_SetMirrorV(m_hACam, Flg);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::GetMirrorV(void)
{
	if(m_GetMirrorV){
		return m_GetMirrorV(m_hACam);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetMirrorH(BOOL Flg)
{
	if(m_SetMirrorH){
		return m_SetMirrorH(m_hACam, Flg);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::GetMirrorH(void)
{
	if(m_GetMirrorH){
		return m_GetMirrorH(m_hACam);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetBrightness(LONG Value)
{
	if(m_SetBrightness){
		return m_SetBrightness(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetBrightness(LPBOOL Error)
{
	if(m_GetBrightness){
		return m_GetBrightness(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetContrast(LONG Value)
{
	if(m_SetContrast){
		return m_SetContrast(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetContrast(LPBOOL Error)
{
	if(m_GetContrast){
		return m_GetContrast(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetHue(LONG Value)
{
	if(m_SetHue){
		return m_SetHue(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetHue(LPBOOL Error)
{
	if(m_GetHue){
		return m_GetHue(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetSaturation(LONG Value)
{
	if(m_SetSaturation){
		return m_SetSaturation(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetSaturation(LPBOOL Error)
{
	if(m_GetSaturation){
		return m_GetSaturation(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetSharpness(LONG Value)
{
	if(m_SetSharpness){
		return m_SetSharpness(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetSharpness(LPBOOL Error)
{
	if(m_GetSharpness){
		return m_GetSharpness(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetBayerGainRGB(LONG Value)
{
	if(m_SetBayerGainRGB){
		return m_SetBayerGainRGB(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetBayerGainRGB(LPBOOL Error)
{
	if(m_GetBayerGainRGB){
		return m_GetBayerGainRGB(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetBayerGainRed(LONG Value)
{
	if(m_SetBayerGainRed){
		return m_SetBayerGainRed(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetBayerGainRed(LPBOOL Error)
{
	if(m_GetBayerGainRed){
		return m_GetBayerGainRed(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetBayerGainGreen(LONG Value)
{
	if(m_SetBayerGainGreen){
		return m_SetBayerGainGreen(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetBayerGainGreen(LPBOOL Error)
{
	if(m_GetBayerGainGreen){
		return m_GetBayerGainGreen(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetBayerGainBlue(LONG Value)
{
	if(m_SetBayerGainBlue){
		return m_SetBayerGainBlue(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetBayerGainBlue(LPBOOL Error)
{
	if(m_GetBayerGainBlue){
		return m_GetBayerGainBlue(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetBayerGainAuto(LONG Value)
{
	if(m_SetBayerGainAuto){
		return m_SetBayerGainAuto(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetBayerGainAuto(LPBOOL Error)
{
	if(m_GetBayerGainAuto){
		return m_GetBayerGainAuto(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetGamma(LONG Value)
{
	if(m_SetGamma){
		return m_SetGamma(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetGamma(LPBOOL Error)
{
	if(m_GetGamma){
		return m_GetGamma(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetBayerMode(LONG Value)
{
	if(m_SetBayerMode){
		return m_SetBayerMode(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetBayerMode(LPBOOL Error)
{
	if(m_GetBayerMode){
		return m_GetBayerMode(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetGlobalGain(LONG Value)
{
	if(m_SetGlobalGain){
		return m_SetGlobalGain(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetGlobalGain(LPBOOL Error)
{
	if(m_GetGlobalGain){
		return m_GetGlobalGain(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetColorGainRed(LONG Value)
{
	if(m_SetColorGainRed){
		return m_SetColorGainRed(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetColorGainRed(LPBOOL Error)
{
	if(m_GetColorGainRed){
		return m_GetColorGainRed(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetColorGainGreen1(LONG Value)
{
	if(m_SetColorGainGreen1){
		return m_SetColorGainGreen1(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetColorGainGreen1(LPBOOL Error)
{
	if(m_GetColorGainGreen1){
		return m_GetColorGainGreen1(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetColorGainGreen2(LONG Value)
{
	if(m_SetColorGainGreen2){
		return m_SetColorGainGreen2(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetColorGainGreen2(LPBOOL Error)
{
	if(m_GetColorGainGreen2){
		return m_GetColorGainGreen2(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetColorGainBlue(LONG Value)
{
	if(m_SetColorGainBlue){
		return m_SetColorGainBlue(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetColorGainBlue(LPBOOL Error)
{
	if(m_GetColorGainBlue){
		return m_GetColorGainBlue(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetExposureTime(LONG Value)
{
	if(m_SetExposureTime){
		return m_SetExposureTime(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetExposureTime(LPBOOL Error)
{
	if(m_GetExposureTime){
		return m_GetExposureTime(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetHalfClock(LONG Value)
{
	if(m_SetHalfClock){
		return m_SetHalfClock(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetHalfClock(LPBOOL Error)
{
	if(m_GetHalfClock){
		return m_GetHalfClock(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetAutoIris(LONG Value)
{
	if(m_SetAutoIris){
		return m_SetAutoIris(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetAutoIris(LPBOOL Error)
{
	if(m_GetAutoIris){
		return m_GetAutoIris(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetSamplingRate(LONG Value)
{
	if(m_SetSamplingRate){
		return m_SetSamplingRate(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetSamplingRate(LPBOOL Error)
{
	if(m_GetSamplingRate){
		return m_GetSamplingRate(m_hACam, Error);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetVideoFormat(LPBOOL Error)
{
	if(m_GetVideoFormat){
		return m_GetVideoFormat(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::WriteSromID(LONG Address, LONG Value)
{
	if(m_SetSamplingRate){
		return m_WriteSromID(m_hACam, Address, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::ReadSromID(LONG Address, LPBOOL Error)
{
	if(m_GetSamplingRate){
		return m_ReadSromID(m_hACam, Address, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::GetCameraInfo(LPCAMERAINFO pInfo)
{
	if(m_GetCameraInfo){
		return m_GetCameraInfo(m_hACam, pInfo);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetStatus(LPBOOL Error)
{
	if(m_GetStatus){
		return m_GetStatus(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::WriteRegister(BYTE Address, DWORD Value)
{
	if(m_WriteRegister){
		return m_WriteRegister(m_hACam, Address, Value);
	}
	return FALSE;
}

inline DWORD CArtCamSdk::ReadRegister(BYTE Address, LPBOOL Error)
{
	if(m_ReadRegister){
		return m_ReadRegister(m_hACam, Address, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::WriteRegisterEx(DWORD Address, DWORD Value)
{
	if(m_WriteRegisterEx){
		return m_WriteRegisterEx(m_hACam, Address, Value);
	}
	return FALSE;
}

inline DWORD CArtCamSdk::ReadRegisterEx(DWORD Address, LPBOOL Error)
{
	if(m_ReadRegisterEx){
		return m_ReadRegisterEx(m_hACam, Address, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetGrayMode(LONG Value)
{
	if(m_SetGrayMode){
		return m_SetGrayMode(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetGrayMode(LPBOOL Error)
{
	if(m_GetGrayMode){
		return m_GetGrayMode(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetGrayGainR(LONG Value)
{
	if(m_SetGrayGainR){
		return m_SetGrayGainR(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetGrayGainR(LPBOOL Error)
{
	if(m_GetGrayGainR){
		return m_GetGrayGainR(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetGrayGainG1(LONG Value)
{
	if(m_SetGrayGainG1){
		return m_SetGrayGainG1(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetGrayGainG1(LPBOOL Error)
{
	if(m_GetGrayGainG1){
		return m_GetGrayGainG1(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetGrayGainG2(LONG Value)
{
	if(m_SetGrayGainG2){
		return m_SetGrayGainG2(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetGrayGainG2(LPBOOL Error)
{
	if(m_GetGrayGainG2){
		return m_GetGrayGainG2(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetGrayGainB(LONG Value)
{
	if(m_SetGrayGainB){
		return m_SetGrayGainB(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetGrayGainB(LPBOOL Error)
{
	if(m_GetGrayGainB){
		return m_GetGrayGainB(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetGrayOffsetR(LONG Value)
{
	if(m_SetGrayOffsetR){
		return m_SetGrayOffsetR(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetGrayOffsetR(LPBOOL Error)
{
	if(m_GetGrayOffsetR){
		return m_GetGrayOffsetR(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetGrayOffsetG1(LONG Value)
{
	if(m_SetGrayOffsetG1){
		return m_SetGrayOffsetG1(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetGrayOffsetG1(LPBOOL Error)
{
	if(m_GetGrayOffsetG1){
		return m_GetGrayOffsetG1(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetGrayOffsetG2(LONG Value)
{
	if(m_SetGrayOffsetG2){
		return m_SetGrayOffsetG2(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetGrayOffsetG2(LPBOOL Error)
{
	if(m_GetGrayOffsetG2){
		return m_GetGrayOffsetG2(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetGrayOffsetB(LONG Value)
{
	if(m_SetGrayOffsetB){
		return m_SetGrayOffsetB(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetGrayOffsetB(LPBOOL Error)
{
	if(m_GetGrayOffsetB){
		return m_GetGrayOffsetB(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetCameraType(LONG Flg)
{
	if(m_SetCameraType){
		return m_SetCameraType(m_hACam, Flg);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetCameraType(LPBOOL Error)
{
	if(m_GetCameraType){
		return m_GetCameraType(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetSyncV(LONG Flg)
{
	if(m_SetSyncV){
		return m_SetSyncV(m_hACam, Flg);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetSyncV(LPBOOL Error)
{
	if(m_GetSyncV){
		return m_GetSyncV(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::SetSyncH(LONG Flg)
{
	if(m_SetSyncH){
		return m_SetSyncH(m_hACam, Flg);
	}
	return FALSE;
}

inline LONG CArtCamSdk::GetSyncH(LPBOOL Error)
{
	if(m_GetSyncH){
		return m_GetSyncH(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::Fpga_WriteRegister(BYTE Address, DWORD Value)
{
	if(m_Fpga_WriteRegister){
		return m_Fpga_WriteRegister(m_hACam, Address, Value);
	}
	return FALSE;
}

inline DWORD CArtCamSdk::Fpga_ReadRegister(BYTE Address, LPBOOL Error)
{
	if(m_Fpga_ReadRegister){
		return m_Fpga_ReadRegister(m_hACam, Address, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_SetPreviewMode(BOOL Preview)
{
	if(m_Monitor_SetPreviewMode){
		return m_Monitor_SetPreviewMode(m_hACam, Preview);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_GetPreviewMode(LPBOOL Error)
{
	if(m_Monitor_GetPreviewMode){
		return m_Monitor_GetPreviewMode(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_SetPreviewSize(LONG Width, LONG Height)
{
	if(m_Monitor_SetPreviewSize){
		return m_Monitor_SetPreviewSize(m_hACam, Width, Height);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_GetPreviewSize(LONG* Width, LONG* Height)
{
	if(m_Monitor_GetPreviewSize){
		return m_Monitor_GetPreviewSize(m_hACam, Width, Height);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_SetColorMode(BOOL ColorMode)
{
	if(m_Monitor_SetColorMode){
		return m_Monitor_SetColorMode(m_hACam, ColorMode);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_GetColorMode(LPBOOL Error)
{
	if(m_Monitor_GetColorMode){
		return m_Monitor_GetColorMode(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_SetCameraClock(LONG Value)
{
	if(m_Monitor_SetCameraClock){
		return m_Monitor_SetCameraClock(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::Monitor_GetCameraClock(LPBOOL Error)
{
	if(m_Monitor_GetCameraClock){
		return m_Monitor_GetCameraClock(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_SetBayerGainAuto(LONG Value)
{
	if(m_Monitor_SetBayerGainAuto){
		return m_Monitor_SetBayerGainAuto(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::Monitor_GetBayerGainAuto(LPBOOL Error)
{
	if(m_Monitor_GetBayerGainAuto){
		return m_Monitor_GetBayerGainAuto(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_SetBayerGainLock(LONG Value)
{
	if(m_Monitor_SetBayerGainLock){
		return m_Monitor_SetBayerGainLock(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::Monitor_GetBayerGainLock(LPBOOL Error)
{
	if(m_Monitor_GetBayerGainLock){
		return m_Monitor_GetBayerGainLock(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_SetBayerGainRed(LONG Value)
{
	if(m_Monitor_SetBayerGainRed){
		return m_Monitor_SetBayerGainRed(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::Monitor_GetBayerGainRed(LPBOOL Error)
{
	if(m_Monitor_GetBayerGainRed){
		return m_Monitor_GetBayerGainRed(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_SetBayerGainGreen(LONG Value)
{
	if(m_Monitor_SetBayerGainGreen){
		return m_Monitor_SetBayerGainGreen(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::Monitor_GetBayerGainGreen(LPBOOL Error)
{
	if(m_Monitor_GetBayerGainGreen){
		return m_Monitor_GetBayerGainGreen(m_hACam, Error);
	}
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_SetBayerGainBlue(LONG Value)
{
	if(m_Monitor_SetBayerGainBlue){
		return m_Monitor_SetBayerGainBlue(m_hACam, Value);
	}
	return FALSE;
}

inline LONG CArtCamSdk::Monitor_GetBayerGainBlue(LPBOOL Error)
{
	if(m_Monitor_GetBayerGainBlue){
		return m_Monitor_GetBayerGainBlue(m_hACam, Error);
	}
	return FALSE;
}


inline BOOL CArtCamSdk::Monitor_SaveCurrentSettings(void)
{	
	if(m_Monitor_SaveCurrentSettings){		
		return m_Monitor_SaveCurrentSettings(m_hACam);
	}	
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_InitRegisterSettings(LONG Flg)
{	
	if(m_Monitor_InitRegisterSettings){		
		return m_Monitor_InitRegisterSettings(m_hACam, Flg);
	}	
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_SetCrossCursorMode(LONG CursorNum, LONG Value)
{	
	if(m_Monitor_SetCrossCursorMode){		
		return m_Monitor_SetCrossCursorMode(m_hACam, CursorNum, Value);	
	}	
	return FALSE;
}

inline LONG CArtCamSdk::Monitor_GetCrossCursorMode(LONG CursorNum, LPBOOL Error)
{	
	if(m_Monitor_GetCrossCursorMode){		
		return m_Monitor_GetCrossCursorMode(m_hACam, CursorNum, Error);	
	}	
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_SetCrossCursorColorR(LONG CursorNum, LONG Value)
{	
	if(m_Monitor_SetCrossCursorColorR){		
		return m_Monitor_SetCrossCursorColorR(m_hACam, CursorNum, Value);	
	}	
	return FALSE;
}

inline LONG CArtCamSdk::Monitor_GetCrossCursorColorR(LONG CursorNum, LPBOOL Error)
{	
	if(m_Monitor_GetCrossCursorColorR){		
		return m_Monitor_GetCrossCursorColorR(m_hACam, CursorNum, Error);	
	}	
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_SetCrossCursorColorG(LONG CursorNum, LONG Value)
{	
	if(m_Monitor_SetCrossCursorColorG){		
		return m_Monitor_SetCrossCursorColorG(m_hACam, CursorNum, Value);	
	}	
	return FALSE;
}

inline LONG CArtCamSdk::Monitor_GetCrossCursorColorG(LONG CursorNum, LPBOOL Error)
{	
	if(m_Monitor_GetCrossCursorColorG){		
		return m_Monitor_GetCrossCursorColorG(m_hACam, CursorNum, Error);	
	}	
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_SetCrossCursorColorB(LONG CursorNum, LONG Value)
{	
	if(m_Monitor_SetCrossCursorColorB){		
		return m_Monitor_SetCrossCursorColorB(m_hACam, CursorNum, Value);	
	}
	return FALSE;
}

inline LONG CArtCamSdk::Monitor_GetCrossCursorColorB(LONG CursorNum, LPBOOL Error)
{	
	if(m_Monitor_GetCrossCursorColorB){		
		return m_Monitor_GetCrossCursorColorB(m_hACam, CursorNum, Error);	
	}	
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_SetCrossCursorColorRGB(LONG CursorNum, LONG Value)
{	
	if(m_Monitor_SetCrossCursorColorRGB){		
		return m_Monitor_SetCrossCursorColorRGB(m_hACam, CursorNum, Value);	
	}	
	return FALSE;
}

inline LONG CArtCamSdk::Monitor_GetCrossCursorColorRGB(LONG CursorNum, LPBOOL Error)
{	
	if(m_Monitor_GetCrossCursorColorRGB){		
		return m_Monitor_GetCrossCursorColorRGB(m_hACam, CursorNum, Error);	
	}	
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_SetCrossCursorPos(LONG CursorNum, LONG ValueX, LONG ValueY)
{	
	if(m_Monitor_SetCrossCursorPos){		
		return m_Monitor_SetCrossCursorPos(m_hACam, CursorNum, ValueX, ValueY);	
	}	
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_GetCrossCursorPos(LONG CursorNum, LONG* ValueX, LONG* ValueY)
{	
	if(m_Monitor_GetCrossCursorPos){		
		return m_Monitor_GetCrossCursorPos(m_hACam, CursorNum, ValueX, ValueY);	
	}	
	return FALSE;
}


inline BOOL CArtCamSdk::Monitor_SetCrossCursorSize(LONG CursorNum, LONG ValueX, LONG ValueY)
{	
	if(m_Monitor_SetCrossCursorSize){		
		return m_Monitor_SetCrossCursorSize(m_hACam, CursorNum, ValueX, ValueY);	
	}	
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_GetCrossCursorSize(LONG CursorNum,  LONG* ValueX, LONG* ValueY)
{	
	if(m_Monitor_GetCrossCursorSize){		
		return m_Monitor_GetCrossCursorSize(m_hACam, CursorNum, ValueX, ValueY);	
	}	
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_SetAutoIrisMode(LONG Value)
{	
	if(m_Monitor_SetAutoIrisMode){		
		return m_Monitor_SetAutoIrisMode(m_hACam, Value);	
	}	
	return FALSE;
}

inline LONG CArtCamSdk::Monitor_GetAutoIrisMode(LPBOOL Error)
{	
	if(m_Monitor_GetAutoIrisMode){		
		return m_Monitor_GetAutoIrisMode(m_hACam, Error);	
	}	
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_SetAutoIrisRange(LONG Min, LONG Max)
{	
	if(m_Monitor_SetAutoIrisRange){		
		return m_Monitor_SetAutoIrisRange(m_hACam, Min, Max);	
	}	
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_GetAutoIrisRange(LONG* Min, LONG* Max)
{	
	if(m_Monitor_GetAutoIrisRange){		
		return m_Monitor_GetAutoIrisRange(m_hACam, Min, Max);	
	}	
	return FALSE;
}

inline BOOL CArtCamSdk::Monitor_LoadFirmware(LPCTSTR szFileName)
{	
	if(m_Monitor_LoadFirmware){		
		return m_Monitor_LoadFirmware(m_hACam, szFileName);	
	}	
	return FALSE;
}

inline LONG CArtCamSdk::GetRealExposureTime(void)
{
	if(m_GetRealExposureTime){		
		return m_GetRealExposureTime(m_hACam);	
	}	
	return 0;
}


#endif	// #ifndef _CARTCAMSDK_
