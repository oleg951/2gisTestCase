#ifndef COMMANDLINEEXCECUTOR_H
#define COMMANDLINEEXCECUTOR_H

#include "CommandLineArgument.h"

#include <fstream>
#include <string>
#include <regex>
#include <codecvt>

using Argument_t = std::shared_ptr<CommandLineArgument>;

//! Класс выполняющий коммануд из командной строки.
class CommandLineExcecutor
{
public:
    /*!
     * \brief Конструктор.
     */
    explicit CommandLineExcecutor();

    /*!
     * \brief Выаолняет команду из командной строки.
     * \param _root - аргументы коммандной строки.
     */
    void exec(Argument_t _root);

private:
    //! Конвертер обычной строки в широкую строку.
    std::wstring_convert<std::codecvt_utf8<wchar_t>> m_wstrConverter;
    //! Регулярное выражение, определяющее слово.
    std::wregex m_wordRx;


    //! Отображает информацию о доступных командах.
    void showInfo(Argument_t _root) const noexcept;
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
    int wordCount(std::ifstream &_fileStream, const std::string &_word);
    /*!
     * \brief Рассчитывает контрольную сумму.
     * \param _fileStream - файловый поток.
     * \return Возвращает контрольную сумму.
     */
    uint32_t checksumm(std::ifstream &_fileStream) const;
    /*!
      * \brief Преобразует строку в нижний регистр.
      * \param _str - исходная строка.
      * \return Возвращает строку в нижнем регистре.
      */
    std::wstring toLower(std::wstring_view _str) const noexcept;

};

#endif // COMMANDLINEEXCECUTOR_H
