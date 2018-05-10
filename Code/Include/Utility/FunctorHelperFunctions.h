#pragma once

#include "Proto.h"

#include "FunctorNoParameters.h"
#include "FunctorTwoParameters.h"
#include "FunctorThreeParameters.h"
#include "FunctorFourParameters.h"
#include "FunctorFiveParameters.h"

BEGIN_NAMESPACE(Utility)

template<typename RETURN>
class FunctorHelperNonMemberNoParameters
{
public:
	typedef Utility::Functor<RETURN ()> Functor;

	template<RETURN (*FUNCTION)()>
	Functor Create()
	{
		return Functor::template Create<FUNCTION>();
	}
};

template<typename RETURN, typename PARAMETER_TYPE>
class FunctorHelperNonMemberOneParameter
{
public:
	typedef Utility::Functor<RETURN (PARAMETER_TYPE)> Functor;

	template<RETURN (*FUNCTION)(PARAMETER_TYPE)>
	Functor Create()
	{
		return Functor::template Create<FUNCTION>();
	}
};

template<typename RETURN, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1>
class FunctorHelperNonMemberTwoParameters
{
public:
	typedef Utility::Functor<RETURN(PARAMETER_TYPE_0, PARAMETER_TYPE_1)> Functor;

	template<RETURN(*FUNCTION)(PARAMETER_TYPE_0, PARAMETER_TYPE_1)>
	Functor Create()
	{
		return Functor::template Create<FUNCTION>();
	}
};

template<typename RETURN, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1, typename PARAMETER_TYPE_2>
class FunctorHelperNonMemberThreeParameters
{
public:
	typedef Utility::Functor<RETURN(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2)> Functor;

	template<RETURN(*FUNCTION)(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2)>
	Functor Create()
	{
		return Functor::template Create<FUNCTION>();
	}
};

template<typename RETURN, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1, typename PARAMETER_TYPE_2, typename PARAMETER_TYPE_3>
class FunctorHelperNonMemberFourParameters
{
public:
	typedef Utility::Functor<RETURN(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3)> Functor;

	template<RETURN(*FUNCTION)(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3)>
	Functor Create()
	{
		return Functor::template Create<FUNCTION>();
	}
};

template<typename RETURN, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1, typename PARAMETER_TYPE_2, typename PARAMETER_TYPE_3, typename PARAMETER_TYPE_4>
class FunctorHelperNonMemberFiveParameters
{
public:
	typedef Utility::Functor<RETURN(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)> Functor;

	template<RETURN(*FUNCTION)(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4)>
	Functor Create()
	{
		return Functor::template Create<FUNCTION>();
	}
};


template<typename CLASS, typename RETURN>
class FunctorHelperMemberNoParameters
{
public:
	typedef Utility::Functor<RETURN ()> Functor;

	template<RETURN (CLASS::*FUNCTION)()>
	Functor Create(CLASS& a_Object)
	{
		return Utility::Functor<RETURN ()>::template Create<CLASS, FUNCTION>(a_Object);
	}

	template<RETURN (CLASS::*FUNCTION)() const>
	Functor CreateConst(CLASS& a_Object)
	{
		return Utility::Functor<RETURN ()>::template CreateConst<CLASS, FUNCTION>(a_Object);
	}
};

template<typename CLASS, typename RETURN, typename PARAMETER0>
class FunctorHelperMemberOneParameter
{
public:
	typedef Utility::Functor<RETURN (PARAMETER0)> Functor;

	template<RETURN (CLASS::*FUNCTION)(PARAMETER0)>
	Functor Create(CLASS& a_Object)
	{
		return Functor::template Create<CLASS, FUNCTION>(a_Object);
	}

	template<RETURN (CLASS::*FUNCTION)(PARAMETER0) const>
	Functor CreateConst(CLASS& a_Object)
	{
		return Functor::template CreateConst<CLASS, FUNCTION>(a_Object);
	}
};

template<typename CLASS, typename RETURN, typename PARAMETER0, typename PARAMETER1>
class FunctorHelperMemberTwoParameters
{
public:
	typedef Utility::Functor<RETURN (PARAMETER0, PARAMETER1)> Functor;

	template<RETURN (CLASS::*FUNCTION)(PARAMETER0, PARAMETER1)>
	Functor Create(CLASS& a_Object)
	{
		return Functor::template Create<CLASS, FUNCTION>(a_Object);
	}

	template<RETURN (CLASS::*FUNCTION)(PARAMETER0, PARAMETER1) const>
	Functor CreateConst(CLASS& a_Object)
	{
		return Functor::template CreateConst<CLASS, FUNCTION>(a_Object);
	}
};

