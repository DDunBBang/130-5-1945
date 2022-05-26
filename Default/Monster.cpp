#include "stdafx.h"
#include "Monster.h"
#include "AbstractFactory.h"

CMonster::CMonster()
{
}

CMonster::CMonster(int _iLv)
{
	m_iLv = _iLv;
}

CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;
	m_fSpeed = 3.f;

	if (m_iLv > 85)
	{
		m_iLv = 1;
		m_tInfo.fX = -10.f;
		m_tInfo.fY = 20.f;
		m_eDir = DIR_RIGHT;
		m_iHP = 10;
	}
	else if (m_iLv > 70)
	{
		m_iLv = 1;
		m_tInfo.fX = WINCX + 10;
		m_tInfo.fY = 20.f;
		m_eDir = DIR_LEFT;
		m_iHP = 10;
	}
	else if (m_iLv > 55)
	{
		m_iLv = 2;
		m_tInfo.fX = WINCX - 20.f;
		m_tInfo.fY = 20.f;
		m_eDir = DIR_DOWN;
		m_iHP = 60;
	}
	else if (m_iLv > 40)
	{
		m_iLv = 2;
		m_tInfo.fX = 20.f;
		m_tInfo.fY = 20.f;
		m_eDir = DIR_DOWN;
		m_iHP = 60;
	}
	else if (m_iLv > 30)
	{
		m_iLv = 3;
		m_tInfo.fX = WINCX / 2;
		m_tInfo.fY = -10.f;
		m_eDir = DIR_LT;
		m_iHP = 120;
	}
	else if (m_iLv > 20)
	{
		m_iLv = 3;
		m_tInfo.fX = WINCX / 2;
		m_tInfo.fY = -10.f;
		m_eDir = DIR_RT;
		m_iHP = 120;
	}
	else if (m_iLv > 10 )
	{
		m_iLv = 4;
		m_tInfo.fCX = 50.f;
		m_tInfo.fCY = 50.f;
		m_tInfo.fX = 100.f;
		m_tInfo.fY = 0.f;
		m_eDir = DIR_DOWN;
		m_iHP = 300;
	}
	else
	{
		m_iLv = 4;
		m_tInfo.fCX = 50.f;
		m_tInfo.fCY = 50.f;
		m_tInfo.fX = WINCX - 100;
		m_tInfo.fY = 0.f;
		m_eDir = DIR_DOWN;
		m_iHP = 300;
	}
}

int CMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Direction();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
	if (4 == m_iLv && 250 < m_tInfo.fY)
		m_eDir = DIR_END;
	if (3 == m_iLv && (20 == m_tInfo.fX || WINCX - 20 == m_tInfo.fX))
		m_fSpeed *= -1.f;
}

void CMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release(void)
{
}

void CMonster::Key_Input(void)
{
}

void CMonster::Direction()
{
	switch (m_eDir)
	{
	case DIR_LEFT:
		m_tInfo.fX -= m_fSpeed;
		break;
	case DIR_UP:
		m_tInfo.fY -= m_fSpeed;
		break;
	case DIR_RIGHT:
		m_tInfo.fX += m_fSpeed;
		break;
	case DIR_DOWN:
		m_tInfo.fY += m_fSpeed;
		break;
	case DIR_LT:
		m_tInfo.fY += 3.f;
		m_tInfo.fX -= m_fSpeed;
		break;
	case DIR_RT:
		m_tInfo.fY += 3.f;
		m_tInfo.fX += m_fSpeed;
		break;
	}
}
