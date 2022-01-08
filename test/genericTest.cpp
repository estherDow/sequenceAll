#include "ModuleInterface.h"
#include <Module.h>
#include <ModuleMock.h>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <cstdint>

using ::testing::AtLeast;                         // #1
using ::testing::NiceMock;


class Module_Test_Fixture : public ::testing::Test {
protected:
    void SetUp() override {
        auto pModuleMock = new ModuleMock();
        auto pModule = new Module();
    }

    void TearDown() override {
        delete mockedModule;
        delete module;
    }
    ModuleInterface *mockedModule{};
    Module* module{};
};


TEST_F(Module_Test_Fixture, NotifyAttachedObjects) {
    module->attach(mockedModule);
    module->notify();

    EXPECT_CALL(mockedModule, update())
        .Times(1);
}

TEST_F(Module_Test_Fixture, DoNotNotifyDetachedObjects) {
module.attach(mockedModule);
module.detach(mockedModule);

EXPECT_CALL(mockedModule, update())
.Times(0);
}
