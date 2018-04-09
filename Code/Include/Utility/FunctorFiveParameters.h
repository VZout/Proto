#pragma once

#include "Proto.h"

#include "ENoInit.h"
#include "FunctorStore.h"
#include "ParameterList.h"

BEGIN_NAMESPACE(Utility)

template<typename RETURN_TYPE, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1, typename PARAMETER_TYPE_2, typename PARAMETER_TYPE_3, typename PARAMETER_TYPE_4>
class Functor<RETURN_TYPE(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)> : public FunctorStore
{
public:
	typedef RETURN_TYPE Return;
	typedef FiveParameterList<PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4> ParameterList;

public:
	Functor();

	Return operator()(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4) const;
	Return operator()(const ParameterList& a_ParameterList) const;

	template<Return(*FUNCTION)(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)>
	static Functor<Return(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)> Create();

	template<typename CLASS_TYPE>
	static Functor<Return(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)> Create(CLASS_TYPE& a_Object);

	template<typename CLASS_TYPE, Return(CLASS_TYPE::*FUNCTION)(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)>
	static Functor<Return(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)> Create(CLASS_TYPE& a_Object);

	// 	template<typename CLASS_TYPE, Return (CLASS_TYPE::*FUNCTION)(PARAMETER_TYPE) const>
	// 	static Functor<Return (PARAMETER_TYPE)> CreateConst(CLASS_TYPE& a_Object);

	template<Return(*FUNCTION)(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)>
	void Bind();

	template<typename CLASS>
	void Bind(CLASS& a_Object);

	template<typename CLASS, Return(CLASS::*FUNCTION)(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)>
	void Bind(CLASS& a_Object);

	template<typename CLASS, Return(CLASS::*FUNCTION)(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4) const>
	void BindConst(CLASS& a_Object);

protected:
	Functor(ENoInit);
};

template<typename RETURN_TYPE, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1, typename PARAMETER_TYPE_2, typename PARAMETER_TYPE_3, typename PARAMETER_TYPE_4>
Functor<RETURN_TYPE(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)>::Functor()
: FunctorStore()
{
}

template<typename RETURN_TYPE, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1, typename PARAMETER_TYPE_2, typename PARAMETER_TYPE_3, typename PARAMETER_TYPE_4>
inline RETURN_TYPE Functor<RETURN_TYPE(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)>::operator()(PARAMETER_TYPE_0 a_Parameter_0, PARAMETER_TYPE_1 a_Parameter_1, PARAMETER_TYPE_2 a_Parameter_2, PARAMETER_TYPE_3 a_Parameter_3, PARAMETER_TYPE_4 a_Parameter_4) const
{
	return reinterpret_cast<RETURN_TYPE(*)(void*, PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)>(m_Function)(m_Object, a_Parameter_0, a_Parameter_1, a_Parameter_2, a_Parameter_3, a_Parameter_4);
}

template<typename RETURN_TYPE, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1, typename PARAMETER_TYPE_2, typename PARAMETER_TYPE_3, typename PARAMETER_TYPE_4>
RETURN_TYPE Functor<RETURN_TYPE(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)>::operator()(const ParameterList &a_ParameterList) const
{
	return operator()(a_ParameterList.m_Parameter0, a_ParameterList.m_Parameter1);
}

template<typename RETURN_TYPE, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1, typename PARAMETER_TYPE_2, typename PARAMETER_TYPE_3, typename PARAMETER_TYPE_4>
template<RETURN_TYPE(*FUNCTION)(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)>
Functor<RETURN_TYPE(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)>
Functor<RETURN_TYPE(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)>::Create()
{
	Functor functor(NoInit);
	functor.Bind<FUNCTION>();
	return functor;
}

// template<typename RETURN_TYPE>
// template<typename CLASS_TYPE>
// inline Functor<RETURN_TYPE ()> 
// 	Functor<RETURN_TYPE ()>::Create(CLASS_TYPE& a_Object)
// {
// 	return Create<CLASS_TYPE, &CLASS_TYPE::operator()>(a_Object);
// }

