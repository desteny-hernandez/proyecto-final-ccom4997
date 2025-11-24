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

		// con un for loop

	// for (auto &i : index)
	// {
	// 	cout << i.first << endl;
	// 	i.second.push_back({1, 5});
	// 	for (auto &i2 : i.second)
	// 	{
	// 		cout << "multimap llave: " << i2.first << endl;
	// 		cout << "multimap valor: " << i2.second << endl;
	// 		cout << endl;
	// 	}
	// }

	return 0;
}
