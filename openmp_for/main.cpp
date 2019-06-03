#include <cmath>
#include <cstdio>
#include <ctime>
#include <iostream>

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

void omp_reduction_array(void)
{
// from http://dvalts.io/optimisation/code/2016/11/06/OpenMP-array_reduction.html
  int myArray[6] = {};
  // Print the array elements to see them before
  std::cout << "Array before run: " << std::endl;
  for (int n = 0; n<6; ++n)
  {
    std::cout << myArray[n] << " " << std::endl;
  } 


  #pragma omp parallel for reduction(+:myArray[:6])
  for (int i=0; i<50; ++i)
  {
    double a = 2.0; // Or something non-trivial justifying the parallelism...
    for (int n = 0; n<6; ++n)
    {
      myArray[n] += a;
    }
  }
  std::cout << "Array after run: " << std::endl;
  // Print the array elements to see them summed
  // add 2 50-times to each element = 100.
  for (int n = 0; n<6; ++n)
  {
    std::cout << myArray[n] << " " << std::endl;
  } 
}

int main()
{
	omp_parallel_test();
	omp_forloop();
	omp_reduction_array();
}
