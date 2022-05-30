#include "stdafx.h"
#include "Player.h"
#include "AbstractFactory.h"

CPlayer::CPlayer::CPlayer()
	:iCount(2), m_bHitCheck(false), m_fdwTime(GetTickCount()), m_fSCTime(GetTickCount()), m_fRCTime(GetTickCount()),
	m_bPause(false), m_bPet(true), m_bPet1(true), m_bImu(false), m_dwHitTime(GetTickCount())
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo = { 250.f, 650.f, 30.f, 30.f };
	m_fSpeed = 6.f;
	m_iHP = 3;
	m_dwBulletTime = GetTickCount();
}

int CPlayer::Update(void)
{
	if (m_bDead)
	{
		for (auto& iter = m_pShield->begin(); iter != m_pShield->end();)
		{
			(*iter)->Set_Dead();
			++iter;
		}
		return OBJ_DEAD;
	}

	Key_Input();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
	if (m_iShieldCount > 4)
	{
		m_iShieldCount = 4;
	}
	if (m_iLv == 4 && m_bPet)
	{
		m_pPet->push_back(Create_Pet());
		m_bPet = false;
	}
	if (m_iLv == 5 && m_bPet1)
	{
		m_pPet->push_back(Create_Pet());
		m_bPet1 = false;
	}
}

void CPlayer::Render(HDC hDC)
{
	if (m_bHitCheck)
	{
		if (m_dwHitTime + 100 < GetTickCount())
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
			m_dwHitTime = GetTickCount();
		}
	}
	else
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
}

void CPlayer::Release(void)
{
}


void CPlayer::Key_Input(void)
{
	// GetKeyState()
	if (GetAsyncKeyState('D') && (m_tRect.right < WINCX))
	{
		if (GetAsyncKeyState('W') && (m_tRect.top > 0))
		{
			m_tInfo.fX += m_fSpeed*sqrtf(0.5);
			m_tInfo.fY -= m_fSpeed*sqrtf(0.5);
		}
		else if (GetAsyncKeyState('S') && (m_tRect.bottom < WINCY))
		{
			m_tInfo.fX += m_fSpeed*sqrtf(0.5);
			m_tInfo.fY += m_fSpeed*sqrtf(0.5);
		}
		else
			m_tInfo.fX += m_fSpeed;
	}

	else if (GetAsyncKeyState('A') && (m_tRect.left > 0))
	{
		if (GetAsyncKeyState('W') && (m_tRect.top > 0))
		{
			m_tInfo.fX -= m_fSpeed*sqrtf(0.5);
			m_tInfo.fY -= m_fSpeed*sqrtf(0.5);
		}
		else if (GetAsyncKeyState('S') && (m_tRect.bottom < WINCY))
		{
			m_tInfo.fX -= m_fSpeed*sqrtf(0.5);
			m_tInfo.fY += m_fSpeed*sqrtf(0.5);
		}
		else
			m_tInfo.fX -= m_fSpeed;
	}

	else if (GetAsyncKeyState('W') && (m_tRect.top > 0))
		m_tInfo.fY -= m_fSpeed;

	else if (GetAsyncKeyState('S') && (m_tRect.bottom < WINCY))
		m_tInfo.fY += m_fSpeed;

	if (m_dwBulletTime + 100 < GetTickCount())
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			if (m_iLv == 1)
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
		m_dwBulletTime = GetTickCount();
	}

	/*if (GetAsyncKeyState(VK_LBUTTON))
	{
		m_fRadian = atan2f(m_pMouse->front()->Get_Info().fY - m_tInfo.fY, m_pMouse->front()->Get_Info().fX - m_tInfo.fX);
		m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY, DIR_LC, m_fRadian));
	}*/

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		if ((m_fRCTime / 1000) + 2 <= (GetTickCount() / 1000))
		{
			m_fRadian = atan2f(m_pMouse->front()->Get_Info().fY - m_tInfo.fY, m_pMouse->front()->Get_Info().fX - m_tInfo.fX);
			m_pBullet->push_back(CAbstractFactory<CBullet>::Create(m_pMouse->front()->Get_Info().fX, m_pMouse->front()->Get_Info().fY, DIR_RC));
			m_fRCTime = GetTickCount();
		}
	}

	if (GetAsyncKeyState('R'))
	{		
		if ((m_dwTime /1000)+20 <= GetTickCount()/1000)
		{				
			m_pBullet->push_back(CAbstractFactory<CBullet>::Create(75, WINCY - 75, DIR_UT));
			m_pBullet->push_back(CAbstractFactory<CBullet>::Create(WINCX - 75, WINCY - 75, DIR_UT));
			//m_dwTime = GetTickCount();
		}
	}
	if (GetAsyncKeyState('C'))
	{
		if ((m_fSCTime / 1000) + 2 <= (GetTickCount() / 1000))
		{
			m_pBullet->push_back(CAbstractFactory<CScrewBullet>::Create(m_tInfo.fX, m_tInfo.fY));
			m_fSCTime = GetTickCount();
		}
	}

	if (GetAsyncKeyState('T'))
		m_bImu = true;
	else if (GetAsyncKeyState('Y'))
		m_bImu = false;

	if (GetAsyncKeyState('Q'))
	{
		if (m_iShieldCount > 0)
		{
			if (m_pShield->begin() == m_pShield->end())
			{
				if (m_iShieldCount == 1)
				{
					m_iShieldCount -= 1;
					m_pShield->push_back(Create_Shield(DIR_UP));
				}
				else if (m_iShieldCount == 2)
				{
					m_iShieldCount -= 2;
					m_pShield->push_back(Create_Shield(DIR_UP));
					m_pShield->push_back(Create_Shield(DIR_RIGHT));
				}
				else if (m_iShieldCount == 3)
				{
					m_iShieldCount -= 3;
					m_pShield->push_back(Create_Shield(DIR_UP));
					m_pShield->push_back(Create_Shield(DIR_DOWN));
					m_pShield->push_back(Create_Shield(DIR_RT));
				}
				else if (m_iShieldCount == 4)
				{
					m_iShieldCount -= 4;
					m_pShield->push_back(Create_Shield(DIR_UP));
					m_pShield->push_back(Create_Shield(DIR_DOWN));
					m_pShield->push_back(Create_Shield(DIR_LEFT));
					m_pShield->push_back(Create_Shield(DIR_RIGHT));
				}
			}
		}
	}
	if (GetAsyncKeyState('1'))
	{
		++m_iShieldCount;
	}

	if (GetAsyncKeyState('O'))
	{
		while (!GetAsyncKeyState('L') & 0x8001)
		{
			continue;
		}
	}

}
CObj * CPlayer::Create_Pet()
{
	if (m_iLv == 4)
	{
		CObj* pet = CAbstractFactory<CPet>::Create(m_tInfo.fX - 40, m_tInfo.fY, DIR_LEFT);
		pet->Set_Target(this);
		pet->Set_Bullet(m_pBullet);
		pet->Set_Target_List(m_pMonster);
		return pet;
	}
	else if (m_iLv == 5)
	{
		CObj* pet1 = CAbstractFactory<CPet>::Create(m_tInfo.fX + 40, m_tInfo.fY, DIR_RIGHT);
		pet1->Set_Target(this);
		pet1->Set_Bullet(m_pBullet);
		pet1->Set_Target_List(m_pMonster);
		return pet1;
	}
	
}

CObj * CPlayer::Create_Shield(DIRECTION eDir)
{
	CObj* Shield = CAbstractFactory<CShield>::Create();
	Shield->Set_Target(this);
	Shield->Set_Dir(eDir);
	return Shield;
}
