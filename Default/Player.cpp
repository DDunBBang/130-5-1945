#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo = { 250.f, 650.f, 40.f, 40.f };
	m_fSpeed = 10.f;
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;
	Key_Input();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	/*if(m_tRect.left<=0)
		m_tInfo.fX= m_tInfo.fCX/2.f;
	else if (m_tRect.right >= WINCX)
		m_tInfo.fX = WINCX-m_tInfo.fCX / 2.f;
	else if (m_tRect.top <= 0)
		m_tInfo.fY = m_tInfo.fCY / 2.f;
	else if (m_tRect.bottom >= WINCY)
		m_tInfo.fY = WINCY-m_tInfo.fCY / 2.f;*/
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, 
		m_tRect.left, 
		m_tRect.top, 
		m_tRect.right, 
		m_tRect.bottom);
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CPlayer::Release(void)
{	
}

void CPlayer::Key_Input(void)
{
	// GetKeyState()
	if (GetAsyncKeyState(VK_RIGHT))
		if(m_tRect.right<WINCX)
			m_tInfo.fX += m_fSpeed;

	if (GetAsyncKeyState(VK_LEFT))
		if (m_tRect.left>0)
			m_tInfo.fX -= m_fSpeed;

	if (GetAsyncKeyState(VK_UP))
		if (m_tRect.top>0)
			m_tInfo.fY -= m_fSpeed;

	if (GetAsyncKeyState(VK_DOWN))
		if (m_tRect.bottom<WINCY)
			m_tInfo.fY += m_fSpeed;

	if (GetAsyncKeyState(VK_SPACE))
	{
		if(m_iLv==1)
			m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_UP));
		else if (m_iLv == 2)
		{
			m_pBullet->push_back(CAbstractFactory<CBullet>::Create((float)m_tRect.left, (float)m_tRect.top, DIR_UP));
			m_pBullet->push_back(CAbstractFactory<CBullet>::Create((float)m_tRect.right, (float)m_tRect.top, DIR_UP));
		}
		else if (m_iLv >= 3)
		{
			m_pBullet->push_back(CAbstractFactory<CBullet>::Create((float)m_tRect.left, (float)m_tRect.top, DIR_UP));
			m_pBullet->push_back(CAbstractFactory<CBullet>::Create((float)m_tRect.right, (float)m_tRect.top, DIR_UP));
			m_pBullet->push_back(CAbstractFactory<CBullet>::Create((float)m_tRect.left, m_tInfo.fY, DIR_LT));
			m_pBullet->push_back(CAbstractFactory<CBullet>::Create((float)m_tRect.right, m_tInfo.fY, DIR_RT));
		}
	}

	if (GetAsyncKeyState('T'))
		++m_iLv;
}