#pragma once
#include "Obj.h"
class CBullet : public CObj
{
public:
	CBullet();
	virtual ~CBullet();

public:
	void Set_Bullet(list<CObj*>* _pBullet) { m_pBullet = _pBullet; }
	void Check_Bullet() { m_bCheck = true; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual	void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void	Direction(void);

	list<CObj*>* m_pBullet;
	bool		m_bCheck;
	bool        m_bRCSize;
};

