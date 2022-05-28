#pragma once

#include "Define.h"
#include "Player.h"
#include "Bullet.h"
#include "Monster.h"
#include "Mouse.h"
class CMainGame
{
public:					// 생성자, 소멸자
	CMainGame();
	~CMainGame();

// public, protected, private 함수
 public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(void);
	void		Release(void);

// public, protected, private 변수
private:
	HDC			m_hDC;
	list<CObj*> m_ObjList[OBJ_END];
	DWORD		m_dwStTime;
	/*DWORD		m_dwEdTime;
	DWORD		m_dwDfTime;*/
	int			m_iHp;

	DWORD		m_dwTime;
	DWORD		m_dwHitTime;

	bool		m_bUnique[2];
};