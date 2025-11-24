#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main()
{
	//
	// vector de pairs: recurrencia, frecuencia
	map<string, vector<pair<string, int>>> index;
	index["cat"];
	index["ball"];
	index["meow"];

	index["cat"].push_back({"meow.txt", 50});
	cout << index["cat"][0].first << endl;
	cout << index["cat"][0].second << endl;

	pair<string, int> test;
	test.second++;
	test.first = "meow";
	cout << test.first << endl;
	cout << test.second << endl;

	return 0;
}
