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
	m_fSpeed = 5.f;

	if (m_iLv > 60)
	{
		m_tInfo.fX = -10;
		m_tInfo.fY = 20;
		m_eDir = DIR_RIGHT;
	}
	else if (m_iLv > 30)
	{
		m_tInfo.fX = WINCX - 20;
		m_tInfo.fY = 20;
		m_eDir = DIR_DOWN;
	}
	else if (m_iLv > 10)
	{
		m_tInfo.fX = WINCX + 10;
		m_tInfo.fY = 300;
		m_eDir = DIR_LEFT;
	}
	else
	{
		m_tInfo.fX = WINCX / 2;
		m_tInfo.fY = WINCY / 2;
		m_eDir = DIR_UP;
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
		break;
	case DIR_RT:
		break;
	}
}
