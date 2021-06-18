#ifndef MOCKCOMMANDLINEEXECUTOR_H
#define MOCKCOMMANDLINEEXECUTOR_H

#include "IFileStream.h"

#include "gmock/gmock.h"

class MockFileStream: public IFileStream {
public:
    MOCK_METHOD(void, open, (std::string_view, std::ios_base::openmode), (override));
    MOCK_METHOD(bool, isOpen, (), (const, override));
    MOCK_METHOD(std::istream&, ImplicitCast, (), (const));

    operator std::istream&() override {
        return ImplicitCast();
    }
};

#endif // MOCKCOMMANDLINEEXECUTOR_H
