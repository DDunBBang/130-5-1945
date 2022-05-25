#include "stdafx.h"
#include "CollisionMgr.h"
#include "AbstractFactory.h"
CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};


	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
			{
				Dest->Set_Dead();
				Sour->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{
				Dest->Set_Dead();
				Sour->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj * pDest, CObj * pSour)
{
	float fWidth = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	float fDiagonal = sqrtf(fWidth*fWidth + fHeight*fHeight);
	float fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX)*0.5f;

	return fRadius >= fDiagonal;
}

void CCollisionMgr::Collision_Item(list<CObj*> _Player, list<CObj*> _Item)
{
	RECT		rc{};


	for (auto& Player : _Player)
	{
		for (auto& Item : _Item)
		{
			if (IntersectRect(&rc, &(Player->Get_Rect()), &(Item->Get_Rect())))
			{
				Player->Set_Up_iLv();
				Item->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::Collision_Monster(list<CObj*> _Player, list<CObj*> _Monster)
{
	RECT		rc{};


	for (auto& Player : _Player)
	{
		for (auto& Monster : _Monster)
		{
			if (IntersectRect(&rc, &(Player->Get_Rect()), &(Monster->Get_Rect())))
			{
				Player->Set_Dead();
				return true;
			}
		}
	}
	return false;
}
