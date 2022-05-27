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
	if (m_eDir == DIR_UT)
	{
		m_fSpeed = 10.f;
		m_tInfo.fCX = 150.f;
		m_tInfo.fCY = 0.f;
	}
	else
	{
		m_tInfo.fCX = 10.f;
		m_tInfo.fCY = 10.f;
		m_fSpeed = 10.f;
	}
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
	if (m_tRect.left < 0 || m_tRect.top < 0 || m_tRect.right > WINCX || m_tRect.bottom > WINCY)
		m_bDead = true;
}

void CBullet::Render(HDC hDC)
{
	if(m_eDir== DIR_UT)
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	else
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
	case DIR_MD:
		m_tInfo.fX += m_fSpeed*cos(m_fRadian*DEGREE)*2;
		m_tInfo.fY += m_fSpeed*sin(m_fRadian*DEGREE)*2;
		break;
	case DIR_UT:
		while (m_tInfo.fCY < 150)
		{
			m_tInfo.fY -= m_fSpeed*0.5f;
			m_tInfo.fCY += m_fSpeed;
			break;
		}
		if (m_tInfo.fCY == 150)
			m_tInfo.fY -= m_fSpeed;		
		break;
	}
}

void CBullet::Release(void)
{
}


