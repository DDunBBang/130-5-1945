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
	m_iTime = rand() % 4 + 3;
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
		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(184, 134, 11));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush); 

		Ellipse(hDC,m_tRect.left,m_tRect.top,m_tRect.right,m_tRect.bottom);
		TCHAR	szBuff[32] = L"";
		wsprintf(szBuff, L"B", nullptr);
		TextOut(hDC, m_tInfo.fX - 5, m_tInfo.fY - 8, szBuff, lstrlen(szBuff));

		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);
	}
	else if (m_iItemCount == 2)
	{
		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 139));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);


		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		
	/*	MoveToEx(hDC, m_tRect.left ,m_tRect.top, nullptr);
		LineTo(hDC, m_tRect.left, m_tRect.bottom + 20);
		LineTo(hDC, m_tRect.left + 30, m_tRect.bottom + 50);
		LineTo(hDC, m_tRect.left + 60, m_tRect.bottom + 20);
		LineTo(hDC, m_tRect.left + 60, m_tRect.top);
		LineTo(hDC, m_tRect.left, m_tRect.top);*/

		/*LineTo(hDC, m_tInfo.fX, m_tInfo.fY + 40);
		LineTo(hDC, m_tInfo.fX + 30, m_tInfo.fY + 20);
		LineTo(hDC, m_tInfo.fX + 30, m_tInfo.fY - 20);
		LineTo(hDC, m_tInfo.fX, m_tInfo.fY - 20);*/

		TCHAR	szBuff[32] = L"";
		wsprintf(szBuff, L"S", nullptr);
		TextOut(hDC, m_tInfo.fX - 5, m_tInfo.fY - 8, szBuff, lstrlen(szBuff));

		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);
	}

	else if (m_iItemCount == 3 && m_iTime == 3)// && rand() & 3 + 2 == 3)
	{

		HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(139, 0, 139));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);


		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		TCHAR	szBuff[32] = L"";
		wsprintf(szBuff, L"M", nullptr);
		TextOut(hDC, m_tInfo.fX - 5, m_tInfo.fY - 8, szBuff, lstrlen(szBuff));


		SelectObject(hDC, oldBrush);
		DeleteObject(myBrush);
	}

	/*if (m_iCheck == 1)
	{
		TCHAR szBuff[32] = L"";
		wsprintf(szBuff, L"POWER UP!!", nullptr);
		TextOut(hDC, m_tInfo.fX - 10, m_tInfo.fY - 8, szBuff, lstrlen(szBuff));
		
	}*/

}



void CItem::Release(void)
{
}

void CItem::Create_Speed(void)
{
	if (m_bFirst)
	{
		m_fX = m_tInfo.fX;
		m_fY = m_tInfo.fY;

		if (m_fX > WINCX * 0.5)
			m_fXSpeed = m_fXSpeed * -1.f;

		m_bFirst = false;
	}
}
