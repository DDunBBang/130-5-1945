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
	m_tInfo.fX = m_Target->Get_Info().fX + m_fDistance*cos(m_fRadian*DEGREE);
	m_tInfo.fY = m_Target->Get_Info().fY - m_fDistance*sin(m_fRadian*DEGREE);
	Update_Rect();

	return OBJ_NOEVENT;
}

void CShield::Late_Update(void)
{
	if (m_dwTime + 5000 < GetTickCount())
		m_bDead = true;

}

void CShield::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CShield::Release(void)
{
}
