//=================================================
//
//	motion.h
// 
//	Author:近田尚也
//
//=================================================

#include "motion.h"
#include "stdio.h"
#include "manager.h"

//=================================================
// コンストラクタ
//=================================================
CMotion::CMotion()
{
	m_PartsCount = NULL;
	m_Loop = NULL;
	m_nMotion = NULL;
	m_nKey = NULL;
	m_nCount = NULL;
	m_nNumKey = NULL;
	m_nFrame = NULL;

	for (int nCnt = 0; nCnt < MAX_MOTIONINFO; nCnt++)
	{
		m_aMotionLoop[nCnt] = false;
	}

	for (int nCnt = 0; nCnt < NUM_MOTION; nCnt++)
	{
		m_aInfo[nCnt].m_bLoop = true;
		m_aInfo[nCnt].m_nNumKey = NULL;

	}


	MotionState = MOTIONSTATE_NEUTRAL;
	MotionType = MOTIONTYPE_NEUTRAL;
	bJump = false;
	bUse = false;
	m_ppModel = nullptr;

	m_nCounterMotion = NULL;
	m_nNext = NULL;
	m_nType = NULL;
	nCounterState = 0;
	nNumAll = NULL;
	m_nNumModel = NULL;
}

//=================================================
// デストラクタ
//=================================================
CMotion::~CMotion()
{

}

//=================================================
// モーションの生成
//=================================================
CMotion* CMotion::Create(const char* txt, CModel** ppModel)
{
	CMotion* pMotion = nullptr;
	pMotion = new CMotion;

	if (pMotion != nullptr)
	{
		pMotion->Init(txt, ppModel);
		return pMotion;
	}
	else
	{
		return nullptr;
	}
}

//=================================================
// モーションの破棄
//=================================================
void CMotion::Uninit(void)
{

}

