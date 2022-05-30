#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"

CMainGame::CMainGame()
	: m_dwTime(GetTickCount()), m_bUnique{ false }, m_iCheck(0), m_bCheck2(false), m_dwMTime(GetTickCount()), m_iScore(0), m_bBoss(false), m_bGame(true), m_bClear(false)
{
	m_iHp = 3;

}

CMainGame::~CMainGame()
{
	Release();

}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);
	m_dwStTime = GetTickCount();
	m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	m_ObjList[OBJ_MOUSE].push_back(CAbstractFactory<CMouse>::Create());
	m_ObjList[OBJ_TEXT].push_back(CAbstractFactory<CText>::Create());

	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet(&m_ObjList[OBJ_PBULLET]);
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Monster(&m_ObjList[OBJ_MONSTER]);
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Pet(&m_ObjList[OBJ_PET]);
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Shield(&m_ObjList[OBJ_SHIELD]);
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Time(m_dwStTime);
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Mouse(&m_ObjList[OBJ_MOUSE]);
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Item(&m_ObjList[OBJ_ITEM]);
	dynamic_cast<CText*>(m_ObjList[OBJ_TEXT].front())->Set_Obj(m_ObjList);
}

void CMainGame::Update(void)
{
	if (20 <= m_iScore && !m_bBoss)
	{
		for (auto& iter : m_ObjList[OBJ_MONSTER])
		{
			Safe_Delete<CObj*>(iter);
		}
		m_ObjList[OBJ_MONSTER].clear();
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(101));
		m_ObjList[OBJ_MONSTER].back()->Set_Target(m_ObjList[OBJ_PLAYER].front());
		dynamic_cast<CMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_Bullet(&m_ObjList[OBJ_MBULLET]);
		m_bBoss = true;
	}
	else if (!m_bBoss)
	{
		if (m_dwTime + 1500 < GetTickCount())
		{
			int iLv = rand() % 100 + 1;
			if (20 >= iLv && 10 < iLv)
			{
				if (!m_bUnique[0])
				{
					m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(iLv));
					m_ObjList[OBJ_MONSTER].back()->Set_Target(m_ObjList[OBJ_PLAYER].front());
					dynamic_cast<CMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_Bullet(&m_ObjList[OBJ_MBULLET]);
					dynamic_cast<CMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_Unique(&m_bUnique[0]);
					m_bUnique[0] = true;
				}
			}
			else if (10 >= iLv)
			{
				if (!m_bUnique[1])
				{
					m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(iLv));
					m_ObjList[OBJ_MONSTER].back()->Set_Target(m_ObjList[OBJ_PLAYER].front());
					dynamic_cast<CMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_Bullet(&m_ObjList[OBJ_MBULLET]);
					dynamic_cast<CMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_Unique(&m_bUnique[1]);
					m_bUnique[1] = true;
				}
			}
			else
			{
				m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(iLv));
				m_ObjList[OBJ_MONSTER].back()->Set_Target(m_ObjList[OBJ_PLAYER].front());
				dynamic_cast<CMonster*>(m_ObjList[OBJ_MONSTER].back())->Set_Bullet(&m_ObjList[OBJ_MBULLET]);
			}
			m_dwTime = GetTickCount();
		}
	}

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end();)
		{
			int iEvent = (*iter)->Update();
			if (OBJ_DEAD == iEvent)
			{
				if (OBJ_MONSTER == i&&dynamic_cast<CMonster*>(*iter)->Get_Drop())
				{
					if (dynamic_cast<CMonster*>(*iter)->Get_LV() == 101)
					{
						m_bBoss = false;
						m_bClear = true;
					}
					++m_iScore;
				}
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
	for (auto& iter : m_ObjList[OBJ_MONSTER])
	{
		dynamic_cast<CMonster*>(iter)->Set_Item(&m_ObjList[OBJ_ITEM]);
	}
	
}

void CMainGame::Late_Update(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}

	m_iCheck = CCollisionMgr::Collision_Item(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_ITEM]);
	if (m_iCheck==3)
	{
		m_bCheck2 = true;
		m_dwMTime = GetTickCount();
	}
	if (m_bCheck2)
	{
		for (auto& iter : m_ObjList[OBJ_ITEM])
		{
			iter->Set_Target(m_ObjList[OBJ_PLAYER].front());
			iter->Set_Magnet_true();
		}

		if (m_dwMTime + 4000 < GetTickCount())
		{
			m_bCheck2 = false;
			for (auto& iter : m_ObjList[OBJ_ITEM])
			{
				iter->Set_Magnet_false();
			}

			m_dwMTime = GetTickCount();
		}

	}

	for (auto& iter : m_ObjList[OBJ_PBULLET])
	{
		CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PBULLET], m_ObjList[OBJ_MONSTER]);
	}

	if (!dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].back())->Get_Imu())
	{
		if (!dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].back())->Get_HitCheck())
		{
			if (CCollisionMgr::Collision_Player(m_ObjList[OBJ_MBULLET], m_ObjList[OBJ_PLAYER]) ||
				CCollisionMgr::Collision_Player(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_PLAYER]))
			{
				dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].back())->Set_HitCheck(true);
				m_dwHitTime = GetTickCount();
			}
		}
		else
		{
			if (m_dwHitTime + 3000 < GetTickCount())
				dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].back())->Set_HitCheck(false);
		}
	}

	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_SHIELD], m_ObjList[OBJ_MBULLET]);
	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_MBULLET], m_ObjList[OBJ_SHIELD]);
	dynamic_cast<CText*>(m_ObjList[OBJ_TEXT].front())->Set_Score(&m_iScore);
	dynamic_cast<CText*>(m_ObjList[OBJ_TEXT].front())->Set_dwStt(&m_dwStTime);
	dynamic_cast<CText*>(m_ObjList[OBJ_TEXT].front())->Set_bGame(&m_bGame);
	dynamic_cast<CText*>(m_ObjList[OBJ_TEXT].front())->Set_bClear(&m_bClear);
	dynamic_cast<CText*>(m_ObjList[OBJ_TEXT].front())->Set_iCheck(&m_iCheck);
}

void CMainGame::Render(void)
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(m_hDC);
	}
}

void CMainGame::Release(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			Safe_Delete<CObj*>(iter);
		}
		m_ObjList[i].clear();
	}
	ReleaseDC(g_hWnd, m_hDC);
}
