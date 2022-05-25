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
	void		Set_Dir(float _fX, float _fY, DIRECTION _eDir) { m_eDir = _eDir; }
	void		Set_Dead() { m_bDead = true; }
	RECT& const Get_Rect() { return m_tRect; }
	INFO& const Get_Info() { return m_tInfo; }

public:
	virtual		void	Initialize(void)	PURE;
	virtual		int	Update(void)		PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;

protected:
	void		Update_Rect(void);

protected:
	INFO		m_tInfo;
	RECT		m_tRect;
	DIRECTION	m_eDir;
	bool		m_bDead;
	float		m_fSpeed;
};

