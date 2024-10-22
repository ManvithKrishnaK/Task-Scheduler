#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Task.h"

TEST_CASE("Task executes correctly") {
    bool executed = false;

    Task task([&executed] { executed = true; }, std::chrono::milliseconds(0));

    REQUIRE_FALSE(executed);  // Task should not be executed yet
    task.execute();
    REQUIRE(executed);        // After execution, the flag should be true
}
