#ifndef IFILESTREAM_H
#define IFILESTREAM_H

#include <ios>
#include <iosfwd>

//! Интерфейс взаимодействия с файловым потоком.
class IFileStream {
public:
    /*!
     * \brief Деструктор.
     */
    virtual ~IFileStream() {};
    /*!
     * \brief Открывает файловый поток.
     * \param _name - наименование файла.
     * \param mode - режим работы
     */
    virtual void open(std::string_view _name,
                      std::ios_base::openmode _mode = std::ios_base::in | std::ios_base::out) = 0;
    /*!
     * \brief Возвращает признак открыторго файла.
     * \return Возвращает true если файл открыт, иначе false.
     */
    [[nodiscard]]
    virtual auto isOpen() const -> bool = 0;
    /*!
     * \brief Оператор неявного преобразования файловым потоком в входной поток.
     */
    virtual operator std::istream&() = 0;
};
#endif // IFILESTREAM_H
