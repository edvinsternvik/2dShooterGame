#pragma once
#include "Buffer.h"

class IndexBuffer : public Buffer {
public:
    IndexBuffer() = default;

    unsigned int getIndexCount() const { return getDataSize() / sizeof(unsigned int); }

private:
    virtual unsigned int getBufferType() const override;
};
