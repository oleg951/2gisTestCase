#include "Fixture.h"

TEST_F(Fixture, empty_file_checksumm_test) {
    std::string emptyText;
    std::stringstream stream(emptyText);

    ASSERT_EQ(executor.checksumm(stream), 0);
}

TEST_F(Fixture, one_letter_checksumm_test) {
    std::string text("A");
    std::stringstream stream(text);

    ASSERT_EQ(executor.checksumm(stream), 65);
}

TEST_F(Fixture, text_checksumm_test) {
    std::string text("Aasdasdas");
    std::stringstream stream(text);

    ASSERT_EQ(executor.checksumm(stream), 658262037);
}
