#ifndef color_h_
#define color_h_

#include "actionbase.h"

/// Reduce color values R,G,B with given values. Values will be decremented
/// _name action:color
/// _param <rval> value to decrement the red value by
/// _param <gval> value to decrement the green value by
/// _param <bval> value to decrement the blue value by

namespace coresystem {
  class color : public actionbase {
  public:

    color ()
    {
      m_rgb[0] = 0;
      m_rgb[1] = 0;
      m_rgb[2] = 0;
    }

    color (int r, int g, int b)
    {
      m_rgb[0] = r;
      m_rgb[1] = g;
      m_rgb[2] = b;
    }

    virtual void update (emitter* em, particle* p, float dt)
    {
      if (p->isDead == false) {
        p->color.r -= m_rgb[0]; 
        if (p->color.r < 0)  
          p->color.r = 0; 
        else if (p->color.r > 255) 
          p->color.r = 255;
        p->color.g -= m_rgb[1]; 
        if (p->color.g < 0)  
          p->color.g = 0; 
        else if (p->color.g > 255) 
          p->color.g = 255;
        p->color.b -= m_rgb[2]; 
        if (p->color.b < 0)  
          p->color.b = 0; 
        else if (p->color.b > 255) 
          p->color.b = 255;
      }
    }
protected:
    int   m_rgb[3];
  };
}

#endif
