#ifndef zonecircle_h_
#define zonecircle_h_

#include "zonebase.h"

namespace coresystem {

/// Defines a circular zone.
/// _name zone:circle
/// _param <x-center> x position of the center as floating point
/// _param <y-center> y position of the center as floating point
/// _param <radius> radius of the circular area as floating point

#define MATH_PI     3.141592

//# --- circle ---
class zoneCircle : public zonebase {
public:
  zoneCircle (float centerx, float centery, float radius)
  {
    m_radius = radius;
    m_center = sf::Vector2f (centerx,centery);
  }

  virtual sf::Vector2f getPoint ()
  {
    float radius = sf::Randomizer::Random (0.f,m_radius);
    float angle  = sf::Randomizer::Random (0.f,360.f);

    float x = m_center.x + radius*cos(angle);
    float y = m_center.y + radius*sin(angle); 
    return sf::Vector2f (x,y);
    /*
    float   r = sqrt (sf::Randomizer::Random(0.f,1.f));
    float   theta = static_cast<float> (MATH_PI * 2.0 * sf::Randomizer::Random(0.f,1.f));
    return  sf::Vector2f (m_center.x + static_cast<float> (r*cos(theta)), m_center.y + static_cast<float> (r*sin(theta)));
    */
  }

  virtual bool contains (float x, float y)
  {
	    x -= m_center.x;
			y -= m_center.y;
			float distSq = x * x + y * y;
			return (distSq <= m_radius);
  }

  virtual void render (sf::RenderWindow& wnd)
  {
    sf::Shape   rc = sf::Shape::Circle (m_center,m_radius,ZONECOLOR,1.f,ZONECOLOR);
    rc.EnableFill(true);
    wnd.Draw (rc);
  }

protected:
    float         m_radius;
    sf::Vector2f  m_center;
};
}

#endif
