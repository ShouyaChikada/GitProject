//=================================================
//
// [pch.h]
// Author:chikada shouya
//
//=================================================
#ifndef _PCH_H_
#define _PCH_H_

// ビルド時の警告用マクロ
#define DIRECTINPUT_VERSION (0x0800)

//========================================
//インクルード
//========================================
#include "stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include"d3dx9.h"
#include "dinput.h"		//キーボード入力処理に必要
#include "Xinput.h"		//ジョイパッド入力処理に必要
#include "xaudio2.h"	//サウンド処理に必要
#include <iostream>
#include <fstream>
#include <sstream>
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
#define CLASS_NAME "WindowsClass"													//ウィンドウクラスの名前
#define WINDOW_NAME "DirectXの基本処理"												//ウィンドウの名前(キャプションに表示)
#define SCREEN_WIDTH (1280)															//ウィンドウの幅
#define SCREEN_HEIGHT (720)															//ウィンドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)				//頂点フォーマット[2D]
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//座標・法線・カラー・テクスチャ
#define D3DFVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)										
#define MAX_TEXTURE (128)															//テクスチャの最大数
#define MAX_BLOCK (128)																//ブロックの最大数
#define MAX_MODEL (32)																// 最大モデル数
#define MAX_PMODEL (15)																//プレイヤーの最大モデル数
#define MAX_HMODEL (15)																//人の最大モデル数

typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//座用変換用係数(1.0fで固定)
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標

}VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
}VERTEX_3D;

#endif