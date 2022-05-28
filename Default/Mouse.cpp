#include "stdafx.h"
#include "Mouse.h"


CMouse::CMouse()
{
}


CMouse::~CMouse()
{
}

void CMouse::Initialize(void)
{

}

int CMouse::Update(void)
{
	POINT pt = {};

	GetCursorPos(&pt);

	ScreenToClient(g_hWnd, &pt);

	m_tInfo.fX = pt.x;
	m_tInfo.fY = pt.y;

	Update_Rect();

	ShowCursor(false);

	return OBJ_NOEVENT;
}

void CMouse::Late_Update(void)
{
}

void CMouse::Render(HDC hDC)
{
	MoveToEx(hDC, m_tInfo.fX-10, m_tInfo.fY,0);
	LineTo(hDC, m_tInfo.fX + 10, m_tInfo.fY);
	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY-10, 0);
	LineTo(hDC, m_tInfo.fX, m_tInfo.fY+10);
	Ellipse(hDC, m_tInfo.fX-4, m_tInfo.fY-4, m_tInfo.fX+4, m_tInfo.fY+4);
}

void CMouse::Release(void)
{
}
