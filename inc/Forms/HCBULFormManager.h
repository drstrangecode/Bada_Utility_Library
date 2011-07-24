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
         * Initialize()
         * Call this to initialize the navigation stack
         * */
        static void Initialize();

        /*
         * OnForeground()
         * Must be called when the app goes to foreground
         * */
        static void OnForeground();

        /*
         * OnBackground()
         * Must be called when the app goes to background
         * */
        static void OnBackground();

        /*
         * Terminate()
         * Call this to finalize the navigation stack
         * */
        static void Terminate();

        /*
         * NumberOfFormsInStack()
         * Returns the size of the current navigation stack
         * */
        static int NumberOfFormsInStack();

    private:

        /*
         * DestroyLastFormInStack()
         * Destroys the last form in the stack, useful when popping forms from the stack
         * */
        static void DestroyLastFormInStack();

        /*
         * CheckInitState()
         * Checks if the form manager has been initialized, throws an error if not
         * */
        static void CheckInitState();

    private:
        static bool _initialized;

};

#endif /* HCBULFormManager_H_ */
