#pragma once
#include "Obj.h"
#include "Bullet.h"
class CPet :
	public CObj
{
public:
	CPet();
	virtual ~CPet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual	void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void Shot();
	void Move();
private:

};

