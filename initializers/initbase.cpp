#include "initbase.h"

#include "age.h"
#include "alpha.h"
#include "bitmap.h"
#include "color.h"
#include "positionabs.h"
#include "dot.h"
#include "scale.h"
#include "velocity.h"
#include "offsetpos.h"
#include "rotate.h"
#include "rotateVelocity.h"
#include "../helper/helper.h"

using namespace coresystem;

/*-------------------------------------------------------------------*/
initbase::initbase () 
{
}
/*-------------------------------------------------------------------*/
initbase::~initbase() 
{
}
/*-------------------------------------------------------------------*/
initbase* initbase::factory (std::vector<zonebase*>& zones, std::string settings)
{
  TStringList    argv;

  //# age
  if (settings.substr (0,4)=="age=") {

    argv = helper::tokenizer (settings.substr (4),",");
    if (argv.size() != 2) {
      throw ("init:age is invalid");
    }
    return new initAge (argv.ToInteger (0), 
                        argv.ToInteger (1));
  }

  //# offsetpos
  if (settings.substr (0,10)=="offsetpos=") {

    argv = helper::tokenizer (settings.substr (10),",");
    if (argv.size() != 2) {
      throw ("init:offsetpos is invalid");
    }
    return new initOffsetpos (argv.ToFloat(0),argv.ToFloat(1)); 
                              
  }

  //# alpha
  if (settings.substr (0,6)=="alpha=") {
    argv = helper::tokenizer (settings.substr (6),",");
    if (argv.size() != 2) {
      throw ("init:alpha is invalid");
    }
    return new initAlpha (argv.ToInteger (0),argv.ToInteger(1));
  }

  //# rotate
  if (settings.substr (0,7)=="rotate=") {
    argv = helper::tokenizer (settings.substr (7),",");
    if (argv.size() != 2) {
      throw ("init:rotate is invalid");
    }
    return new initRotate (argv.ToFloat(0),argv.ToFloat(1));
  }
  //# rotatevelocity
  if (settings.substr (0,15)=="rotatevelocity=") {
    argv = helper::tokenizer (settings.substr (15),",");
    if (argv.size() != 2) {
      throw ("init:rotatevelocity is invalid");
    }
    return new initRotateVelocity (argv.ToFloat(0),argv.ToFloat(1));
  }

  //# bitmap
  if (settings.substr (0,7)=="bitmap=") {
    argv = helper::tokenizer (settings.substr (7),",");
    if (argv.size() != 3) {
      throw ("init:bitmap is invalid");
    }
    return new initBitmap (argv[0].c_str(),argv.ToFloat(1),argv.ToFloat(2));
  } 
  //# color
  if (settings.substr (0,6)=="color=") {
    return new initColor (settings.substr(6).c_str());
  }
  //# dot
  if (settings.substr (0,4)=="dot=") {
    argv = helper::tokenizer (settings.substr (4),",");
    if (argv.size() != 1) {
      throw ("init:dot is invalid");
    }
    return new initDot (argv.ToInteger(0));
  }
  //# positionabs
  if (settings.substr (0,12)=="positionabs=") {
  	//# maybe we have a reference
    int	zone = helper::ZoneReference(settings.substr(12));
    if (zone!=-1) {
    	if (zone >= static_cast<int> (zones.size())) {
      	throw ("zonereference for init:positionabs is invalid");
      }
      return new initPositionAbs(zones[zone]);
    }
    else {
	    //# the following string is a zone
  	  zonebase* z = zonebase::factory (settings.substr(12));
    	return new initPositionAbs (z);
    }
  }
  //# scale
  if (settings.substr (0,6)=="scale=") {
    argv = helper::tokenizer (settings.substr (6),",");
    if (argv.size() != 2) {
      throw ("init:scale is invalid");
    }
    return new initScale (argv.ToFloat(0),argv.ToFloat(1));
  } 
  //# velocity
  if (settings.substr (0,9)=="velocity=") {
    argv = helper::tokenizer (settings.substr (9),",");
    if (argv.size() != 4) {
      throw ("init:velocity is invalid");
    }
    return new initVelocity (argv.ToFloat(0),argv.ToFloat(1),argv.ToFloat(2),argv.ToFloat(3));
  } 

  throw helper::errormessage("unknown init command: %s",settings.c_str());
  return NULL;
}
/*-------------------------------------------------------------------*/
