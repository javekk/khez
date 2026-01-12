#pragma once
#include <functional>
#include <iostream>
#include <string>

class TestLib {
   private:
    uint tab = 0;

    uint totalTestsNumber = 0;
    uint failedTestsNumber = 0;
    bool shortCircuit = false;

   public:
    void describe(const std::string& description, std::function<void()> tests);
    void it(const std::string& description, std::function<void()> test);
    void setShortCircuit(bool value);
};

void describe(const std::string& description, std::function<void()> tests);
void it(const std::string& description, std::function<void()> test);
void expect(bool condition,
            const std::string message = std::string("Assertion failed"));