// Copyright (c) 2023, Pedro Palacios Almendros.

#pragma once

class OutputStream {
public:
    OutputStream &operator<<(char c);
    OutputStream &operator<<(const char* str);
protected:
    virtual void writeChar(char c) = 0;
};
