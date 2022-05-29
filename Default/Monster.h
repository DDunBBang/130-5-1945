
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
	void Set_Unique(bool* _pUnique) { m_pUnique = _pUnique; }
	const int Get_LV() const { return m_iLv; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Attack_Player();
	void		Direction();
	void		Boss();

	list<CObj*>* m_pBullet;
	list<CObj*>* m_pItem;

	bool*		m_pUnique;
	bool		m_bDrop;

	DWORD		m_dwPattern1;
	DWORD		m_dwPattern2;
	DWORD		m_dwPattern2_1;
	DWORD		m_dwPattern3;

	float		m_fTheta;
};
