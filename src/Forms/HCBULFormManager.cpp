/*
 * HCBULFormManager.cpp
 *
 *  Created on: 16/gen/2011
 *  Author: Alkemist
 */

#include "Forms/HCBULFormManager.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

ArrayList HCBULFormManager::_currentFormsStack;
bool HCBULFormManager::_initialized = false;

void HCBULFormManager::CheckInitState() {
    AppAssertf(_initialized, "HCBULFormManager has not been initialized, please call HCBULFormManager::Initialize() in your OnAppInitializing()");
}

void HCBULFormManager::Initialize() {
    AppLog("HCBULFormManager::Initialize()");

    AppAssertf(!_initialized, "trying to re-initialize HCBULFormManager");

    _initialized = true;
    _currentFormsStack.Construct();
}

void HCBULFormManager::Terminate() {
    AppLog("HCBULFormManager::Terminate()");

    CheckInitState();

    // Destroy the current forms stack
    while (_currentFormsStack.GetCount() > 0) {
        DestroyLastFormInStack();
    }

    _initialized = false;
}

int HCBULFormManager::NumberOfFormsInStack() {
    CheckInitState();
    return _currentFormsStack.GetCount();
}

void HCBULFormManager::PushForm(HCBULBaseManagedForm * form) {

    CheckInitState();

    Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();

    // Add new form in the stack
    _currentFormsStack.Add(*form);

    // Add new form on display
    pFrame->AddControl(*form);
    pFrame->SetCurrentForm(*form);

    // Show new form
    form->Draw();
    form->Show();

}

void HCBULFormManager::DestroyLastFormInStack() {

    CheckInitState();

    if (Application::GetInstance()->GetAppFrame() != 0) {

        Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();

        HCBULBaseManagedForm * currentForm = static_cast<HCBULBaseManagedForm *> (_currentFormsStack.GetAt(_currentFormsStack.GetCount() - 1));

        // Remove current form from display
        pFrame->RemoveControl(*currentForm);
    }

    // Remove the form from the navigation stack (fo not deallocate)
    _currentFormsStack.RemoveAt(_currentFormsStack.GetCount() - 1, false);

}

void HCBULFormManager::PopForm() {

    CheckInitState();

    Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();

    if (_currentFormsStack.GetCount() > 1) {
        HCBULBaseManagedForm * previousForm = static_cast<HCBULBaseManagedForm *> (_currentFormsStack.GetAt(_currentFormsStack.GetCount() - 2));

        // Show previous form
        pFrame->SetCurrentForm(*previousForm);
        previousForm->Draw();
        previousForm->Show();

        DestroyLastFormInStack();
    } else {
        AppLog("Warning: not popping root form");
    }
}
