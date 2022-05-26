#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	m_fSpeed = 5.f;
}

int CMonster::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	Move();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
}

void CMonster::Render(HDC hDC)
{
	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CMonster::Release(void)
{
}

void CMonster::Move()
{
	switch (m_eDir)
	{
	case DIR_LEFT:
		if (m_tRect.left <= 0 || m_tRect.right >= WINCX)
			m_fSpeed *= -1.f;
		m_tInfo.fX += m_fSpeed;
		break;
	}
}
