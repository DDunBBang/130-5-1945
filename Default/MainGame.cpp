#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"

CMainGame::CMainGame():m_dwStTime(GetTickCount())//,m_dwEdTime(m_dwStTime+1000)
{
	m_iHp = 1;
	//m_dwDfTime = (m_dwEdTime - m_dwStTime) / 1000;
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);
	m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	for(int i=0;i<10;++i)
		m_ObjList[OBJ_MONSTER].push_back(CAbstractFactory<CMonster>::Create(250,150,DIR_LEFT));
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Bullet(&m_ObjList[OBJ_PBULLET]);
	dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].front())->Set_Monster(&m_ObjList[OBJ_MONSTER]);
	
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
			dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].back())->Set_Bullet(&m_ObjList[OBJ_PBULLET]);//테스트용
			dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].back())->Set_Monster(&m_ObjList[OBJ_MONSTER]);
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

	for (auto& iter : m_ObjList[OBJ_PBULLET])
	{
		if(iter->Get_Dir()==DIR_UT)
			CCollisionMgr::Collision_Monster(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_PBULLET]);
		else
			CCollisionMgr::Collision_Rect(m_ObjList[OBJ_MONSTER], m_ObjList[OBJ_PBULLET]);
	}
	

	if(CCollisionMgr::Collision_Monster(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MBULLET]))
	{
		--m_iHp;
		if (m_iHp!=0)
		{
			m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
			dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].back())->Set_Bullet(&m_ObjList[OBJ_PBULLET]);
			dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].back())->Set_Monster(&m_ObjList[OBJ_MONSTER]);
			m_dwStTime = GetTickCount();
		}
	}

	if (CCollisionMgr::Collision_Monster(m_ObjList[OBJ_PLAYER], m_ObjList[OBJ_MONSTER]))
	{
		--m_iHp;
		if (m_iHp != 0)
		{
			m_ObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
			dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].back())->Set_Bullet(&m_ObjList[OBJ_PBULLET]);
			dynamic_cast<CPlayer*>(m_ObjList[OBJ_PLAYER].back())->Set_Monster(&m_ObjList[OBJ_MONSTER]);
			m_dwStTime = GetTickCount();
		}
	} //체크 완료

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

	TCHAR	szBuff1[32] = L"";
	swprintf_s(szBuff1, L"Bullet Count : %d", m_ObjList[OBJ_PBULLET].size());
	TextOut(m_hDC, WINCX-150, WINCY - 50, szBuff1, lstrlen(szBuff1));
	
	//if()
	TCHAR	szBuff2[32] = L"";
	int i = m_dwStTime / 1000 + 10 - GetTickCount() / 1000;
	if (m_iHp > 0)
	{
		if (i > 0 && i <= 10)
		{
			swprintf_s(szBuff2, L"필살기 남은 시간 : %d", ((i)));
			TextOut(m_hDC, 250, 50, szBuff2, lstrlen(szBuff2));
		}
		else if (i <= 0)
		{
			swprintf_s(szBuff2, L"필살기 준비 완료 사용 : C");
			TextOut(m_hDC, 250, 50, szBuff2, lstrlen(szBuff2));
			if (GetAsyncKeyState('C'))
				m_dwStTime = GetTickCount();
		}
	}
	else if (m_iHp <= 0)
	{
		TCHAR	szBuff3[32] = L"";
		swprintf_s(szBuff3, L"GAME OVER!!!");
		TextOut(m_hDC, WINCX *0.5-50, WINCY *0.5, szBuff3, lstrlen(szBuff3));
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
