#include "stdafx.h"
#include "Item.h"


CItem::CItem()
	: m_fXSpeed(0.f), m_bFirst(true), m_fX(0.f), m_fY(0.f)
{
}


CItem::~CItem()
{
	Release();
}

void CItem::Initialize(void)
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 20.f;

	m_fSpeed = float(rand() % 45 + 3.f) / 10.f;
	m_fXSpeed = float(rand() % 25 + 0.5f) / 10.f;
	
	m_iItemCount = rand() % 3 + 1;
}



int CItem::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Create_Speed();

	if (m_bMagnet)
	{

		float fWidth = m_tInfo.fX - m_Target->Get_Info().fX;
		float fHeight = m_tInfo.fY - m_Target->Get_Info().fY;
		float fRadian = atan2f(fHeight, fWidth);
		m_tInfo.fX -= cosf(fRadian) * 5.f;
		m_tInfo.fY -= sinf(fRadian) * 5.f;

	}
	else
	{
		m_tInfo.fX += m_fXSpeed;
		m_tInfo.fY += m_fSpeed;
	}	

	Update_Rect();

	return OBJ_NOEVENT;
}

void CItem::Late_Update(void)
{
	if (0 >= m_tInfo.fX || WINCX < m_tInfo.fX)
	{
		m_fXSpeed *= -1.f;
	}
	if (WINCY <= m_tInfo.fY || 0 >= m_tInfo.fY)
	{
		m_fSpeed *= -1.f;
	}	
}



void CItem::Render(HDC hDC)
{
	if (m_iItemCount == 1)
	{
		Ellipse(hDC,m_tRect.left,m_tRect.top,m_tRect.right,m_tRect.bottom);
		TCHAR	szBuff[32] = L"";
		wsprintf(szBuff, L"B", nullptr);
		TextOut(hDC, m_tInfo.fX - 5, m_tInfo.fY - 8, szBuff, lstrlen(szBuff));
	}
	else if (m_iItemCount == 2)
	{
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		TCHAR	szBuff[32] = L"";
		wsprintf(szBuff, L"SHIELD", nullptr);
		TextOut(hDC, m_tInfo.fX - 25, m_tInfo.fY - 8, szBuff, lstrlen(szBuff));
	}
	else
	{
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		TCHAR	szBuff[32] = L"";
		wsprintf(szBuff, L"MAGNET", nullptr);
		TextOut(hDC, m_tInfo.fX - 25, m_tInfo.fY - 8, szBuff, lstrlen(szBuff));
	}
}



void CItem::Release(void)
{
}

void CItem::Create_Speed(void)
{
	if (m_bFirst == true)
	{
		m_fX = m_tInfo.fX;
		m_fY = m_tInfo.fY;

		if (m_fX > WINCX * 0.5)
			m_fXSpeed = m_fXSpeed * -1.f;

		m_bFirst = false;
	}
}
