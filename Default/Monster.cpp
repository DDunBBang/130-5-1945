
#include "stdafx.h"
#include "stdafx.h"
#include "Monster.h"
#include "AbstractFactory.h"
#include "Item.h"

CMonster::CMonster():m_bDrop(true)
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
	m_fSpeed = 4.f;

	if (101 == m_iLv)
	{
		m_tInfo.fCX = 200.f;
		m_tInfo.fCY = 100.f;
		m_tInfo.fX = WINCX * 0.5f;
		m_tInfo.fY = 100.f;
		m_eDir = DIR_LEFT;
		m_iHP = 300;
		m_fSpeed = 2.f;
	}
	else if (m_iLv > 85 && 100 >= m_iLv)
	{
		m_iLv = 1;
		m_tInfo.fX = -10.f;
		m_tInfo.fY = 20.f;
		m_eDir = DIR_RIGHT;
		m_iHP = 1;	// 60;
	}
	else if (m_iLv > 70)
	{
		m_iLv = 1;
		m_tInfo.fX = WINCX + 10;
		m_tInfo.fY = 20.f;
		m_eDir = DIR_LEFT;
		m_iHP = 1; //60;
	}
	else if (m_iLv > 55)
	{
		m_iLv = 2;
		m_tInfo.fX = WINCX - 20.f;
		m_tInfo.fY = 20.f;
		m_eDir = DIR_DOWN;
		m_iHP = 1;// 120;
	}
	else if (m_iLv > 40)
	{
		m_iLv = 3;
		m_tInfo.fX = 20.f;
		m_tInfo.fY = 20.f;
		m_eDir = DIR_DOWN;
		m_iHP = 1;// 120;
	}
	else if (m_iLv > 30)
	{
		m_iLv = 4;
		m_tInfo.fX = WINCX / 2;

		m_tInfo.fY = 0.f;
		m_eDir = DIR_LT;
		m_iHP = 1;// 180;
	}
	else if (m_iLv > 20)
	{
		m_iLv = 4;
		m_tInfo.fX = WINCX / 2;

		m_tInfo.fY = 0.f;
		m_eDir = DIR_RT;
		m_iHP = 1;// 180;
	}
	else if (m_iLv > 10)
	{
		m_iLv = 5;
		m_tInfo.fCX = 50.f;
		m_tInfo.fCY = 50.f;
		m_tInfo.fX = 100.f;
		m_tInfo.fY = 10.f;
		m_eDir = DIR_DOWN;
		m_iHP = 3000;
	}
	else
	{
		m_iLv = 5;
		m_tInfo.fCX = 50.f;
		m_tInfo.fCY = 50.f;
		m_tInfo.fX = WINCX - 100;
		m_tInfo.fY = 10.f;
		m_eDir = DIR_DOWN;
		m_iHP = 3000;
	}
}

int CMonster::Update(void)
{
	if (m_bDead)
	{
		if(m_bDrop)
 			m_pItem->push_back(CAbstractFactory<CItem>::Create(m_tInfo.fX, m_tInfo.fY));
		///*if (2 == rand() % 2 + 1)
		//{*/
		//	m_pItem->push_back(CAbstractFactory<CItem>::Create(m_tInfo.fX, m_tInfo.fY));
		////}
		return OBJ_DEAD;
	}

	Direction();
	if (5 != m_iLv)
	{
		if (m_dwTime + 500 < GetTickCount())
		{
			Attack_Player();
			m_dwTime = GetTickCount();
		}
	}
	else
	{
		if (m_dwTime + 1300 < GetTickCount())
		{
			Attack_Player();
			m_dwTime = GetTickCount();
		}
	}
	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
	if (5 == m_iLv && 200 < m_tInfo.fY)
		m_eDir = DIR_END;
	if (4 == m_iLv && (20 > m_tInfo.fX || WINCX - 20 < m_tInfo.fX))
		m_fSpeed *= -1.f;
	if (101 == m_iLv && (100 > m_tInfo.fX || WINCX - 100 < m_tInfo.fX))
		m_fSpeed *= -1.f;

	if (0 >= m_iHP)
	{
		if (5 == m_iLv)
			m_pUnique = false;
		m_bDead = true;
	}

	if (m_tRect.left < -100 || m_tRect.top < -100 || m_tRect.right > WINCX + 300 || m_tRect.bottom > WINCY + 300)
	{
		m_bDrop = false;
		m_bDead = true;
	}

	if (101 == m_iLv && 0 >= m_iHP)
   		m_bDead = true;

}

void CMonster::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CMonster::Release(void)
{
}

void CMonster::Attack_Player()
{
	if (1 == m_iLv)
	{
		m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_DOWN));
		dynamic_cast<CBullet*>(m_pBullet->back())->Check_Bullet();
	}
	else if (2 == m_iLv)
	{
		m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LEFT));
		dynamic_cast<CBullet*>(m_pBullet->back())->Check_Bullet();
	}
	else if (3 == m_iLv)
	{
		m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RIGHT));
		dynamic_cast<CBullet*>(m_pBullet->back())->Check_Bullet();
	}
	else if (5 == m_iLv)
	{
		m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_DOWN));
		dynamic_cast<CBullet*>(m_pBullet->back())->Check_Bullet();
		m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LB));
		dynamic_cast<CBullet*>(m_pBullet->back())->Check_Bullet();
		m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_RB));
		dynamic_cast<CBullet*>(m_pBullet->back())->Check_Bullet();
	}
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
