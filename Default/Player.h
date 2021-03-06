#pragma once

#include "Obj.h"
#include "Bullet.h"
#include "Monster.h"
#include "Pet.h"
#include "Shield.h"
#include "ScrewBullet.h"
#include "Item.h"
class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();
	
public:
	
	void Set_Monster(list<CObj*>* _pMonster) { m_pMonster = _pMonster; }
	void Set_Pet(list<CObj*>* _pPet) { m_pPet = _pPet; }
	void Set_Shield(list<CObj*>* _pShield) { m_pShield = _pShield; }
	void Set_Mouse(list<CObj*>* _pMouse) { m_pMouse = _pMouse; }
	void Set_HitCheck(bool _bCheck) { m_bHitCheck = _bCheck; }
	void Set_Item(list<CObj*>* Item) { m_pItem = Item; }
	const bool Get_HitCheck() const { return m_bHitCheck; }
	const bool Get_Imu() const { return m_bImu; }


public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Key_Input(void);

	CObj* Create_Pet();
	CObj* Create_Shield(DIRECTION eDir);
	CObj* Create_Item(int Count);

	list<CObj*>* m_pMonster;
	list<CObj*>* m_pPet;
	list<CObj*>* m_pShield;
	list<CObj*>* m_pMouse;
	list<CObj*>* m_pItem;

	DWORD		m_dwBulletTime;
	DWORD		m_dwCountTime;
	DWORD		m_dwHitTime;

	int iCount;
	float m_fdwTime;
	float m_fSCTime;
	float m_fRCTime;
	bool m_bHitCheck;
	bool m_bPause;
	bool m_bPet;
	bool m_bPet1;
	bool m_bImu;
};

