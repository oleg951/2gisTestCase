#ifndef FIXTURE_H
#define FIXTURE_H

#include "CommandLineExcecutor.h"

#include "gtest/gtest.h"

#include <boost/program_options.hpp>

//! Объект для тестирования.
class Fixture: public ::testing::Test {
protected:
    //! Тестируемый класс.
    static CommandLineExcecutor executor;
    //! Текст для тестирования.
    static std::string text;
    //! Описание параметров командной строкиж
    static boost::program_options::options_description desc;
};

#endif // FIXTURE_H
