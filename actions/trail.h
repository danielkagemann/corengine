#ifndef trail_h_
#define trail_h_

#include "actionbase.h"
#include "../emitters/emitter.h"

/// Make clones of movine particles at current position. The clones cannot move
/// _name action:trail
/// _param <seconds> time in seconds as float when recent moving particles are cloned
/// _param <x-offset> offset in pixel to move the cloned particle in x-direction as float [optional]
/// _param <y-offset> offset in pixel to move the cloned particle in y-direction as float [optional]

namespace coresystem {
  class trail : public actionbase {
  public:

    trail ()
    {
      m_rate = 1.f;
      m_offset = sf::Vector2f (0.f,0.f);
      m_timer.Reset ();
    }

    trail (float r, float x=0.f, float y=0.f)
    {
      m_rate = r;
      m_offset.x = x;
      m_offset.y = y;

      m_timer.Reset ();
    }

    virtual void update (emitter* em, particle* p, float dt)
    {
      if (p->isDead == false) {
      
        //# if interval expired
        if (m_timer.GetElapsedTime () >= m_rate) {
        	//# take not only the given particle but ALL from emitter
          int	len = static_cast<int> (em->getParticles ().size());
          for (int i = 0; i < len; i++) {

            //# check if particle is moving
            if (!(em->getParticles ()[i]->velocity.x == 0.f && em->getParticles ()[i]->velocity.y == 0.f)) {
              
              //# define the zone where it takes places (if defined)
              if (zoneimpact(em->getParticles ()[i]->position)==false) {
                return;
              }
              //# make clone
              particle    *clone = new particle (em->getParticles ()[i]);
              
              //# remove velocity
              clone->velocity.x = clone->velocity.y = 0.f;

              //# remove path information
              clone->usepath = false;
              
              //# some offset
              clone->position.x += m_offset.x;
              clone->position.y += m_offset.y;
              
              //# add to emitter
              em->getParticles().push_back (clone);
            }              
          }
          //# reset timer
          m_timer.Reset();
        }
      }
    }
  protected:
    sf::Clock     m_timer;
    sf::Vector2f  m_offset;
    float         m_rate;
  };
}

#endif
