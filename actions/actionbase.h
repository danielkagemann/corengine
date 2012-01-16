#ifndef actionbase_h_
#define actionbase_h_

#include <SFML/Graphics.hpp>
#include "../particle.h"
#include "../zones/zonebase.h"

/// An action is used for each particle on each iteration. Actions can also be used only in a defined zone when using action:@zonenumber,actionstring
/// _name DESCRIPTION

namespace coresystem {

  class emitter;

  class actionbase {
    public:
      actionbase ();
      virtual ~actionbase ();

      virtual void update (emitter* em, particle* p, float dt) = 0;

      static actionbase* factory (std::vector<zonebase*>& zones,std::string settings);

      void setzone (zonebase* z);
      
      bool zoneimpact (const sf::Vector2f& pos);

      zonebase* getZone ();

  protected:
    zonebase*   m_zone;
  };

}

#endif
