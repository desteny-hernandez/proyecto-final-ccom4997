#include "InvertedIndex.h"

using namespace std;

int main()
{
	InvertedIndex movies("moviesdb/");
	movies.search();
	return 0;
}

