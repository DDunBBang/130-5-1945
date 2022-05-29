#include "stdafx.h"
#include "Shield.h"


CShield::CShield()
{
}


CShield::~CShield()
{
}

void CShield::Initialize(void)
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_fDistance = 60.f;
	m_fRadian = 0.f;
	m_fSpeed = 5.f;
}

int CShield::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	m_fRadian += m_fSpeed;
	
	Direction();

	Update_Rect();

	return OBJ_NOEVENT;
}

void CShield::Late_Update(void)
{
}

void CShield::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CShield::Release(void)
{
}

void CShield::Direction(void)
{
	switch (m_eDir)
	{
	case DIR_LEFT:
		m_tInfo.fX = m_Target->Get_Info().fX + m_fDistance*cos((135 + m_fRadian)*DEGREE);
		m_tInfo.fY = m_Target->Get_Info().fY - m_fDistance*sin((135 + m_fRadian)*DEGREE);
		break;
	case DIR_UP:
		m_tInfo.fX = m_Target->Get_Info().fX + m_fDistance*cos((225 + m_fRadian)*DEGREE);
		m_tInfo.fY = m_Target->Get_Info().fY - m_fDistance*sin((225 + m_fRadian)*DEGREE);
		break;
	case DIR_RIGHT:
		m_tInfo.fX = m_Target->Get_Info().fX + m_fDistance*cos((45 + m_fRadian)*DEGREE);
		m_tInfo.fY = m_Target->Get_Info().fY - m_fDistance*sin((45 + m_fRadian)*DEGREE);
		break;
	case DIR_DOWN:
		m_tInfo.fX = m_Target->Get_Info().fX + m_fDistance*cos((315 + m_fRadian)*DEGREE);
		m_tInfo.fY = m_Target->Get_Info().fY - m_fDistance*sin((315 + m_fRadian)*DEGREE);
		break;
	case DIR_RT:
		m_tInfo.fX = m_Target->Get_Info().fX + m_fDistance*cos((90 + m_fRadian)*DEGREE);
		m_tInfo.fY = m_Target->Get_Info().fY - m_fDistance*sin((90 + m_fRadian)*DEGREE);
		break;
	
	
	}
}
