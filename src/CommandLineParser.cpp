#include "CommandLineParser.h"

#include "CommandLineArgument.h"

#include <regex>

CommandLineParser::CommandLineParser(int _argc, char **_argv):
    m_argc(_argc), m_argv(_argv), m_nextArg(1)
{

}

void CommandLineParser::parse(std::shared_ptr<CommandLineArgument> _root)
{
    try {
        m_nextArg = 1;

        while (m_nextArg != m_argc) {

           auto [arg, value] = nextArg();
           auto argument = _root->child(arg);

           auto parent = argument->parent();
           std::shared_ptr<CommandLineArgument> sharedParent = parent.lock();
           if (sharedParent && sharedParent != _root && !sharedParent->hasValue()) {
               throw std::invalid_argument(std::string("No value specified for argument ")
                                            + std::string(sharedParent->arg()));
           }

           argument->setValue(value);
        }
    }
    catch (std::exception &_exception) {
        throw std::invalid_argument(_exception.what());
    }
}

std::pair<std::string, std::string> CommandLineParser::nextArg()
{
    std::regex flagRegex("-[a-zA-Z]+");
    if (m_nextArg == m_argc) {
        return std::make_pair(std::string(), std::string());
    }

    std::string flag = m_argv[m_nextArg];
    if (!std::regex_match(flag, flagRegex)) {
        throw std::invalid_argument(flag + std::string(" is not argument"));
    }

    m_nextArg++;

    if (m_nextArg == m_argc) {
        return std::make_pair(flag, std::string());
    }

    std::string value = m_argv[m_nextArg];
    if (std::regex_match(value, flagRegex)) {
        return std::make_pair(flag, std::string());
    }

    m_nextArg++;

    return std::make_pair(flag, value);
}
