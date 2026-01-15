#include "test_lib.h"

static TestLib globalTest;

void TestLib::describe(const std::string& description,
                       std::function<void()> tests) {
    tab++;
    std::cout << std::string(tab, '\t') << description << "\n";
    tests();
    tab--;

    if (tab == 0) {
        if (failedTestsNumber == 0) {
            std::cout << "🎉 " << totalTestsNumber << " test(s) passed!\n";
        } else {
            std::cout << "❌ Failed " << failedTestsNumber << " out of "
                      << totalTestsNumber << " test(s) failed!\n";
        }
    }
}

void TestLib::it(const std::string& description, std::function<void()> test) {
    tab++;
    try {
        totalTestsNumber++;
        test();
        std::cout << std::string(tab, '\t') << "✓ " << description << "\n";
    } catch (const std::exception& e) {
        failedTestsNumber++;
        std::cout << std::string(tab, '\t') << "✗ " << description << " - "
                  << e.what() << "\n";
        if (shortCircuit) {
            tab--;
            throw;
        }
    }
    tab--;
}

void TestLib::setShortCircuit(bool value) { shortCircuit = value; }

void describe(const std::string& description, std::function<void()> tests) {
    globalTest.describe(description, tests);
}

void it(const std::string& description, std::function<void()> test) {
    globalTest.it(description, test);
}

void expectImpl(bool condition, int line, const std::string& message) {
    if (!condition) {
        throw std::runtime_error(message + " (line " + std::to_string(line) +
                                 ")");
    }
}
