#pragma once
#include "Obj.h"

class CItem :
	public CObj
{
public:
	CItem();
	virtual ~CItem();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual	void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	void Create_Speed(void);
private:
	float	m_fXSpeed;
	bool	m_bFirst;
	float	m_fX;
	float	m_fY;
	int		m_iTime;
};
