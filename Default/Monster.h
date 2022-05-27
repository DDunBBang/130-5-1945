
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
	int			m_iHP;
};
