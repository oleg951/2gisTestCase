#ifndef COMMANDLINEEXCECUTOR_H
#define COMMANDLINEEXCECUTOR_H

#include <istream>
#include <string>
#include <regex>
#include <codecvt>

#include <boost/program_options.hpp>

class IFileStream;

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
     * \param[in] _fileSteamInterface - интерфейс взаимодействия с файлом.
     */
    void exec(const boost::program_options::variables_map &_map,
              const boost::program_options::options_description &_desc,
              IFileStream &_fileSteamInterface);

    /*!
     * \brief Считывает количетсво слов в входном потоке.
     * \param _inputStream - файловый поток.
     * \param _word - искомое слово.
     * \return Возвращает количество вхождений слова в файл.
     */
    [[nodiscard]]
    auto wordCount(std::istream &_inputStream, const std::string &_word) -> int;
    /*!
     * \brief Рассчитывает контрольную сумму входного потока.
     * \param _inputStream - файловый поток.
     * \return Возвращает контрольную сумму.
     */
    [[nodiscard]]
    auto checksumm(std::istream &_inputStream) const -> uint32_t;

private:
    //! Конвертер обычной строки в широкую строку.
    std::wstring_convert<std::codecvt_utf8<wchar_t>> m_wstrConverter;
    //! Регулярное выражение, определяющее слово.
    std::wregex m_wordRx;

    /*!
     * \brief Отображает информацию о доступных командах.
     * \param _desc - описание команд.
     */
    inline void showInfo(const boost::program_options::options_description &_desc) const noexcept;
    /*!
     * \brief Обрататывает команду работы с файлом.
     * \param[in] _map - аргументы командной строки..
     * \throw std::runtime_error - если не удалось обработать комманду.
     */
    void proccessFile(const boost::program_options::variables_map &_map,
                      IFileStream &_fileSteamInterface);
};

#endif // COMMANDLINEEXCECUTOR_H
