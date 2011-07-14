#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>

#define PI 3.14159265

double diangle(double x, double y)
{
    if (y >= 0)
        return (x >= 0 ? y/(x+y) : 1-x/(-x+y));
    else
        return (x < 0 ? 2-y/(-x-y) : 3+x/(x-y));
}

double xCoord(double a) {
    return (a < 2 ? 1-a : a-3);
}
double yCoord(double a) {
    return (a < 3 ? ((a > 1) ? 2-a : a) : a-4);
}
double norm(double x, double y) {
    return sqrt(x*x+y*y);
}

int main () {
    std::cout << "compare radians to diangles"  << std::endl;
    const int Nmax = 10000000;
    std::vector<double> rad(Nmax);
    std::vector<double> dia(Nmax);
    clock_t c0, c1;
    
    for(std::size_t i=0;i<rad.size();i++) {
        rad[i]=(double)i/(double)rad.size()*2*PI;
        dia[i]=(double)i/(double)rad.size()*4.0;
    }
    
    // radians to unit-vectors
    std::vector<double> x1(Nmax);
    std::vector<double> y1(Nmax);
    c0 = clock();
    for(std::size_t i=0;i<rad.size();i++) {
        x1[i]=cos(rad[i]);
        y1[i]=sin(rad[i]);
    }
    c1 = clock();
    std::cout << "cos/sin\t" << (float)(c1 - c0)/CLOCKS_PER_SEC << "\n";
    
    // unit-vectors to radians
    std::vector<double> rad2(Nmax);
    c0 = clock();
    for(std::size_t i=0;i<rad.size();i++) {
        rad2[i] = atan2( y1[i] , x1[i] );
    }
    c1 = clock();
    std::cout << "atan2\t" << (float)(c1 - c0)/CLOCKS_PER_SEC << "\n";
    
    // diangles to unit-vectors
    std::vector<double> x2(Nmax);
    std::vector<double> y2(Nmax);
    double l;
    c0 = clock();
    for(std::size_t i=0;i<rad.size();i++) {
        x2[i]=xCoord(dia[i]);
        y2[i]=yCoord(dia[i]);
        l=norm(x2[i],y2[i]);
        x2[i]=x2[i]/l;
        y2[i]=y2[i]/l;
    }
    c1 = clock();
    std::cout << "dia2vec\t" << (float)(c1 - c0)/CLOCKS_PER_SEC << "\n";    
    
    // unit-vectors to diangles
    std::vector<double> dia2(Nmax);
    c0 = clock();
    for(std::size_t i=0;i<rad.size();i++) {
        dia2[i]=diangle(x2[i],y2[i]);
    }
    c1 = clock();
    std::cout << "vec2dia\t" << (float)(c1 - c0)/CLOCKS_PER_SEC << "\n";     
    
       
}
