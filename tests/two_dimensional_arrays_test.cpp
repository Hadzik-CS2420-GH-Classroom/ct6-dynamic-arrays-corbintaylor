#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "two_dimensional_arrays.h"

// Helper: capture stdout from twoDimensionalArrays()
static std::string captureOutput() {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    twoDimensionalArrays();
    std::cout.rdbuf(oldCout);
    return buffer.str();
}

// ==================== 2. Dynamic 2D Array ====================

TEST(TwoDimensionalArraysTest, Dynamic2DArrayPrinted) {
    std::string output = captureOutput();
    EXPECT_TRUE(output.find("Row 0: 1 2 3 4") != std::string::npos)
        << "Dynamic 2D array should print Row 0: 1 2 3 4";
    EXPECT_TRUE(output.find("Row 1: 5 6 7 8") != std::string::npos)
        << "Dynamic 2D array should print Row 1: 5 6 7 8";
    EXPECT_TRUE(output.find("Row 2: 9 10 11 12") != std::string::npos)
        << "Dynamic 2D array should print Row 2: 9 10 11 12";
}

TEST(TwoDimensionalArraysTest, Dynamic2DArrayFreed) {
    std::string output = captureOutput();
    EXPECT_TRUE(output.find("2D array memory freed (rows first, then spine)") != std::string::npos)
        << "Should free the dynamic 2D array rows first, then the spine";
}

// ==================== 4. Flat Array as 2D ====================

TEST(TwoDimensionalArraysTest, FlatArrayAs2D) {
    std::string output = captureOutput();
    // Find the flat array section specifically
    auto flatPos = output.find("Flat array as 2D:");
    ASSERT_TRUE(flatPos != std::string::npos)
        << "Should print the flat array as a 2D grid";
    std::string flatSection = output.substr(flatPos);
    EXPECT_TRUE(flatSection.find("Row 0: 1 2 3 4") != std::string::npos)
        << "Flat array should print Row 0: 1 2 3 4";
    EXPECT_TRUE(flatSection.find("Row 1: 5 6 7 8") != std::string::npos)
        << "Flat array should print Row 1: 5 6 7 8";
    EXPECT_TRUE(flatSection.find("Row 2: 9 10 11 12") != std::string::npos)
        << "Flat array should print Row 2: 9 10 11 12";
}

TEST(TwoDimensionalArraysTest, FlatArrayFreed) {
    std::string output = captureOutput();
    EXPECT_TRUE(output.find("Flat array freed (just one delete[]!)") != std::string::npos)
        << "Should free the flat array with a single delete[]";
}
