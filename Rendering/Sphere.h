#pragma once
#include <GL/gl.h>

#include <cstddef>

#include <vector>

class Sphere
{
public:
    Sphere(const float radius=1.0f, const int nSlices=8, const int nStacks=8);
    ~Sphere(void) = default;
    size_t getNumVertices() const;
    size_t getNumNormals() const;
    size_t getNumIndices() const;
    const std::vector<GLfloat>& getVertices() const;
    const std::vector<GLfloat>& getNormals() const;
    const std::vector<GLushort>& getIndices() const;

private:
    float radius;
    int nSlices, nStacks;
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLushort> indices;
};