template<typename CLASS, typename RETURN, typename PARAMETER0, typename PARAMETER1, typename PARAMETER2>
class FunctorHelperMemberThreeParameters
{
public:
	typedef Utility::Functor<RETURN(PARAMETER0, PARAMETER1, PARAMETER2)> Functor;

	template<RETURN(CLASS::*FUNCTION)(PARAMETER0, PARAMETER1, PARAMETER2)>
	Functor Create(CLASS& a_Object)
	{
		return Functor::template Create<CLASS, FUNCTION>(a_Object);
	}

	template<RETURN(CLASS::*FUNCTION)(PARAMETER0, PARAMETER1, PARAMETER2) const>
	Functor CreateConst(CLASS& a_Object)
	{
		return Functor::template CreateConst<CLASS, FUNCTION>(a_Object);
	}
};

template<typename CLASS, typename RETURN, typename PARAMETER0, typename PARAMETER1, typename PARAMETER2, typename PARAMETER3>
class FunctorHelperMemberFourParameters
{
public:
	typedef Utility::Functor<RETURN(PARAMETER0, PARAMETER1, PARAMETER2, PARAMETER3)> Functor;

	template<RETURN(CLASS::*FUNCTION)(PARAMETER0, PARAMETER1, PARAMETER2, PARAMETER3)>
	Functor Create(CLASS& a_Object)
	{
		return Functor::template Create<CLASS, FUNCTION>(a_Object);
	}

	template<RETURN(CLASS::*FUNCTION)(PARAMETER0, PARAMETER1, PARAMETER2, PARAMETER3) const>
	Functor CreateConst(CLASS& a_Object)
	{
		return Functor::template CreateConst<CLASS, FUNCTION>(a_Object);
	}
};

template<typename CLASS, typename RETURN, typename PARAMETER0, typename PARAMETER1, typename PARAMETER2, typename PARAMETER3, typename PARAMETER4>
class FunctorHelperMemberFiveParameters
{
public:
	typedef Utility::Functor<RETURN(PARAMETER0, PARAMETER1, PARAMETER2, PARAMETER3, PARAMETER4)> Functor;

	template<RETURN(CLASS::*FUNCTION)(PARAMETER0, PARAMETER1, PARAMETER2, PARAMETER3, PARAMETER4)>
	Functor Create(CLASS& a_Object)
	{
		return Functor::template Create<CLASS, FUNCTION>(a_Object);
	}

	template<RETURN(CLASS::*FUNCTION)(PARAMETER0, PARAMETER1, PARAMETER2, PARAMETER3, PARAMETER4) const>
	Functor CreateConst(CLASS& a_Object)
	{
		return Functor::template CreateConst<CLASS, FUNCTION>(a_Object);
	}
};

template<typename RETURN>
FunctorHelperNonMemberNoParameters<RETURN> CreateFunctorHelper(RETURN (*)())
{
	return FunctorHelperNonMemberNoParameters<RETURN>();
}

template<typename RETURN, typename PARAMETER_TYPE>
FunctorHelperNonMemberOneParameter<RETURN, PARAMETER_TYPE> CreateFunctorHelper(RETURN (PARAMETER_TYPE))
{
	return FunctorHelperNonMemberOneParameter<RETURN, PARAMETER_TYPE>();
}

template<typename RETURN, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1>
FunctorHelperNonMemberTwoParameters<RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1> CreateFunctorHelper(RETURN(PARAMETER_TYPE_0, PARAMETER_TYPE_1))
{
	return FunctorHelperNonMemberTwoParameters<RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1>();
}

template<typename RETURN, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1, typename PARAMETER_TYPE_2>
FunctorHelperNonMemberThreeParameters<RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2> CreateFunctorHelper(RETURN(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2))
{
	return FunctorHelperNonMemberThreeParameters<RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2>();
}

template<typename RETURN, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1, typename PARAMETER_TYPE_2, typename PARAMETER_TYPE_3>
FunctorHelperNonMemberFourParameters<RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3> CreateFunctorHelper(RETURN(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3))
{
	return FunctorHelperNonMemberFourParameters<RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3>();
}

template<typename RETURN, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1, typename PARAMETER_TYPE_2, typename PARAMETER_TYPE_3, typename PARAMETER_TYPE_4>
FunctorHelperNonMemberFiveParameters<RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4> CreateFunctorHelper(RETURN(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4))
{
	return FunctorHelperNonMemberFiveParameters<RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4>();
}

