
// from: http://www.cgal.org/Manual/latest/doc_html/cgal_manual/Generator_ref/Function_random_polygon_2.html
//
// "2-opt" heuristic for generating a random polygon

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/random_polygon_2.h>
#include <CGAL/Random.h>
#include <CGAL/algorithm.h>


#include <CGAL/double.h>
typedef double RT;


#include <fstream>
#include <list>

typedef CGAL::Simple_cartesian<RT>                        K;
typedef K::Point_2                                        Point_2;
typedef std::list<Point_2>                                Container;
typedef CGAL::Polygon_2<K, Container>                     Polygon_2;
typedef CGAL::Creator_uniform_2<RT, Point_2>             Creator;
typedef CGAL::Random_points_in_square_2<Point_2, Creator> Point_generator;

typedef Polygon_2::Vertex_iterator VertexItr;

const double RADIUS = 1.0;
const int MAX_POLY_SIZE = 100;

int main( ) {
    Polygon_2            polygon;
    std::list<Point_2>   point_set;
    CGAL::Random         rand;

    int size = rand.get_int(4, MAX_POLY_SIZE);

    // copy size points from the generator, eliminating duplicates, so the
    // polygon will have <= size vertices
    CGAL::copy_n_unique( Point_generator(RADIUS), size,
                         std::back_inserter(point_set));
    /*
    std::ostream_iterator< Point_2 >  out( std::cout, " " );
    std::cout << "From the following " << point_set.size() << " points "
             << std::endl;
    std::copy(point_set.begin(), point_set.end(), out);
    std::cout << std::endl;
    */
    
    CGAL::random_polygon_2(point_set.size(), 
                           std::back_inserter(polygon),
                           point_set.begin());
    std::cout << "The following simple polygon was made: " << std::endl;
    std::cout << " N = " << polygon.size() << "\n";
    VertexItr it, it_end;
    it= polygon.vertices_begin();
    it_end = polygon.vertices_end();
    for( ; it!=it_end; it++) {
        std::cout << "( " << it->x() << " , " << it->y() << " )"  << "\n";
    }
    return 0;
}
