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
				if (Dest->Get_Dir() == DIR_UT || Dest->Get_Dir() == DIR_RC)
				{
					if (dynamic_cast<CMonster*>(Sour)->Get_LV() == 101)
						Dest->Set_Dead();
					Sour->Critical_Hit();
				}
				else
					Dest->Set_Dead();
					Sour->Hit();
			}
		}
	}
}

bool CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{
				Dest->Set_Dead();
				Sour->Hit();
				return true;
			}
		}
	}
	return false;
}

bool CCollisionMgr::Collision_Player(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (Check_Sphere(Dest, Sour))
			{
				Sour->Hit();
				return true;
			}
		}
	}
	return false;
}

bool CCollisionMgr::Check_Sphere(CObj * pDest, CObj * pSour)
{
	float fWidth = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	float fDiagonal = sqrtf(fWidth*fWidth + fHeight*fHeight);
	float fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX)*0.5f;

	return fRadius >= fDiagonal;
}

bool CCollisionMgr::Collision_Item(list<CObj*> _Player, list<CObj*> _Item)
{
	RECT		rc{};

	for (auto& Player : _Player)
	{
		for (auto& Item : _Item)
		{
			if (IntersectRect(&rc, &(Player->Get_Rect()), &(Item->Get_Rect())))
			{
				if (Item->Get_ItemCount() <= 3)
				{
					Player->Set_Up_iLv();
				}

				else if (Item->Get_ItemCount() == 4)
				{
					Player->Set_Shield_Count();
				}
				else if (Item->Get_ItemCount() == 5)
				{
					Item->Set_Dead();	
					return true;
				}
				Item->Set_Dead();
			}
		}
	}
	return false;
}



bool CCollisionMgr::Collision_Oneside(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT		rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Sour : _Sour)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Sour->Get_Rect())))
			{
				Dest->Set_Dead();
				return true;
			}
		}
	}
	return false;
}
