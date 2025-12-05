#include "InvertedIndex.h"
#include <chrono>

using namespace std;

using namespace std::chrono;

// int main()
// {
// 	InvertedIndex movies("moviesdb/");
// 	movies.search();
// 	return 0;
// }


int main()
{
	auto start = high_resolution_clock::now();

	InvertedIndex flowers("baby-dataset-flowers");
	flowers.search();

	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Time: " << duration.count() << endl;
	return 0;
}

