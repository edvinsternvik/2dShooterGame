#pragma once
#include "VertexBuffer.h"
#include "VertexArrayObject.h"
#include "IndexBuffer.h"

static float vertexData[] {
    0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 1.0, 0.0,
    1.0, 1.0, 1.0, 1.0,
    0.0, 1.0, 0.0, 1.0
};

static unsigned int indexData[] {
    0, 1, 2, 2, 3, 0
};

class SpriteData {
public:
    SpriteData() : vao(), vbo({VertexAttribute(2, VertexAttributeType::FLOAT, false), VertexAttribute(2, VertexAttributeType::FLOAT, false)}), ibo() {
        vao.bind();

        vbo.setData(vertexData, sizeof(vertexData), BufferDataUsage::STATIC_DRAW);
        vbo.bind();

        ibo.setData(indexData, sizeof(indexData), BufferDataUsage::STATIC_DRAW);
        ibo.bind();

        vao.unbind();
    }

public:
    VertexArrayObject vao;
    VertexBuffer vbo;
    IndexBuffer ibo;
};

