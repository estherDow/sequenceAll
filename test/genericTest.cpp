#include "ModuleInterface.h"
#include <Module.h>
#include <ModuleMock.h>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::AtLeast;                         // #1



class Module_Test_Fixture : public ::testing::Test {
protected:
    virtual void SetUp() {
        mockedModule = new ModuleMock();
        module = new Module();
    }

    virtual void TearDown() {
        delete mockedModule;
        delete module;
    }
    NiceMock<ModuleMock> mockedModule{};
    Module* module{};
};


TEST_F(Module_Test_Fixture, NotifyAttachedObjects) {
    module.attach(mockedModule);
    module.notify();

    EXPECT_CALL(mockedModule, update())
        .Times(1);
}

TEST_F(Module_Test_Fixture, DoNotNotifyDetachedObjects) {
module.attach(mockedModule);
module.detach(mockedModule);

EXPECT_CALL(mockedModule, update())
.Times(0);
}
