#include "CommandLineExcecutor.h"

#include "CommandLineArgumentConsts.h"

#include <iostream>

CommandLineExcecutor::CommandLineExcecutor():
    m_wordRx(m_wstrConverter.from_bytes(CommandLineConsts::WORD_REGEXP))
{
}

void CommandLineExcecutor::exec(const boost::program_options::variables_map &_map,
                                const boost::program_options::options_description &_desc)
{
    if (_map.contains(CommandLineConsts::HELP)) {
        showInfo(_desc);
    }
    else if (_map.contains(CommandLineConsts::FILE_PATH)) {
        proccessFile(_map);
    }
}

inline void CommandLineExcecutor::showInfo(const boost::program_options::options_description &_desc) const noexcept
{
    std::cout << _desc;
}

void CommandLineExcecutor::proccessFile(const boost::program_options::variables_map &_map)
{
    try {
        std::string filePath = _map[CommandLineConsts::FILE_PATH].as<std::string>();

        std::ifstream fileStream(filePath);
        if (!fileStream.is_open()) {
            throw std::runtime_error(std::string("Could not open file: ").append(filePath));
        }

        if (!_map.contains(CommandLineConsts::FILE_MODE)) {
            throw std::runtime_error("File mode not specified");
        }

        std::string mode = _map[CommandLineConsts::FILE_MODE].as<std::string>();
        if (mode == CommandLineConsts::CHECKSUMM_MODE) {
            std::cout << checksumm(fileStream) << std::endl;
        }
        else if (mode == CommandLineConsts::WORD_COUNT_MODE) {
            if (!_map.contains(CommandLineConsts::FIND_WORD)) {
                throw std::runtime_error("No search word specified");
            }

            std::cout << wordCount(fileStream, _map[CommandLineConsts::FIND_WORD].as<std::string>()) << std::endl;
        }
        else {
            throw std::runtime_error(std::string("Unknow file mode: ").append(mode));
        }
    }
    catch (const std::exception &exception) {
        throw std::runtime_error(std::string("Failed to process file:\n").append(exception.what()));
    }
}

auto CommandLineExcecutor::wordCount(std::ifstream &_fileStream, const std::string &_word) -> int
{
    std::wstring wWord = toLower(m_wstrConverter.from_bytes(_word));

    using rxIt_t =  std::wsregex_token_iterator;
    int count = 0;
    std::string line;
    while (getline(_fileStream, line)) {
        std::wstring wline = toLower(m_wstrConverter.from_bytes(line));

        for (rxIt_t it {wline.cbegin(), wline.cend(), m_wordRx, 0}; it != rxIt_t{}; ++it) {
            std::wstring word = (*it);
			
            if (word == wWord) {
                count++;
            }
        }
    }

    return count;
}

auto CommandLineExcecutor::checksumm(std::ifstream &_fileStream) const -> uint32_t
{
    constexpr unsigned long sizeOf = sizeof(uint32_t);
    uint32_t checksumm = 0;

    std::array<char, sizeOf> arr {0};
    uint32_t convertedValue {0};
    while (_fileStream.good() && !_fileStream.eof()) {
        _fileStream.read(&arr[0], sizeOf);

        std::memcpy(&convertedValue, &arr, sizeOf);
        checksumm += convertedValue;
    }

    return checksumm;
}

auto CommandLineExcecutor::toLower(std::wstring_view _str) const noexcept -> std::wstring
{
    std::wstring lowerStr;

    for (auto ch: _str) {
        if (ch >=  CommandLineConsts::RUS_FIRST_LETTER && ch <= CommandLineConsts::RUS_LAST_LETTER) {
            ch += CommandLineConsts::RUS_LOWERCASE_LETTER_OFFSET;
        }
        else {
            ch = towlower(ch);
        }

        lowerStr += ch;
    }

    return lowerStr;
}
