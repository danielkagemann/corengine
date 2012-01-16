#ifndef initbase_h_
#define initbase_h_

#include <iostream>
#include "../particle.h"
#include "../zones/zonebase.h"

namespace coresystem {

  //# forward declaration
class emitter;

//# ---- init base ----
class initbase {
public:
  initbase ();
  virtual ~initbase();

  virtual void init (emitter* em, particle* p) = 0;

  static initbase* factory (std::vector<zonebase*>& zones, std::string settings);
};

}

#endif