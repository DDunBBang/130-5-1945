#pragma once
#include "Obj.h"
#include "Player.h"
class CText :
	public CObj
{
public:
	CText();
	virtual ~CText();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual	void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
	
	void Set_Obj(list<CObj*>* _pObjList) { m_pObjList = _pObjList; }
	void Set_Score(int* is) { m_iScore = is; }
	void Set_dwStt(DWORD* st) { m_dwStTime = st; }
	void Set_bGame(bool* bG) { m_bGame = bG; }
	void Set_bClear(bool* bC) { m_bClear = bC; }
	void Set_iCheck(int* bC) { m_iCheck = bC; }
private:
	list<CObj*>* m_pObjList;
	int* m_iScore;
	DWORD* m_dwStTime;
	DWORD  m_dwGTime;
	bool* m_bGame;
	bool* m_bClear;
	int* m_iCheck;
	int m_iCH;
};

