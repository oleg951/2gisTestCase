#ifndef COMMANDLINEEXCECUTOR_H
#define COMMANDLINEEXCECUTOR_H

#include <fstream>
#include <string>
#include <regex>
#include <codecvt>

#include <boost/program_options.hpp>

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
     * \param[in] _map - аргументы командной строки.
     * \param[in] _desc - описание аргументов командной строки.
     */
    void exec(const boost::program_options::variables_map &_map,
              const boost::program_options::options_description &_desc);

private:
    //! Конвертер обычной строки в широкую строку.
    std::wstring_convert<std::codecvt_utf8<wchar_t>> m_wstrConverter;
    //! Регулярное выражение, определяющее слово.
    std::wregex m_wordRx;

    //! Отображает информацию о доступных командах.
    inline void showInfo(const boost::program_options::options_description &_desc) const noexcept;
    /*!
     * \brief Обрататывает команду работы с файлом.
     * \param[in] _map - аргументы командной строки..
     * \throw std::runtime_error - если не удалось обработать комманду.
     */
    void proccessFile(const boost::program_options::variables_map &_map);
    /*!
     * \brief Считывает количетсво слов в файле.
     * \param _fileStream - файловый поток.
     * \param _word - искомое слово.
     * \return Возвращает количество вхождений слова в файл.
     */
    [[nodiscard]]
    auto wordCount(std::ifstream &_fileStream, const std::string &_word) -> int;
    /*!
     * \brief Рассчитывает контрольную сумму.
     * \param _fileStream - файловый поток.
     * \return Возвращает контрольную сумму.
     */
    [[nodiscard]]
    auto checksumm(std::ifstream &_fileStream) const -> uint32_t;
    /*!
      * \brief Преобразует строку в нижний регистр.
      * \param _str - исходная строка.
      * \return Возвращает строку в нижнем регистре.
      */
    [[nodiscard]]
    auto toLower(std::wstring_view _str) const noexcept -> std::wstring;

};

#endif // COMMANDLINEEXCECUTOR_H