//=================================================
// 初期化
//=================================================
HRESULT CMotion::Init(const char* txt, CModel** ppModel)
{
	FILE* pFile;

	// ローカル変数
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int nCnt = NULL;
	int nIdxModelParent = NULL;
	int ModelCount = NULL,Index = NULL;
	int nMotion = NULL, nCount = NULL, nKey = NULL;
	char omit[3] = {};

	// ファイルオープン
	pFile = fopen(txt, "r");

	// ファイルポインタに情報が入っていたら
	if (pFile != nullptr)
	{
		char aStr[256] = {};

		while (1)
		{
			// 文字の読み込み
			fscanf(pFile, "%s", &aStr[0]);
			//ストラコンプ（読み込んだ文字が一致したら)
			if (strcmp(aStr, "SCRIPT") == 0)
			{
				while (1)
				{
					// 文字の読み込み
					fscanf(pFile, "%s", &aStr[0]);

					if (strcmp(aStr, "NUM_MODEL") == 0)
					{
						// (=)の除去
						fscanf(pFile, "%s", &omit[0]);
						fscanf(pFile, "%d", &m_nNumModel);
					}
					else if (strcmp(aStr, "MODEL_FILENAME") == 0)
					{
						// (=)の除去
						fscanf(pFile, "%s", &omit[0]);

						// 文字の読み込み
						fscanf(pFile, "%s", &aStr[0]);

						const char* MODELFILE = {};
						MODELFILE = aStr;

						ppModel[nCnt] = CModel::Create(MODELFILE);

						nCnt++;
					}
					else if (strcmp(aStr, "CHARACTERSET") == 0)
					{
						while (1)
						{
							// 文字の読み込み
							fscanf(pFile, "%s", &aStr[0]);

							if (strcmp(aStr, "NUM_PARTS") == 0)
							{
								// (=)の除去
								fscanf(pFile, "%s", &omit[0]);
								fscanf(pFile, "%d", &m_nNumModel);
							}
							else if (strcmp(aStr, "PARTSSET") == 0)
							{
								while (1)
								{
									// 文字の読み込み
									fscanf(pFile, "%s", &aStr[0]);

									if (strcmp(aStr, "INDEX") == 0)
									{
										// (=)の除去
										fscanf(pFile, "%s", &omit[0]);
										fscanf(pFile, "%d", &Index);
									}
									else if (strcmp(aStr, "PARENT") == 0)
									{
										// (=)の除去
										fscanf(pFile, "%s", &omit[0]);
										fscanf(pFile, "%d", &nIdxModelParent);
										if (nIdxModelParent == -1)
										{
											ppModel[Index]->SetParent(NULL);
										}
										else
										{
											ppModel[Index]->SetParent(ppModel[nIdxModelParent]);
										}
									}

									else if (strcmp(aStr, "POS") == 0)
									{
										// 文字の読み込み
										fscanf(pFile, "%s", &omit[0]);
										fscanf(pFile, "%f", &pos.x);
										fscanf(pFile, "%f", &pos.y);
										fscanf(pFile, "%f", &pos.z);
										ppModel[Index]->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));

									}
									else if (strcmp(aStr, "ROT") == 0)
									{
										// 文字の読み込み
										fscanf(pFile, "%s", &omit[0]);
										fscanf(pFile, "%f", &rot.x);
										fscanf(pFile, "%f", &rot.y);
										fscanf(pFile, "%f", &rot.z);
										ppModel[Index]->SetRot(D3DXVECTOR3(rot.x, rot.y, rot.z));
									}
									if (strcmp(aStr, "END_PARTSSET") == 0)
									{
										break;
									}
								}
							}

							if (strcmp(aStr, "END_CHARACTERSET") == 0)
							{
								break;
							}
						}
					}
					else if (strcmp(aStr, "MOTIONSET") == 0)
					{
						while (1)
						{
							// 文字の読み込み
							fscanf(pFile, "%s", &aStr[0]);

							if (strcmp(aStr, "LOOP") == 0)
							{
								// 文字の読み込み
								fscanf(pFile, "%s", &omit[0]);
								fscanf(pFile, "%d", &m_aInfo[nMotion].m_bLoop);
							}
							else if (strcmp(aStr, "NUM_KEY") == 0)
							{
								// 文字の読み込み
								fscanf(pFile, "%s", &omit[0]);
								fscanf(pFile, "%d", &m_aInfo[nMotion].m_nNumKey);
							}
							else if (strcmp(aStr, "KEYSET") == 0)
							{
								nCount = 0;

								while (1)
								{
									// 文字の読み込み
									fscanf(pFile, "%s", &aStr[0]);

									while (1)
									{
										// 文字の読み込み
										fscanf(pFile, "%s", &aStr[0]);

										if (strcmp(aStr, "FRAME") == 0)
										{
											fscanf(pFile, "%s", &omit[0]);
											fscanf(pFile, "%d", &m_aInfo[nMotion].m_aKeyInfo[nKey].m_nFrame);
											break;
										}

									}

									while (1)
									{
										// 文字の読み込み
										fscanf(pFile, "%s", &aStr[0]);

										if (strcmp(aStr, "KEY") == 0)
										{
											while (1)
											{
												// 文字の読み込み
												fscanf(pFile, "%s", &aStr[0]);

												if (strcmp(aStr, "POS") == 0)
												{
													fscanf(pFile, "%s", &omit[0]);
													fscanf(pFile, "%f", &m_aInfo[nMotion].m_aKeyInfo[nKey].m_aKey[nCount].m_fPosX);
													fscanf(pFile, "%f", &m_aInfo[nMotion].m_aKeyInfo[nKey].m_aKey[nCount].m_fPosY);
													fscanf(pFile, "%f", &m_aInfo[nMotion].m_aKeyInfo[nKey].m_aKey[nCount].m_fPosZ);

												}
												else if (strcmp(aStr, "ROT") == 0)
												{
													fscanf(pFile, "%s", &omit[0]);
													fscanf(pFile, "%f", &m_aInfo[nMotion].m_aKeyInfo[nKey].m_aKey[nCount].m_fRotX);
													fscanf(pFile, "%f", &m_aInfo[nMotion].m_aKeyInfo[nKey].m_aKey[nCount].m_fRotY);
													fscanf(pFile, "%f", &m_aInfo[nMotion].m_aKeyInfo[nKey].m_aKey[nCount].m_fRotZ);

												}
												if (strcmp(aStr, "END_KEY") == 0)
												{
													nCount++;

													break;
												}
											}
										}
										if (strcmp(aStr, "END_KEYSET") == 0)
										{
											nKey++;
											nCount = 0;
											break;
										}

									}
									break;


								}

							}
							if (strcmp(aStr, "END_MOTIONSET") == 0)
							{
								nMotion++;
								nKey = 0;
								break;
							}

						}

					}

					if (strcmp(aStr, "END_SCRIPT") == 0)
					{
						break;
					}
				}
				break;
			}
		}
	}

	// ファイルを閉じる
	fclose(pFile);

	return S_OK;
}

