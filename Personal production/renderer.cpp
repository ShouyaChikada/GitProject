//=================================================
//
// [renderer.cpp]
// Author:chikada shouya
//
//=================================================
#include "renderer.h"
#include "object.h"
#include "debugproc.h"
#include "input.h"
#include "manager.h"
//#include "game.h"
//#include "fade.h"

int CRenderer::m_nCountFPS = 0;
//============================================
// コンストラクタ処理
//============================================
CRenderer::CRenderer()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		m_apTextureMT[nCnt] = NULL;
		m_apRenderMT[nCnt] = NULL;
	}
	m_pZBuffMT = NULL;	
	m_pVtxBuffMT = NULL;

}

//============================================
// デストラクタ処理
//============================================
CRenderer::~CRenderer()
{

}

//============================================
// 初期化処理
//============================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//LPDIRECT3DSURFACE9 pRenderDef, pZBuffDef;
	
	//Direct3D
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}
	//現在のディスプレイ
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//デバイスの生成
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	//Direct3D
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//レンターステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	//テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	////レンダリングターゲット用テクスチャの作成
	//m_pD3DDevice->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT, 1,
	//	D3DUSAGE_RENDERTARGET,
	//	D3DFMT_A8B8G8R8,
	//	D3DPOOL_DEFAULT,
	//	&m_apTextureMT[0], NULL);

	////テクスチャレンダリング用インターフェースの作成
	//m_apTextureMT[0]->GetSurfaceLevel(0, &m_apRenderMT[0]);

	////テクスチャレンダリング用にバッファの生成
	//m_pD3DDevice->CreateDepthStencilSurface(SCREEN_WIDTH, SCREEN_HEIGHT,
	//										D3DFMT_D16, 
	//										D3DMULTISAMPLE_NONE, 
	//										0, TRUE, 
	//										&m_pZBuffMT, NULL);

	////現在のレンダリングターゲットを取得(保存)
	//m_pD3DDevice->GetRenderTarget(0, &pRenderDef);

	////現在のZバッファの取得(保存)
	//m_pD3DDevice->GetDepthStencilSurface(&pZBuffDef);
	//
	////レンダリングターゲットを生成したテクスチャに設定
	//m_pD3DDevice->SetRenderTarget(0, m_apRenderMT[0]);

	////Zバッファを生成したZバッファに設定
	//m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

	////レンダリングターゲット用テクスチャのクリア
	//m_pD3DDevice->Clear(0, NULL,
	//	D3DCLEAR_TARGET,
	//	D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	////レンダリングターゲットを元に戻す
	//m_pD3DDevice->SetRenderTarget(0, pRenderDef);
	//
	////Zバッファを元に戻す
	//m_pD3DDevice->SetDepthStencilSurface(pZBuffDef);

	//テクスチャレンダリング用ビューポートの設定
	m_pViewportMT.X = 0;
	m_pViewportMT.Y = 0;
	m_pViewportMT.Width = SCREEN_WIDTH;
	m_pViewportMT.Height = SCREEN_HEIGHT;
	m_pViewportMT.MinZ = 0.0f;
	m_pViewportMT.MaxZ = 1.0f;

	//頂点バッファの生成
	m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffMT, NULL);

	VERTEX_2D* pVtx = NULL;

	// ロック
	m_pVtxBuffMT->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// アンロック
	m_pVtxBuffMT->Unlock();

	return S_OK;

}

//============================================
// 終了処理
//============================================
void CRenderer::Uninit(void)
{

	//デバイスの破棄
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	//オブジェクトの破棄
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}

	//頂点バッファの破棄
	if (m_pVtxBuffMT != NULL)
	{
		m_pVtxBuffMT->Release();
		m_pVtxBuffMT = NULL;
	}

	//Zバッファの破棄
	if (m_pZBuffMT != NULL)
	{
		m_pZBuffMT->Release();
		m_pZBuffMT = NULL;
	}

	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		//インターフェースの破棄
		if (m_apRenderMT[nCnt] != NULL)
		{
			m_apRenderMT[nCnt]->Release();
			m_apRenderMT[nCnt] = NULL;
		}
		
		//テクスチャの破棄
		if (m_apTextureMT[nCnt] != NULL)
		{
			m_apTextureMT[nCnt]->Release();
			m_apTextureMT[nCnt] = NULL;
		}
	}

	//すべて破棄
	CObject::ReleaseAll();
}

//============================================
//更新処理
//============================================
void CRenderer::Update(void)
{
	// キーボード
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();
	pInputKeyboard = CManager::GetKeyboard();

	//すべての更新処理
	CObject::UpdateAll();
	

	if (pInputKeyboard->GetTrigger(DIK_F3))
	{
		onWireFrame();
	}
	else if (pInputKeyboard->GetTrigger(DIK_F4))
	{
		offWireFrame();

	}
}

