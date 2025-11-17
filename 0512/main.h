//=================================================
//
//	main.h
// 
//	Author:近田尚也
//
//=================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//========================================
//インクルード
//========================================
#include <stdio.h>
#include<windows.h>
#include"d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)//ビルド時の警告用マクロ
#include "dinput.h" //キーボード入力処理に必要
#include "Xinput.h" //ジョイパッド入力処理に必要
#include "xaudio2.h"//サウンド処理に必要
#include <iostream>
#include <vector>

//========================================
//ライブラリのリンク
//========================================
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")	//キーボード入力処理に必要
#pragma comment(lib,"xinput.lib")	//ジョイパッド入力処理に必要

//========================================
//マクロ定義
//========================================
#define CLASS_NAME "WindowsClass" //ウィンドウクラスの名前
#define WINDOW_NAME "MaginityP.P." //ウィンドウの名前(キャプションに表示)
#define SCREEN_WIDTH (1280) //ウィンドウの幅
#define SCREEN_HEIGHT (720) //ウィンドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1) //頂点フォーマット[2D]
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//座標・法線・カラー・テクスチャ
#define D3DFVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)	
#define MAX_TEXTURE (128)	//テクスチャの最大数
#define MAX_BLOCK (128)		//ブロックの最大数
#define MAX_MODEL (32)		// 最大モデル数
#define MAX_PMODEL (16)		//プレイヤーの最大モデル数
#define MAX_HMODEL (15)		//人の最大モデル数

int GetFPS(void);
using namespace std;

#endif
