#pragma once

#include "Proto.h"

#include "ENoInit.h"
#include "FunctorStore.h"
#include "ParameterList.h"

BEGIN_NAMESPACE(Utility)

template<typename RETURN_TYPE>
class Functor<RETURN_TYPE ()> : public FunctorStore
{
public:
	typedef RETURN_TYPE Return;
	typedef NoParametersList ParameterList;

public:
	Functor();

	Return operator()() const;
	Return operator()(const ParameterList& a_ParameterList) const;

	template<Return (*FUNCTION)()>
	static Functor<Return ()> Create();

	template<typename CLASS_TYPE>
	static Functor<Return ()> Create(CLASS_TYPE& a_Object);

	template<typename CLASS_TYPE, Return (CLASS_TYPE::*FUNCTION)()>
	static Functor<Return ()> Create(CLASS_TYPE& a_Object);

	template<typename CLASS_TYPE, Return (CLASS_TYPE::*FUNCTION)() const>
	static Functor<Return ()> CreateConst(CLASS_TYPE& a_Object);

	template<Return (*FUNCTION)()>
	void Bind();

	template<typename CLASS>
	void Bind(CLASS& a_Object);

	template<typename CLASS, Return (CLASS::*FUNCTION)()>
	void Bind(CLASS& a_Object);

	template<typename CLASS, Return (CLASS::*FUNCTION)() const>
	void BindConst(CLASS& a_Object);

protected:
	Functor(ENoInit);
};

template<typename RETURN_TYPE>
Functor<RETURN_TYPE ()>::Functor()
	: FunctorStore()
{
}

template<typename RETURN_TYPE>
RETURN_TYPE Functor<RETURN_TYPE ()>::operator()() const
{
	return reinterpret_cast<RETURN_TYPE (*)(void*)>(m_Function)(m_Object);
}

template<typename RETURN_TYPE>
RETURN_TYPE Functor<RETURN_TYPE ()>::operator()(const ParameterList&) const
{
	return operator()();
}

template<typename RETURN_TYPE>
template<RETURN_TYPE (*FUNCTION)()>
Functor<RETURN_TYPE ()> 
Functor<RETURN_TYPE ()>::Create()
{
	Functor functor(NoInit);
	functor.Bind<FUNCTION>();
	return functor;
}

template<typename RETURN_TYPE>
template<typename CLASS_TYPE>
inline Functor<RETURN_TYPE ()> 
Functor<RETURN_TYPE ()>::Create(CLASS_TYPE& a_Object)
{
	return Create<CLASS_TYPE, &CLASS_TYPE::operator()>(a_Object);
}

template<typename RETURN_TYPE>
template<typename CLASS_TYPE, RETURN_TYPE (CLASS_TYPE::*FUNCTION)()>
inline Functor<RETURN_TYPE ()> 
Functor<RETURN_TYPE ()>::Create(CLASS_TYPE& a_Object)
{
	Functor<RETURN_TYPE ()> functor(NoInit);
	functor.Bind<CLASS_TYPE, FUNCTION>(a_Object);
	return functor;
}

template<typename RETURN_TYPE>
template<typename CLASS_TYPE, RETURN_TYPE (CLASS_TYPE::*FUNCTION)() const>
inline Functor<RETURN_TYPE ()> 
Functor<RETURN_TYPE ()>::CreateConst(CLASS_TYPE& a_Object)
{
	Functor<RETURN_TYPE ()> functor(NoInit);
	functor.BindConst<CLASS_TYPE, FUNCTION>(a_Object);
	return functor;
}

template<typename RETURN_TYPE>
template<RETURN_TYPE (*FUNCTION)()>
void Functor<RETURN_TYPE ()>::Bind()
{
	struct Wrapper
	{
		static RETURN_TYPE Invoke(void*)
		{
			return (*FUNCTION)();
		}
	};

	m_Function = reinterpret_cast<Function>(&Wrapper::Invoke);
}

template<typename RETURN_TYPE>
template<typename CLASS_TYPE>
inline void Functor<RETURN_TYPE ()>::Bind(CLASS_TYPE& a_Object)
{
	Bind<CLASS_TYPE, &CLASS_TYPE::operator()>(a_Object);
}

template<typename RETURN_TYPE>
template<typename CLASS_TYPE, RETURN_TYPE (CLASS_TYPE::*FUNCTION)()>
inline void Functor<RETURN_TYPE ()>::Bind(CLASS_TYPE& a_Object)
{
	struct Wrapper
	{
		static RETURN_TYPE Invoke(void* a_Object)
		{
			CLASS_TYPE* object = static_cast<CLASS_TYPE*>(a_Object);
			return (object->*FUNCTION)();
		}
	};

	m_Function = reinterpret_cast<Function>(&Wrapper::Invoke);
	m_Object = const_cast<void*>(static_cast<const void*>(&a_Object));
}


template<typename RETURN_TYPE>
template<typename CLASS_TYPE, RETURN_TYPE (CLASS_TYPE::*FUNCTION)() const>
inline void Functor<RETURN_TYPE ()>::BindConst(CLASS_TYPE& a_Object)
{
	struct Wrapper
	{
		static RETURN_TYPE Invoke(void* a_Object)
		{
			CLASS_TYPE* object = static_cast<CLASS_TYPE*>(a_Object);
			return (object->*FUNCTION)();
		}
	};

	m_Function = reinterpret_cast<Function>(&Wrapper::Invoke);
	m_Object = const_cast<void*>(static_cast<const void*>(&a_Object));
}

template<typename RETURN_TYPE>
Functor<RETURN_TYPE ()>::Functor(ENoInit)
: FunctorStore(NoInit)
{
}

END_NAMESPACE(Utility)
