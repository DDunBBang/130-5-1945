#pragma once

#include "Define.h"
#include "Player.h"
#include "Bullet.h"
#include "Monster.h"
#include "Mouse.h"
#include "Item.h"
#include "Text.h"
class CMainGame
{
public:					// ������, �Ҹ���
	CMainGame();
	~CMainGame();

	// public, protected, private �Լ�
public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(void);
	void		Release(void);

public:
	bool		Get_Game() { return m_bGame; }
	bool		Get_Clear() { return m_bClear; }
	// public, protected, private ����
private:
	HDC			m_hDC;
	list<CObj*> m_ObjList[OBJ_END];
	DWORD		m_dwStTime;
	DWORD		m_dwTime;
	DWORD		m_dwHitTime;
	DWORD		m_dwMTime;

	int			m_iHp;
	int			m_iScore;
	bool		m_bUnique[2];
	int		m_iCheck;
	bool		m_bCheck2;
	bool		m_bBoss;
	bool		m_bClear;
	bool		m_bGame;
};