#include <cmath>
#include <cstdio> 
#include <ctime>

void omp_parallel_test(void) {
#pragma omp parallel
  {
    // Code inside this region runs in parallel.
    // will print Hello for each thread created
    printf("Hello!\n");
  }
}

void omp_forloop() {

	const int size = 256000;
	double sinTable[size];
	std::clock_t t;

	// single-thread
	t = std::clock();
        for(int n=0; n<size; ++n)
                sinTable[n] = std::sin(2 * M_PI * n / size);
        t = std::clock() - t;
        printf("single-thread for took %.3f s\n", float(t)/CLOCKS_PER_SEC);

	// parallel
	t = std::clock();
    	#pragma omp parallel for
    	for(int n=0; n<size; ++n)
      		sinTable[n] = std::sin(2 * M_PI * n / size);
 	t = std::clock() - t;
	printf("parallel for took %.3f s\n", float(t)/CLOCKS_PER_SEC);
    	// the table is now initialized

}

int main()
{
	omp_parallel_test();
	omp_forloop();
}
