#include "CommandLineParser.h"
#include "CommandLineExcecutor.h"
#include "CommandLineArgumentConsts.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <codecvt>

#include <boost/program_options.hpp>

using namespace std;

auto commandLineArgument(const char *_argumentFullName) -> string;

auto main(int argc, char**argv) -> int
{
    try {
        CommandLineExcecutor executor;

        boost::program_options::options_description desc("Options");
        desc.add_options()
                (commandLineArgument(CommandLineConsts::HELP).c_str(), "Show help")
                (commandLineArgument(CommandLineConsts::FILE_PATH).c_str(),  boost::program_options::value<string>(),
                 "The path to the file")
                (commandLineArgument(CommandLineConsts::FILE_MODE).c_str(), boost::program_options::value<string>(),
                 "File mode")
                (commandLineArgument(CommandLineConsts::FIND_WORD).c_str(), boost::program_options::value<string>(),
                 "Prints the number of words in the file");


        boost::program_options::variables_map vm;
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
        boost::program_options::notify(vm);

        executor.exec(vm, desc);
    }
    catch (const std::exception &exception) {
        cerr << exception.what() << endl;
    }

    return 0;
}

auto commandLineArgument(const char *_argumentFullName) -> string {
    string arg(_argumentFullName);
    arg.push_back(',');
    arg.push_back(arg[0]);

    return arg;
}
