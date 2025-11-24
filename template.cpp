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
int readFiles(const string &directory, map<string, map<string, int>> &index)
{
	int counter = 0;

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

			string word;

			while (file >> word)
			{
				index[word][entry.path().filename().string()]++;
			}
		}
	}
	// returns the amount of files in that folder
	return counter;
}

// uso: imprime el inverted index creado
// input: inverted index maps
void invertedIndexDisplay(const map<string, map<string, int>> &index)
{
	// imprime el inverted index
	for (auto &i : index)
	{
		// llave: palabra encontrada | valor: nodo de un map
		cout << "palabra: \"" << i.first << "\"" << endl;

		// para accesar el nombre del documento y la frecuencia de esa palabra, se itera por el valor de cada palabra
		int k = 0;
		for (auto &j : i.second)
		{
			// llave: documento | valor: frecuencia en ese documento
			cout << "\t" << ++k << ". nombre del documento: " << j.first << " | frecuencia: " << j.second << endl;
		}
		cout << endl;
	}
}

void search(const string word, const map<string, map<string, int>> &index)
{

	cout << "\nbuscando \"" << word << "\" en el inverted index..." << endl;
	if (index.find(word) != index.end())
	{
		cout << "la palabra \"" << word << "\" fue encontrada con mayor frecuencia en los siguientes 3 documentos: " << endl;
		multimap<int, string, greater<int>> wordSearch;
		for (auto &i : index.at(word))
		{
			// se le añade al multimap las llaves y los valores encontrados para el inverted_index
			wordSearch.insert({i.second, i.first});
		}
		// se imprime las primeras 3 instancias encontradas
		auto it = wordSearch.begin();
		int k = 0;
		while (it != wordSearch.end() && k < 3)
		{
			cout << "\t" << ++k << ". frecuencia: " << it->first << " | nombre: " << it->second << endl;
			it++; // se mueve al otro nodo
		}
	}
	else
	{
		cout << "\"" << word << "\" no fue encontrada (T_T)" << endl;
	}
}

int main()
{
	map<string, map<string, int>> inverted_index;

	// int baby_dataset = readFiles("baby-dataset-flowers/", inverted_index);
	// cout << "The amount of files in baby dataset is: " << baby_dataset << "\n";

	int movies = readFiles("moviesdb/", inverted_index);
	cout << "The amount of files in moviesdb is: " << movies << "\n";

	search("flower", inverted_index);

	// invertedIndexDisplay(inverted_index);

	// int movies_dataset = readFiles("moviesdb/");
	// cout << "The amount of files in moviesdb is: " << movies_dataset << "\n";

	return 0;
}