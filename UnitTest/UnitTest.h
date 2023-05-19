#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <functional>

#define _UNIT_TEST_CONCAT_INNER(a, b) a ## b
#define _UNIT_TEST_CONCAT(a, b) _UNIT_TEST_CONCAT_INNER(a, b)
#define _UNIT_TEST_FUNCTION _UNIT_TEST_CONCAT(test_, __LINE__)

#define UNIT_TEST_BEGIN static Tester _UNIT_TEST_FUNCTION([](){ UnitTest::log("[%s:%d]\r\n", __FILE__, __LINE__);
#define UNIT_TEST_END UnitTest::log("[v] Test completed successfully!\r\n"); return true; });
#define UNIT_TEST_LOG(...) UnitTest::log("[%d] User log: ", __LINE__); UnitTest::log(__VA_ARGS__); UnitTest::log("\r\n")
#define UNIT_TEST_ASSERT(expression) UnitTest::log("%d: Checking expression '" #expression "'... ", __LINE__); if((expression) == false) { UnitTest::log("Error!\r\n"); return false; } UnitTest::log("Ok!\r\n")
#define UNIT_TEST_COMPARE(value1, value2) UnitTest::log("%d: Checking if values '" #value1 "' and '" #value2 "' are equal... " , __LINE__); if((value1) != (value2)) { UnitTest::log("Error!\r\n"); return false; } UnitTest::log("Ok!\r\n")

class Tester;

class UnitTest{
    friend class Tester;
private:
    static Tester* first;
    static Tester* last;
    static std::function<void(char)> write_function;
public:
    static void run(bool abort_at_error = true, std::function<void(char)> write_function = [](char data){fputc(data, stdout);});
    static void log(const char* message, ...) __attribute__((format(printf, 1, 2)));
};

class Tester{
    friend class UnitTest;
private:
    Tester* next {nullptr};
    const std::function<bool(void)> test_function;
public:
    Tester(std::function<bool(void)> test_function);
};
