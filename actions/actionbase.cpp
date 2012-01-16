#include "actionbase.h"
#include "../helper/helper.h"

#include "accelerate.h"
#include "age.h"
#include "move.h"
#include "death.h"
#include "fade.h"
#include "lineardrag.h"
#include "randomdrift.h"
#include "scale.h"
#include "speedlimit.h"
#include "slowdown.h"
#include "stop.h"
#include "boundingbox.h"
#include "collide.h"
#include "morph.h"
#include "rotate.h"
#include "trail.h"
#include "randompos.h"
#include "color.h"
#include "path.h"

using namespace coresystem;

/*-------------------------------------------------------------------*/
actionbase::actionbase ()
{
  m_zone = NULL;
}
/*-------------------------------------------------------------------*/
actionbase::~actionbase ()
{}
/*-------------------------------------------------------------------*/
actionbase* actionbase::factory (std::vector<zonebase*>& zones, std::string settings)
{
  TStringList                 argv;
  zonebase                    *usedZone = NULL;
  actionbase                  *action   = NULL;

  //# check for zoned actions
  int zone = helper::ZoneReference (settings);
  if (zone!=-1) {
    //# adjust settings string
    size_t id = settings.find (",");
    if (id == -1) {
      throw ("invalid action with zone configured");
    }
    settings = settings.substr (id+1);

    //# check zone
    if (zone >= static_cast<int> (zones.size())) {
      throw ("zone reference for action is invalid");
    }
    usedZone = zones[zone];
  }

  //# accelerate
  if (settings.substr (0,11)=="accelerate=") {

    argv = helper::tokenizer (settings.substr (11),",");
    if (argv.size() != 2) {
      throw ("action:accelerate is invalid");
    }
    action = new accelerate (argv.ToFloat (0), argv.ToFloat (1));
  }
  //# color
  if (settings.substr (0,6)=="color=") {

    argv = helper::tokenizer (settings.substr (6),",");
    if (argv.size() != 3) {
      throw ("action:color is invalid");
    }
    action = new color (argv.ToInteger(0), 
                        argv.ToInteger(1),
                        argv.ToInteger(2));
  }
  //# morph
  if (settings.substr (0,6)=="morph=") {

    argv = helper::tokenizer (settings.substr (6),",");
    if (argv.size() != 2) {
      throw ("action:morph is invalid");
    }
  	//# maybe we have a reference
    int	zone = helper::ZoneReference(argv[0]);
    if (zone!=-1) {
    	if (zone >= static_cast<int> (zones.size())) {
      	throw ("zonereference for action:morph is invalid");
      }
      action = new morph (zones[zone], argv.ToInteger(1));
    }
    else {
      throw ("invalid action:morph zone specified");
    }
  }
  //# age
  else if (settings.substr (0,3)=="age") {
    action = new age ();
  }
  //# stop
  else if (settings.substr (0,5)=="stop=") {
    argv = helper::tokenizer (settings.substr (5),",");
    if (argv.size ()==2) {
      action= new stop (argv[0].c_str(), argv[1] == "yes" ? true : false);
    }
    else if (argv.size() == 1) {
      //# should be used within a zone
      action= new stop (argv[0] == "yes" ? true : false);
    }
    else {
      throw ("action:stop is invalid");
    }
  }
  //# move
  else if (settings.substr (0,4)=="move") {
    action = new move ();
  }
  //# rotate
  else if (settings.substr (0,6)=="rotate") {
    action = new rotate ();
  }
  //# collide
  else if (settings.substr (0,7)=="collide") {
    action = new collide ();
  }
  //# fade
  else if (settings.substr (0,5)=="fade=") {

    argv = helper::tokenizer (settings.substr (5),",");
    if (argv.size() != 1) {
      throw ("action:fade is invalid");
    }
    action = new fade (atoi (argv[0].c_str())); 
  }
  //# lineardrag
  else if (settings.substr (0,11)=="lineardrag=") {

    argv = helper::tokenizer (settings.substr (11),",");
    if (argv.size() != 1) {
      throw ("action:lineardrag is invalid");
    }
    action = new lineardrag (argv.ToFloat (0)); 
  }
  //# slowdown
  else if (settings.substr (0,9)=="slowdown=") {

    argv = helper::tokenizer (settings.substr (9),",");
    if (argv.size() != 1) {
      throw ("action:slowdown is invalid");
    }
    action = new slowdown (argv.ToFloat (0)); 
  }
  //# scale
  else if (settings.substr (0,6)=="scale=") {

    argv = helper::tokenizer (settings.substr (6),",");
    if (argv.size() != 1) {
      throw ("action:scale is invalid");
    }
    action = new scale (argv.ToFloat (0)); 
  }
  //# speedlimit
  else if (settings.substr (0,11)=="speedlimit=") {

    argv = helper::tokenizer (settings.substr (11),",");
    if (argv.size() != 2) {
      throw ("action:speedlimit is invalid");
    }
    action = new speedlimit (argv.ToFloat (0),argv.ToFloat (1));
  }
  //# randomdrift
  else if (settings.substr (0,12)=="randomdrift=") {
    
    argv = helper::tokenizer (settings.substr (12),",");
    if (argv.size() != 2) {
      throw ("action:randomdrift is invalid");
    }
    action = new randomdrift (argv.ToFloat (0),argv.ToFloat (1));
  }
  //# randompos
  else if (settings.substr (0,10)=="randompos=") {
    
    argv = helper::tokenizer (settings.substr (10),",");
    if (argv.size() != 4) {
      throw ("action:randompos is invalid");
    }
    action = new randompos (argv.ToFloat (0),
                            argv.ToFloat (1),
                            argv.ToFloat (2),
                            argv.ToFloat (3)
                             ); 
  }
  //# death
  else if (settings.substr (0,6)=="death=") {

    argv = helper::tokenizer (settings.substr (6),",");
    if (argv.size() != 5) {
      throw ("action:death is invalid");
    }
    action = new death (argv.ToFloat (0),
                      argv.ToFloat (1),
                      argv.ToFloat (2),
                      argv.ToFloat (3),
                      (argv[4] == "yes") ? true : false); 
  }
  //# boundingbox
  else if (settings.substr (0,12)=="boundingbox=") {

    argv = helper::tokenizer (settings.substr (12),",");
    if (argv.size() != 5) {
      throw ("action:boundingbox is invalid");
    }
    action = new boundingbox (atoi (argv[0].c_str()),
                      argv.ToInteger (1),
                      argv.ToInteger (2),
                      argv.ToInteger (3),
                      argv.ToFloat   (4));
  }
  //# trail
  else if (settings.substr (0,6)=="trail=") {
    argv = helper::tokenizer (settings.substr (6),",");
    
    if (argv.size() == 3) {
      action = new trail ( argv.ToFloat(0), argv.ToFloat(1), argv.ToFloat(2) );
    }
    else if (argv.size() == 1) {
      action = new trail ( argv.ToFloat(0) );
    }
    else {
      throw ("action:trail is invalid");
    }
  }
  //# path
  else if (settings.substr (0,5)=="path=") {
    argv = helper::tokenizer (settings.substr (5),",");
    if (argv.size() != 3) {
      throw ("action:path is invalid");
    }
    action = new path ( argv[0].c_str(), argv.ToFloat (1), argv.ToFloat (2) );
  }


  if (action!=NULL) {
    //# set the zone
    action->setzone (usedZone);
    return action;
  }

  //# error handling
  throw helper::errormessage("unknown action command: %s",settings.c_str());

  return NULL;
}
/*-------------------------------------------------------------------*/
void actionbase::setzone (zonebase* z)
{
  m_zone = z;
}
/*-------------------------------------------------------------------*/
bool actionbase::zoneimpact (const sf::Vector2f& pos)
{
  if (m_zone != NULL && m_zone->contains (pos.x,pos.y) == false) {
    return false;
  }

  return true;
}
/*-------------------------------------------------------------------*/
zonebase* actionbase::getZone ()
{
  return m_zone;
}
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
