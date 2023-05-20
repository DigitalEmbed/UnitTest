#include "UnitTest.h"

UNIT_TEST_BEGIN
{
    UNIT_TEST_LOG("Testing messages... %d", 1);

    int a = 3;
    int* b = &a;
    UNIT_TEST_COMPARE(a, *b);   // Pass

    *b = 5;
    UNIT_TEST_ASSERT(a == 5);   // Error

    int c = 10;
    UNIT_TEST_COMPARE(3*a, c);  // Pass
}
UNIT_TEST_END

int main()
{
    UnitTest::run(
        false,                                  // Abort all tests at error. Default value = true.
        [](char data) {fputc(data, stdout);}    // Print implementation. Default value is using fputc with stdout.
    );
    return 0;
}
