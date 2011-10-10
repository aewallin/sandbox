/*  
 *  Copyright 2010-2011 Anders Wallin (anders.e.e.wallin "at" gmail.com)
 *  
 *  This file is part of OpenCAMlib.
 *
 *  OpenCAMlib is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  OpenCAMlib is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with OpenCAMlib.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GL_DATA_H
#define GL_DATA_H

#include <QObject>
#include <QGLBuffer>
#include <QVarLengthArray>
#include <QMutex>
#include <QMutexLocker>


#include <iostream>
#include <set>
#include <cmath>

#include <boost/foreach.hpp>

#include "glvertex.hpp"

// additional data, not strictly required for OpenGL rendering is stored here
struct VertexData {
    inline void addPolygon( unsigned int idx )   { polygons.insert( idx );  }
    inline void removePolygon(unsigned int idx ) { polygons.erase( idx );   }
    inline bool empty()                          { return polygons.empty(); }
// DATA
    /// The set of polygons. Each polygon has an uint index which is stored here.
    /// Note: we want to access polygons from highest index to lowest, thus compare with "greater"
    typedef std::set< unsigned int, std::greater<unsigned int> > PolygonSet;
    /// the polygons to which this vertex belongs. i.e. for each vertex we store in this set all the polygons to which it belongs.
    PolygonSet polygons;
    void str() {
        BOOST_FOREACH( GLuint pIdx, polygons ) {
            std::cout << pIdx << " ";
        }
    }
};

// parameters for rendering held by a GLData
// vertex position/color/normal and polygon indices held in vertex- and index-arrays other data here
struct GLParameters {
    // the type of this GLData, one of:
    //                GL_POINTS,
    //                GL_LINE_STRIP,
    //                GL_LINE_LOOP,
    //                GL_LINES,
    //                GL_TRIANGLE_STRIP,
    //                GL_TRIANGLE_FAN,
    //                GL_TRIANGLES,
    //                GL_QUAD_STRIP,
    //                GL_QUADS,
    //                GL_POLYGON 
    GLenum type;
    GLenum polygonMode_face; // face = GL_FRONT | GL_BACK  | GL_FRONT_AND_BACK
    GLenum polygonMode_mode; // mode = GL_POINT, GL_LINE, GL_FILL
    int polyVerts; // vertices per polygon
};

/// a GLData object holds data which is drawn by OpenGL using VBOs
class GLData {
public:
    GLData();
    unsigned int addVertex(float x, float y, float z, float r, float g, float b);
    unsigned int addVertex(float x, float y, float z, float r, float g, float b, float nx, float ny, float nz);
    unsigned int addVertex(GLVertex v);
    void modifyVertex( unsigned int id, float x, float y, float z, float r, float g, float b, float nx, float ny, float nz);
    void setNormal(unsigned int id, float nx, float ny, float nz);
    void removeVertex( unsigned int id );
    int addPolygon( std::vector<GLuint>& verts );
    void removePolygon( unsigned int polygonIdx );
    void print() ;

    void setTriangles() {setType(GL_TRIANGLES); glp[workIndex].polyVerts=3;}
    void setQuads() {setType(GL_QUADS); glp[workIndex].polyVerts=4;}
    void setPoints() {setType(GL_POINTS); glp[workIndex].polyVerts=1;}
    void setLineStrip() {setType(GL_LINE_STRIP); glp[workIndex].polyVerts=1;}
    void setLines() {setType(GL_LINES); glp[workIndex].polyVerts=2;}
    void setQuadStrip() {setType(GL_QUAD_STRIP); glp[workIndex].polyVerts=1;}
    
    //GLenum polygonMode_face; // face = GL_FRONT | GL_BACK  | GL_FRONT_AND_BACK
    void setPolygonModeFront() { glp[workIndex].polygonMode_face = GL_FRONT; }
    void setPolygonModeBack() { glp[workIndex].polygonMode_face = GL_BACK; }
    void setPolygonModeFrontAndBack() { glp[workIndex].polygonMode_face = GL_FRONT_AND_BACK; }
    
    //GLenum polygonMode_mode; // mode = GL_POINT, GL_LINE, GL_FILL
    void setPolygonModeFill() { glp[workIndex].polygonMode_mode = GL_FILL; }
    void setPolygonModePoint() { glp[workIndex].polygonMode_mode = GL_POINT; }
    void setPolygonModeLine() { glp[workIndex].polygonMode_mode = GL_LINE; }
            
// static constants and typedefs
    typedef GLVertex vertex_type;
    static const GLenum index_type = GL_UNSIGNED_INT;
    static const GLenum coordinate_type = GL_FLOAT;
    static const GLenum color_type = GL_FLOAT;
    static const unsigned int vertex_offset = 0;
    static const unsigned int color_offset = 12;
    static const unsigned int normal_offset = 24;

    QMutex renderMutex; // renderer locks this while rendering, swapBuffer locks while swapping
    QMutex workMutex;

    const GLVertex* getVertexArray() const { return vertexArray[renderIndex].data(); }
    const GLuint* getIndexArray() const { return indexArray[renderIndex].data(); }
    inline const int polygonVertices() const { return glp[renderIndex].polyVerts; }
    inline const GLenum GLType() const { return glp[renderIndex].type; }
    inline const GLenum polygonFaceMode() const { return glp[renderIndex].polygonMode_face;}
    inline const GLenum polygonFillMode() const { return glp[renderIndex].polygonMode_mode;}
    inline const int indexCount() const { return indexArray[renderIndex].size(); }

    void swap() {
        swapBuffers();
        copyBuffers();
    }
    void swapBuffers() {  // neither rendering nor working is allowed during this operation!
        renderMutex.lock();
        workMutex.lock();
            renderIndex = (renderIndex==0) ? 1 : 0 ;
            workIndex = (workIndex==0) ? 1 : 0 ;
        workMutex.unlock();
        renderMutex.unlock();
    }
    
    void copyBuffers() { // rendering is allowed durint this call, since we only read from [renderIndex] here
        workMutex.lock();
            vertexArray[workIndex] = vertexArray[renderIndex];
            indexArray[workIndex] = indexArray[renderIndex];
            glp[workIndex] = glp[renderIndex];
        workMutex.unlock();
    }
    
protected:
    /// set type for GL-rendering, e.g. GL_TRIANGLES, GL_QUADS
    void setType(GLenum t) { glp[workIndex].type = t; }
// data. double buffered. rendering uses [renderIndex], worker-task uses [workIndex]
    QVarLengthArray<GLVertex>    vertexArray[2];
    QVarLengthArray<VertexData>  vertexDataArray; // only one, since not needed for OpenGL drawing!
    QVarLengthArray<GLuint>      indexArray[2];
    GLParameters glp[2];

    unsigned int renderIndex;
    unsigned int workIndex;    
};


#endif
