#include "stdafx.h"
#include "ScrewBullet.h"


CScrewBullet::CScrewBullet()
{
}


CScrewBullet::~CScrewBullet()
{
}

void CScrewBullet::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
	m_tInfo2.fCX = 30.f;
	m_tInfo2.fCY = 30.f;

	m_fSpeed = 5.f;
	m_fTspeed = 20.f;
	m_fDistance = 10.f;
}

int CScrewBullet::Update(void)
{
	POINT pt = { m_tInfo.fX ,m_tInfo.fY };
	pt.y =m_tInfo.fY- m_fSpeed;

	m_fRadian += m_fTspeed;
	m_fRadian2 += m_fTspeed;
	m_tInfo.fX=pt.x+ m_fDistance*cos(m_fRadian*DEGREE);
	m_tInfo.fY = pt.y-m_fDistance*sin(m_fRadian*DEGREE);

	m_tInfo2.fX = pt.x + m_fDistance*cos((m_fRadian-180)*DEGREE);
	m_tInfo2.fY = pt.y - m_fDistance*sin((m_fRadian - 180)*DEGREE);

	Update_Rect();
	Update_Rect2();

	return OBJ_NOEVENT;
}

void CScrewBullet::Late_Update(void)
{
	if (m_tRect.left < 0 || m_tRect.top < 0 || m_tRect.right > WINCX || m_tRect.bottom > WINCY)
		m_bDead = true;

	if (m_tRect2.left < 0 || m_tRect2.top < 0 || m_tRect2.right > WINCX || m_tRect2.bottom > WINCY)
		m_bDead = true;
}

void CScrewBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	Ellipse(hDC, m_tRect2.left, m_tRect2.top, m_tRect2.right, m_tRect2.bottom);
}

void CScrewBullet::Release(void)
{
}

void CScrewBullet::Update_Rect2(void)
{
	m_tRect2.left = int(m_tInfo2.fX - (m_tInfo2.fCX * 0.5f));
	m_tRect2.top = int(m_tInfo2.fY - (m_tInfo2.fCY * 0.5f));
	m_tRect2.right = int(m_tInfo2.fX + (m_tInfo2.fCX * 0.5f));
	m_tRect2.bottom = int(m_tInfo2.fY + (m_tInfo2.fCY * 0.5f));
}
