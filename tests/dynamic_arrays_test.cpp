#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "dynamic_arrays.h"

// Helper: capture stdout from dynamicArrays()
static std::string captureOutput() {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    dynamicArrays();
    std::cout.rdbuf(oldCout);
    return buffer.str();
}

// ==================== 1. Initial Dynamic Array ====================

TEST(DynamicArraysTest, EmptyArrayCreated) {
    std::string output = captureOutput();
    EXPECT_TRUE(output.find("count=0, capacity=4") != std::string::npos)
        << "Should create an empty dynamic array with capacity 4";
}

// ==================== 2. Adding Elements ====================

TEST(DynamicArraysTest, ThreeElementsAdded) {
    std::string output = captureOutput();
    EXPECT_TRUE(output.find("[10, 20, 30]  (count=3, capacity=4)") != std::string::npos)
        << "Should add 10, 20, 30 to the array";
}

TEST(DynamicArraysTest, ArrayFull) {
    std::string output = captureOutput();
    EXPECT_TRUE(output.find("[10, 20, 30, 40]  (count=4, capacity=4)") != std::string::npos)
        << "Should add 40 to fill the array to capacity";
}

// ==================== 3. Resizing the Array ====================

TEST(DynamicArraysTest, NewCapacityDoubled) {
    std::string output = captureOutput();
    EXPECT_TRUE(output.find("New capacity: 8") != std::string::npos)
        << "Should double capacity from 4 to 8";
}

TEST(DynamicArraysTest, ElementsCopied) {
    std::string output = captureOutput();
    EXPECT_TRUE(output.find("Copied 4 elements to new array") != std::string::npos)
        << "Should copy 4 elements to the new array";
}

TEST(DynamicArraysTest, ResizedCorrectly) {
    std::string output = captureOutput();
    EXPECT_TRUE(output.find("[10, 20, 30, 40]  (count=4, capacity=8)") != std::string::npos)
        << "After resize, should have same elements with capacity 8";
}

// ==================== 4. Adding After Resize ====================

TEST(DynamicArraysTest, AddedAfterResize) {
    std::string output = captureOutput();
    EXPECT_TRUE(output.find("[10, 20, 30, 40, 50, 60, 70]  (count=7, capacity=8)") != std::string::npos)
        << "Should add 50, 60, 70 after resize for count=7, capacity=8";
}

// ==================== 5. Cleanup ====================

TEST(DynamicArraysTest, MemoryFreed) {
    std::string output = captureOutput();
    EXPECT_TRUE(output.find("Dynamic array freed") != std::string::npos)
        << "Should free the dynamic array at the end";
}
