
#pragma once

#include "Obj.h"
#include "Bullet.h"
class CMonster : public CObj
{
public:
	CMonster();
	CMonster(int _iLv);
	virtual ~CMonster();

public:
	void Set_Bullet(list<CObj*>* _pBullet) { m_pBullet = _pBullet; }
	void Set_Item(list<CObj*>* _pItem) { m_pItem = _pItem; }
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Key_Input(void);
	void		Direction();
	list<CObj*>* m_pBullet;
	list<CObj*>* m_pItem;
	int			m_iHP;
};
