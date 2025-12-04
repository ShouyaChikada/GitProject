//=============================================
//
// [shadowS.cpp]
// author chikada shouya
//
//=============================================

#include "shadows.h"													
#include "manager.h"
#include "debugproc.h"

//コンストラクタ
CShadowS::CShadowS(int nPriority):CObjectX(nPriority)
{
	m_mtxWorld = {};
	m_pVtxBuff = nullptr;
	m_bLook = false;
}

// デストラクタ
CShadowS::~CShadowS()
{

}

// 影の生成
CShadowS* CShadowS::Create(std::string FilePath)
{
	CShadowS* pShadowS = nullptr;
	pShadowS = new CShadowS;

	if (pShadowS != nullptr)
	{
		pShadowS->SetIdx(FilePath);
		pShadowS->Init();
		return pShadowS;
	}
	else
	{
		return nullptr;
	}
}
//=======================================
//初期化処理
//=======================================
HRESULT CShadowS::Init (void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CObjectX::Init();
	
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, NULL);

	VERTEX_2D* pVtx = nullptr;

	// ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// アンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}
//=======================================
//終了処理
//=======================================
void CShadowS::Uninit(void)
{

	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CObjectX::Uninit();

}
//=======================================
//更新処理
//=======================================
void CShadowS::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();

	CObjectX::Update();

	// キーボード
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();
	pInputKeyboard = CManager::GetKeyboard();

	//オーを押したとき
	if (pInputKeyboard->GetTrigger(DIK_O) == true)
	{
		m_bLook = true;
	}

	//ピーを押したとき
	if (pInputKeyboard->GetTrigger(DIK_P) == true)
	{
		m_bLook = false;
	}

	CObjectX::SetPosition(pos);
}
//=======================================
//描画処理
//=======================================
void CShadowS::Draw(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ステンシルテストを有効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	// Zバッファへの書込みを無効にする
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// カラーバッファへの書き込みを無効にする
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00000000);

	// ステンシルバッファの比較パラメータの設定
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);		// どっちも合格しているとき
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCR);		// ステンシルバッファは合格、Zバッファは不合格の時
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);			// ステンシルバッファが不合格になっているとき

	// 表面のカリング
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	// 影モデルの描画
	CObjectX::Draw();

	// ステンシルバッファの参照値を設定("1"になる)
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

	// ステンシルバッファの比較パラメータの設定
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT);		// どっちも合格しているとき
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// ステンシルバッファは合格、Zバッファは不合格の時
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// ステンシルバッファが不合格になっているとき

	// 裏面のカリング
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// 影モデルの描画
	CObjectX::Draw();

	// カラーバッファへの書き込みを有効にする
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0000000F);

	// ステンシルバッファの参照値を設定("2"になる)
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x02);

	// ステンシルバッファの比較パラメータの設定
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);		// どっちも合格しているとき
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		// ステンシルバッファは合格、Zバッファは不合格の時
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		// ステンシルバッファが不合格になっているとき

	// 画面の大きさの黒いポリゴンを出す

	//m_Obj2D->Draw();

		// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0, 2); //頂点情報構造体のサイズ


	// すべて元に戻す 
	// Zバッファへの書込みを有効にする
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	// ステンシルテストを無効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	// カリング
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
//=========================
//影の設定処理
//=========================
void CShadowS::SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	SetPosition(pos);
	SetRot(rot);
}