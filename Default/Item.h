#pragma once
#include "Obj.h"
class CItem : public CObj
{
public:
	CItem();
	~CItem();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
private:
	void Create_Speed(void);
private:
	float	m_ffXSpeed;
	float m_fX;
	float m_fY;
	int m_iFirst;

};

