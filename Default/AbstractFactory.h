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
	static CObj* Create(float _fX, float _fY, DIRECTION _eDir)
	{
		CObj* pInstace = new T;
		pInstace->Initialize();
		pInstace->Set_Pos();
		pInstace->Set_Dir();

		return pInstace;
	}

};

