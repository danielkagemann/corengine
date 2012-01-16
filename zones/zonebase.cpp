#include "zonebase.h"
#include "../helper/helper.h"

#include "rect.h"
#include "point.h"
#include "circle.h"
#include "bitmap.h"

using namespace coresystem;

/*-------------------------------------------------------------------*/
zonebase::zonebase ()
{}
/*-------------------------------------------------------------------*/
zonebase::~zonebase () {}
/*-------------------------------------------------------------------*/
zonebase* zonebase::factory (std::string settings)
{
  TStringList    argv;
  //# rect
  if (settings.substr (0,5)=="rect=") {

    argv = helper::tokenizer (settings.substr (5),",");
    if (argv.size() != 4) {
      throw ("rect= is invalid");
    }
    return new zoneRect (argv.ToFloat(0),argv.ToFloat(1),argv.ToFloat(2),argv.ToFloat(3));
  }
  //# point
  else if (settings.substr (0,6) == "point=") {
    argv = helper::tokenizer (settings.substr (6),",");
    if (argv.size() != 2) {
      throw ("point= is invalid");
    }
    return new zonePoint (argv.ToFloat(0),argv.ToFloat(1));

  }
  //# circle
  else if (settings.substr (0,7) == "circle=") {
    argv = helper::tokenizer (settings.substr (7),",");
    if (argv.size() != 3) {
      throw ("circle= is invalid");
    }
    return new zoneCircle(argv.ToFloat(0),argv.ToFloat(1),argv.ToFloat(2));

  }
  //# bitmap
  else if (settings.substr (0,7) == "bitmap=") {
    argv = helper::tokenizer (settings.substr (7),",");
    if (argv.size()==1) {
      return new zoneBitmap (argv[0].c_str());
    }
    else if (argv.size()==3) {
      return new zoneBitmap (argv[0].c_str(), argv.ToFloat(1),argv.ToFloat(2));
    }
    else  {
      throw ("bitmap= is invalid");
    }
  }

  throw helper::errormessage("unknown zone command: %s",settings.c_str());

  return NULL;
}
/*-------------------------------------------------------------------*/
void zonebase::render (sf::RenderWindow& wnd)
{
  //# nothing to do here
}
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