template<typename CLASS, typename RETURN>
FunctorHelperMemberNoParameters<CLASS, RETURN> CreateFunctorHelper(RETURN (CLASS::*)())
{
	return FunctorHelperMemberNoParameters<CLASS, RETURN>();
}

template<typename CLASS, typename RETURN>
FunctorHelperMemberNoParameters<const CLASS, RETURN> CreateFunctorHelper(RETURN (CLASS::* const)() const)
{
	return FunctorHelperMemberNoParameters<const CLASS, RETURN>();
}

template<typename CLASS, typename RETURN, typename PARAMETER_TYPE>
FunctorHelperMemberOneParameter<CLASS, RETURN, PARAMETER_TYPE> CreateFunctorHelper(RETURN(CLASS::*)(PARAMETER_TYPE))
{
	return FunctorHelperMemberOneParameter<CLASS, RETURN, PARAMETER_TYPE>();
}

template<typename CLASS, typename RETURN, typename PARAMETER_TYPE>
FunctorHelperMemberOneParameter<const CLASS, RETURN, PARAMETER_TYPE> CreateFunctorHelper(RETURN(CLASS::* const)(PARAMETER_TYPE) const)
{
	return FunctorHelperMemberOneParameter<const CLASS, RETURN, PARAMETER_TYPE>();
}

template<typename CLASS, typename RETURN, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1>
FunctorHelperMemberTwoParameters<CLASS, RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1> CreateFunctorHelper(RETURN(CLASS::*)(PARAMETER_TYPE_0, PARAMETER_TYPE_1))
{
	return FunctorHelperMemberTwoParameters<CLASS, RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1>();
}

template<typename CLASS, typename RETURN, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1>
FunctorHelperMemberTwoParameters<const CLASS, RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1> CreateFunctorHelper(RETURN(CLASS::* const)(PARAMETER_TYPE_0, PARAMETER_TYPE_1) const)
{
	return FunctorHelperMemberTwoParameters<const CLASS, RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1>();
}

template<typename CLASS, typename RETURN, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1, typename PARAMETER_TYPE_2>
FunctorHelperMemberThreeParameters<CLASS, RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2> CreateFunctorHelper(RETURN(CLASS::*)(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2))
{
	return FunctorHelperMemberThreeParameters<CLASS, RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2>();
}

template<typename CLASS, typename RETURN, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1, typename PARAMETER_TYPE_2>
FunctorHelperMemberThreeParameters<const CLASS, RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2> CreateFunctorHelper(RETURN(CLASS::* const)(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2) const)
{
	return FunctorHelperMemberThreeParameters<const CLASS, RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2>();
}

template<typename CLASS, typename RETURN, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1, typename PARAMETER_TYPE_2, typename PARAMETER_TYPE_3>
FunctorHelperMemberFourParameters<CLASS, RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3> CreateFunctorHelper(RETURN(CLASS::*)(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3))
{
	return FunctorHelperMemberFourParameters<CLASS, RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3>();
}

template<typename CLASS, typename RETURN, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1, typename PARAMETER_TYPE_2, typename PARAMETER_TYPE_3>
FunctorHelperMemberFourParameters<const CLASS, RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3> CreateFunctorHelper(RETURN(CLASS::* const)(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3) const)
{
	return FunctorHelperMemberFourParameters<const CLASS, RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3>();
}

template<typename CLASS, typename RETURN, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1, typename PARAMETER_TYPE_2, typename PARAMETER_TYPE_3, typename PARAMETER_TYPE_4>
FunctorHelperMemberFiveParameters<CLASS, RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4> CreateFunctorHelper(RETURN(CLASS::*)(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4))
{
	return FunctorHelperMemberFiveParameters<CLASS, RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4>();
}

template<typename CLASS, typename RETURN, typename PARAMETER_TYPE_0, typename PARAMETER_TYPE_1, typename PARAMETER_TYPE_2, typename PARAMETER_TYPE_3, typename PARAMETER_TYPE_4>
FunctorHelperMemberFiveParameters<const CLASS, RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4> CreateFunctorHelper(RETURN(CLASS::* const)(PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4) const)
{
	return FunctorHelperMemberFiveParameters<const CLASS, RETURN, PARAMETER_TYPE_0, PARAMETER_TYPE_1, PARAMETER_TYPE_2, PARAMETER_TYPE_3, PARAMETER_TYPE_4>();
}

#define CREATE_FUNCTOR(a_Function) \
	Utility::CreateFunctorHelper(&a_Function).Create<a_Function>();

