#pragma once
#include "./UnitTest/UnitTest.h"

class AnyClass {
    USING_UNIT_TEST
	private:
        int anyMethodPrivate(void);
    public:
        AnyClass(void);
        bool anyMethodPublic(void);
};
