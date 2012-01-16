#ifndef helper_h_
#define helper_h_

#include <string>
#include <vector>

#include <stdarg.h>		//# linux requirement
#include <stdio.h>		//# linux requirement
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

class FileInfo {
public:
  FileInfo(const char* lpFile)
  {
	  m_name = lpFile;
    struct stat	info;
    stat (m_name.c_str(),&info);
    memcpy (&m_tm,&info.st_mtime, sizeof(time_t));
    m_timer.Reset();
  }
  
  bool isModified ()
  { 
     if (m_timer.GetElapsedTime() >= 1.f) {
     		m_timer.Reset ();
        struct stat		tmp;
        stat (m_name.c_str(),&tmp);
       	if (difftime(m_tm, tmp.st_mtime) != 0.f) {
        	memcpy (&m_tm,&tmp.st_mtime,sizeof(time_t));
          return true;
       	}
     }
     return false;
  }
  
protected:
	time_t	m_tm;
  std::string		m_name;
  sf::Clock			m_timer;
};

template <typename T>
class TRange {
public:
  TRange () {m_l=m_u=(T)0;}
  TRange (T val) {m_l = m_u = val;}
  TRange (T v1,T v2) {set(v1,v2);}
  void set (T v1, T v2){m_l=(v1<v2)?v1:v2;m_u=(v1>v2)?v1:v2;}

  T getLower(){return m_l;}
  T getUpper(){return m_u;}
  bool equal (){return (m_l==m_u)?true:false;}
  T getRandom (){return sf::Randomizer::Random(m_l,m_u);}

protected:
  T   m_l;
  T   m_u;
};
typedef TRange<int>   TRangeInt;
typedef TRange<float> TRangeFloat;

class TStringList : public std::vector<std::string> {
public:
  float   ToFloat (int index)
  {
    return static_cast<float> (atof ( at(index).c_str() ));
  }
  int   ToInteger (int index)
  {
    return static_cast<int> (atoi ( at(index).c_str() ));
  }
};

class helper {
public:
  static char* errormessage (const char* sub, ...)
  {
    static char buffer[1024]={0};
    va_list argList;
    va_start(argList,sub);
    if (vsnprintf (buffer,
                   sizeof (buffer), 
                   sub,
                   argList) > 0) {
    }
    va_end(argList);
    return buffer;
  }

  static TStringList tokenizer (std::string line, std::string sep)
  {
    TStringList    results;

    while(line.length()>0) {
      size_t id = line.find (sep,0);
      if (id==-1) {
        break;
      }
      results.push_back (line.substr (0,id));
      line = line.substr(id+sep.length());
    }

    //# last component
    if (line.length()>0) {
      results.push_back (line);
    }
    return results;
  }
  
  static int ZoneReference (std::string line) 
  {
 		if (line.length()>0) {
    	if (line.substr(0,1)=="@") {
      	return atoi (line.substr(1).c_str()) - 1;
      }
		}
    return -1;
  }
};

#endif
