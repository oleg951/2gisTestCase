#include "CommandLineExcecutor.h"

#include "FileStream.h"
#include "CommandLineArgumentConsts.h"

#include <iostream>

CommandLineExcecutor::CommandLineExcecutor():
    m_wordRx(m_wstrConverter.from_bytes(CommandLineConsts::WORD_REGEXP))
{
}

void CommandLineExcecutor::exec(const boost::program_options::variables_map &_map,
                                const boost::program_options::options_description &_desc,
                                IFileStream &_fileSteamInterface)
{
    if (_map.count(CommandLineConsts::HELP) != 0) {
        showInfo(_desc);
    }
    else if (_map.count(CommandLineConsts::FILE_PATH) != 0) {
        proccessFile(_map, _fileSteamInterface);
    }
    else {
        throw std::runtime_error("Unknow commands");
    }
}

inline void CommandLineExcecutor::showInfo(const boost::program_options::options_description &_desc) const noexcept
{
    std::cout << _desc;
}

void CommandLineExcecutor::proccessFile(const boost::program_options::variables_map &_map,
                                        IFileStream &_fileSteamInterface)
{
    try {
        std::string filePath = _map[CommandLineConsts::FILE_PATH].as<std::string>();

        _fileSteamInterface.open(filePath);
        if (!_fileSteamInterface.isOpen()) {
            throw std::runtime_error(std::string("Could not open file: ").append(filePath));
        }

        if (_map.count(CommandLineConsts::FILE_MODE) == 0) {
            throw std::runtime_error("File mode not specified");
        }

        std::string mode = _map[CommandLineConsts::FILE_MODE].as<std::string>();
        if (mode == CommandLineConsts::CHECKSUMM_MODE) {
            std::cout << checksumm(_fileSteamInterface) << std::endl;
        }
        else if (mode == CommandLineConsts::WORD_COUNT_MODE) {
            if (_map.count(CommandLineConsts::FIND_WORD) == 0) {
                throw std::runtime_error("No search word specified");
            }

            std::cout << wordCount(_fileSteamInterface, _map[CommandLineConsts::FIND_WORD].as<std::string>()) << std::endl;
        }
        else {
            throw std::runtime_error(std::string("Unknow file mode: ").append(mode));
        }
    }
    catch (const std::exception &exception) {
        throw std::runtime_error(std::string("Failed to process file:\n").append(exception.what()));
    }
}

auto CommandLineExcecutor::wordCount(std::istream &_inputStream, const std::string &_word) -> int
{
    std::wstring wWord = toLower(m_wstrConverter.from_bytes(_word));

    using rxIt_t =  std::wsregex_token_iterator;
    int count = 0;
    std::string line;
    while (getline(_inputStream, line)) {
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

auto CommandLineExcecutor::checksumm(std::istream &_inputStream) const -> uint32_t
{
    constexpr unsigned long sizeOf = sizeof(uint32_t);
    uint32_t checksumm = 0;

    std::array<char, sizeOf> arr {0};
    uint32_t convertedValue {0};
    while (_inputStream.good() && !_inputStream.eof()) {
        _inputStream.read(&arr[0], sizeOf);

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
