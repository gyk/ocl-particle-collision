#include "Sphere.h"

#define M_PI        3.14159265358979323846
#define M_PI_2      1.57079632679489661923

#include <cmath>
#include <cassert>


Sphere::Sphere(const float radius, const int nSlices, const int nStacks)
    : radius(radius), nSlices(nSlices), nStacks(nStacks)
{
    vertices.resize(3 * nSlices * nStacks);
    normals.resize(3 * nSlices * nStacks);

    const float R = 1.0f / (nSlices - 1);
    const float S = 1.0f / (nStacks - 1);

    auto v = vertices.begin();
    auto n = normals.begin();
    
    for (int r=0; r<nSlices; r++) {
        for (int s=0; s<nStacks; s++) {
            float const y = (float)(sin(-M_PI_2 + M_PI * r * R));
            float const x = (float)(cos(2*M_PI * s * S) * sin(M_PI * r * R));
            float const z = (float)(sin(2*M_PI * s * S) * sin(M_PI * r * R));

            *v++ = x * radius;
            *v++ = y * radius;
            *v++ = z * radius;

            *n++ = x;
            *n++ = y;
            *n++ = z;
        }
    }

    indices.resize(6 * nSlices * nStacks);
    auto i = indices.begin();
    for (int r=0; r<nSlices; r++) {
        for (int s=0; s<nStacks; s++) {
            *i++ = r * nStacks + s;
            *i++ = (r + 1) * nStacks + s;
            *i++ = (r + 1) * nStacks + (s + 1);
            *i++ = r * nStacks + s;
            *i++ = (r + 1) * nStacks + (s + 1);
            *i++ = r * nStacks + (s + 1);
        }
    }

    assert(vertices.size() == this->getNumVertices() * 3);
    assert(normals.size() == this->getNumNormals() * 3);
    assert(indices.size() == this->getNumIndices());
}

size_t Sphere::getNumVertices() const
{
    return nSlices * nStacks;
}

size_t Sphere::getNumNormals() const
{
    return nSlices * nStacks;
}

size_t Sphere::getNumIndices() const
{
    return 6 * nSlices * nStacks;
}

const std::vector<GLfloat>& Sphere::getVertices() const
{
    return vertices;
}

const std::vector<GLfloat>& Sphere::getNormals() const
{
    return normals;
}

const std::vector<GLushort>& Sphere::getIndices() const
{
    return indices;
}
