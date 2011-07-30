/*
 * FormNavigationManager.h
 *
 *  Created on: 16/gen/2011
 *  Author: Alkemist
 */

#ifndef FormNavigationManager_H_
#define FormNavigationManager_H_

#include <FApp.h>
#include <FBase.h>
#include <FUi.h>

namespace DSBadaUtilityLib {

    class IStackBasedNavigationForm: public Osp::Ui::Controls::Form {
        public:
            /*
             * FormWillAppear(): called before a form is made visible to the user
             * */
            virtual void FormWillAppear() {};

            /*
             * FormWillDisappear(): called before a form removed from the app frame
             * */
            virtual void FormWillDisappear() {};

            /*
             * ReceivedLowMemoryAlert(): called when a low memory level is detected
             * It is advisable for the form to free some memory when this happens
             * */
            virtual void ReceivedLowMemoryAlert() {};

            /*
             * ReceivedLowBatteryAlert(): called when a low battery level is detected
             * */
            virtual void ReceivedLowBatteryAlert() {};
    };

    class FormNavigationManager: public Osp::Ui::Controls::Form {

        private:
            /*
             * Our current navigation stack
             * */
            Osp::Base::Collection::ArrayList _currentFormsStack;

            /*
             * Object instance
             * */
            static FormNavigationManager * _instance;

            /*
             * Private constructor
             * */
            FormNavigationManager();

        public:

            static const RequestId SET_ROOT_FORM = 100;
            static const RequestId PUSH_FORM = 101;
            static const RequestId POP_FORM = 102;

            static FormNavigationManager * GetInstance();

            /*
             * SetRootForm()
             * Sets a root form for the current navigation stack
             * */
            void SetRootForm(IStackBasedNavigationForm * form);

            /*
             * PushForm()
             * Pushes a new form onto the current navigation stack
             * */
            void PushForm(IStackBasedNavigationForm * form);

            /*
             * PopForm()
             * Pops a form from the current stack and destroys it
             * */
            void PopForm();

            /*
             * Terminate()
             * Call this to finalize the navigation stack
             * */
            void Terminate();

            /*
             * Background()
             * Called when the app goes to background
             * */
            void Background();

            /*
             * Foreground()
             * Called when the app goes to foreground
             * */
            void Foreground();

            /*
             * LowMemoryAlert()
             * Called by the application when a OnLowMemory is received
             * */
            void LowMemoryAlert();

            /*
             * LowBatteryAlert()
             * Called by the application when OnBatteryLevelChanged
             * is received with a low battery level
             * */
            void LowBatteryAlert();

            /*
             * NumberOfFormsInCurrentStack()
             * Returns the size of the current navigation stack
             * */
            int NumberOfFormsInCurrentStack();

        private:

            /*
             * Initialize()
             * Call this to initialize the navigation stack
             * */
            void Initialize();

        private:

            /*
             * Used internally to receive form-switch messages
             * */
            virtual void OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList * pArgs);

    };

}

#endif /* FormNavigationManager_H_ */
