#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

#include <iomanip>
#include <iostream>
#include <fstream>
#include <numeric>

#include <openvoronoi/voronoidiagram.hpp>
#include <openvoronoi/version.hpp>
#include <openvoronoi/utility/vd2svg.hpp>

#include <boost/random.hpp>
#include <boost/timer.hpp>


//const char *POINT_INPUT_FILE = "bv_point_orig.txt";
const char *POINT_INPUT_FILE = "bv_point_mod.txt";

typedef ovd::Point point_type;
typedef double coordinate_type;

void construct_voronoi_points(std::vector<point_type>& points) {
    int bins =  (int)(sqrt(2)*sqrt(points.size()));  // number of bins for nearest-neighbor bin-search
    ovd::VoronoiDiagram* vd = new ovd::VoronoiDiagram(1,bins);
    for(unsigned int n=0;n<points.size();++n) {
        std::cout << "inserting point " << n << " : " << points[n] << "\n";
        vd->insert_point_site( points[n] ); // insert each point. This returns an int-handle which we do not use here.
    }
    assert( vd->check() ); // this runs a sanity-check on the diagram. This is slow, so run only in debug mode.

    vd2svg("bv.svg", vd);
    delete vd;
}



int main(int argc,char *argv[]) {
    std::vector<point_type> points;
    std::ifstream input_file(POINT_INPUT_FILE);
    int num_points;
    coordinate_type x, y;
    input_file >> num_points;
    std::cout << "num_points = " << num_points << "\n";
    points.reserve(num_points);
    for (int i = 0; i < num_points; ++i) {
        
            input_file >> x >> y;
            // coordinate_type minimum_coordinate = std::numeric_limits<uint32_t>::min();
            // coordinate_type maximum_coordinate = std::numeric_limits<uint32_t>::max();
            coordinate_type minimum_coordinate = 8000;
            coordinate_type maximum_coordinate = 23000;
            std::cout << i << " : " << x << " " << y << " : "; // << "\n";
            // For OpenVoronoi we scale coordinates so they fit within a unit circle.
            // e.g. a box centered at (0,0) with side-length 0.8
            x -= (maximum_coordinate+minimum_coordinate)/2; // center around x=0
            y -= (maximum_coordinate+minimum_coordinate)/2; // center around y=0
            x *= 2/(maximum_coordinate-minimum_coordinate); // scale to fit within [-0.4, 0.4]
            y *= 2/(maximum_coordinate-minimum_coordinate); // scale to fit within [-0.4, 0.4]
            assert( (-1 <= x) && ( x <= 1 ) );
            assert( (-1 <= y) && ( y <= 1 ) );
            std::cout << x << " " << y  << "\n";
            
            // all point-sites must be unique!
            assert( std::count( points.begin(), points.end(), point_type(x, y) ) == 0 );

            points.push_back(point_type(x, y));
    }
    input_file.close();

    construct_voronoi_points(points);

    return 0;
}

