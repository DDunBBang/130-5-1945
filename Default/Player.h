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
	const bool Get_HitCheck() const { return m_bHitCheck; }
	void Set_HitCheck(bool _bCheck) { m_bHitCheck = _bCheck; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Key_Input(void);
	CObj* Create_Pet();
	CObj* Create_Shield();

	list<CObj*>* m_pMonster;
	list<CObj*>* m_pPet;
	list<CObj*>* m_pItem;

	int iCount;
	bool m_bHitCheck;

};

