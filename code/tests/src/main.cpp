#include <gtest/gtest.h>
#include "Tests.h"
#include "UnitTests.h"
using namespace MBI_project::Tests;

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
