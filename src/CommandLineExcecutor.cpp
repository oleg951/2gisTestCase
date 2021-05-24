#include "CommandLineExcecutor.h"

#include "CommandLineArgumentConsts.h"

#include <iostream>
#include <iomanip>
#include <codecvt>
#include <regex>

CommandLineExcecutor::CommandLineExcecutor():
    m_wordRx(m_wstrConverter.from_bytes(CommandLineConsts::WORD_REGEXP))
{
}

void CommandLineExcecutor::exec(Argument_t _root)
{
    Argument_t child = _root->child(CommandLineConsts::HELP);

    if (child->hasValue()) {
        std::cout << "Options:";
        showInfo(_root);
        return;
    }

    Argument_t file = _root->child(CommandLineConsts::FILE_PATH);
    proccessFile(file);
}

void CommandLineExcecutor::showInfo(Argument_t _root) const noexcept
{
    std::cout << std::setw(CommandLineConsts::OUTPIT_WIDE) << std::left <<_root->arg() << std::right << _root->description() << std::endl;
    for (const auto [name, descr]: _root->availableValues()) {
        std::cout << std::setw(CommandLineConsts::OUTPIT_WIDE) << std::left << "  " + name << std::right << descr << std::endl;
    }

    for (const auto [name, arg]: _root->children()) {
        showInfo(arg);
    }
}

void CommandLineExcecutor::proccessFile(Argument_t _file)
{
    if (!_file->hasValue()) {
        throw std::runtime_error("File path not specified");
    }

    std::string filePath = _file->to<std::string>();

    std::ifstream fileStream(filePath, std::ios_base::in);
    if (!fileStream.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    Argument_t fileMode = _file->child(CommandLineConsts::FILE_MODE);
    if (!fileMode->hasValue()) {
        throw std::runtime_error("Mode not specified");
    }

    std::string mode = fileMode->to<std::string>();;

    if (mode == CommandLineConsts::WORD_COUNT_MODE) {
        Argument_t wordArg = _file->child(CommandLineConsts::FIND_WORD);
        if (!wordArg->hasValue()) {
            throw std::runtime_error("No search word specified");
        }

        std::string word = wordArg->to<std::string>();
        int count = wordCount(fileStream, word);
        std::cout << "Number of words "<< word <<" in file " << filePath << ": "
                  << count << std::endl;
    }
    else if (mode == CommandLineConsts::CHECKSUMM_MODE) {
        std::cout << "File checksumm: " << checksumm(fileStream) << std::endl;
    }
}

int CommandLineExcecutor::wordCount(std::ifstream &_fileStream, const std::string &_word)
{
    std::wstring wWord = toLower(m_wstrConverter.from_bytes(_word));

    using rxIt_t =  std::wsregex_token_iterator;
    int count = 0;
    std::string line;
    while (getline(_fileStream, line)) {
        std::wstring wline = toLower(m_wstrConverter.from_bytes(line));

        for (rxIt_t it {wline.cbegin(), wline.cend(), m_wordRx, 0}; it != rxIt_t{}; ++it) {
            std::wstring word = (*it);

            if (!word.compare(wWord)) {
                count++;
            }
        }
    }

    return count;
}

uint32_t CommandLineExcecutor::checksumm(std::ifstream &_fileStream) const
{
    uint32_t checksumm = 0;

    while (_fileStream.good() && !_fileStream.eof()) {
        uint32_t word = 0;
        _fileStream.read((char *) &word, sizeof(uint32_t));

        checksumm += word;
    }

    return checksumm;
}

std::wstring CommandLineExcecutor::toLower(std::wstring_view _str) const noexcept
{
    std::wstring lowerStr;

    for (auto ch: _str) {
        if (ch >=  1040 && ch <= 1071) {
            ch += 32;
        }
        else {
            ch = towlower(ch);
        }

        lowerStr += ch;
    }

    return lowerStr;
}
