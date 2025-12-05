#include "InvertedIndex.h"
#include <chrono>

using namespace std;

using namespace std::chrono;

int main()
{
	InvertedIndex movies("moviesdb/");
	movies.search();
	return 0;
}