//=================================================
// 更新
//=================================================
void CMotion::Update(CModel** ppModel)
{
	KEY Diff, Value;//差と値

	//全モデル(パーツ)の更新
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		//次のモーション
		m_nNext = (m_nKey + 1) % m_aInfo[MotionType].m_nNumKey;

		//位置の算出
		Diff.m_fPosX = m_aInfo[MotionType].m_aKeyInfo[m_nNext].m_aKey[nCntModel].m_fPosX - m_aInfo[MotionType].m_aKeyInfo[m_nKey].m_aKey[nCntModel].m_fPosX;
		Diff.m_fPosY = m_aInfo[MotionType].m_aKeyInfo[m_nNext].m_aKey[nCntModel].m_fPosY - m_aInfo[MotionType].m_aKeyInfo[m_nKey].m_aKey[nCntModel].m_fPosY;
		Diff.m_fPosZ = m_aInfo[MotionType].m_aKeyInfo[m_nNext].m_aKey[nCntModel].m_fPosZ - m_aInfo[MotionType].m_aKeyInfo[m_nKey].m_aKey[nCntModel].m_fPosZ;

		//向きの算出						
		Diff.m_fRotX = m_aInfo[MotionType].m_aKeyInfo[m_nNext].m_aKey[nCntModel].m_fRotX - m_aInfo[MotionType].m_aKeyInfo[m_nKey].m_aKey[nCntModel].m_fRotX;
		Diff.m_fRotY = m_aInfo[MotionType].m_aKeyInfo[m_nNext].m_aKey[nCntModel].m_fRotY - m_aInfo[MotionType].m_aKeyInfo[m_nKey].m_aKey[nCntModel].m_fRotY;
		Diff.m_fRotZ = m_aInfo[MotionType].m_aKeyInfo[m_nNext].m_aKey[nCntModel].m_fRotZ - m_aInfo[MotionType].m_aKeyInfo[m_nKey].m_aKey[nCntModel].m_fRotZ;

		//求める値						   
		Value.m_fPosX = m_aInfo[MotionType].m_aKeyInfo[m_nKey].m_aKey[nCntModel].m_fPosX + Diff.m_fPosX * ((float)(m_nCounterMotion) / (float)(m_aInfo[MotionType].m_aKeyInfo[m_nKey].m_nFrame));
		Value.m_fPosY = m_aInfo[MotionType].m_aKeyInfo[m_nKey].m_aKey[nCntModel].m_fPosY + Diff.m_fPosY * ((float)(m_nCounterMotion) / (float)(m_aInfo[MotionType].m_aKeyInfo[m_nKey].m_nFrame));
		Value.m_fPosZ = m_aInfo[MotionType].m_aKeyInfo[m_nKey].m_aKey[nCntModel].m_fPosZ + Diff.m_fPosZ * ((float)(m_nCounterMotion) / (float)(m_aInfo[MotionType].m_aKeyInfo[m_nKey].m_nFrame));

		//求める値						   
		Value.m_fRotX = m_aInfo[MotionType].m_aKeyInfo[m_nKey].m_aKey[nCntModel].m_fRotX + Diff.m_fRotX * ((float)(m_nCounterMotion) / (float)(m_aInfo[MotionType].m_aKeyInfo[m_nKey].m_nFrame));
		Value.m_fRotY = m_aInfo[MotionType].m_aKeyInfo[m_nKey].m_aKey[nCntModel].m_fRotY + Diff.m_fRotY * ((float)(m_nCounterMotion) / (float)(m_aInfo[MotionType].m_aKeyInfo[m_nKey].m_nFrame));
		Value.m_fRotZ = m_aInfo[MotionType].m_aKeyInfo[m_nKey].m_aKey[nCntModel].m_fRotZ + Diff.m_fRotZ * ((float)(m_nCounterMotion) / (float)(m_aInfo[MotionType].m_aKeyInfo[m_nKey].m_nFrame));

		//パーツの位置・向きを設定
		//ppModel[nCntModel]->SetPos(D3DXVECTOR3(Value.m_fPosX, Value.m_fPosY, Value.m_fPosZ));
		ppModel[nCntModel]->SetRot(D3DXVECTOR3(Value.m_fRotX, Value.m_fRotY, Value.m_fRotZ));
	}

	//モーションを動かす
	m_nCounterMotion++;

	//カウンターモーションのリセット処理
	if (m_nCounterMotion >= m_aInfo[MotionType].m_aKeyInfo[m_nKey].m_nFrame)
	{
		m_nCounterMotion = 0;
		m_nKey++;
		m_nNext++;

		if (m_nKey >= m_aInfo[MotionType].m_nNumKey)
		{
			m_nKey = 0;
		}

		if (m_nNext >= m_aInfo[MotionType].m_nNumKey)
		{
			m_nNext = 0;	
		}
	}
}