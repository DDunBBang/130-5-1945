#include "stdafx.h"
#include "Item.h"


CItem::CItem()
	: m_ffXSpeed(0), m_bFirst(true)
{
}


CItem::~CItem()
{
	Release();
}

void CItem::Initialize(void)
{
	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 25.f;

	m_iItemCount = rand() % 2 + 1;
	m_fSpeed = float(rand() % 45 + 3.f) / 10.f;
	m_ffXSpeed = float(rand() %  25 + 0.5f) / 10.f;
}



int CItem::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Create_Speed();

	m_tInfo.fY += m_fSpeed;

	return OBJ_NOEVENT;
}

void CItem::Late_Update(void)
{
	if (100 >= m_tRect.left || WINCX - 100 <= m_tRect.right)
	{
		m_ffXSpeed *= -1.f;
	}
	else if (WINCY - 100 <= m_tRect.bottom || 100 >= m_tRect.top)
	{
		m_fSpeed *= -1.f;
	}
}



void CItem::Render(HDC hDC)
{
	if (m_iItemCount == 1)
	{
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		TCHAR	szBuff[32] = L"";
		wsprintf(szBuff, L"B", nullptr);
		TextOut(hDC, m_tInfo.fX - 5, m_tInfo.fY - 8, szBuff, lstrlen(szBuff));

	}

	if (m_iItemCount == 2)
	{
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		TCHAR	szBuff[32] = L"";
		wsprintf(szBuff, L"SHIELD", nullptr);
		TextOut(hDC, m_tInfo.fX - 25, m_tInfo.fY - 8, szBuff, lstrlen(szBuff));

	}
}



void CItem::Release(void)
{
}

void CItem::Create_Speed(void)
{
	if (1 == m_bFirst)
	{
		m_fX = m_tInfo.fX;
		m_fY = m_tInfo.fY;

		m_bFirst = false;
	}

	if (WINCX - 400 > m_fX)
	{
		m_tInfo.fX += m_ffXSpeed;
	}
	else if (WINCX - 400 < m_fX)
	{
		m_tInfo.fX -= m_ffXSpeed;
	}
}
