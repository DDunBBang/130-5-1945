#include "stdafx.h"
#include "Text.h"


CText::CText()
{
}


CText::~CText()
{
}

void CText::Initialize(void)
{
}

int CText::Update(void)
{



	return OBJ_NOEVENT;
}

void CText::Late_Update(void)
{
}

void CText::Render(HDC hDC)
{
	TCHAR	szBuff[32] = L"";
	swprintf_s(szBuff, L"Player Count : %d", m_pObjList[OBJ_PLAYER].front()->Get_HP());
	TextOut(hDC, 50, WINCY - 50, szBuff, lstrlen(szBuff));

	TCHAR	szBuff1[32] = L"";
	swprintf_s(szBuff1, L"Bullet Count : %zd", m_pObjList[OBJ_PBULLET].size());
	TextOut(hDC, WINCX - 150, WINCY - 50, szBuff1, lstrlen(szBuff1));

	TCHAR	szBuff4[32] = L"";
	swprintf_s(szBuff4, L"SCORE : %d", *m_iScore);
	TextOut(hDC, WINCX *0.5, WINCY - 50, szBuff4, lstrlen(szBuff4));

	//if()
	TCHAR	szBuff2[32] = L"";

	int i = ((*m_dwStTime / 1000) + 20) - (GetTickCount() / 1000);
	if (m_pObjList[OBJ_PLAYER].front()->Get_HP() > 0)
	{
		if (i > 0 && i <= 20)
		{
			Rectangle(hDC, 50, WINCY - 65, 150, WINCY - 50);
			if (i <= 10)
			{
				HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 215, 0));
				HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

				Rectangle(hDC, 50, WINCY - 65, 150 - i * 5, WINCY - 50);

				SelectObject(hDC, oldBrush);
				DeleteObject(myBrush);
			}
			else if (i > 10 && i <= 20)
			{
				HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
				HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

				Rectangle(hDC, 50, WINCY - 65, 150 - i * 5, WINCY - 50);

				SelectObject(hDC, oldBrush);
				DeleteObject(myBrush);
			}
		}
		else if (i <= 0)
		{
			HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 127));
			HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

			Rectangle(hDC, 50, WINCY - 65, 150, WINCY - 50);

			SelectObject(hDC, oldBrush);
			DeleteObject(myBrush);

			swprintf_s(szBuff2, L"필살기 사용 : R");
			TextOut(hDC, 50, WINCY - 90, szBuff2, lstrlen(szBuff2));
			if (GetAsyncKeyState('R'))
			{
				*m_dwStTime = GetTickCount();
				dynamic_cast<CPlayer*>(m_pObjList[OBJ_PLAYER].front())->Set_Time(*m_dwStTime);
			}
		}
	}
	else if (m_pObjList[OBJ_PLAYER].front()->Get_HP() <= 0)
	{

		TCHAR	szBuff3[32] = L"";
		swprintf_s(szBuff3, L"GAME OVER!!!");
		TextOut(hDC, (int)WINCX *0.5 - 50, (int)WINCY *0.5, szBuff3, (int)lstrlen(szBuff3));
		*m_bGame = false;

	}
	if (m_pObjList[OBJ_PLAYER].front()->Get_Shield_Count() >= 0)
	{
		Rectangle(hDC, WINCX - 30, WINCY - 150, WINCX - 10, WINCY - 50);
		if (m_pObjList[OBJ_PLAYER].front()->Get_Shield_Count() == 1)
		{
			HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(240, 230, 140));
			HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

			Rectangle(hDC, WINCX - 30, WINCY - 75, WINCX - 10, WINCY - 50);

			SelectObject(hDC, oldBrush);
			DeleteObject(myBrush);
		}
		else if (m_pObjList[OBJ_PLAYER].front()->Get_Shield_Count() == 2)
		{
			HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(240, 230, 140));
			HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

			Rectangle(hDC, WINCX - 30, WINCY - 100, WINCX - 10, WINCY - 50);

			SelectObject(hDC, oldBrush);
			DeleteObject(myBrush);
		}
		else if (m_pObjList[OBJ_PLAYER].front()->Get_Shield_Count() == 3)
		{
			HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(240, 230, 140));
			HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

			Rectangle(hDC, WINCX - 30, WINCY - 125, WINCX - 10, WINCY - 50);

			SelectObject(hDC, oldBrush);
			DeleteObject(myBrush);
		}
		else if (m_pObjList[OBJ_PLAYER].front()->Get_Shield_Count() == 4)
		{
			HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(240, 230, 140));
			HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

			Rectangle(hDC, WINCX - 30, WINCY - 150, WINCX - 10, WINCY - 50);

			SelectObject(hDC, oldBrush);
			DeleteObject(myBrush);
		}
	}
	if (*m_bClear)
	{
		TCHAR	szBuff3[32] = L"";
		swprintf_s(szBuff3, L"GAME CLEAR!!!");
		TextOut(hDC, (int)WINCX *0.5 - 50, (int)WINCY *0.5, szBuff3, (int)lstrlen(szBuff3));
	}
}

void CText::Release(void)
{
}
