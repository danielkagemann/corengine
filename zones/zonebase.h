#ifndef zonebase_h_
#define zonebase_h_

#include <SFML/Graphics.hpp>

namespace coresystem {

#define ZONECOLOR sf::Color(50,50,50,100)

//# ---- zone interface ---
class zonebase {
public: 
  zonebase ();
  virtual ~zonebase ();

  virtual sf::Vector2f getPoint () = 0;
  virtual bool contains (float x, float y) = 0;
  //virtual bool collide (particle* p) = 0;
  virtual size_t getCount () {return 1;}

  virtual void render (sf::RenderWindow& wnd);

  static zonebase* factory (std::string settings);
};

}

#endif
