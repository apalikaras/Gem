/*-----------------------------------------------------------------
LOG
    GEM - Graphics Environment for Multimedia

    age an image

    Copyright (c) 1997-1999 Mark Danks. mark@danks.org
    Copyright (c) 2001-2011 IOhannes m zmölnig. forum::für::umläute. IEM. zmoelnig@iem.at
    Copyright (c) 2002 James Tittle & Chris Clepper
    For information on usage and redistribution, and for a DISCLAIMER OF ALL
    WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.

    this is based on EffecTV by Fukuchi Kentauro
    * Copyright (C) 2001 FUKUCHI Kentarou

-----------------------------------------------------------------*/

#ifndef _INCLUDE__GEM_PIXES_PIX_CONVERT_H_
#define _INCLUDE__GEM_PIXES_PIX_CONVERT_H_

#include "Base/GemPixObj.h"

/*-----------------------------------------------------------------
-------------------------------------------------------------------
CLASS
    pix_convert

    Change pix from "any" color-space to GL_RGBA

KEYWORDS
    pix

DESCRIPTION

-----------------------------------------------------------------*/

class GEM_EXTERN pix_convert : public GemPixObj
{
    CPPEXTERN_HEADER(pix_convert, GemPixObj);

    public:

    //////////
    // Constructor
    pix_convert();

 protected:

    //////////
    // Destructor
    virtual ~pix_convert();

    //////////
    // Do the processing
    void 	processImage(imageStruct &image);

    imageStruct m_image;
 private:
    static void colorMessCallback(void *data, t_symbol*s);
};

#endif	// for header file
