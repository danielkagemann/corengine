#ifndef initdot_h_
#define initdot_h_


/// Defines a dot bitmap for new particles.
/// _name init:dot
/// _param <radius> radius to be used as integer

#include "initbase.h"
#include <math.h>
#include <stdio.h>

namespace coresystem {
//# --- dot ---
class initDot : public initbase {
public:
  initDot (int size)
  {
    m_size = size;
  }
  
  virtual void init (emitter* em, particle* p)
  {
    //# make unique filename out of data
    char    filename[200];
    sprintf (filename, "c%d%d%d%d%d.png",m_size,p->color.r,p->color.g,p->color.b,p->color.a);

    if (em->getResource ().existImage (filename) == false) {
      sf::Image&	img = em->getResource().addImage(filename,filledCircle (p->color));
      p->shape.SetImage (img);
      p->shape.SetCenter(img.GetWidth()/2.f, img.GetHeight()/2.f);
    }
    else {
      sf::Image&	img = em->getResource().Image (filename);
      p->shape.SetImage (img);
      p->shape.SetCenter(img.GetWidth()/2.f, img.GetHeight()/2.f);
    }
	} 
  
private:
  sf::Image filledCircle(sf::Color col)
  {
    int x0 = m_size / 2;
    int y0 = x0;
    int r = m_size / 2;

    sf::Image     img (m_size+1,m_size+1);
    for (int yy = 0; yy < m_size+1; yy++) {
      for (int xx = 0; xx < m_size+1; xx++) {
        img.SetPixel (xx,yy,sf::Color(255,255,255));
      }
    }
    img.SetSmooth(true);
    img.CreateMaskFromColor (sf::Color(255,255,255));

    for (int x = -r; x < r ; x++)
    {
        int height = (int)sqrt( (double)r * r - x * x);

        for (int y = -height; y < height; y++)
            img.SetPixel(x + x0, y + y0, col);
    }

    return img;
  }

protected:
	int 	m_size;    
};

}


#endif
