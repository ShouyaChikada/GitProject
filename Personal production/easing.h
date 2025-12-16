//=================================================
//
// [Easeing.h]	イージングヘッダー
// Author:chikada shouya
//
//=================================================
#ifndef _EASING_H_
#define _EASING_H_

#include "main.h"
#include "manager.h"

// template<class T>Tを任意の型として関数内で使用できる
 
//=================================================
// Lerp (線形補間) 関数
//=================================================
D3DXVECTOR3 Lerp(const D3DXVECTOR3& Current, const D3DXVECTOR3& Dest, float t) 
{
	return (Current + t * (Dest - Current));
}

template<class T> T EaseInSine(T t)
{
  return (1 - cosf((t * D3DX_PI) / 2));
}

template<class T> T EaseOutSine(T t)
{
  return (sinf((t * D3DX_PI) / 2));
}

template<class T> T EaseInOutSine(T t)
{
	return (-(cosf(D3DX_PI * t) - 1) / 2);
}

template<class T> T EaseOutQuad(T t)
{
	//変数xはアニメーションの絶対的な進行度を0（アニメーションの開始）と1（アニメーションの終了）の範囲
	return (1 - (1 - t) * (1 - t));
}

template<class T> T EaseInQuint(T t)
{
	return (t * t * t * t * t);
}

template<class T> T EaseInBounce(T t)
{
	return (1 - EaseOutBounce(1 - t));
}

template<class T> T EaseOutBounce(T t)
{
	const float n1 = 7.5625f;
	const float d1 = 2.75f;

	if (t < 1 / d1) 
	{
		return (n1 * t * t);
	}
	else if (t < 2 / d1)
	{
	  return (n1 * (t -= 1.5 / d1) * t + 0.75f);
	}
	else if (t < 2.5 / d1) 
	{
	  return (n1 * (t -= 2.25 / d1) * t + 0.9375f);
	}
	else 
	{
	  return (n1 * (t -= 2.625 / d1) * t + 0.984375f);
	}
}

template<class T> T EaseInOutBounce(T t)
{
	return t < 0.5
	  ? ((1 - EaseOutBounce(1 - 2 * t)) / 2)
	  : ((1 + EaseOutBounce(2 * t - 1)) / 2);
}
#endif