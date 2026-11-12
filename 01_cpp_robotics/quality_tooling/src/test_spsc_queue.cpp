#include <gtest/gtest.h>

#include <optional>

#include "../../modern_cpp/src/spsc_ring_buffer.hpp"

struct TestPayload {
    int id;
    double data;
};

constexpr size_t TEST_CAPACITY = 4;

TEST(SpscRingBufferTest, InitiallyEmpty) {
    SpscRingBuffer<TestPayload, TEST_CAPACITY> buffer_;

    EXPECT_FALSE(buffer_.pop());
}

// Test 2: Inserimento e rimozione base
TEST(SpscRingBufferTest, PushAndPopSingleElement) {
    SpscRingBuffer<TestPayload, TEST_CAPACITY> buffer_;
    TestPayload test = {12, 31.46};

    EXPECT_TRUE(buffer_.push(test));

    auto result = buffer_.pop();

    EXPECT_TRUE(result.has_value());

    EXPECT_EQ(result.value().id, test.id);
}

// Test 3: Saturazione della coda
TEST(SpscRingBufferTest, PushUntilFull) {
    SpscRingBuffer<TestPayload, TEST_CAPACITY> buffer_;
    TestPayload test = {13, 43.94};

    for (size_t i = 0; i < TEST_CAPACITY - 1; ++i) {
        EXPECT_TRUE(buffer_.push(test));
    }
    EXPECT_FALSE(buffer_.push(test));
}

// Test 4: Comportamento circolare (Wrap-around)
TEST(SpscRingBufferTest, WrapAroundBehavior) {
    // TODO: Riempi la coda fino al limite
    SpscRingBuffer<TestPayload, TEST_CAPACITY> buffer_;
    TestPayload test = {13, 43.94};

    for (size_t i = 0; i < TEST_CAPACITY - 1; ++i) {
        EXPECT_TRUE(buffer_.push(test));
    }

    // TODO: Estrai 2 elementi con pop()
    EXPECT_TRUE(buffer_.pop().has_value());
    EXPECT_TRUE(buffer_.pop().has_value());
    // TODO: Inserisci altri 2 elementi con push()
    EXPECT_TRUE(buffer_.push({24, 22.04}));
    EXPECT_TRUE(buffer_.push({36, 31.32}));
    // TODO: Verifica che push() abbiano avuto successo (gli indici head/tail hanno fatto il giro)
    auto result = buffer_.pop();
    EXPECT_TRUE(result.has_value());
}