#include <iostream>

#include "CommandLineArgument.h"
#include "CommandLineParser.h"

#include <iomanip>

using namespace std;

void showInfo(std::shared_ptr<CommandLineArgument> root) noexcept;

int main(int argc, char**argv)
{
    // Инициализация дерева аргументов с их возможными значениями.
    auto root = std::make_shared<CommandLineArgument>("", "");
    auto fileArg = std::make_shared<CommandLineArgument>("-f", "The path to the file");
    fileArg->addChild(std::make_shared<CommandLineArgument>("-v", "Search word in file"));

    auto mode = std::make_shared<CommandLineArgument>("-m", "File mode");
    mode->addAvailableValue("words", "Prints value count in file");
    mode->addAvailableValue("checksum", "Prints 32-bit checksum of file");
    fileArg->addChild(mode);

    root->addChild(fileArg);
    root->addChild(std::make_shared<CommandLineArgument>("-h", "Show help"));

    try {
        // Парсим командную строку.
        CommandLineParser parser(argc, argv);
        parser.parse(root);

        if (root->child("-h")->hasValue()) {
            cout << "Options:";
            showInfo(root);
        }
    }
    catch (const std::exception &exception) {
        cout << exception.what() << endl;
    }

    return 0;
}

void showInfo(std::shared_ptr<CommandLineArgument> _root) noexcept {
    cout << setw(20) << left <<_root->arg() << right << _root->description() << endl;
    for (const auto [name, descr]: _root->availableValues()) {
        cout << setw(20) << left << "  " + name << right << descr << endl;
    }

    for (const auto [name, arg]: _root->children()) {
        showInfo(arg);
    }
}