template<typename RETURN_TYPE, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1, typename PARAMETER_TYPE_2, typename PARAMETER_TYPE_3, typename PARAMETER_TYPE_4>
template<typename CLASS_TYPE, RETURN_TYPE(CLASS_TYPE::*FUNCTION)(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)>
inline Functor<RETURN_TYPE(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)>
Functor<RETURN_TYPE(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)>::Create(CLASS_TYPE& a_Object)
{
	Functor<RETURN_TYPE(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)> functor(NoInit);
	functor.Bind<CLASS_TYPE, FUNCTION>(a_Object);
	return functor;
}

// template<typename RETURN_TYPE>
// template<typename CLASS_TYPE, RETURN_TYPE (CLASS_TYPE::*FUNCTION)() const>
// inline Functor<RETURN_TYPE ()> 
// 	Functor<RETURN_TYPE ()>::CreateConst(CLASS_TYPE& a_Object)
// {
// 	Functor<RETURN_TYPE ()> functor(NoInit);
// 	functor.BindConst<CLASS_TYPE, FUNCTION>(a_Object);
// 	return functor;
// }

template<typename RETURN_TYPE, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1, typename PARAMETER_TYPE_2, typename PARAMETER_TYPE_3, typename PARAMETER_TYPE_4>
template<RETURN_TYPE(*FUNCTION)(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)>
void Functor<RETURN_TYPE(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)>::Bind()
{
	struct Wrapper
	{
		static RETURN_TYPE Invoke(void*, PARAMETER_TYPE_0 a_Parameter_0, PARAMETER_TYPE_1 a_Parameter_1, PARAMETER_TYPE_2 a_Parameter_2, PARAMETER_TYPE_3 a_Parameter_3, PARAMETER_TYPE_4 a_Parameter_4)
		{
			return (*FUNCTION)(a_Parameter_0, a_Parameter_1, a_Parameter_2, a_Parameter_3, a_Parameter_4);
		}
	};

	m_Function = reinterpret_cast<Function>(&Wrapper::Invoke);
}

// template<typename RETURN_TYPE>
// template<typename CLASS_TYPE>
// inline void Functor<RETURN_TYPE ()>::Bind(CLASS_TYPE& a_Object)
// {
// 	Bind<CLASS_TYPE, &CLASS_TYPE::operator()>(a_Object);
// }
// 
template<typename RETURN_TYPE, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1, typename PARAMETER_TYPE_2, typename PARAMETER_TYPE_3, typename PARAMETER_TYPE_4>
template<typename CLASS_TYPE, RETURN_TYPE(CLASS_TYPE::*FUNCTION)(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)>
inline void Functor<RETURN_TYPE(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)>::Bind(CLASS_TYPE& a_Object)
{
	struct Wrapper
	{
		static RETURN_TYPE Invoke(void* a_Object, PARAMETER_TYPE_0 a_Parameter_0, PARAMETER_TYPE_1 a_Parameter_1, PARAMETER_TYPE_2 a_Parameter_2, PARAMETER_TYPE_3 a_Parameter_3, PARAMETER_TYPE_4 a_Parameter_4)
		{
			CLASS_TYPE* object = static_cast<CLASS_TYPE*>(a_Object);
			return (object->*FUNCTION)(a_Parameter_0, a_Parameter_1, a_Parameter_2, a_Parameter_3, a_Parameter_4);
		}
	};

	m_Function = reinterpret_cast<Function>(&Wrapper::Invoke);
	m_Object = const_cast<void*>(static_cast<const void*>(&a_Object));
}
// 
// 
// template<typename RETURN_TYPE>
// template<typename CLASS_TYPE, RETURN_TYPE (CLASS_TYPE::*FUNCTION)() const>
// inline void Functor<RETURN_TYPE ()>::BindConst(CLASS_TYPE& a_Object)
// {
// 	struct Wrapper
// 	{
// 		static RETURN_TYPE Invoke(void* a_Object)
// 		{
// 			CLASS_TYPE* object = static_cast<CLASS_TYPE*>(a_Object);
// 			return (object->*FUNCTION)();
// 		}
// 	};
// 
// 	m_Function = reinterpret_cast<Function>(&Wrapper::Invoke);
// 	m_Object = const_cast<void*>(static_cast<const void*>(&a_Object));
// }

template<typename RETURN_TYPE, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1, typename PARAMETER_TYPE_2, typename PARAMETER_TYPE_3, typename PARAMETER_TYPE_4>
Functor<RETURN_TYPE(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)>::Functor(ENoInit)
: FunctorStore(NoInit)
{
}

END_NAMESPACE(Utility)
