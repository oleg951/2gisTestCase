#ifndef FILESTREAM_H
#define FILESTREAM_H

#include "IFileStream.h"

#include <fstream>

class FileStream: public IFileStream
{
public:
    /*!
     * \brief Деструктор.
     */
    ~FileStream();
    /*!
     * \brief Открывает файловый поток.
     * \param _name - наименование файла.
     * \param mode - режим работы
     */
    void open(std::string_view _name, std::ios_base::openmode _mode) override;
    /*!
     * \brief Возвращает признак открыторго файла.
     * \return Возвращает true если файл открыт, иначе false.
     */
    [[nodiscard]]
    virtual auto isOpen() const -> bool override;

    /*!
     * \brief Оператор неявного преобразования файловым потоком в входной поток.
     */
    operator std::istream&() override;

private:
    //! Файловый поток.
    std::fstream m_fileStream;
};
#endif // FILESTREAM_H
