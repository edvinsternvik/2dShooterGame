#include "IndexBuffer.h"
#include <GL/glew.h>

unsigned int IndexBuffer::getBufferType() const {
    return GL_ELEMENT_ARRAY_BUFFER;
}
