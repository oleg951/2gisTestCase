#include "CommandLineParser.h"

#include "CommandLineArgument.h"
#include "CommandLineArgumentConsts.h"

#include <regex>

CommandLineParser::CommandLineParser(int _argc, char **_argv):
    m_argumentRx(CommandLineConsts::FLAG_REGEXP), m_argc(_argc), m_argv(_argv), m_nextArg(1)
{

}

void CommandLineParser::parse(std::shared_ptr<CommandLineArgument> _root)
{
    m_nextArg = 1;

    while (m_nextArg != m_argc) {

        auto [arg, value] = nextArg();
        std::shared_ptr<CommandLineArgument> argument;
        try {
            argument = _root->child(arg);
        }
        catch (...) {
            throw std::invalid_argument(std::string("Unknown argument ")
                                        + std::string(arg));
        }

        auto parent = argument->parent();
        std::shared_ptr<CommandLineArgument> sharedParent = parent.lock();
        if (sharedParent && sharedParent != _root && !sharedParent->hasValue()) {
            throw std::invalid_argument(std::string("No value specified for argument ")
                                        + std::string(sharedParent->arg()));
        }

        if (!argument->setValue(value)) {
            throw std::invalid_argument(std::string("Invalid value ") + value
                                        + std::string(" for argument ") + arg);
        }
    }
}

std::pair<std::string, std::string> CommandLineParser::nextArg()
{
    if (m_nextArg == m_argc) {
        return {std::string(), std::string()};
    }

    std::string flag = m_argv[m_nextArg];
    if (!std::regex_match(flag, m_argumentRx)) {
        throw std::invalid_argument(flag + std::string(" is not argument"));
    }

    m_nextArg++;

    if (m_nextArg == m_argc) {
        return {flag, std::string()};
    }

    std::string value = m_argv[m_nextArg];
    if (std::regex_match(value, m_argumentRx)) {
        return {flag, std::string()};
    }

    m_nextArg++;

    return {flag, value};
}
