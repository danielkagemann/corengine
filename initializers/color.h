#ifndef initcolor_h_
#define initcolor_h_

#include "initbase.h"

/// Defines RGB value for the particle without alpha.
/// _name init:color
/// _param <hexstring> like 910030 means red=0x91, green=0x00, blue=0x30

namespace coresystem {
//# ---- color ----
class initColor : public initbase {
public:
  initColor (const char* lpHex)
  {
    if (lpHex == NULL || strlen(lpHex) < 6) {
      throw ("invalid color");
    }
    int   r,g,b;
    char  buffer[3];
    memset (buffer,0,sizeof(buffer));
    strncpy (buffer,lpHex,2);
    sscanf (buffer,"%x", &r);
    strncpy (buffer,lpHex+2,2);
    sscanf (buffer,"%x", &g);
    strncpy (buffer,lpHex+4,2);
    sscanf (buffer,"%x", &b);
    m_color = sf::Color(r,g,b);
  }

  virtual void init (emitter* em, particle* p)
  {
    p->color.r = m_color.r;
    p->color.g = m_color.g;
    p->color.b = m_color.b;

    //# in case of a shape we have to set the color there
    if (p->shape.GetImage() != NULL) {
      p->shape.SetColor (p->color);
    }
  }
protected:
  sf::Color     m_color;
};

}


#endif