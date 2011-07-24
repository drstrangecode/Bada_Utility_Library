/*
 * HCBULBaseManagedForm.cpp
 *
 *  Created on: 21/mag/2011
 *  Author: HorrorAlkemist
 */

#include "Forms/HCBULBaseManagedForm.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Collection;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

HCBULBaseManagedForm::HCBULBaseManagedForm() {
    _startParameters.Construct();
}

HCBULBaseManagedForm::~HCBULBaseManagedForm() {

    /*
     * Destroys the start parameters
     * */

    IMapEnumerator * pMapEnum = _startParameters.GetMapEnumeratorN();
    pMapEnum->Reset();

    while (pMapEnum->MoveNext() == E_SUCCESS) {
        delete pMapEnum->GetKey();
        delete pMapEnum->GetValue();
    }
    delete pMapEnum;

}

Object & HCBULBaseManagedForm::GetFormStartParameterForKey(const String & key) {
    return *_startParameters.GetValue(key);
}

void HCBULBaseManagedForm::SetFormStartParameter(const String & key, Object & value) {

    bool alreadyExists;
    _startParameters.ContainsKey(key, alreadyExists);
    AppAssertf(!alreadyExists, "This start parameter [%S] has already been set", key.GetPointer());
    _startParameters.Add(key, value);

}

void HCBULBaseManagedForm::SetFormLongStartParameter(const String & key, Long & value) {
    String * ptrKey = new String(key);
    Long * ptrVal = new Long(value);

    SetFormStartParameter(*ptrKey, *ptrVal);
}

void HCBULBaseManagedForm::SetFormIntegerStartParameter(const String & key, Integer & value) {
    String * ptrKey = new String(key);
    Integer * ptrVal = new Integer(value);

    SetFormStartParameter(*ptrKey, *ptrVal);
}

void HCBULBaseManagedForm::SetFormStringStartParameter(const String & key, String & value) {
    String * ptrKey = new String(key);
    String * ptrVal = new String(value);

    SetFormStartParameter(*ptrKey, *ptrVal);
}

void HCBULBaseManagedForm::SetFormBooleanStartParameter(const String & key, Boolean & value) {
    String * ptrKey = new String(key);
    Boolean * ptrVal = new Boolean(value);

    SetFormStartParameter(*ptrKey, *ptrVal);
}

void HCBULBaseManagedForm::SetFormDoubleStartParameter(const Osp::Base::String & key, Osp::Base::Double & value) {
    String * ptrKey = new String(key);
    Double * ptrVal = new Double(value);

    SetFormStartParameter(*ptrKey, *ptrVal);
}

String HCBULBaseManagedForm::GetFormStartParameterStringForKey(const String & key) {
    Object & objVal = GetFormStartParameterForKey(key);
    String & value = static_cast<String &> (objVal);
    return value;
}

Integer HCBULBaseManagedForm::GetFormStartParameterIntegerForKey(const String & key) {
    Object & objVal = GetFormStartParameterForKey(key);
    Integer & value = static_cast<Integer &> (objVal);
    return value;
}

Long HCBULBaseManagedForm::GetFormStartParameterLongForKey(const String & key) {
    Object & objVal = GetFormStartParameterForKey(key);
    Long & value = static_cast<Long &> (objVal);
    return value;
}

Boolean HCBULBaseManagedForm::GetFormStartParameterBooleanForKey(const String & key) {
    Object & objVal = GetFormStartParameterForKey(key);
    Boolean & value = static_cast<Boolean &> (objVal);
    return value;
}

Double HCBULBaseManagedForm::GetFormStartParameterDoubleForKey(const String & key) {
    Object & objVal = GetFormStartParameterForKey(key);
    Double & value = static_cast<Double &> (objVal);
    return value;
}


