#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"

CMainGame::CMainGame()
	: m_dwTime(GetTickCount()), m_bUnique{ false }, m_bCheck(false), m_bCheck2(false), m_dwMTime(GetTickCount()), m_iScore(0), m_bBoss(false), m_bClear(false)
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
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet(&m_ObjList[OBJ_PBULLET]);
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Monster(&m_ObjList[OBJ_MONSTER]);
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Pet(&m_ObjList[OBJ_PET]);
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Shield(&m_ObjList[OBJ_SHIELD]);
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Time(m_dwStTime);
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Mouse(&m_ObjList[OBJ_MOUSE]);
}

void CMainGame::Update(void)
{

	if (10 == m_iScore && !m_bBoss)
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

	m_bCheck = CCollisionMgr::Collision_Item(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_ITEM]);

	if (m_bCheck)
	{
		m_bCheck2 = true;
		m_bCheck = false;
	}
	if (m_bCheck2)
	{
		for (auto& iter : m_ObjList[OBJ_ITEM])
		{
			iter->Set_Magnet_true();
			iter->Set_Target(m_ObjList[OBJ_PLAYER].front());
		}
	}
	if (m_bCheck2 && m_dwMTime + 4000 < GetTickCount())
	{
		m_bCheck2 = false;
		for (auto& iter : m_ObjList[OBJ_ITEM])
		{
			iter->Set_Magnet_false();
		}
		m_dwMTime = GetTickCount();
	}

	for (auto& iter : m_ObjList[OBJ_PBULLET])
	{
		if (iter->Get_Dir() == DIR_UT|| iter->Get_Dir() == DIR_RC)
			CCollisionMgr::Collision_Oneside(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_PBULLET]);
		else
			CCollisionMgr::Collision_Rect(m_ObjList[OBJ_PBULLET], m_ObjList[OBJ_MONSTER]);
	}

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

	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_SHIELD], m_ObjList[OBJ_MONSTER]);
}

void CMainGame::Render(void)
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	if (m_iScore < 6 && m_iHp>0)
	{
		for (size_t i = 0; i < OBJ_END; ++i)
		{
			for (auto& iter : m_ObjList[i])
				iter->Render(m_hDC);
		}
	}
	
	TCHAR	szBuff[32] = L"";
	swprintf_s(szBuff, L"Player Count : %d", m_ObjList[OBJ_PLAYER].front()->Get_HP());
	TextOut(m_hDC, 50, WINCY - 50, szBuff, lstrlen(szBuff));

	TCHAR	szBuff1[32] = L"";
	swprintf_s(szBuff1, L"Bullet Count : %zd", m_ObjList[OBJ_PBULLET].size());
	TextOut(m_hDC, WINCX-150, WINCY - 50, szBuff1, lstrlen(szBuff1));

	TCHAR	szBuff4[32] = L"";
	swprintf_s(szBuff4, L"SCORE : %d", m_iScore);
	TextOut(m_hDC, WINCX *0.5, WINCY - 50, szBuff4, lstrlen(szBuff4));
	
	//if()
	TCHAR	szBuff2[32] = L"";

	int i = ((m_dwStTime / 1000) + 20) - (GetTickCount() / 1000);
	if (m_ObjList[OBJ_PLAYER].front()->Get_HP() > 0)
	{
		if (i > 0 && i <= 20)
		{
			Rectangle(m_hDC, 50, WINCY - 65, 150, WINCY - 50);
			if (i <= 10)
			{
				HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 215, 0));
				HBRUSH oldBrush = (HBRUSH)SelectObject(m_hDC, myBrush);

				Rectangle(m_hDC, 50, WINCY - 65, 150 - i * 5, WINCY - 50);

				SelectObject(m_hDC, oldBrush);
				DeleteObject(myBrush);				
			}
			else if (i>10&&i <= 20)
			{
				HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
				HBRUSH oldBrush = (HBRUSH)SelectObject(m_hDC, myBrush);

				Rectangle(m_hDC, 50, WINCY - 65, 150 - i * 5, WINCY - 50);

				SelectObject(m_hDC, oldBrush);
				DeleteObject(myBrush);
			}
		}
		else if (i <= 0)
		{
			HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 127));
			HBRUSH oldBrush = (HBRUSH)SelectObject(m_hDC, myBrush);

			Rectangle(m_hDC, 50, WINCY - 65, 150, WINCY - 50);

			SelectObject(m_hDC, oldBrush);
			DeleteObject(myBrush);

			swprintf_s(szBuff2, L"필살기 사용 : R");
			TextOut(m_hDC, 50, WINCY - 90, szBuff2, lstrlen(szBuff2));
			if (GetAsyncKeyState('R'))
			{
				m_dwStTime = GetTickCount();
				dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Time(GetTickCount());
			}
		}
	}
	else if (m_ObjList[OBJ_PLAYER].front()->Get_HP() <= 0)
	{
		if (m_dwStTime + 2000 < GetTickCount())
		{
			if ((m_dwStTime + 4000) < GetTickCount())
			{
				m_dwStTime = GetTickCount();
			}
			else
			{
				TCHAR	szBuff3[32] = L"";
				swprintf_s(szBuff3, L"GAME OVER!!!");
				TextOut(m_hDC, (int)WINCX *0.5 - 50, (int)WINCY *0.5, szBuff3, (int)lstrlen(szBuff3));
			}
		}
	}
	if (m_bClear)
	{
		TCHAR	szBuff3[32] = L"";
		swprintf_s(szBuff3, L"GAME CLEAR!!!");
		TextOut(m_hDC, (int)WINCX *0.5 - 50, (int)WINCY *0.5, szBuff3, (int)lstrlen(szBuff3));
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
