#ifndef COMMANDLINEARGUMENTCONSTS_H
#define COMMANDLINEARGUMENTCONSTS_H

#include <string>

//! Константы.
namespace CommandLineConsts {
    //! Аргумент, определяющий путь до файла.
    constexpr const char *FILE_PATH {"-f"};
    //! Аргумент, определяющий искомое слово.
    constexpr const char *FIND_WORD {"-v"};
    //! Аргумент, определяющий режим работы.
    constexpr const char *FILE_MODE {"-m"};
    //! Аргумент, определяющий режим подсчета слов.
    constexpr const char *WORD_COUNT_MODE {"words"};
    //! Аргумент, определяющий режим рассчета контрольной суммы.
    constexpr const char *CHECKSUMM_MODE {"checksumm"};
    //! Аргумент, определяющий вывод информации об аргументах.
    constexpr const char *HELP {"-h"};

    //! Регулярное выражение, определяющее аргумент.
    constexpr const char *FLAG_REGEXP {"-[a-zA-Z]+"};
    //! Регулярное выражение, определяющее слово.
    constexpr const char *WORD_REGEXP {"[a-zA-Zа-яА-Я]+"};

    //! Ширина вывода информации об аргументах.
    constexpr const int OUTPIT_WIDE {20};
};

#endif // COMMANDLINEARGUMENTCONSTS_H
