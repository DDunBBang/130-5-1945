#pragma once

#include "Obj.h"
#include "Bullet.h"
class CPlayer :	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();
	
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
	

	list<CObj*>* m_pBullet;

};

