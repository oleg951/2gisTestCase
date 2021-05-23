#include "CommandLineParser.h"
#include "CommandLineExcecutor.h"
#include "CommandLineArgumentConsts.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <codecvt>

using namespace std;

int main(int argc, char**argv)
{
    // Инициализация дерева аргументов с их возможными значениями.
    auto root = std::make_shared<CommandLineArgument>("", "");
    auto fileArg = std::make_shared<CommandLineArgument>(CommandLineConsts::FILE_PATH, "The path to the file");
    fileArg->addChild(std::make_shared<CommandLineArgument>(CommandLineConsts::FIND_WORD, "Finds words in a file"));

    auto mode = std::make_shared<CommandLineArgument>(CommandLineConsts::FILE_MODE, "File mode");
    mode->addAvailableValue(CommandLineConsts::WORD_COUNT_MODE, "Prints the number of words in the file");
    mode->addAvailableValue(CommandLineConsts::CHECKSUMM_MODE, "Prints 32-bit checksum of the file");
    fileArg->addChild(mode);

    root->addChild(fileArg);
    root->addChild(std::make_shared<CommandLineArgument>(CommandLineConsts::HELP, "Show help"));

    try {
        // Парсим командную строку.
        CommandLineParser parser(argc, argv);
        parser.parse(root);

        CommandLineExcecutor executor;
        executor.exec(root);
    }
    catch (const std::exception &exception) {
        cerr << exception.what() << endl;
    }

    return 0;
}
