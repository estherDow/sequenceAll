#include <OutputFactory.h>

#include <typeinfo>
#include <assert.h>
#include <unity.h>



OutputFactory outputFactory;
OscOut *oscOut;


void test_function_return_cv() {

}

void test_function_return_led() {

}

void test_function_return_osc() {
  TEST_ASSERT_NOT_NULL(outputFactory.make(OSC));
}

void test_function_return_midi() {

}






int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_function_return_osc);
  //  RUN_TEST(test_function_return_cv);
  //  RUN_TEST(test_function_return_midi);
  //  RUN_TEST(test_function_return_led);
    UNITY_END();

    return 0;
}
