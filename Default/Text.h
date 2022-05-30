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
private:
	list<CObj*>* m_pObjList;
	int* m_iScore;
	DWORD* m_dwStTime;
	bool* m_bGame;
	bool* m_bClear;
};

