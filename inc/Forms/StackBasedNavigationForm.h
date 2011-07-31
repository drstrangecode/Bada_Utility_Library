
#ifndef ___StackBasedNavigationForm_h__
#define ___StackBasedNavigationForm_h__

#include <FUi.h>

namespace DSBadaUtilityLib {

    class StackBasedNavigationForm : public Osp::Ui::Controls::Form {
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

}

#endif // ___StackBasedNavigationForm_h__
