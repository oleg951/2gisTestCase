#include "FileStream.h"


FileStream::~FileStream()
{
    m_fileStream.close();
}

void FileStream::open(std::string_view _name, std::ios_base::openmode _mode)
{
    m_fileStream.open(_name.data(), _mode);
}

auto FileStream::isOpen() const -> bool
{
    return m_fileStream.is_open();
}

FileStream::operator std::istream &()
{
    return m_fileStream;
}
