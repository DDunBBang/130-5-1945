#pragma once

#include "Obj.h"
#include "Bullet.h"
#include "Monster.h"
#include "Pet.h"
#include "Shield.h"
class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();
	
public:
	
	void Set_Monster(list<CObj*>* _pMonster) { m_pMonster = _pMonster; }
	void Set_Pet(list<CObj*>* _pPet) { m_pPet = _pPet; }
	void Set_Item(list<CObj*>* _pItem) { m_pItem = _pItem; }
	void Set_Mouse(list<CObj*>* _pMouse) { m_pMouse = _pMouse; }
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	CObj* Create_Pet();
	CObj* Create_Shield();
private:
	void		Key_Input(void);

	list<CObj*>* m_pMonster;
	list<CObj*>* m_pPet;
	list<CObj*>* m_pItem;
	list<CObj*>* m_pMouse;

	int iCount;
	float m_fdwTime;
};

