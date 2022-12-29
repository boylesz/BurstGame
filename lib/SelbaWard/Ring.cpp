#define _USE_MATH_DEFINES

#include "Ring.hpp"
#include <math.h>

const float pi = M_PI;

namespace selbaward {
    Ring::Ring(const float radius, const float hole, const unsigned int numberOfSides) {
        m_radius = radius;
        m_hole = hole;
        m_sectorSize = 1.f;
	    m_sectorOffset = 0.f;
	    m_numberOfSides = numberOfSides;
	    m_color = sf::Color::White;
        m_vertices.setPrimitiveType(sf::TriangleStrip);

        priv_updateVertices();
    }

    void Ring::setRadius(const float radius) {
        m_radius = radius;
        priv_updateVertices();
    }

    float Ring::getRadius() const {
        return m_radius;
    }

    void Ring::setHole(const float hole) {
        m_hole = hole;
        priv_updateVertices();
    }

    float Ring::getHole() const {
        return m_hole;
    }

    void Ring::setNumberOfSides(const unsigned int numberOfSides) {
        m_numberOfSides = numberOfSides;
        priv_updateVertices();
    }

    unsigned int Ring::getNumberOfSides() const {
        return m_numberOfSides;
    }

    void Ring::setColor(const sf::Color color) {
        m_color = color;
        for (unsigned int i = 0; i < m_vertices.getVertexCount(); i++)
            m_vertices[i].color = color;
    }

    sf::Color Ring::getColor() const {
        return m_color;
    }

    void Ring::setSectorSize(const float sectorSize) {
        m_sectorSize = sectorSize;
        priv_updateVertices();
    }

    float Ring::getSectorSize() const {
        return m_sectorSize;
    }

    void Ring::setSectorOffset(const float sectorOffset) {
        m_sectorOffset = sectorOffset;
        priv_updateVertices();
    }

    float Ring::getSectorOffset() const {
        return m_sectorOffset;
    }

    // PRIVATE

    void Ring::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();

        if (m_vertices.getVertexCount() > 0)
            target.draw(m_vertices, states);
    }

    void Ring::priv_updateVertices() {
        const float sectorOffset = 2.f * pi * m_sectorOffset; // Map offset to range
        const float sectorSize = 2.f * pi * m_sectorSize; // Map sector size to range
        m_vertices.resize(m_numberOfSides * 2 + 1);
        
        const float angleStep = pi / m_numberOfSides;

        for (int i = 0; i <= m_numberOfSides * 2; i++) {
            const float angle = sectorOffset + sectorSize * i / 2 / m_numberOfSides;
            m_vertices[i].position = sf::Vector2f(cos(angle) * m_radius * (i % 2 == 0 ? 1.f : m_hole), sin(angle) * m_radius * (i % 2 == 0 ? 1.f : m_hole));
            m_vertices[i].color = m_color;
        }
    }
}