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

#include <iostream>
#include <cassert>
#include <set>
#include <vector>

#include <boost/foreach.hpp>

#include "gldata.hpp"


GLData::GLData() {
    // some reasonable defaults...
    type = GL_TRIANGLES;
    polyVerts = 3;
    polygonMode_face = GL_FRONT_AND_BACK;
    polygonMode_mode = GL_LINE;

}

unsigned int GLData::addVertex(float x, float y, float z, float r, float g, float b) {
    return addVertex( GLVertex(x,y,z,r,g,b) );
}

unsigned int GLData::addVertex(float x, float y, float z, float r, float g, float b, float nx, float ny, float nz) {
    return addVertex( GLVertex(x,y,z,r,g,b,nx,ny,nz) );
}

unsigned int GLData::addVertex(GLVertex v) {
    // add vertex with empty polygon-list.
    unsigned int idx = vertexArray.size();
    vertexArray.append(v);
    vertexDataArray.append( VertexData() );
    assert( vertexArray.size() == vertexDataArray.size() );
    return idx; // return index of newly appended vertex
}


void GLData::setNormal(unsigned int vertexIdx, float nx, float ny, float nz) {
    vertexArray[vertexIdx].setNormal(nx,ny,nz);
}

void GLData::removeVertex( unsigned int vertexIdx ) {
    // i) for each polygon of this vertex, call remove_polygon:
    typedef std::set< unsigned int, std::greater<unsigned int> > PolygonSet;
    PolygonSet pset = vertexDataArray[vertexIdx].polygons;
    BOOST_FOREACH( unsigned int polygonIdx, pset ) {
        //std::cout << " removeVertex( " << vertexIdx << " calling removePolygon( " << polygonIdx << " )\n";
        removePolygon( polygonIdx );
    }
    // ii) overwrite with last vertex:
    unsigned int lastIdx = vertexArray.size()-1;
    if (vertexIdx != lastIdx) {
        vertexArray[vertexIdx] = vertexArray[lastIdx];
        vertexDataArray[vertexIdx] = vertexDataArray[lastIdx];
        // request each polygon to re-number this vertex.
        BOOST_FOREACH( unsigned int polygonIdx, vertexDataArray[vertexIdx].polygons ) {
            unsigned int idx = polygonIdx*polyVerts;
            for (int m=0;m<polyVerts;++m) {
                if ( indexArray[ idx+m ] == lastIdx )
                    indexArray[ idx+m ] = vertexIdx;
            }
        }
    }
    // shorten array
    vertexArray.resize( vertexArray.size()-1 );
    vertexDataArray.resize( vertexDataArray.size()-1 );
    assert( vertexArray.size() == vertexDataArray.size() );
    //std::cout << " removeVertex done.\n";
}

int GLData::addPolygon( std::vector<GLuint>& verts) {
    // append to indexArray, request each vertex to update
    unsigned int polygonIdx = indexArray.size()/polyVerts;
    BOOST_FOREACH( GLuint vertex, verts ) {
        indexArray.append(vertex);
        vertexDataArray[vertex].addPolygon(polygonIdx); // add index to vertex i1
    }
    return polygonIdx;
}

void GLData::removePolygon( unsigned int polygonIdx) {
    //std::cout << "   GLData::removePolygon( " << polygonIdx << " )\n";
    unsigned int idx = polyVerts*polygonIdx; // start-index for polygon
    
    // i) request remove for each vertex in polygon:
    for (int m=0; m<polyVerts ; ++m) // this polygon has the following 3/4 vertices. we call removePolygon on them all
        vertexDataArray[ indexArray[idx+m]   ].removePolygon(polygonIdx);
    
    // check for orphan vertices (?), and delete them (?)
    
    unsigned int last_index = (indexArray.size()-polyVerts);
    // if deleted polygon is last on the list, do nothing??
    if (idx!=last_index) { 
        // ii) remove from polygon-list by overwriting with last element
        for (int m=0; m<polyVerts ; ++m)
            indexArray[idx+m  ] = indexArray[ last_index+m   ];
        // iii) for the moved polygon, request that each vertex update the polygon number
        for (int m=0; m<polyVerts ; ++m) {
            vertexDataArray[ indexArray[idx+m   ] ].addPolygon( idx/polyVerts ); // this is the new polygon index
            vertexDataArray[ indexArray[idx+m   ] ].removePolygon( last_index/polyVerts ); // this polygon is no longer there!
        }
    }
    indexArray.resize( indexArray.size()-polyVerts ); // shorten array
    //std::cout << "   removePolygon( " << polygonIdx << " ) done.\n";
} 
    
void GLData::print() {
    std::cout << "GLData vertices: \n";
    //int n = 0;
    for( int n = 0; n < vertexArray.size(); ++n ) {
        std::cout << n << " : ";
        vertexArray[n].str();
        std::cout << " polys: "; 
        //vertexDataArray[n].str();
        std::cout << "\n";
    }
    std::cout << "GLData polygons: \n";
    int polygonIndex = 0;
    for( int n=0; n< indexArray.size(); n=n+polyVerts) {
        std::cout << polygonIndex << " : ";
        for (int m=0;m<polyVerts;++m)
            std::cout << indexArray[n+m] << " "; 
        std::cout << "\n";
        ++polygonIndex;
    }
}


