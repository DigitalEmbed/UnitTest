#include "./AnyCppLib.h"

AnyClass::AnyClass(void){
}

int AnyClass::anyMethodPrivate(void){
    return -1;
}

bool AnyClass::anyMethodPublic(void){
    return true;
}

UNIT_TEST_CLASS_BEGIN(AnyClass)
{
    AnyClass any_class;
    UNIT_TEST_COMPARE(any_class.anyMethodPrivate(), -1);    // Pass
    UNIT_TEST_ASSERT(any_class.anyMethodPublic() == true);  // Pass
}
UNIT_TEST_CLASS_END
