#pragma once

#include "Proto.h"
#include "EButton.h"
#include "EThumbStick.h"
#include "ETrigger.h"
#include "IController.h"
#include "Utility/Functors.h"

#include <vector>

BEGIN_NAMESPACE(IO)

typedef Utility::Functor<void(short)> ControllerButtonDownCallback;
typedef Utility::Functor<void(short)> ControllerButtonUpCallback;
typedef Utility::Functor<void(ETrigger, float)> ControllerTriggerPulledCallback;
typedef Utility::Functor<void(ETrigger)> ControllerTriggerReleasedCallback;
typedef Utility::Functor<void(EThumbStick, float, float)> ControllerThumbStickMovedCallback;
typedef Utility::Functor<void(EThumbStick)> ControllerThumbStickReleasedCallback;

#define ADD_CONTROLLER_BUTTONDOWN_CALLBACK(CONTROLLER, CLASS_TYPE, FUNCTION, OBJECT) \
	CONTROLLER->AddButtonDownCallback<CLASS_TYPE, &CLASS_TYPE::FUNCTION>(OBJECT);

#define ADD_CONTROLLER_BUTTONUP_CALLBACK(CONTROLLER, CLASS_TYPE, FUNCTION, OBJECT) \
	CONTROLLER->AddButtonUpCallback<CLASS_TYPE, &CLASS_TYPE::FUNCTION>(OBJECT);

#define ADD_CONTROLLER_TRIGGERPULLED_CALLBACK(CONTROLLER, CLASS_TYPE, FUNCTION, OBJECT) \
	CONTROLLER->AddTriggerPulledCallback<CLASS_TYPE, &CLASS_TYPE::FUNCTION>(OBJECT);

#define ADD_CONTROLLER_TRIGGERRELEASED_CALLBACK(CONTROLLER, CLASS_TYPE, FUNCTION, OBJECT) \
	CONTROLLER->AddTriggerReleasedCallback<CLASS_TYPE, &CLASS_TYPE::FUNCTION>(OBJECT);

#define ADD_CONTROLLER_THUMBSTICKMOVED_CALLBACK(CONTROLLER, CLASS_TYPE, FUNCTION, OBJECT) \
	CONTROLLER->AddThumbStickMovedCallback<CLASS_TYPE, &CLASS_TYPE::FUNCTION>(OBJECT);

#define ADD_CONTROLLER_THUMBSTICKRELEASED_CALLBACK(CONTROLLER, CLASS_TYPE, FUNCTION, OBJECT) \
	CONTROLLER->AddThumbStickReleasedCallback<CLASS_TYPE, &CLASS_TYPE::FUNCTION>(OBJECT);

class ControllerBase : public IController
{
public:
	ControllerBase();
	virtual ~ControllerBase();

	template<typename CLASS, void(CLASS::*FUNCTION)(short)>
	void AddButtonDownCallback(CLASS &a_Object)
	{
		ControllerButtonDownCallback *callback = new ControllerButtonDownCallback();
		callback->Bind<CLASS, FUNCTION>(a_Object);
		m_ButtonDownCallbacks.push_back(callback);
	}

	template<typename CLASS, void(CLASS::*FUNCTION)(short)>
	void AddButtonUpCallback(CLASS &a_Object)
	{
		ControllerButtonUpCallback *callback = new ControllerButtonUpCallback();
		callback->Bind<CLASS, FUNCTION>(a_Object);
		m_ButtonUpCallbacks.push_back(callback);
	}

	template<typename CLASS, void(CLASS::*FUNCTION)(ETrigger, float)>
	void AddTriggerPulledCallback(CLASS &a_Object)
	{
		ControllerTriggerPulledCallback *callback = new ControllerTriggerPulledCallback();
		callback->Bind<CLASS, FUNCTION>(a_Object);
		m_TriggerPulledCallbacks.push_back(callback);
	}

	template<typename CLASS, void(CLASS::*FUNCTION)(ETrigger)>
	void AddTriggerReleasedCallback(CLASS &a_Object)
	{
		ControllerTriggerReleasedCallback *callback = new ControllerTriggerReleasedCallback();
		callback->Bind<CLASS, FUNCTION>(a_Object);
		m_TriggerReleasedCallbacks.push_back(callback);
	}

	template<typename CLASS, void(CLASS::*FUNCTION)(EThumbStick, float, float)>
	void AddThumbStickMovedCallback(CLASS &a_Object)
	{
		ControllerThumbStickMovedCallback *callback = new ControllerThumbStickMovedCallback();
		callback->Bind<CLASS, FUNCTION>(a_Object);
		m_ThumbStickMovedCallbacks.push_back(callback);
	}

	template<typename CLASS, void(CLASS::*FUNCTION)(EThumbStick)>
	void AddThumbStickReleasedCallback(CLASS &a_Object)
	{
		ControllerThumbStickReleasedCallback *callback = new ControllerThumbStickReleasedCallback();
		callback->Bind<CLASS, FUNCTION>(a_Object);
		m_ThumbStickReleasedCallbacks.push_back(callback);
	}

protected:
	uint32_t GetButtonIndex(EButton a_Button);

	std::vector<ControllerButtonDownCallback*> m_ButtonDownCallbacks;
	std::vector<ControllerButtonUpCallback*> m_ButtonUpCallbacks;
	std::vector<ControllerTriggerPulledCallback*> m_TriggerPulledCallbacks;
	std::vector<ControllerTriggerReleasedCallback*> m_TriggerReleasedCallbacks;
	std::vector<ControllerThumbStickMovedCallback*> m_ThumbStickMovedCallbacks;
	std::vector<ControllerThumbStickReleasedCallback*> m_ThumbStickReleasedCallbacks;
};

bool IsButtonFlagSet(short a_Flags, EButton a_ButtonCode);

END_NAMESPACE(IO)
