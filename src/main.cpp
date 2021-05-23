#include "CommandLineParser.h"
#include "CommandLineArgument.h"
#include "CommandLineArgumentConsts.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <codecvt>

using namespace std;

using Argument_t = std::shared_ptr<CommandLineArgument>;

//! Отображает информацию о доступных командах.
void showInfo(Argument_t root) noexcept;
/*!
 * \brief Обрабатывает введеную коммандную строку.
 * \param _root - команды командной строки.
 */
void proccessCommandLine(Argument_t _root);
/*!
 * \brief Обрататывает команду работы с файлом.
 * \param _file - аргумент содержащий путь до файла.
 * \throw std::runtime_error - если не удалось обработать комманду.
 */
void proccessFile(Argument_t _file);
/*!
 * \brief Считывает количетсво слов в файле.
 * \param _fileStream - файловый поток.
 * \param _word - искомое слово.
 * \return Возвращает количество вхождений слова в файл.
 */
int wordCount(ifstream &_fileStream, const string &_word);
/*!
 * \brief Рассчитывает контрольную сумму.
 * \param _fileStream - файловый поток.
 * \return Возвращает контрольную сумму.
 */
uint32_t checksumm(ifstream &_fileStream);
/*!
  * \brief Преобразует строку в нижний регистр.
  * \param _str - исходная строка.
  * \return Возвращает строку в нижнем регистре.
  */
 wstring toLower(wstring_view _str);

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

        proccessCommandLine(root);
    }
    catch (const std::exception &exception) {
        cerr << exception.what() << endl;
    }

    return 0;
}

void showInfo(Argument_t _root) noexcept {
    cout << setw(CommandLineConsts::OUTPIT_WIDE) << left <<_root->arg() << right << _root->description() << endl;
    for (const auto [name, descr]: _root->availableValues()) {
        cout << setw(CommandLineConsts::OUTPIT_WIDE) << left << "  " + name << right << descr << endl;
    }

    for (const auto [name, arg]: _root->children()) {
        showInfo(arg);
    }
}

void proccessCommandLine(Argument_t _root) {
    Argument_t child = _root->child(CommandLineConsts::HELP);

    if (child->hasValue()) {
        cout << "Options:";
        showInfo(_root);
        return;
    }

    Argument_t file = _root->child(CommandLineConsts::FILE_PATH);
    proccessFile(file);
}

void proccessFile(Argument_t _file) {
    if (!_file->hasValue()) {
        throw std::runtime_error("File path not specified");
    }

    string filePath = _file->to<string>();

    ifstream fileStream(filePath, ios_base::in);
    if (!fileStream.is_open()) {
        throw runtime_error("Could not open file");
    }

    Argument_t fileMode = _file->child(CommandLineConsts::FILE_MODE);
    if (!fileMode->hasValue()) {
        throw std::runtime_error("Mode not specified");
    }

    string mode = fileMode->to<string>();;

    if (mode == CommandLineConsts::WORD_COUNT_MODE) {
        Argument_t wordArg = _file->child(CommandLineConsts::FIND_WORD);
        if (!wordArg->hasValue()) {
            throw std::runtime_error("No search word specified");
        }

        string word = wordArg->to<string>();

        cout << "Number of words "<< word <<" in file " << filePath << ": "
             << wordCount(fileStream, word) <<endl;
    }
    else if (mode == CommandLineConsts::CHECKSUMM_MODE) {
        cout << "File checksumm: " << checksumm(fileStream) << endl;
    }
}

int wordCount(ifstream &_fileStream, const string &_word) {
    wstring_convert<std::codecvt_utf8<wchar_t>> wConverter;
    wstring wWord = toLower(wConverter.from_bytes(_word));

    using rxIt_t = wsregex_token_iterator;
    wregex rx(wConverter.from_bytes(CommandLineConsts::WORD_REGEXP));
    int count = 0;
    string line;
    while (getline(_fileStream, line)) {
        wstring wline = toLower(wConverter.from_bytes(line));

        for (rxIt_t it {wline.cbegin(), wline.cend(), rx, 0}; it != rxIt_t{}; ++it) {
            wstring word = (*it);

            if (!word.compare(wWord)) {
                count++;
            }
        }
    }

    return count;
}

uint32_t checksumm(ifstream &_fileStream) {
    uint32_t checksumm = 0;

    while (_fileStream.good() && !_fileStream.eof()) {
        uint32_t word = 0;
        _fileStream.read((char *) &word, sizeof(uint32_t));

        checksumm += word;
    }

    return checksumm;
}

wstring toLower(wstring_view _str) {
    wstring lowerStr;

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
