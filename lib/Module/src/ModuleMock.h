//
// Created by Kenneth Dow on 26/12/21.
//
#ifndef SEQUENCEALL_MODULEMOCK_H
#define SEQUENCEALL_MODULEMOCK_H

#include <ModuleInterface.h>
#include "gmock/gmock.h"  // Brings in gMock.
class ModuleMock : public ModuleInterface {
public:
    MOCK_METHOD(void, update, (OSCClientInterface & message),(override));
    MOCK_METHOD(void, attach, (ModuleInterface *module),(override));
    MOCK_METHOD(void, detach, (ModuleInterface *module),(override));
    MOCK_METHOD(void, notify, (OSCClientInterface & message),(override));

};
#endif //SEQUENCEALL_MODULEMOCK_H
