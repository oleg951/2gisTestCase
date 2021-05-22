#include "CommandLineArgument.h"

#include <sstream>

CommandLineArgument::CommandLineArgument(std::string_view _arg, std::string_view _description):
    m_arg(_arg), m_description(_description), m_parent(nullptr)
{

}

void CommandLineArgument::setValue(const std::string &_value)
{
    if (!m_availableValues.empty() && m_availableValues.contains(_value)) {
        throw std::out_of_range("the value of the command line argument is out of range");
    }

    m_value = _value;
}

bool CommandLineArgument::hasValue() const noexcept
{
    return m_value.has_value();
}

bool CommandLineArgument::addChild(CommandLineArgument &&_child) noexcept
{
    const auto [it, success] = m_children.insert(std::make_pair(_child.arg(), std::move(_child)));
    if (success) {
        it->second.setParent(this);
    }

    return success;
}

bool CommandLineArgument::addChild(const CommandLineArgument &_child) noexcept
{
    auto [it, success] = m_children.insert(std::make_pair(_child.arg(), _child));
    if (success) {
        it->second.setParent(this);
    }

    return success;
}

CommandLineArgument &CommandLineArgument::child(const std::string &_arg)
{
    if (m_children.contains(_arg)) {
        return m_children.at(_arg);
    }

    for (auto ch: m_children) {
        return  ch.second.child(_arg);
    }

    throw std::out_of_range("the argument of the command line argument is out of range");
}

const std::map<std::string, CommandLineArgument> &CommandLineArgument::children() const noexcept
{
    return  m_children;
}

CommandLineArgument *CommandLineArgument::parent() const noexcept
{
    return m_parent;
}

std::string_view CommandLineArgument::arg() const
{
    return  m_arg;
}

void CommandLineArgument::setArg(std::string_view _arg)
{
    m_arg = _arg;
}

std::string_view CommandLineArgument::description() const
{
    return m_description;
}

void CommandLineArgument::setDescription(std::string_view _description)
{
    m_description = _description;
}

void CommandLineArgument::addAvailableValue(std::string_view _value,
                                            std::string_view _description) noexcept
{
    m_availableValues.insert(std::make_pair(_value, _description));
}

const std::map<std::string, std::string> &CommandLineArgument::availableValues() const noexcept
{
    return m_availableValues;
}

void CommandLineArgument::setParent(CommandLineArgument *_parent)
{
    m_parent = _parent;
}

void Converter::operator()(const std::string &_in, int &_out) const
{
    _out = std::stoi(_in);
}

void Converter::operator()(const std::string &_in, double &_out) const
{
    _out = std::stod(_in);
}

void Converter::operator()(const std::string &_in, bool &_out) const
{
    std::istringstream in(_in);
    in >> std::boolalpha >> _out;
}
