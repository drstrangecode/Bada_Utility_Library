/*
 * HCBULFormManager.h
 *
 *  Created on: 16/gen/2011
 *  Author: Alkemist
 */

#ifndef HCBULFormManager_H_
#define HCBULFormManager_H_

#include <FApp.h>
#include <FBase.h>
#include <FUi.h>

#include "HCBULBaseManagedForm.h"

class HCBULFormManager: public Osp::Ui::Controls::Form {

    private:
        /*
         * Our current navigation stack
         * */
        static Osp::Base::Collection::ArrayList _currentFormsStack;

    public:
        /*
         * PushForm(HCBULBaseManagedForm * form)
         * Pushes a new form onto the current navigation stack
         * */
        static void PushForm(HCBULBaseManagedForm * form);

        /*
         * PopForm()
         * Pops a form from the current stack and destroys it
         * */
        static void PopForm();

        /*
         * PopToRootForm()
         * Removes all the stacked forms, except the root form
         * */
        static void PopToRootForm();

        /*
         * Initialize()
         * Call this to initialize the navigation stack
         * */
        static void Initialize();

        /*
         * Terminate()
         * Call this to finalize the navigation stack
         * */
        static void Terminate();

    private:

        /*
         * DestroyLastFormInStack()
         * Destroys the last form in the stack, useful when poppingf forms from the stack
         * */
        static void DestroyLastFormInStack();

};

#endif /* HCBULFormManager_H_ */
