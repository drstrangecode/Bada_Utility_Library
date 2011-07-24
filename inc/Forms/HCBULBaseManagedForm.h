/*
 * HCBULBaseManagedForm.h
 *
 *  Created on: 21/mag/2011
 *  Author: HorrorAlkemist
 */

#ifndef HCBULBaseManagedForm_H_
#define HCBULBaseManagedForm_H_

#include <FBase.h>
#include <FUi.h>

class HCBULBaseManagedForm : public Osp::Ui::Controls::Form {
    public:
        HCBULBaseManagedForm();
        virtual ~HCBULBaseManagedForm();

    private:
        Osp::Base::Collection::HashMap _startParameters;

    protected:
        Osp::Base::Object & GetFormStartParameterForKey(const Osp::Base::String & key);
        Osp::Base::String GetFormStartParameterStringForKey(const Osp::Base::String & key);
        Osp::Base::Integer GetFormStartParameterIntegerForKey(const Osp::Base::String & key);
        Osp::Base::Long GetFormStartParameterLongForKey(const Osp::Base::String & key);
        Osp::Base::Boolean GetFormStartParameterBooleanForKey(const Osp::Base::String & key);
        Osp::Base::Double GetFormStartParameterDoubleForKey(const Osp::Base::String & key);

    public:
        void SetFormStartParameter(const Osp::Base::String & key, Osp::Base::Object & val);
        void SetFormLongStartParameter(const Osp::Base::String & key,Osp::Base::Long & value);
        void SetFormIntegerStartParameter(const Osp::Base::String & key, Osp::Base::Integer & value);
        void SetFormStringStartParameter(const Osp::Base::String & key, Osp::Base::String & value);
        void SetFormBooleanStartParameter(const Osp::Base::String & key, Osp::Base::Boolean & value);
        void SetFormDoubleStartParameter(const Osp::Base::String & key, Osp::Base::Double & value);

};

#endif /* HCBULBaseManagedForm_H_ */
