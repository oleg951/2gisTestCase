#ifndef COMMANDARGUMENTPARSER_H
#define COMMANDARGUMENTPARSER_H

#include <map>
#include <vector>
#include <string_view>

class CommandLineArgument;

//! Класс, представляющий парсер аргументов командной строки.
class CommandLineParser
{
public:
    /*!
     * \brief Состояния парсера.
     */
    enum class State {
        Command,    ///< Команда.
        Value,      ///< Значение.

        UnknowState ///< Неизвестное состояние.
    };
    /*!
     * \brief Конструктор.
     */
    explicit CommandLineParser();

    /*!
     * \brief Парсит аргументы коммандной строки.
     * \param argc - количетсво аргументов.
     * \param argv - аргументы.
     * \throw std::exception - если не удалось распарсить аргументы командной строки.
     * \return Ассоциированный список агрументов коммандной строки с значением.
     */
    void parse(int argc, char **argv, CommandLineArgument &_root);

private:

    //! Текущее состояние.
    State m_currState;
    //! Предыдущее состояние.
    State m_prevState;
};

#endif // COMMANDARGUMENTPARSER_H
