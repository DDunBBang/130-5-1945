#include "stdafx.h"
#include "Pet.h"
#include "AbstractFactory.h"

CPet::CPet()
{
}


CPet::~CPet()
{
}

void CPet::Initialize(void)
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_fSpeed = 8.f;
	m_fDistance = 40.f;
};
int CPet::Update(void)
{
	if(m_bDead)
		return OBJ_DEAD;

	Shot();
	Move();
	Update_Rect();
	return OBJ_NOEVENT;
}

void CPet::Late_Update(void)
{
	if (m_eDir == DIR_LEFT)
	{		
		if (m_tRect.right >= m_Target->Get_Rect().left - 10.f)
		{
			if (m_tRect.left <= 0)
				m_tInfo.fX = 10.f;
			else
				m_tInfo.fX = m_Target->Get_Rect().left - m_fSpeed;
		}
	}
	else
	{
		if (m_tRect.left <= m_Target->Get_Rect().right + 10.f)
		{
			if (m_tRect.right >= WINCX)
				m_tInfo.fX = WINCX - 10.f;
			else
				m_tInfo.fX = m_Target->Get_Rect().right + m_fSpeed;
		}
	}

	if (m_Target->Get_Dead())
	{
		m_bDead = true;
	}

}

void CPet::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPet::Release(void)
{
}

void CPet::Shot()
{
	if (m_dwTime + 1000 <= GetTickCount())
	{
		m_pBullet->push_back(Create_Udo());
		m_dwTime = GetTickCount();	
	}
}

void CPet::Move()
{
	m_fRadian = atan2f((m_Target->Get_Info().fY - m_tInfo.fY), (m_Target->Get_Info().fX - m_tInfo.fX));

	m_tInfo.fX += m_fSpeed*cos(m_fRadian);
	m_tInfo.fY += m_fSpeed*sin(m_fRadian);
}

CObj * CPet::Create_Udo()
{
	CObj* Udo = CAbstractFactory<CUdoBullet>::Create(m_tInfo.fX, m_tInfo.fY);
	Udo->Set_Target_List((m_pTarget_List));

	return Udo;
}
