 /* ------------------------------------------------------------------
  * GEM - Graphics Environment for Multimedia
  *
  *  Copyright (c) 2002-2011 IOhannes m zmölnig. forum::für::umläute. IEM. zmoelnig@iem.at
  *	zmoelnig@iem.kug.ac.at
  *  For information on usage and redistribution, and for a DISCLAIMER
  *  OF ALL WARRANTIES, see the file, "GEM.LICENSE.TERMS"
  *
  *  this file has been generated...
  * ------------------------------------------------------------------
  */

#ifndef _INCLUDE__GEM_OPENGL_GEMGLCLEARACCUM_H_
#define _INCLUDE__GEM_OPENGL_GEMGLCLEARACCUM_H_

#include "Base/GemGLBase.h"

/*
 CLASS
	GEMglClearAccum
 KEYWORDS
	openGL	0
 DESCRIPTION
	wrapper for the openGL-function
	"glClearAccum( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)"
 */

class GEM_EXTERN GEMglClearAccum : public GemGLBase
{
	CPPEXTERN_HEADER(GEMglClearAccum, GemGLBase);

	public:
	  // Constructor
	  GEMglClearAccum (t_float, t_float, t_float, t_float);	// CON

	protected:
	  // Destructor
	  virtual ~GEMglClearAccum ();
	  // Do the rendering
	  virtual void	render (GemState *state);

	// variables
	  GLfloat	red;		// VAR
	  virtual void	redMess(t_float);	// FUN

	  GLfloat	green;		// VAR
	  virtual void	greenMess(t_float);	// FUN

	  GLfloat	blue;		// VAR
	  virtual void	blueMess(t_float);	// FUN

	  GLfloat	alpha;		// VAR
	  virtual void	alphaMess(t_float);	// FUN


	private:

	// we need some inlets
	  t_inlet *m_inlet[4];

	// static member functions
	  static void	 redMessCallback (void*, t_float);
	  static void	 greenMessCallback (void*, t_float);
	  static void	 blueMessCallback (void*, t_float);
	  static void	 alphaMessCallback (void*, t_float);
};
#endif // for header file
