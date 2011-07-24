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

void HCBULFormManager::Initialize() {
    _currentFormsStack.Construct();
}

void HCBULFormManager::Terminate() {
    AppLog("HCBULFormManager::Terminate()");
    // Destroy the current forms stack
    while (_currentFormsStack.GetCount() > 0) {
        DestroyLastFormInStack();
    }
}

void HCBULFormManager::PushForm(HCBULBaseManagedForm * form) {
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

    Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
    HCBULBaseManagedForm * currentForm = static_cast<HCBULBaseManagedForm *> (_currentFormsStack.GetAt(_currentFormsStack.GetCount() - 1));

    // Remove current form from display
    pFrame->RemoveControl(*currentForm);

    // Remove from stack and deallocate
    _currentFormsStack.RemoveAt(_currentFormsStack.GetCount() - 1, false);

}

void HCBULFormManager::PopForm() {
    Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();

    if (_currentFormsStack.GetCount() > 1) {
        HCBULBaseManagedForm * previousForm = static_cast<HCBULBaseManagedForm *> (_currentFormsStack.GetAt(_currentFormsStack.GetCount() - 2));

        // Show previous form
        pFrame->SetCurrentForm(*previousForm);
        previousForm->Draw();
        previousForm->Show();
    }

    DestroyLastFormInStack();

}

void HCBULFormManager::PopToRootForm() {

    // Remove all forms in stack
    while (_currentFormsStack.GetCount() > 0) {
        DestroyLastFormInStack();
    }
}
