////////////////////////////////////////////////////////
//
// GEM - Graphics Environment for Multimedia
//
// zmoelnig@iem.kug.ac.at
//
// Implementation file
//
//    Copyright (c) 1997-2000 Mark Danks.
//    Copyright (c) Günther Geiger.
//    Copyright (c) 2001-2011 IOhannes m zmölnig. forum::für::umläute. IEM. zmoelnig@iem.at
//    For information on usage and redistribution, and for a DISCLAIMER OF ALL
//    WARRANTIES, see the file, "GEM.LICENSE.TERMS" in this distribution.
//
/////////////////////////////////////////////////////////

#include "VertexBuffer.h"

/* for post(), error(),... */
#include "m_pd.h"

VertexBuffer:: VertexBuffer() :
  size(0),
  stride(0),
  vbo(0),
  array(NULL),
  dirty(false),
  enabled(false),
  attrib_index(0),
  attrib_name(""),
  attrib_array(""),
  offset(0)
{
}
VertexBuffer:: VertexBuffer (unsigned int size_,
    unsigned int stride_) :
  size(0),
  stride(stride_),
  vbo(0),
  array(NULL),
  dirty(false),
  enabled(false),
  attrib_index(0),
  attrib_name(""),
  attrib_array(""),
  offset(0)
{
  resize(size_);
}
VertexBuffer:: VertexBuffer (const VertexBuffer&vb)
  :size(0)
  ,stride(vb.stride)
  ,vbo(vb.vbo)
  ,array(NULL)
  ,dirty(false)
  ,enabled(vb.enabled)
  ,attrib_index(vb.attrib_index)
  ,attrib_name(vb.attrib_name)
  ,attrib_array(vb.attrib_array)
  ,offset(vb.offset)
{
  resize(vb.size);
}

VertexBuffer:: ~VertexBuffer (void)
{
  //::post("destroying VertexBuffer[%p] with %dx%d elements at %p", this, size, stride, array);
  destroy();

  if(array) {
    delete[]array;
  }
  array=NULL;
}
void VertexBuffer:: resize (unsigned int size_)
{
  float*tmp=NULL;
  try {
    tmp=new float[size_*stride];
  } catch (std::bad_alloc& ba)  {
    ::error("vertexbuffer resize failed: %s ", ba.what());
    return;
  }
  if(array) {
    delete[]array;
    array=0;
  }
  array=tmp;
  size=size_;

  unsigned int i;
  for(i=0; i<size*stride; i++) {
    array[i]=0;
  }
  dirty=true;
}

bool VertexBuffer:: create (void)
{
  if(!vbo) {
    glGenBuffers(1, &vbo);
  }
  if(vbo) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size * stride * sizeof(float), array,
                 GL_DYNAMIC_DRAW);
  }
  return (0!=vbo);
}
bool VertexBuffer:: render (void)
{
  // render from the VBO
  //::post("VertexBuffer::render: %d?", enabled);
  if ( enabled ) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    if ( dirty ) {
      //::post("push vertex %p\n", this);
      glBufferData(GL_ARRAY_BUFFER, size * stride * sizeof(float), array,
                   GL_DYNAMIC_DRAW);
      dirty = false;
    }
  }
  return enabled;
}
void VertexBuffer:: destroy (void)
{
  if ( vbo ) {
    glBindBuffer(1, vbo);
    glDeleteBuffers(1, &vbo);
  }
  vbo=0;
}