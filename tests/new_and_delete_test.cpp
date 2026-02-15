#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "new_and_delete.h"

// Helper: capture stdout from newAndDelete()
static std::string captureOutput() {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    newAndDelete();
    std::cout.rdbuf(oldCout);
    return buffer.str();
}

// ==================== 1. Heap Arrays with new[] ====================

TEST(NewAndDeleteTest, HeapArrayCreated) {
    std::string output = captureOutput();
    EXPECT_TRUE(output.find("Heap array: 10 20 30 40 50") != std::string::npos)
        << "Should allocate a heap array, fill it with 10-50, and print all elements";
}

// ==================== 2. Freeing Arrays with delete[] ====================

TEST(NewAndDeleteTest, ArrayMemoryFreed) {
    std::string output = captureOutput();
    EXPECT_TRUE(output.find("Array memory freed and pointer set to nullptr") != std::string::npos)
        << "Should free the heap array with delete[] and set pointer to nullptr";
}

// ==================== 3. Smart Pointers: unique_ptr ====================

TEST(NewAndDeleteTest, SmartValueCreated) {
    std::string output = captureOutput();
    EXPECT_TRUE(output.find("Smart value: 99") != std::string::npos)
        << "Should create a unique_ptr<int> with value 99 and dereference it";
}

TEST(NewAndDeleteTest, SmartArrayCreated) {
    std::string output = captureOutput();
    EXPECT_TRUE(output.find("Smart array: 100 200 300") != std::string::npos)
        << "Should create a unique_ptr to an array of 3 ints and print them";
}

// ==================== 4. Smart Pointers: shared_ptr ====================

TEST(NewAndDeleteTest, SharedPtrValue) {
    std::string output = captureOutput();
    EXPECT_TRUE(output.find("sharedA value: 77") != std::string::npos)
        << "Should create a shared_ptr with value 77 and print through sharedA";
    EXPECT_TRUE(output.find("sharedB value: 77") != std::string::npos)
        << "Should copy sharedA to sharedB and print through sharedB";
}

TEST(NewAndDeleteTest, SharedPtrRefCount) {
    std::string output = captureOutput();
    EXPECT_TRUE(output.find("Reference count: 2") != std::string::npos)
        << "Should show reference count of 2 after copying a shared_ptr";
}
