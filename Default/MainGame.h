#pragma once

#include "Define.h"
#include "Player.h"
#include "Bullet.h"
#include "Monster.h"
#include "Mouse.h"
#include "Item.h"
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

public:
	bool		Get_Game() { return m_bGame; }
	// public, protected, private 변수
private:
	HDC			m_hDC;
	list<CObj*> m_ObjList[OBJ_END];
	DWORD		m_dwStTime;
	DWORD		m_dwTime;
	DWORD		m_dwHitTime;
	DWORD		m_dwMTime;
	DWORD		m_dwGetItemTime;

	int			m_iHp;
	int			m_iScore;
	bool		m_bUnique[2];
	bool		m_bCheck;
	bool		m_bCheck2;
	bool		m_bBoss;
	bool		m_bClear;
	bool		m_bGame;
};