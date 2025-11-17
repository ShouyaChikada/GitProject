//=================================================
//
//	fade.cpp
// 
// Author:近田 尚也
//
//=================================================
#include "fade.h"
#include "manager.h"
// コンストラクタ
CFade::CFade()
{
	m_pVtxBuff = nullptr;						// 頂点バッファ
	m_Fade = FADE_NONE;							// フェイド
	m_col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);		// カラー
}

// デストラクタ
CFade::~CFade()
{

}

// フェードの生成
CFade* CFade::Create(void)
{
	CFade* pFade = nullptr;
	pFade = new CFade;

	if (pFade != nullptr)
	{
		pFade->Init();
		return pFade;
	}
	else
	{
		return nullptr;
	}
}

// 初期化処理
HRESULT CFade::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);//黒いポリゴン(不透明)にしておく

	VERTEX_2D* pVtx;

	//頂点バッファの生成・頂点情報の設定
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[2].col = m_col;
	pVtx[1].col = m_col;
	pVtx[3].col = m_col;

	//アンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}
//フェードの破棄処理
void CFade::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

}

//フェードの更新処理
void CFade::Update(void)
{
	if (m_Fade == FADE_NONE) return;

	VERTEX_2D* pVtx = nullptr;

	if (m_Fade == FADE_IN)
	{//フェードイン状態
		m_col.a -= 0.07f;	//ポリゴンを透明にしていく

		if (m_col.a <= 0.0f)
		{
			m_col.a = 0.0f;
			m_Fade = FADE_NONE;	//何もしていない状態に

		}
	}
	else if (m_Fade == FADE_OUT)
	{//フェードアウト状態
		m_col.a += 0.07f;	//ポリゴンを不透明にしていく
		
		if (m_col.a >= 1.0f)
		{

			m_col.a = 1.0f;
			m_Fade = FADE_IN;	//フェードイン状態に
			CManager::SetMode(m_pScene);

			return;
		}
	}
	//ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;
	//アンロック
	m_pVtxBuff->Unlock();

}
//フェードの描画処理
void CFade::Draw(void)
{
	// FOGを消す
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャを設定
	pDevice->SetTexture(0, NULL);//テクスチャを使用しないときは必ずNULLを指定する

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類
		0,
		2); //頂点情報構造体のサイズ

	// FOGの設定
	CManager::GetRenderer()->SetupVertexFog(D3DCOLOR_XRGB(255, 255, 255), D3DFOG_LINEAR, TRUE, 0.005f);

}
//フェードの設定処理
void CFade::SetFade(CScene* pScene)
{
	if (m_Fade != FADE_NONE)
	{
		delete pScene;

		pScene = nullptr;

		return;
	}
	
	if (m_pScene != nullptr)
	{
		m_pScene = nullptr;
	}

	if (m_pScene == nullptr)
	{
		m_pScene = pScene;
		m_Fade = FADE_OUT;
	}
}
// 取得処理
CFade::FADE CFade::GetFadeState(void)
{
	return m_Fade;
}