#pragma once

#include "Obj.h"

template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory()	{}
	~CAbstractFactory() {}

	static CObj* Create()
	{
		CObj* pInstance = new T;
		pInstance->Initialize();

		return pInstance;
	}
	static CObj* Create(float _fX, float _fY, DIRECTION _eDir=DIR_END)
	{
		CObj* pInstace = new T;
		if(_eDir!=DIR_END)
			pInstace->Set_Dir(_eDir);
		pInstace->Initialize();
		pInstace->Set_Pos(_fX,_fY);

		return pInstace;
	}
	static CObj* Create(float _fX, float _fY, DIRECTION _eDir,float fRadian)
	{
		CObj* pInstace = new T;
		pInstace->Initialize();
		pInstace->Set_Pos(_fX, _fY);
		pInstace->Set_Dir(_eDir);
		pInstace->Set_Radian(fRadian);
		return pInstace;
	}


};

