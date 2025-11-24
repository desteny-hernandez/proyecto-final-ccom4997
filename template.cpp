#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;
namespace fs = filesystem;

// itera por todos los archivos del folder
// input: nombre del folder (string)
// output: cantidad de archivos (int)
int readFiles(const string &directory)
{
	int counter = 0;
	map<string, map<string, int>> inverted_index;

	// itera por todos los archivos del folder
	for (const auto &entry : fs::directory_iterator(directory))
	{
		if (entry.is_regular_file())
		{
			ifstream file(entry.path());
			if (!file.is_open())
			{
				cerr << "No se pudo abrir el archivo: " << entry.path() << '\n';
				continue;
			}
			counter++;

			// imprime el nombre del archivo
			// entry.path().filename().string()

			string word;

			while (file >> word)
			{
				inverted_index[word][entry.path().filename().string()]++;
			}
		}

		// imprime el inverted index
		for (auto i = inverted_index.begin(); i != inverted_index.end(); i++)
		{
			// llave: palabra encontrada | valor: nodo de un map
			cout << "palabra: \"" << i->first << "\"" << endl;

			// para accesar el nombre del documento y la frecuencia de esa palabra, se itera por el valor de cada palabra
			int k = 0;
			for (auto j = inverted_index[i->first].begin(); j != inverted_index[i->first].end(); j++)
			{
				// llave: documento | valor: frecuencia en ese documento
				cout << "\t" << ++k << ". nombre del documento: " << j->first << " | frecuencia: " << j->second << endl;
			}
			cout << endl;
		}
	}
	// returns the amount of files in that folder
	return counter;
}

int main()
{

	// How you send the file name dependes of where your executable file is
	int baby_dataset = readFiles("baby-dataset-flowers/");
	cout << "The amount of files in baby dataset is: " << baby_dataset << "\n";

	// int movies_dataset = readFiles("moviesdb/");
	// cout << "The amount of files in moviesdb is: " << movies_dataset << "\n";

	return 0;
}