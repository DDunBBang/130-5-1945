#pragma once
#include "Obj.h"
class CUdoBullet :
	public CObj
{
public:
	CUdoBullet();
	virtual ~CUdoBullet();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual	void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
private:
	float disX;
	float disY;
};

