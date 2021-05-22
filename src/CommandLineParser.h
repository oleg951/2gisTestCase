#ifndef COMMANDARGUMENTPARSER_H
#define COMMANDARGUMENTPARSER_H

#include <map>
#include <vector>
#include <memory>
#include <string_view>

class CommandLineArgument;

//! Класс, представляющий парсер аргументов командной строки.
class CommandLineParser
{
public:
    /*!
     * \brief Конструктор.
     */
    explicit CommandLineParser(int argc, char **argv);

    /*!
     * \brief Парсит аргументы коммандной строки.W
     * \throw std::exception - если не удалось распарсить аргументы командной строки.
     */
    void parse(std::shared_ptr<CommandLineArgument> _root);

private:
    //! Количество аргументов.
    int m_argc;
    //! Аргументы командной строки.
    char **m_argv;

    //! Следующий несчитанные аргумент.
    int m_nextArg;

    /*!
     * \brief Считывает аргумент и значение.
     * \return Возвращает несчитанные аргумент с значением \first - аргумент, \second -  значение.
     * \throw std::invalid_argument - если не удалось считать аргумент.
     */
    std::pair<std::string, std::string> nextArg();
};

#endif // COMMANDARGUMENTPARSER_H
