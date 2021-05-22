#include <iostream>

#include "CommandLineArgument.h"

using namespace std;

void showInfo(const CommandLineArgument &_root) noexcept;

int main(int argc, char*argv[])
{
    cout << argc << endl;
    for (int i = 0; i < argc; ++i) {
        cout << argv[i] << endl;
    }

    uint32_t test = (uint32_t)1000;
    cout << sizeof(uint32_t*) << " " << sizeof (test) << sizeof (char*) << sizeof(char) << endl;

    CommandLineArgument root("Options:", "");
    CommandLineArgument fileArg = CommandLineArgument("-f", "The path to the file");
    fileArg.addChild(CommandLineArgument("-v", "Search word in file"));

    CommandLineArgument mode = CommandLineArgument("-m", "File mode");
    mode.addAvailableValue("words", "Prints value count in file");
    mode.addAvailableValue("checksum", "Prints 32-bit checksum of file");
    fileArg.addChild(mode);

    root.addChild(fileArg);
    root.addChild(CommandLineArgument("-h", "Show help"));

    showInfo(root);

    return 0;
}

void showInfo(const CommandLineArgument &_root) noexcept {

    cout << _root.arg() << "\t" << _root.description() << endl;
    for (const auto [name, descr]: _root.availableValues()) {
        cout << "  " << name << '\t' << descr << endl;
    }

    for (const auto [name, arg]: _root.children()) {
        showInfo(arg);
    }
}
