#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}

void CBullet::Initialize(void)
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	m_fSpeed = 10.f;
}

int CBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Direction();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CBullet::Late_Update(void)
{
}

void CBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Direction(void)
{
	switch (m_eDir)
	{
	case DIR_UP:
		m_tInfo.fY -= m_fSpeed;
		break;
	case DIR_LT:
		m_tInfo.fX -= m_fSpeed*cos(75* DEGREE);
		m_tInfo.fY -= m_fSpeed*sin(75* DEGREE);
		break;
	case DIR_RT:
		m_tInfo.fX += m_fSpeed*cos(75* DEGREE);
		m_tInfo.fY -= m_fSpeed*sin(75* DEGREE);
		break;
	}
}

void CBullet::Release(void)
{
}


