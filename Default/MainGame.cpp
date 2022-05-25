#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"

CMainGame::CMainGame()
{
	m_iHp = 100;
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);
	m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet(&m_ObjList[OBJ_PBULLET]);
}

void CMainGame::Update(void)
{

	if (GetAsyncKeyState('Y') & 0x80000)
	{
		--m_iHp;
		if (m_ObjList[OBJ_PLAYER].size())
		{
			m_ObjList[OBJ_PLAYER].front()->Set_Dead();
			m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());	
			dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].back())->Set_Bullet(&m_ObjList[OBJ_PBULLET]);//테스트용//테스트용
		}
	}
	m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(20, 20, DIR_RIGHT));

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end();)
		{
			int iEvent = (*iter)->Update();
			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}
	
}

void CMainGame::Late_Update(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Late_Update();
	}

	CCollisionMgr::Collision_Item(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_ITEM]);

	CCollisionMgr::Collision_Sphere(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MBULLET]);
	if (!m_ObjList[OBJ_PLAYER].size())
	{
		--m_iHp;
		if (m_iHp)
		{
			m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
			dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].back())->Set_Bullet(&m_ObjList[OBJ_PBULLET]);
		}
	}

	if (CCollisionMgr::Collision_Monster(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]))
	{
		--m_iHp;
		if (m_iHp)
		{
			m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
			dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].back())->Set_Bullet(&m_ObjList[OBJ_PBULLET]);
		}
	}

	


}

void CMainGame::Render(void)
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render(m_hDC);
	}

	TCHAR	szBuff[32] = L"";
	swprintf_s(szBuff, L"Player Count : %d", m_iHp);
	TextOut(m_hDC, 50, WINCY - 50, szBuff, lstrlen(szBuff));
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
