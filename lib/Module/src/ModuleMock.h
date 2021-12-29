//
// Created by Kenneth Dow on 26/12/21.
//
#ifndef SEQUENCEALL_MODULEMOCK_H
#define SEQUENCEALL_MODULEMOCK_H

#include <ModuleInterface.h>
#include <gtest/gtest.h>
class ModuleMock : public ModuleInterface {
public:
    MOCK_METHOD(void, update, (OscMsgChild & message));
    MOCK_METHOD(void, attach, (ModuleInterface *module));
    MOCK_METHOD(void, detach, (ModuleInterface *module));
    MOCK_METHOD(void, notify, (OscMsgChild & message));

};
#endif //SEQUENCEALL_MODULEMOCK_H
