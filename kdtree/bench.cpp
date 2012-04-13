
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>

#include <stdlib.h>
#include <cassert>
#include <boost/timer.hpp>

#include "kdtree.hpp"
boost::timer timer;

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
void format_line(int num_points, int num_tests, double total_time, double time_per_test) {
    std::cout << "| " << std::setw(16) << num_points << " ";
    std::cout << "| " << std::setw(15) << num_tests << " ";
    std::cout << "| " << std::setw(17) << time_per_test << " ";
    std::cout << "| " << std::setw(17) << total_time << " ";
    std::cout << "| " << std::setw(17) << 1e6*time_per_test/(log(num_points)/log(2)) << " ";
    std::cout << "|" << std::endl << std::flush;
}

void run_test(int NUM_TESTS, std::vector<int> NUM_POINTS, std::vector<int> NUM_RUNS) {
    for (int i = 0; i < NUM_TESTS; ++i) {

        kdtree::KDTree<Point> tr(2);
        for(int k=0; k<NUM_POINTS[i]; k++) {
            double x = ((float)rand() / RAND_MAX) * 200.0 - 100.0;
            double y = ((float)rand() / RAND_MAX) * 200.0 - 100.0;
            Point p(x,y);
            tr.insert( p );
        }
    
        timer.restart();
        for (int j = 0; j < NUM_RUNS[i]; ++j) {
            double x = ((float)rand() / RAND_MAX) * 200.0 - 100.0;
            double y = ((float)rand() / RAND_MAX) * 200.0 - 100.0;
            Point ps(x,y);
            std::pair<Point,double> pt = tr.nearest( ps );
        }
        double total_time = timer.elapsed();
        double time_per_test = total_time / NUM_RUNS[i];
        format_line(NUM_POINTS[i], NUM_RUNS[i], total_time, time_per_test);
    }
}

int main() {
    const int max_exponent = 30;
    std::vector<int> NUM_POINTS;
    std::vector<int> NUM_RUNS;

    for (int m=10;m<max_exponent;m++) {
        NUM_POINTS.push_back( (int)( pow(2,0.5*m) ) ); // this nicely spaced points on log-axis
        if (m<20)
            NUM_RUNS.push_back(1000000);
        else if (m<30)
            NUM_RUNS.push_back(100000);
        else
            NUM_RUNS.push_back(10000);
    }
    int NUM_TESTS = NUM_POINTS.size();

    run_test(NUM_TESTS, NUM_POINTS, NUM_RUNS);
    

    return 0;
}
