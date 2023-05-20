#include "./UnitTest.h"
#include <stdarg.h>
#include <stdint.h>

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
    uint16_t error_counter = 0;
    uint16_t error_totalizer = 0;
    UnitTest::write_function = write_function;
    UnitTest::log("[!] Running tests...\r\n\r\n");
    for (Tester* iterator = UnitTest::first ; iterator != nullptr ; iterator = iterator->next){
        if (iterator->test_function() == false){
            error_counter++;
            if (abort_at_error == true){
                UnitTest::log("\r\n[x] Failed test... Fix it to proceed.\r\n");
                break;
            }
        }
        if (error_counter == 0){
            UnitTest::log("[v] This test was passed!\r\n\r\n");
        } else {
            UnitTest::log("[x] This test was run and %d error%c %s found.\r\n\r\n", error_counter, error_counter > 1 ? 's' : 0, error_counter > 1 ? "were" : "was");
        }
        error_totalizer += error_counter;
        error_counter = 0;
    }

    if (error_totalizer == 0){
        UnitTest::log("[v] All tests were passed!\r\n\r\n");
    } else {
        UnitTest::log("[x] All tests were run and %d error%c %s found.\r\n", error_totalizer, error_totalizer > 1 ? 's' : 0, error_totalizer > 1 ? "were" : "was");
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
