////////////////////////////////////////////////////////
//
// GEM - Graphics Environment for Multimedia
//
// zmoelnig@iem.kug.ac.at
//
// Implementation file
//
//    Copyright (c) 1997-1999 Mark Danks.
//    Copyright (c) Günther Geiger.
//    Copyright (c) 2001-2011 IOhannes m zmölnig. forum::für::umläute. IEM. zmoelnig@iem.at
//
//    For information on usage and redistribution, and for a DISCLAIMER OF ALL
//    WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.
//
/////////////////////////////////////////////////////////

#include "GLUtil.h"

#include "Gem/GemGL.h"

#include <map>
#include <string>
#include <algorithm>


struct  t_namemap_data
{
  const char *s;
  int i;
};

#define NAMEMAP_ENTRY(x) { #x, (int)x }

static const t_namemap_data s_namemap_data[] = {

    /*
     * the following include is generated by something as awful as:
     * we are using std::map to store the mapping between GL-symbols and values,
     * as Pd's symbol-table is rather small (~1024 entries)
     * and we don't want to pollute it with about 3500 symbols
     * which are likely to never be used...
     */
  /* BASH

  grep define ../Gem/glew.h                                             \
  | grep "GL_"                                                          \
  | awk '{print $2}'                                                    \
  | egrep "^GL_"                                                        \
  | sort -u                                                             \
  | while read f; do                                                    \
     echo "  GLMAP_ENTRY($f),";                                         \
  done > GLUtil_generated.h

  */

  #include "GLUtil_generated.h"
  { 0    , 0 }
};
static std::map<const char*, int>s_namemap;
static void create_namemap(void) {
  const t_namemap_data*data = 0;
  for(data = s_namemap_data; data->s; data++) {
    s_namemap[data->s] = data->i;
  }
}

// I hate Microsoft...I shouldn't have to do this!
#ifdef _WIN32
/* disable warnings about unknown pragmas */
# pragma warning( disable : 4068 )
#endif


#define _GL_UNDEFINED -1

// if error dump gl errors to debugger string, return error
GLenum glReportError (void)
{
	GLenum err = glGetError();
	if (GL_NO_ERROR != err) {
		post("GL: %s",(char*)gluErrorString(err));
	}
	// ensure we are returning an OSStatus noErr if no error condition
	if (err == GL_NO_ERROR)
		return 0;
	else
		return err;
}

int getGLbitfield(int argc, t_atom *argv){
  int accum=0;
  int mode=0;

  if (!(argc%2))argc--;
  for (int n=0; n<argc; n++){
    if (n%2){ // && or ||
      char c=*argv->a_w.w_symbol->s_name;
      switch (c) {
      case '|':
	mode = 0;
	break;
      case '&':
	mode=1;
	break;
      default:
	return _GL_UNDEFINED;
      }
      argv++;
    } else {
      int value=getGLdefine(argv++);
      if (value==_GL_UNDEFINED)return _GL_UNDEFINED;
      if (mode==0)accum|=value;
      else accum&=value;
    }
  }
  return accum;

}

int getGLdefine(const t_atom *ap)
{
  if (!ap)return _GL_UNDEFINED;
  if (ap->a_type == A_SYMBOL)return getGLdefine(ap->a_w.w_symbol);
  if (ap->a_type == A_FLOAT)return atom_getint((t_atom*)ap);
  return _GL_UNDEFINED;
}

int getGLdefine(const t_symbol *s)
{
  if (s && s->s_name)return getGLdefine(s->s_name);
  else return _GL_UNDEFINED;
}

int getGLdefine(const char *fixname)
{
  std::string str=fixname;
  std::transform(str.begin(), str.end(),str.begin(), ::toupper);
  static int firsttime=1;
  if(firsttime)create_namemap();
  firsttime=0;

  std::map<const char*,int>::iterator it = s_namemap.find(str.c_str());
  if(it!=s_namemap.end()) {
    return it->second;
  }
  return _GL_UNDEFINED;

}
