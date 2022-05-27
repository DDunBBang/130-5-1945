#pragma once

#include "Obj.h"
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void	Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour);
	static void	Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour);
	static bool Check_Sphere(CObj* pDest, CObj* pSour);
	static void	Collision_Item(list<CObj*> _Player, list<CObj*> _Item);
	static bool Collision_Oneside(list<CObj*> _Dest, list<CObj*> _Sour);
};

