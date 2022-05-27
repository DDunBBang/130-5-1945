#include "stdafx.h"
#include "UdoBullet.h"


CUdoBullet::CUdoBullet()
{
}


CUdoBullet::~CUdoBullet()
{
}

void CUdoBullet::Initialize(void)
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;
	m_fSpeed = 20.f;
}

int CUdoBullet::Update(void)
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_pTarget_List->begin() != m_pTarget_List->end())
	{
		float imsi = sqrtf(WINCX*WINCX + WINCY*WINCY);
		for (auto& iter = m_pTarget_List->begin(); iter != m_pTarget_List->end(); ++iter)
		{			
			m_fDistance = sqrtf(((*iter)->Get_Info().fX - m_tInfo.fX)*((*iter)->Get_Info().fX - m_tInfo.fX) +
				((*iter)->Get_Info().fY - m_tInfo.fY)*((*iter)->Get_Info().fY - m_tInfo.fY));
			if (m_fDistance < imsi)
			{
				imsi = m_fDistance;
				Set_Target((*iter));
			}
		}
		if (m_Target)
		{
			float disX = m_Target->Get_Info().fX - m_tInfo.fX;
			float disY = m_Target->Get_Info().fY - m_tInfo.fY;
			m_fRadian = atan2f(disY, disX);
			m_tInfo.fX += m_fSpeed*cosf(m_fRadian);
			m_tInfo.fY += m_fSpeed*sinf(m_fRadian);
		}		
	}
	else
	{
		m_tInfo.fX += m_fSpeed*cosf(m_fRadian);
		m_tInfo.fY += m_fSpeed*sinf(m_fRadian);
	}
	Update_Rect();

	return OBJ_NOEVENT;
}

void CUdoBullet::Late_Update(void)
{
	if (m_tRect.left < 0 || m_tRect.top < 0 || m_tRect.right > WINCX || m_tRect.bottom > WINCY)
		m_bDead = true;
}

void CUdoBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CUdoBullet::Release(void)
{
}
