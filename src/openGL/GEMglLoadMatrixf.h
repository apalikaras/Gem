 /* ------------------------------------------------------------------
  * GEM - Graphics Environment for Multimedia
  *
  *  Copyright (c) 2004 tigital@mac.com
  *  For information on usage and redistribution, and for a DISCLAIMER
  *  OF ALL WARRANTIES, see the file, "GEM.LICENSE.TERMS"
  *
  * ------------------------------------------------------------------
  */

#ifndef _INCLUDE__GEM_OPENGL_GEMGLLOADMATRIXF_H_
#define _INCLUDE__GEM_OPENGL_GEMGLLOADMATRIXF_H_

#include "Base/GemGLBase.h"

/*
 CLASS
	GEMglLoadMatrixf
 KEYWORDS
	openGL	0
 DESCRIPTION
	wrapper for the openGL-function
	"glLoadMatrixf( GLfloat matrix)"
 */

class GEM_EXTERN GEMglLoadMatrixf : public GemGLBase
{
	CPPEXTERN_HEADER(GEMglLoadMatrixf, GemGLBase);

	public:
	  // Constructor
	  GEMglLoadMatrixf (t_float);	// CON

	protected:
	  // Destructor
	  virtual ~GEMglLoadMatrixf ();
          // check extensions
          virtual bool isRunnable(void);

	  // Do the rendering
	  virtual void	render (GemState *state);

	// variables
	  GLfloat		m_matrix[16];		// VAR
	  virtual void	matrixMess(int argc, t_atom* argv);	// FUN


	private:

	// we need some inlets
	  t_inlet *m_inlet;

	// static member functions
	  static void	 matrixMessCallback (void*, t_symbol*,int, t_atom*);
};
#endif // for header file
