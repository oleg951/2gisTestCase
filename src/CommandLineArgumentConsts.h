#ifndef COMMANDLINEARGUMENTCONSTS_H
#define COMMANDLINEARGUMENTCONSTS_H

#include <string>

//! Константы.
namespace CommandLineConsts {
    //! Аргумент, определяющий путь до файла.
    constexpr const char *FILE_PATH {"filePath"};
    //! Аргумент, определяющий искомое слово.
    constexpr const char *FIND_WORD {"word"};
    //! Аргумент, определяющий режим работы.
    constexpr const char *FILE_MODE {"mode"};
    //! Аргумент, определяющий режим подсчета слов.
    constexpr const char *WORD_COUNT_MODE {"words"};
    //! Аргумент, определяющий режим рассчета контрольной суммы.
    constexpr const char *CHECKSUMM_MODE {"checksumm"};
    //! Аргумент, определяющий вывод информации об аргументах.
    constexpr const char *HELP {"help"};

    //! Регулярное выражение, определяющее слово.
    constexpr const char *WORD_REGEXP {"[a-zA-Zа-яА-Я]+"};

    //! Значение русской А в кодировке UTF.
    constexpr const int RUS_FIRST_LETTER {1040};
    //! Значение русской Я в кодировке UTF.
    constexpr const int RUS_LAST_LETTER {1071};
    //! Смещение русских строчным букв относительно заглавных.
    constexpr const int RUS_LOWERCASE_LETTER_OFFSET {32};
}

#endif // COMMANDLINEARGUMENTCONSTS_H
