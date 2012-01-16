#ifndef stop_h_
#define stop_h_

#include <SFML/Graphics.hpp>
#include "actionbase.h"

/// Defines a stop action. Can only be used as action zone.
/// _name action:stop
/// _param <inside> Stop if particle is within or not within the zone. Valid values are yes or no

namespace coresystem {

  //# can only be used with a zone (actionzone)
  class stop : public actionbase  { 
    public:
      stop (bool inside)
      {
        m_particle_inside = inside;
      }

      stop (const char* lpFile, bool inside)
      {
        if (m_image.LoadFromFile (lpFile) == false) {
          throw ("cannot open bitmap for stop action");
        }
        m_particle_inside = inside;
      }

      virtual void update (emitter* em, particle* p, float dt)
      {
        if (this->getZone()) {
          if (this->getZone ()->contains (p->position.x,p->position.y) == m_particle_inside) {
            //# set velocity to zero
            p->velocity = sf::Vector2f(0.f,0.f);
          }
        }
        //# no zone means using a bitmap as mask
        else {
          if (m_image.GetWidth()>0) {
            sf::Sprite spr (m_image);
            if (WithinTransparency(spr,p->position)==false) {
              //# set velocity to zero
              p->velocity = sf::Vector2f(0.f,0.f);
            }
          }
          else {
            throw ("no zone and no bitmap mask for action stop");
          }
        }
      }

  private:
      bool WithinTransparency (const sf::Sprite& Object1, sf::Vector2f objectPos)
      { 
      // null reference happened
        sf::Vector2f      pos = Object1.GetPosition();

        if (objectPos.y >= pos.y) {
          //# now check pixel transparency in object1 for that position
          int alpha = Object1.GetPixel (static_cast<int> (objectPos.x-pos.x), static_cast<int> (objectPos.y-pos.y)).a;
          if (alpha != 0) {
            return false;
          }
        }
        return true;
      }

  protected:
    sf::Image       m_image;
    bool            m_particle_inside;
  };
}

#endif
