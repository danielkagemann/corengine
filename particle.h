#ifndef particle_h_
#define particle_h_

#include <SFML/Graphics.hpp>

namespace coresystem
{
  struct particle {
    sf::Vector2f    position;
    sf::Vector2f    velocity;
    float           scalefactor;
    sf::Color       color;
    float           lifetime;
    float           angle;
    float           angleVelo;
    
    sf::Vector2f    pathvalue;
    bool            usepath;

    bool            isDead;
    
    sf::Sprite			shape;
    
    //# default particle
    particle ()
    {
      position    = sf::Vector2f(0.f,0.f);
      velocity    = sf::Vector2f(0.f,0.f);
      scalefactor = 1.f;
      color    	  = sf::Color(254,254,254);
      lifetime 	  = 1.f;
      angle    	  = 0.f;
      angleVelo	  = 0.f;
      isDead   	  = true;
      usepath     = true;
      pathvalue   = sf::Vector2f(0.f,0.f);
    }

    particle (const particle* p) 
    {
      *this = p;
    }

    particle* operator= (const particle* p)
    {
      position    = p->position;
      velocity    = p->velocity;
      scalefactor = p->scalefactor;
      color    	  = p->color;
      lifetime 	  = p->lifetime;
      angle    	  = p->angle;
      angleVelo	  = p->angleVelo;
      pathvalue   = p->pathvalue;
      usepath     = p->usepath;
      isDead   	  = false;

      //# get dimension of image
      sf::Vector2f    sz = sf::Vector2f (static_cast<float>(p->shape.GetImage()->GetWidth()), static_cast<float>(p->shape.GetImage()->GetHeight()));
      
      //# set the image
      shape.SetImage (*p->shape.GetImage ());

      //# set center
      shape.SetCenter(sz.x/2.f, sz.y/2.f);
      
      //# resize
      sf::Vector2f  scale = p->shape.GetScale();
      shape.SetScale (scale);

      //# set the color
      shape.SetColor (color);
      
      return this;
    }

    void Draw (sf::RenderWindow& wnd)
    {
      if (isDead == false) {
        if (shape.GetImage() == NULL) {
          throw ("no shape defined");
        }
        else {
          shape.SetPosition (position);
          wnd.Draw (shape);
        }
      }
    }
  };
}

#endif
