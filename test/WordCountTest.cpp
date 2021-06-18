#include "Fixture.h"

TEST_F(Fixture, empty_word_count_test) {
    std::string emptyText;
    std::stringstream stream(emptyText);

    ASSERT_EQ(executor.wordCount(stream, "test"), 0);
}

TEST_F(Fixture, find_english_words_count_test) {
    {
        std::stringstream stream(text);
        ASSERT_EQ(executor.wordCount(stream, "inSIDe"), 1);
    }
    {
        std::stringstream stream(text);
        ASSERT_EQ(executor.wordCount(stream, "inside"), 1);
    }
    {
        std::stringstream stream(text);
        ASSERT_EQ(executor.wordCount(stream, "by"), 2);
    }
    {
        std::stringstream stream(text);
        ASSERT_EQ(executor.wordCount(stream, "THE"), 11);
    }
}

TEST_F(Fixture, find_russian_words_count_test) {
    {
        std::stringstream stream(text);
        ASSERT_EQ(executor.wordCount(stream, "мЫ"), 4);
    }
    {
        std::stringstream stream(text);
        ASSERT_EQ(executor.wordCount(stream, "оказались"), 2);
    }
    {
        std::stringstream stream(text);
        ASSERT_EQ(executor.wordCount(stream, "ОКАЗАЛИСЬ"), 2);
    }
    {
        std::stringstream stream(text);
        ASSERT_EQ(executor.wordCount(stream, "На"), 3);
    }
}
