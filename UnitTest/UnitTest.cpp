#include "./UnitTest.h"
#include <stdarg.h>

Tester* UnitTest::first = nullptr;
Tester* UnitTest::last = nullptr;
std::function<void(char)> UnitTest::write_function = nullptr;

Tester::Tester(std::function<bool(void)> test_function) : test_function(test_function) {
    if (UnitTest::first == nullptr){
        UnitTest::first = this;
    }
    if (UnitTest::last != nullptr){
        UnitTest::last->next = this;
    }
    UnitTest::last = this;
}

void UnitTest::run(bool abort_at_error, std::function<void(char)> write_function){
    UnitTest::write_function = write_function;
    UnitTest::log("[!] Running tests...\r\n\r\n");
    for (Tester* iterator = UnitTest::first ; iterator != nullptr ; iterator = iterator->next){
        if (iterator->test_function() == false && abort_at_error == true){
            UnitTest::log("\r\n[x] Failed test... Fix it to proceed.\r\n");
            break;
        }
        UnitTest::log("\r\n[v] All tests passed!");
    }
}

void UnitTest::log(const char* message, ...){
    char buffer[100] = {0};
    va_list arguments;
    va_start(arguments, message);
    vsnprintf(buffer, 100, message, arguments);
    for(const auto& byte : buffer){
        UnitTest::write_function(byte);
    }
    va_end(arguments);
}
