#include <gtest/gtest.h>

#include "./tests/list_test.cpp"
#include "./tests/stack_test.cpp"
#include "./tests/vector_test.cpp"
#include "./tests/queue_test.cpp"
#include "./tests/map_test.cpp"
#include "./tests/set_test.cpp"
#include "./tests/array_test.cpp"
#include "./tests/multiset_test.cpp"

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
