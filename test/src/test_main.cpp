#include <gtest/gtest.h>
#include <glog/logging.h>

/**
 * @brief Main function for test harness
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, const char ** argv) {
    google::InitGoogleLogging(argv[0]);
    testing::InitGoogleTest(&argc, (char**) argv);
    return RUN_ALL_TESTS();

}

