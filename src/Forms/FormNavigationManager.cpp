/*
 * FormNavigationManager.cpp
 *
 *  Created on: 16/gen/2011
 *  Author: Alkemist
 */

#include "Forms/FormNavigationManager.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Ui::Animations;

namespace DSBadaUtilityLib {

FormNavigationManager * FormNavigationManager::_instance = 0;

FormNavigationManager * FormNavigationManager::GetInstance() {
	if (_instance == 0) {
		_instance = new FormNavigationManager();
		_instance->Initialize();
	}
	return _instance;
}

FormNavigationManager::FormNavigationManager() {

}

void FormNavigationManager::Initialize() {
	AppLog("FormNavigationManager::Initialize()");
	_currentFormsStack.Construct();

	Form::Construct(FORM_STYLE_NORMAL);

	// Adds itself to the app frame, so we can receive user events from the event queue
	Frame * pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	pFrame->AddControl(*this);
}

void FormNavigationManager::Terminate() {
	AppLog("FormNavigationManager::Terminate()");
}

void FormNavigationManager::Background() {
	if (NumberOfFormsInCurrentStack() == 0)
		return;

	StackBasedNavigationForm * form =
			static_cast<StackBasedNavigationForm *> (_currentFormsStack.GetAt(
					_currentFormsStack.GetCount() - 1));
	form->FormWillDisappear();
}

void FormNavigationManager::Foreground() {
	if (NumberOfFormsInCurrentStack() == 0)
		return;

	StackBasedNavigationForm * form =
			static_cast<StackBasedNavigationForm *> (_currentFormsStack.GetAt(
					_currentFormsStack.GetCount() - 1));
	form->FormWillAppear();
}

void FormNavigationManager::LowMemoryAlert() {
	AppLog("FormNavigationManager::LowMemoryAlert()");

	if (NumberOfFormsInCurrentStack() == 0)
		return;

	StackBasedNavigationForm * form =
			static_cast<StackBasedNavigationForm *> (_currentFormsStack.GetAt(
					_currentFormsStack.GetCount() - 1));
	form->ReceivedLowMemoryAlert();
}

void FormNavigationManager::LowBatteryAlert() {
	AppLog("FormNavigationManager::LowBatteryAlert()");

	if (NumberOfFormsInCurrentStack() == 0)
		return;

	StackBasedNavigationForm * form =
			static_cast<StackBasedNavigationForm *> (_currentFormsStack.GetAt(
					_currentFormsStack.GetCount() - 1));
	form->ReceivedLowBatteryAlert();
}

int FormNavigationManager::NumberOfFormsInCurrentStack() {
	return _currentFormsStack.GetCount();
}

void FormNavigationManager::PushForm(StackBasedNavigationForm * form) {

	ArrayList * list = new ArrayList();
	list->Add(*form);

	SendUserEvent(FormNavigationManager::PUSH_FORM, list);
}

void FormNavigationManager::SetRootForm(StackBasedNavigationForm * form) {

	ArrayList * list = new ArrayList();
	list->Add(*form);

	SendUserEvent(FormNavigationManager::SET_ROOT_FORM, list);
}

void FormNavigationManager::PopForm() {
	SendUserEvent(FormNavigationManager::POP_FORM, 0);
}

void FormNavigationManager::OnUserEventReceivedN(RequestId requestId,
		IList* pArgs) {

	switch (requestId) {
	case SET_ROOT_FORM: {
		AppLog("FormNavigationManager: setting root form");

		AppAssertf(NumberOfFormsInCurrentStack() == 0, "This navigation stack has already a root form");

		Frame * pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();

		StackBasedNavigationForm * nextForm = static_cast<StackBasedNavigationForm *> (pArgs->GetAt(0));

		// Add new form in the stack
		_currentFormsStack.Add(*nextForm);
		// Add new form on display, the form is automatically set as the current form
		pFrame->AddControl(*nextForm);
		// Call FormWillAppear() on the root form
		nextForm->FormWillAppear();
		// Show new form
		nextForm->Draw();
		nextForm->Show();

		delete pArgs;
	}
		break;

	case PUSH_FORM: {
		AppLog("FormNavigationManager: pushing form");

		AppAssertf(NumberOfFormsInCurrentStack() > 0, "This navigation stack has no root form, please set a root form with SetRootForm()");

		StackBasedNavigationForm * nextForm = static_cast<StackBasedNavigationForm *> (pArgs->GetAt(0));
		StackBasedNavigationForm * currentForm = static_cast<StackBasedNavigationForm *> (_currentFormsStack.GetAt(_currentFormsStack.GetCount() - 1));

		Frame * pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();

		// Call FormWillDisappear() on the old form
		currentForm->FormWillDisappear();
		// Add new form in the stack
		_currentFormsStack.Add(*nextForm);
		// Add new form on display, nextForm becomes the current form
		pFrame->AddControl(*nextForm);
		// Re-set currentForm as the current form so we can perform a nice animation
		pFrame->SetCurrentForm(*currentForm);
		// Call FormWillAppear() on the new form
		nextForm->FormWillAppear();

		// Perform the transition with a nice slide-in animation
		FrameAnimator * pAnimator = pFrame->GetFrameAnimator();
		pAnimator->SetFormTransitionAnimation(
				FRAME_ANIMATOR_FORM_TRANSITION_ANIMATION_TRANSLATE_LEFT, 600,
				ANIMATION_INTERPOLATOR_EASE_IN_OUT);

		pAnimator->SetCurrentForm(*nextForm);

		delete pArgs;
	}
		break;

	case POP_FORM: {
		AppLog("FormNavigationManager: popping form");

		AppAssertf(NumberOfFormsInCurrentStack() > 0, "This navigation stack has no root form, please set a root form with SetRootForm()");

		Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();

		AppAssertf(_currentFormsStack.GetCount() > 1, "Illegal: Trying to pop the root form");

		StackBasedNavigationForm * previousForm = static_cast<StackBasedNavigationForm *> (_currentFormsStack.GetAt(_currentFormsStack.GetCount() - 2));
		StackBasedNavigationForm * currentForm = static_cast<StackBasedNavigationForm *> (_currentFormsStack.GetAt(_currentFormsStack.GetCount() - 1));

		// Call FormWillDisappear() on the current form
		currentForm->FormWillDisappear();
		// Call FormWillAppear() on the previous form
		previousForm->FormWillAppear();

		// Perform the transition with a nice slide-out animation
		FrameAnimator * pAnimator = pFrame->GetFrameAnimator();
		pAnimator->SetFormTransitionAnimation(
				FRAME_ANIMATOR_FORM_TRANSITION_ANIMATION_TRANSLATE_RIGHT, 600,
				ANIMATION_INTERPOLATOR_EASE_IN_OUT);

		pAnimator->SetCurrentForm(*previousForm);

		pFrame->RemoveControl(*currentForm);
		_currentFormsStack.RemoveAt(_currentFormsStack.GetCount() - 1, false);

	}
		break;
	}
}

}
