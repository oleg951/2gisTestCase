#include "CommandLineArgumentConsts.h"

#include "Fixture.h"
#include "MockFileStream.h"

using namespace boost::program_options;

using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::_;

TEST_F(Fixture, args_empty_test) {
    MockFileStream fstream;

    ASSERT_THROW(executor.exec({}, desc, fstream), std::runtime_error);
}

TEST_F(Fixture, show_info_args_test) {
    MockFileStream fstream;

    variables_map map;
    map.insert({CommandLineConsts::HELP, {}});

    ASSERT_NO_THROW(executor.exec(map, desc, fstream));
}

TEST_F(Fixture, file_path_is_empty_test) {
    MockFileStream fstream;

    std::string path;
    variables_map map;
    variable_value value(path, false);
    map.insert({CommandLineConsts::FILE_PATH, {}});

    ASSERT_THROW(executor.exec(map, desc, fstream), std::runtime_error);
}

TEST_F(Fixture, could_open_file_test) {
    std::string path;
    MockFileStream fstream;

    EXPECT_CALL(fstream, isOpen()).WillOnce(Return(false));
    EXPECT_CALL(fstream, open(path, _)).Times(1);

    variables_map map;
    variable_value value(path, false);
    map.insert({CommandLineConsts::FILE_PATH, value});

    ASSERT_THROW(executor.exec(map, desc, fstream), std::runtime_error);
}

TEST_F(Fixture, open_file_without_mode_test) {
    std::string path;
    MockFileStream fstream;

    EXPECT_CALL(fstream, isOpen()).WillOnce(Return(true));
    EXPECT_CALL(fstream, open(path, _)).Times(1);

    variables_map map;
    variable_value value(path, false);
    map.insert({CommandLineConsts::FILE_PATH, value});

    ASSERT_THROW(executor.exec(map, desc, fstream), std::runtime_error);
}

TEST_F(Fixture, file_checksumm_test) {
    std::stringstream stream(text);
    std::string path;
    MockFileStream fstream;

    EXPECT_CALL(fstream, ImplicitCast()).WillOnce(ReturnRef(stream));
    EXPECT_CALL(fstream, isOpen()).WillOnce(Return(true));
    EXPECT_CALL(fstream, open(path, _)).Times(1);

    variables_map map;
    variable_value filePathValue(path, false);
    map.insert({CommandLineConsts::FILE_PATH, filePathValue});

    variable_value checksumm(std::string(CommandLineConsts::CHECKSUMM_MODE), false);
    map.insert({CommandLineConsts::FILE_MODE, checksumm});

    ASSERT_NO_THROW(executor.exec(map, desc, fstream));
}

TEST_F(Fixture, open_file_without_search_word_test) {
    std::string path;
    MockFileStream fstream;

    EXPECT_CALL(fstream, isOpen()).WillOnce(Return(true));
    EXPECT_CALL(fstream, open(path, _)).Times(1);

    variables_map map;
    variable_value filePathValue(path, false);
    map.insert({CommandLineConsts::FILE_PATH, filePathValue});

    variable_value wordCount(std::string(CommandLineConsts::WORD_COUNT_MODE), false);
    map.insert({CommandLineConsts::FILE_MODE, wordCount});

    ASSERT_THROW(executor.exec(map, desc, fstream), std::runtime_error);
}

TEST_F(Fixture, search_word_test) {
    std::stringstream stream(text);
    std::string path;
    MockFileStream fstream;

    EXPECT_CALL(fstream, ImplicitCast()).WillOnce(ReturnRef(stream));
    EXPECT_CALL(fstream, isOpen()).WillOnce(Return(true));
    EXPECT_CALL(fstream, open(path, _)).Times(1);

    variables_map map;
    variable_value filePathValue(path, false);
    map.insert({CommandLineConsts::FILE_PATH, filePathValue});

    variable_value wordCount(std::string(CommandLineConsts::WORD_COUNT_MODE), false);
    map.insert({CommandLineConsts::FILE_MODE, wordCount});

    std::string word {"THE"};
    variable_value wordValue(word, false);
    map.insert({CommandLineConsts::FIND_WORD, wordValue});

    ASSERT_NO_THROW(executor.exec(map, desc, fstream));
}

