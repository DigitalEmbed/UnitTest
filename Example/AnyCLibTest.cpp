#include "./AnyCLib.h"
#include "./UnitTest/UnitTest.h"

UNIT_TEST_BEGIN
{
    UNIT_TEST_COMPARE(cFunction1(), 1);         // Pass
    UNIT_TEST_COMPARE(cFunction2(), 'a');       // Pass
    UNIT_TEST_COMPARE(cFunction3(), 3.14);      // Pass
}
UNIT_TEST_END
