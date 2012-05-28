
#include <string>
#include <iostream>


#include <stdlib.h>
#include <cassert>

#include "kdtree.hpp"

struct Point {
    Point() {
        x.reserve(2);
        x[0]=0;x[1]=0;
    }
    Point(double xi,double yi) { 
        x.clear();
        x.push_back(xi);
        x.push_back(yi);

    }
    double dist(const Point& p) const {
        return (x[0]-p[0])*(x[0]-p[0]) + (x[1]-p[1])*(x[1]-p[1]); 
    }
    double operator[](unsigned int i) const {
        return x[i];
    }
    double& operator[](unsigned int i) { return x[i]; }
    
    std::vector<double> x;
};

int main() {
    kdtree::KDTree<Point> tr(2);
    
    int vcount = 10000;
    for(int i=0; i<vcount; i++) {
        float x, y;
        x = ((float)rand() / RAND_MAX) * 200.0 - 100.0;
        y = ((float)rand() / RAND_MAX) * 200.0 - 100.0;

        //double r = x*x+y*y; //+z*z;
        //std::cout << "inserting " << x << " " << y << "  r= " << r << "\n";
        Point p(x,y);
        
        assert( tr.insert( p ) == 0);
    }
    
    //tr.print_tree();
    
    Point ps(0,0);
    std::pair<Point,double> pt = tr.nearest( ps );
    if (pt.second)
        std::cout << "nearest " << pt.first[0] << " " << pt.first[1] << "\n";
    std::cout << " calls: " << tr.get_num_calls() << "\n";
    return 0;
}
