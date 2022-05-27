#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"
CPlayer::CPlayer():iCount(2)
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

	if (GetAsyncKeyState('X'))
	{
		if (m_pMonster->size()!=0)
		{
			float fRadian = atan2((m_pMonster->front()->Get_Info().fY - m_tInfo.fY), (m_pMonster->front()->Get_Info().fX - m_tInfo.fX))*180/PI;
			m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_MD, fRadian));
		}
	}

	if (GetAsyncKeyState('C'))
	{		
		if (m_dwTime + 10000 <= GetTickCount())
		{				
			m_pBullet->push_back(CAbstractFactory<CBullet>::Create(75, WINCY - 75, DIR_UT));
			m_pBullet->push_back(CAbstractFactory<CBullet>::Create(WINCX - 75, WINCY - 75, DIR_UT));
			m_dwTime = GetTickCount();
		}
	}

	if (GetAsyncKeyState('T'))
		++m_iLv;

	if (GetAsyncKeyState('P'))
	{
		if (iCount > 0)
		{
			if (m_dwTime + 2000 <= GetTickCount())
			{
				m_pPet->push_back(Create_Pet());
				--iCount;
				m_dwTime = GetTickCount();
			}
		}
	}
	if (GetAsyncKeyState('S'))
	{
		if (m_iShieldCount > 0)
		{
			--m_iShieldCount;
			m_pItem->push_back(Create_Shield());
		}
	}
		
	//if (GetAsyncKeyState('M'))
		//m_pMonster->push_back(CAbstractFactory<CMonster>::Create(250, 150, DIR_LEFT));
}
CObj * CPlayer::Create_Pet()
{
	if (iCount == 2)
	{
		CObj* pet = CAbstractFactory<CPet>::Create(m_tInfo.fX-40,m_tInfo.fY,DIR_LEFT);
		pet->Set_Target(this);
		pet->Set_Bullet(m_pBullet);
		return pet;
	}
	else if (iCount == 1)
	{
		CObj* pet = CAbstractFactory<CPet>::Create(m_tInfo.fX + 40, m_tInfo.fY, DIR_RIGHT);
		pet->Set_Target(this);
		pet->Set_Bullet(m_pBullet);
		return pet;
	}
}

CObj * CPlayer::Create_Shield()
{
	CObj* Shield = CAbstractFactory<CShield>::Create();
	Shield->Set_Target(this);

	return Shield;
}
