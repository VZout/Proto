#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Utility)

class NoParametersList
{
};

template<typename TYPE0>
class OneParameterList
{
	OneParameterList(TYPE0 a_Parameter0)
	: m_Parameter0(a_Parameter0)
	{
	}

	TYPE0 m_Parameter0;
};

template<typename TYPE0, typename TYPE1>
class TwoParameterList
{
	TwoParameterList(TYPE0 a_Parameter0, TYPE1 a_Parameter1)
	: m_Parameter0(a_Parameter0)
	, m_Parameter1(a_Parameter1)
	{
	}

	TYPE0 m_Parameter0;
	TYPE1 m_Parameter1;
};

template<typename TYPE0, typename TYPE1, typename TYPE2>
class ThreeParameterList
{
	ThreeParameterList(TYPE0 a_Parameter0, TYPE1 a_Parameter1, TYPE2 a_Parameter2)
		: m_Parameter0(a_Parameter0)
		, m_Parameter1(a_Parameter1)
		, m_Parameter2(a_Parameter2)
	{
	}

	TYPE0 m_Parameter0;
	TYPE1 m_Parameter1;
	TYPE2 m_Parameter2;
};

template<typename TYPE0, typename TYPE1, typename TYPE2, typename TYPE3>
class FourParameterList
{
	FourParameterList(TYPE0 a_Parameter0, TYPE1 a_Parameter1, TYPE2 a_Parameter2, TYPE3 a_Parameter3)
		: m_Parameter0(a_Parameter0)
		, m_Parameter1(a_Parameter1)
		, m_Parameter2(a_Parameter2)
		, m_Parameter3(a_Parameter3)
	{
	}

	TYPE0 m_Parameter0;
	TYPE1 m_Parameter1;
	TYPE2 m_Parameter2;
	TYPE3 m_Parameter3;
};

template<typename TYPE0, typename TYPE1, typename TYPE2, typename TYPE3, typename TYPE4>
class FiveParameterList
{
	FiveParameterList(TYPE0 a_Parameter0, TYPE1 a_Parameter1, TYPE2 a_Parameter2, TYPE3 a_Parameter3, TYPE4 a_Parameter4)
		: m_Parameter0(a_Parameter0)
		, m_Parameter1(a_Parameter1)
		, m_Parameter2(a_Parameter2)
		, m_Parameter3(a_Parameter3)
		, m_Parameter4(a_Parameter4)
	{
	}

	TYPE0 m_Parameter0;
	TYPE1 m_Parameter1;
	TYPE2 m_Parameter2;
	TYPE3 m_Parameter3;
	TYPE4 m_Parameter4;
};

END_NAMESPACE(Utility)
