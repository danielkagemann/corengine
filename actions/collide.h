#ifndef collision_h_
#define collision_h_

#include "actionbase.h"
#include "../emitters/emitter.h"

/// Define if particles should collide.
/// _name action:collide

namespace coresystem {
  class collide : public actionbase {
  public:
    collide ()
    {}

    virtual void update (emitter* em, particle* p, float dt)
    {
      if (p->isDead == false) {

        //# check the other particles
        for (int i = 0; i < static_cast<int> (em->getParticles().size()); i++) {
          //# ignore us
          if (em->getParticles()[i] == p) {
            continue;
          }

          float dx = em->getParticles()[i]->position.x - p->position.x;
          float dy = em->getParticles()[i]->position.y - p->position.y;

          float spring = 0.05f;

          float distance = sqrt(dx*dx + dy*dy);
          float minDist  = diameter (em->getParticles()[i])/2 + diameter(p)/2;
          if (distance < minDist) { 
            float angle = atan2(dy, dx);
            float targetX = p->position.x + cos(angle) * minDist;
            float targetY = p->position.y + sin(angle) * minDist;
            float ax = (targetX - em->getParticles()[i]->position.x) * spring;
            float ay = (targetY - em->getParticles()[i]->position.y) * spring;
            p->velocity.x -= ax;
            p->velocity.y -= ay;
            em->getParticles()[i]->velocity.x += ax;
            em->getParticles()[i]->velocity.y += ay;
          }
        }   
      }
    }

  private:
    float diameter (particle* p)
    {
      float cx = p->scalefactor;
      float cy = p->scalefactor;
      if (p && p->shape.GetImage()) {
        cx = static_cast<float> (p->shape.GetImage()->GetWidth());
        cy = static_cast<float> (p->shape.GetImage()->GetHeight());
      }
      float dia = cx*cx + cy*cy;
      return static_cast<float> (sqrt (dia));
    }
  };
}

#endif