//============================================
//描画処理
//============================================
void CRenderer::Draw(void)
{
	LPDIRECT3DSURFACE9 pRenderWk = NULL;
	LPDIRECT3DTEXTURE9 pTextureWk = NULL;

	CFade* pFade = CManager::GetFade();
	CScene* pScene = CManager::GetScene();
	m_nCountFPS = GetFPS();

	//バックバッファ
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),		// 128, 154, 255, 255
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//D3DXVECTOR3 posV = pCamera->GetPosV();
	//D3DXVECTOR3 posR = pCamera->GetPosR();
	//D3DXVECTOR3 vecU = pCamera->GetVecU();

	//D3DXVECTOR3 posV = D3DXVECTOR3(0.0f, 150.0f, -550.0f);
	//D3DXVECTOR3 posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//D3DXVECTOR3 vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	////バックバッファ			  
	//m_pD3DDevice->Clear(0, NULL,
	//	D3DCLEAR_ZBUFFER,
	//	D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	////レンダリングターゲットをテクスチャ[0]に設定ss
	//ChangeTarget(posV, posR, vecU);

	//m_apTextureMT[0] = NULL;

	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//描画開始が成功されたとき

		// FOGの設定
		//SetupVertexFog(D3DCOLOR_XRGB(255, 255, 255), D3DFOG_LINEAR, TRUE, 0.08f);

		//オブジェクトすべての描画
		CObject::DrawAll();

		pFade->Draw();

		if (pScene != nullptr)
		{
			pScene->Draw();
		}

		// FOGを消す
		//m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);		
#if 1

		CDebugProc::Print("FPS:%d\n",m_nCountFPS);

		//デバッグフォントの描画
		CDebugProc::Draw(15,15);

		CDebugProc::End();

#endif
		////頂点バッファをデータストリームに設定
		//m_pD3DDevice->SetStreamSource(0, m_pVtxBuffMT, 0, sizeof(CObject::VERTEX_2D));

		////テクスチャの設定
		//m_pD3DDevice->SetTexture(0, m_apTextureMT[1]);

		////頂点フォーマットの設定
		//m_pD3DDevice->SetFVF(FVF_VERTEX_2D);

		////ポリゴンの描画
		//m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		//	0, 2); //頂点情報構造体のサイズ

		////レンダリングターゲットを元に戻す
		//m_pD3DDevice->SetRenderTarget(0, pRenderWk);
		//
		//////頂点バッファをデータストリームに設定
		////m_pD3DDevice->SetStreamSource(0, m_pVtxBuffMT, 0, sizeof(CObject::VERTEX_2D));

		////テクスチャの設定
		//m_pD3DDevice->SetTexture(0, m_apTextureMT[0]);

		//////頂点フォーマットの設定
		////m_pD3DDevice->SetFVF(FVF_VERTEX_2D);

		////ポリゴンの描画
		//m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		//	0, 2); //頂点情報構造体のサイズ

		//	//テクスチャ[0]とテクスチャ[1]を入れ替える
		//pTextureWk = m_apTextureMT[0];
		//m_apTextureMT[0] = m_apTextureMT[1];
		//m_apTextureMT[1] = pTextureWk;

		////レンダー[0]とレンダー[1]を入れ替える
		//pRenderWk = m_apRenderMT[0];
		//m_apRenderMT[0] = m_apRenderMT[1];
		//m_apRenderMT[1] = pRenderWk;

		//描画終了
		m_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}
//============================================
// デバイスの取得
//============================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}

//============================================
// ワイヤーフレーム(オン)
//============================================
void CRenderer::onWireFrame(void) 
{
	m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}

//============================================
// ワイヤーフレーム(オフ)
//============================================
void CRenderer::offWireFrame(void) 
{
	m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//============================================
// レンダリングターゲットの設定
//============================================
void CRenderer::ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU)
{
	D3DXMATRIX mtxView, mtxProjection;
	float fAspect = 0.0f;

	//レンダリングターゲットを生成したテクスチャに設定
	m_pD3DDevice->SetRenderTarget(0, m_apRenderMT[0]);

	//Zバッファを生成したZバッファに設定
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

	//テクスチャレンダリング用のビューポートの設定
	m_pD3DDevice->SetViewport(&m_pViewportMT);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&mtxView);
		
	//ビューマトリックスの生成;
	D3DXMatrixLookAtLH(&mtxView, &posV, &posR, &vecU);

	//ビューマトリックスの設定
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&mtxProjection);

	//プロジェクションマトリックスの作成
	fAspect = (float)m_pViewportMT.Width / (float)m_pViewportMT.Height;

	D3DXMatrixPerspectiveFovLH(&mtxProjection,
								D3DXToRadian(45.0f),
								fAspect,
								10.0f,5000.0f);

	//プロジェクションマトリックスの設定
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);


}

//============================================
// テクスチャの取得
//============================================
LPDIRECT3DTEXTURE9 CRenderer::GetTextureMT(void)
{
	return m_apTextureMT[0];
}

//============================================
// フォグの設定
//============================================
void CRenderer::SetupVertexFog(DWORD Color, DWORD Mode, BOOL UseRange, FLOAT Density)
{
	//デバイスの取得
	m_pD3DDevice = GetDevice();

	float Start = 10.0f,    // Linear fog distances
		End = 5000.0f;

	// Enable fog blending.
	m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	// Set the fog color.
	m_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, Color);

	// Set fog parameters.
	if (D3DFOG_LINEAR == Mode)
	{
		m_pD3DDevice->SetRenderState(D3DRS_FOGVERTEXMODE, Mode);
		m_pD3DDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&Start));
		m_pD3DDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&End));
	}
	else
	{
		m_pD3DDevice->SetRenderState(D3DRS_FOGVERTEXMODE, Mode);
		m_pD3DDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&Density));
	}

	if (UseRange)
		m_pD3DDevice->SetRenderState(D3DRS_RANGEFOGENABLE, TRUE);
}