#define CREATE_MEMBER_FUNCTOR(a_Object, a_Function) \
	Utility::CreateFunctorHelper(a_Function).Create<a_Function>(a_Object);

END_NAMESPACE(Utility)


/*
void NoParams() { }
void OneParam(void *a_Param0) { }
void TwoParams(void *a_Param0, void *a_Param1) { }
void ThreeParams(void *a_Param0, void *a_Param1, void *a_Param2) { }
void FourParams(void *a_Param0, void *a_Param1, void *a_Param2, void *a_Param3) { }
void FiveParams(void *a_Param0, void *a_Param1, void *a_Param2, void *a_Param3, void *a_Param4) { }

void *param0 = NULLPTR;
void *param1 = NULLPTR;
void *param2 = NULLPTR;
void *param3 = NULLPTR;
void *param4 = NULLPTR;

typedef Utility::Functor<void()> FunctorNoParam;
FunctorNoParam functorNoParam = CREATE_FUNCTOR(NoParams);
functorNoParam();

typedef Utility::Functor<void(void*)> FunctorOneParam;
FunctorOneParam functorOneParam = CREATE_FUNCTOR(OneParam);
functorOneParam(param0);

typedef Utility::Functor<void(void*, void*)> FunctorTwoParams;
FunctorTwoParams functorTwoParams = CREATE_FUNCTOR(TwoParams);
functorTwoParams(param0, param1);

typedef Utility::Functor<void(void*, void*, void*)> FunctorThreeParams;
FunctorThreeParams functorThreeParams = CREATE_FUNCTOR(ThreeParams);
functorThreeParams(param0, param1, param2);

typedef Utility::Functor<void(void*, void*, void*, void*)> FunctorFourParams;
FunctorFourParams functorFourParams = CREATE_FUNCTOR(FourParams);
functorFourParams(param0, param1, param2, param3);

typedef Utility::Functor<void(void*, void*, void*, void*, void*)> FunctorFiveParams;
FunctorFiveParams functorFiveParams = CREATE_FUNCTOR(FiveParams);
functorFiveParams(param0, param1, param2, param3, param4);

class FunctorTestClass
{
public:
	void NoParams() { }
	void OneParam(void *a_Param0) { }
	void TwoParams(void *a_Param0, void *a_Param1) { }
	void ThreeParams(void *a_Param0, void *a_Param1, void *a_Param2) { }
	void FourParams(void *a_Param0, void *a_Param1, void *a_Param2, void *a_Param3) { }
	void FiveParams(void *a_Param0, void *a_Param1, void *a_Param2, void *a_Param3, void *a_Param4) { }
};

FunctorTestClass functorTestClass;

typedef Utility::Functor<void()> MemberFunctorNoParam;
MemberFunctorNoParam memberFunctorNoParam = CREATE_MEMBER_FUNCTOR(functorTestClass, &FunctorTestClass::NoParams);
memberFunctorNoParam();

typedef Utility::Functor<void(void*)> MemberFunctorOneParam;
MemberFunctorOneParam memberFunctorOneParam = CREATE_MEMBER_FUNCTOR(functorTestClass, &FunctorTestClass::OneParam);
memberFunctorOneParam(param0);

typedef Utility::Functor<void(void*, void*)> MemberFunctorTwoParams;
MemberFunctorTwoParams memberFunctorTwoParams = CREATE_MEMBER_FUNCTOR(functorTestClass, &FunctorTestClass::TwoParams);
memberFunctorTwoParams(param0, param1);

typedef Utility::Functor<void(void*, void*, void*)> MemberFunctorThreeParams;
MemberFunctorThreeParams memberFunctorThreeParams = CREATE_MEMBER_FUNCTOR(functorTestClass, &FunctorTestClass::ThreeParams);
memberFunctorThreeParams(param0, param1, param2);

typedef Utility::Functor<void(void*, void*, void*, void*)> MemberFunctorFourParams;
MemberFunctorFourParams memberFunctorFourParams = CREATE_MEMBER_FUNCTOR(functorTestClass, &FunctorTestClass::FourParams);
memberFunctorFourParams(param0, param1, param2, param3);

typedef Utility::Functor<void(void*, void*, void*, void*, void*)> MemberFunctorFiveParams;
MemberFunctorFiveParams memberFunctorFiveParams = CREATE_MEMBER_FUNCTOR(functorTestClass, &FunctorTestClass::FiveParams);
memberFunctorFiveParams(param0, param1, param2, param3, param4);

*/