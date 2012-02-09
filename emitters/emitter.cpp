/*
 *  emitter.cpp
 *  corengine
 *
 *  Created by Daniel Kagemann on 15.09.10.
 *  Copyright 2010 corefault.de. All rights reserved.
 *
 */

#include "emitter.h"
#include <fstream>
#include <iostream>
#include <string>

#include "../initializers/initbase.h"
#include "../initializers/bitmap.h"
#include "../zones/zonebase.h"
#include "../filter/filterbase.h"
#include "../helper/helper.h"
#include "../helper/mtime.h"

using namespace coresystem;

/*-------------------------------------------------------------------*/
void emitter::removeScene ()
{
   if (m_scenes.empty () == false) {
      Scene*   front = m_scenes.front ();
      
      int  i;
      for (i = static_cast<int>(front->actions.size()-1);i>=0;i--) {
         delete front->actions[i];
         front->actions[i] = NULL;
      }
      front->actions.clear ();
      
      for (i = static_cast<int> (front->initializers.size()-1);i>=0;i--) {
         delete front->initializers[i];
         front->initializers[i] = NULL;
      }
      front->initializers.clear ();  
      
      //# remove front
      m_scenes.erase (m_scenes.begin());
      
      //# free memory#
      delete front;
   }
}
/*-------------------------------------------------------------------*/
emitter::emitter() 
{
   m_newobjects= 0;
   m_particle.clear();
   m_initialized=false;
}
/*-------------------------------------------------------------------*/
void emitter::removeParticles ()
{
   int i;
   for (i = static_cast<int> (m_particle.size()-1); i>=0; i--) {
      delete m_particle[i];
      m_particle[i] = NULL;
   }
   m_particle.clear ();
}
/*-------------------------------------------------------------------*/
emitter::~emitter()
{
	int i;
	removeParticles();
   for (i = 0; i < static_cast<int> (m_scenes.size()); i++) {
      removeScene ();
   }
}
/*-------------------------------------------------------------------*/
void emitter::render (sf::RenderWindow& wnd, bool zonedisplay)
{
   mtime    ti(__func__);
   
   if (m_initialized==false) {
      throw ("emitter not initialized");
   }
   
   int   i;
   
   //# time for scene elapsed ?
   bool create = false;
   if (m_scenes.empty () == false && m_scenes.front()->elapsetime > 0.f && m_scenetimer.GetElapsedTime() > m_scenes.front()->elapsetime) {
      //# change to next scene
      removeScene ();
      m_scenetimer.Reset();
      create = setnumber();//# update objects
   }
   
   //# scenes available ?
   if (m_scenes.empty ()) {
      //# no more scenes
      return;
   }
   
   //# creator time ?
   creator (create);
   
   //# get length in a variable to avoid action cloning particles will blow the loop
   int length = static_cast<int> (m_particle.size()-1);
   
   for (i = length; i >= 0; i--) {
   
      if (m_particle[i]->isDead == true) {
         delete m_particle[i];
         m_particle[i] = NULL;
         m_particle.erase (m_particle.begin()+i);
         continue;
      }
      
      //# actions
      handleactions(i, 1.f);
      
      //# draw particle
      m_particle[i]->Draw (wnd);
   }
   
   //# get current scene
   Scene  *pcurrent = m_scenes.front ();
   
	//# filter for this scene
   for (int f = 0; f < static_cast<int> (pcurrent->filter.size()); f++) {
      pcurrent->filter[f]->perform (wnd);
   }
   
   //# draw zones for the actions
   if (zonedisplay) {
      for (i = 0; i < static_cast<int> (pcurrent->actions.size()); i++) {
         if (pcurrent->actions[i]->getZone ()!=NULL) {
            pcurrent->actions[i]->getZone ()->render (wnd);
         }
      }
   }
}
/*-------------------------------------------------------------------*/
bool emitter::setnumber ()
{
   if (m_scenes.empty ()==true) {
      return false;
   }
   
   unsigned int num = m_scenes.front ()->numOfObjects;
   float timerate   = m_scenes.front ()->numTimerate;
   
   int len = static_cast<int> (m_scenes.size());
   
   switch (m_scenes.front ()->numMode) {
      case Scene::CreateAll:
         m_timerate  = timerate;
         m_newobjects= num;
         OUTPUT ("setnumber (all, scenes: %d, rate: %.02f, obj: %d)\n",len,timerate,num);
         break;
      case Scene::CreatePulse:
      
         /*if (timerate / num <= 0.4f) {
            m_newobjects = num * 0.4;
            m_timerate   = 0.4f;
         }
         else*/ {
            m_newobjects = 1;
            m_timerate   = timerate / num;
         }
         OUTPUT ("setnumber (pulse, scenes: %d, rate: %.02f, obj: %d)\n",len,timerate,num);
         break;
      default:
      case Scene::CreateNothing:
         m_timerate = 0;
         m_newobjects = 0;
         OUTPUT ("setnumber (nothing, scenes: %d, rate: %.02f, obj: %d)\n",len,timerate,num);
         return false;
   }
   m_timer.Reset ();
   removeParticles();
   return true;
}
/*-------------------------------------------------------------------*/
void emitter::removeDeadParticles ()
{
   for (int i = static_cast<int> (m_particle.size()-1); i>=0; i--) {
      if (m_particle[i]->isDead == true) {
         delete m_particle[i];
         m_particle[i] = NULL;
         m_particle.erase (m_particle.begin()+i);
      }
   }
}
/*-------------------------------------------------------------------*/
void emitter::creator (bool initial)
{
   //# TODO the framerate of sfml is set to 30
   //# means this routine is called 1000/30 = 0.033seconds
   //# supported modes are: all or pulse
   //# in pulse mode we have to ensure that number of pixels created at one time is
   if (initial == false && m_timerate == 0.f) {
      removeDeadParticles();
      return;
   }
   if (m_timer.GetElapsedTime () > m_timerate) {
      //# remove all dead pixels
      //# and create the new elements
      
      //TODO removed particles???
      //removeDeadParticles ();
      
      printf ("creating %d objects (timerate: %.04f)\n", m_newobjects,m_timerate);
      //# now create the new objects
      for (int i = 0; i < m_newobjects; i++) {
         particle    *p = new particle;
         
         handleinitializers(p);
         
         m_particle.push_back (p);
      }
      
      m_timer.Reset ();
   }
}
/*-------------------------------------------------------------------*/
void emitter::init ()
{
   m_initialized = true;
   srand((unsigned) time(NULL));
   
   //# set number for first scene
   setnumber ();
   
   creator (true);
   
   //# start scene timer
   m_scenetimer.Reset ();
}
/*-------------------------------------------------------------------*/
void emitter::addAction (actionbase* a)
{
   if (a == NULL) {
      throw ("emitterbase::add null pointer as action");
   }
   //# add to last scene
   m_scenes.back()->actions.push_back (a);
}
/*-------------------------------------------------------------------*/
void emitter::handleinitializers (particle* p)
{
   Scene* pcurrent = m_scenes.front ();
   
   int a;
   if (p->isDead == true) {
      for (a = 0; a < static_cast<int> (pcurrent->initializers.size()); a++) {
         pcurrent->initializers[a]->init (this, p);
      }
      
      //# now set particle to active
      p->isDead=false;
   }
}
/*-------------------------------------------------------------------*/
void emitter::handleactions      (int pidx, float elapsed)
{
   Scene* pcurrent = m_scenes.front ();
   
   int a;
   for (a = 0; a < static_cast<int> (pcurrent->actions.size()); a++) {
      pcurrent->actions[a]->update(this, m_particle[pidx],elapsed);
   }
}
/*-------------------------------------------------------------------*/
void emitter::addInitializer (initbase* i, int scene_id)
{
   if (i == NULL) {
      throw ("emitterbase::add null pointer as initializer");
   }
   
   Scene  *scene = (scene_id==-1) ? m_scenes.back() : m_scenes[scene_id];
   
   //# add to current scene (back)
   //# some initializers have to go in front of all others
   if (dynamic_cast<initBitmap*> (i)!=NULL) {
      scene->initializers.insert (m_scenes.back()->initializers.begin(),i);
   }
   else {
      scene->initializers.push_back (i);
   }
}
/*-------------------------------------------------------------------*/
emitter::emitter(const char* lpFile)
{
   m_newobjects= 0;
   m_particle.clear();
   m_initialized=false;
   
   std::ifstream    ini (lpFile, std::ios::in);
   if (!ini) {
      throw ("given configuration file cannot be opened");
   }
   
   std::string     line;
   
   //# to have access to the zones we need a zone handler here
   std::vector<zonebase*>		zonelist;
   
   //# iterate through file
   while (ini.eof()==false) {
		line.clear ();
      
		getline (ini,line);
      
      //# empty lines
      if (line.length()==0) {
         continue;
      }
      
      if (line.substr(line.length()-1, 1)=="\r") {
         line.erase (line.end()-1);
      }
      
      //# comments
      if (line.substr(0,1) == "#") {
         continue;
      }
      
      //# empty lines
      if (line.length()==0) {
         continue;
      }
      
      //# factorize the different items
      if (line.substr(0,6) == "scene ") {
         //# create new scene
         Scene* pnew = new Scene (static_cast<float> (atof (line.substr(6).c_str())));
         m_scenes.push_back (pnew);
      }
      else if (line.substr(0,5) == "zone ") {
         zonelist.push_back (zonebase::factory(line.substr(5)));
      }
      else if (line.substr (0,5) == "init ") {
         addInitializer(initbase::factory(zonelist, line.substr(5)));
      }
      else if (line.substr (0,7) == "action ") {
         addAction (actionbase::factory (zonelist, line.substr(7)));
      }
      else if (line.substr (0,7) == "filter ") {
         addFilter (filterbase::factory (line.substr(7)));
      }
      else if (line.substr (0,4) == "num ") {
         std::vector<std::string>  argv = helper::tokenizer (line.substr (4),",");
         
         Scene::CREATORMODE		mode = Scene::CreateAll;
         if (argv.size() < 2) {
            throw ("num is invalid");
         }
         if (argv.size() == 3) {
            if (argv[2] == "all") {
               mode = Scene::CreateAll;
            }
            else if (argv[2] == "pulse") {
               mode = Scene::CreatePulse;
            }
            else {
               throw ("unsupported num: creatormode");
            }
         }
         
         //# check if first argument is a zonereference
         int zone = helper::ZoneReference(argv[0]);
         if (zone != -1) {
            if (zone >= static_cast<int> (zonelist.size())) {
               throw ("referenced zone for num: is invalid");
            }
            
            m_scenes.back()->numMode = mode;
            m_scenes.back()->numOfObjects = static_cast<unsigned int>(zonelist[zone]->getCount());
            m_scenes.back()->numTimerate = static_cast<float> (atof(argv[1].c_str()));
         }
         else {
            m_scenes.back()->numMode = mode;
            m_scenes.back()->numOfObjects = atoi (argv[0].c_str());
            m_scenes.back()->numTimerate = static_cast<float> (atof(argv[1].c_str()));
         }
      }
      else {
         OUTPUT ("invalid command: %s\n",line.c_str());
      }
      
   }
   ini.close();
}
/*-------------------------------------------------------------------*/
std::vector<particle*>& emitter::getParticles ()
{
	return m_particle;
}
/*-------------------------------------------------------------------*/
bool emitter::isInitialized ()
{
	return m_initialized;
}
/*-------------------------------------------------------------------*/
void emitter::addFilter (filterbase* flt)
{
   //# add filter to scene
	m_scenes.back()->filter.push_back (flt);
}
/*-------------------------------------------------------------------*/
sharedimage&  emitter::getResource ()
{
   return m_resourcehandler;
}
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
