#ifndef SELBAWARD_RING_HPP
#define SELBAWARD_RING_HPP

#include "Common.hpp"

namespace selbaward {
    class Ring : public sf::Drawable, public sf::Transformable {
        public:
            Ring(float radius = 0.f, float hole = 0.5f, unsigned int numberOfSides = 36u);
            void setRadius(float radius);
            float getRadius() const;
            void setHole(float hole);
	        float getHole() const;
            void setNumberOfSides(unsigned int numberOfSides);
            unsigned int getNumberOfSides() const;
            void setColor(sf::Color color);
	        sf::Color getColor() const;
            void setSectorSize(float sectorSize);
	        float getSectorSize() const;
	        void setSectorOffset(float sectorOffset);
	        float getSectorOffset() const;

        private:
            float m_radius;
            float m_hole;
            float m_sectorSize;
            float m_sectorOffset;
            unsigned int m_numberOfSides;
            sf::Color m_color;
            sf::PrimitiveType m_primitiveType;
            sf::VertexArray m_vertices;

            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	        void priv_updateVertices();
    };
}

#endif