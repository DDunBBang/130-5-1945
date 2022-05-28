#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void		Set_Pos(float _fX, float _fY) 
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	void		Set_Dir(DIRECTION _eDir) { m_eDir = _eDir; }
	void		Set_Dead() { m_bDead = true; }
	bool		Get_Dead() { return m_bDead; }
	const RECT& Get_Rect() { return m_tRect; }
	INFO&		Get_Info() { return m_tInfo; }
	void		Set_Up_iLv(void)	{ ++m_iLv; }
	void		Set_Radian(float _fRadian) { m_fRadian = _fRadian; }
	DIRECTION		Get_Dir() { return m_eDir; }
	void		Set_Target(CObj* m_tar) { m_Target = m_tar; }
	void		Set_Target_List(list<CObj*>* m_tar) { m_pTarget_List = m_tar; }
	void		Set_Bullet(list<CObj*>* _pBullet) { m_pBullet = _pBullet; }
	void		Set_Time(DWORD _m_dwTime) { m_dwTime = _m_dwTime; }
	void		Hit() { --m_iHP; }
	void		Set_Shield_Count(void) { ++m_iShieldCount; }
	int		Get_ItemCount(void) { return m_iItemCount; }
	const void		Set_Magnet_true(void) { m_bMagnet = true; }
	const int	Get_HP() const { return m_iHP; }
	const void  Set_Magnet_false(void) { m_bMagnet = false; }
	const void		Set_Check(int _Check) { m_iCheck = _Check; }
public:
	virtual		void	Initialize(void)	PURE;
	virtual		int		Update(void)		PURE;
	virtual		void	Late_Update(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;


protected:
	void		Update_Rect(void);

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	DIRECTION	m_eDir;
	DWORD		m_dwTime;
	bool		m_bDead;
	float		m_fRadian;
	float		m_fSpeed;
	float		m_fDistance;
	int			m_iLv;
	int			m_iShieldCount;
	int			m_iItemCount;
	int			m_iHP;
	bool		m_bMagnet;
	int			m_iCheck;
	
	POINT		m_Pt;
	CObj* m_Target;
	list<CObj*>* m_pBullet;
	list<CObj*>* m_pTarget_List;
};

