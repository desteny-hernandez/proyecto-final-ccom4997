#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;
namespace fs = filesystem;

class InvertedIndex
{
private:
	map<string, map<string, int>> inverted_index;
	int countFiles; // cantidad de files leidos
	int indexSize;	// cantidad de palabras guardadas en el inverted_index

public:
	InvertedIndex()
	{
		countFiles = -1;
	}

	// le puedes dar al constructor
	InvertedIndex(const string &directory)
	{
		readFiles(directory);
		indexSize = inverted_index.size(); // guarda la cantidad de palabras que se encuantra en el inverted_inde
	}

	// uso: imprime cuantos archivos ha leido para el inverted index
	void getFilesAmount() const
	{
		if (countFiles == -1)
		{
			cout << "No se ha leido ningún archivo ヽ(*。>Д<)o゜" << endl;
		}
		else
		{
			cout << "Se ha leido un total de " << countFiles << " archivos." << endl;
		}
	}

	// uso: imprime el size del inverted index;
	int size() const
	{
		return indexSize; // guarda la cantidad de palabras que se encuantra en el inverted_inde
	}

	// uso: itera por todos los archivos del folder y guarda todas las palabras encontradas en ellas en el inverted_index
	// input: nombre del folder (string)
	void readFiles(const string &directory)
	{
		countFiles = 0;
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
				string word;
				while (file >> word)
				{
					inverted_index[word][entry.path().filename().string()]++;
				}
				countFiles++; // incrementa el contador de files
			}
		}
	}

	// uso: busca "word" adentro del inverted_index
	// input: word := palabra que se va a buscar, all := desplega TODOS los archivos donde "word" fue encontrado
	void search(const string &word, bool all = false) const
	{
		cout << "\nBuscando \"" << word << "\" en el inverted index..." << endl;
		if (inverted_index.find(word) != inverted_index.end())
		{

			multimap<int, string, greater<int>> searchedWord; // se crea un multimap que guarda en cuales documentos se encuantra word
			int contador = 0;																	// cuenta las veces que se encontró la palabra en el inverted_index
			for (auto &i : inverted_index.at(word))
			{
				// se le añade al multimap las llaves y los valores encontrados para el inverted_index
				searchedWord.insert({i.second, i.first});
				contador++;
			}

			// desplega cantidad de veces que la palabra fue encontrada
			cout << "la palabra \"" << word << "\" fue encontrada en ";
			if (contador == 1)
				cout << "solo un archivo: " << endl;
			else if (contador == 2)
				cout << "dos archivos: " << endl;
			else
				cout << contador << " archivos y fue utilizada con mayor frecuencia en los siquientes: " << endl;

			// se imprime las primeras 3 instancias encontradas
			auto it = searchedWord.begin();
			contador = 0; // reset el contador
			if (all)
				while (it != searchedWord.end())
				{
					cout << "\t" << ++contador << ". " << it->second << " | cantidad: " << it->first << endl;
					it++; // se mueve al proximo nodo
				}
			else
				while (it != searchedWord.end() && contador < 3)
				{
					cout << "\t" << ++contador << ". " << it->second << " | cantidad: " << it->first << endl;
					it++; // se mueve al proximo nodo
				}
		}
		else
		{
			cout << "\"" << word << "\" no fue encontrada en ningún archivo (T_T)" << endl;
		}
	}

	// uso: imprime el inverted index creado
	void display()
	{
		// imprime el inverted index
		for (auto &i : inverted_index)
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

	// ask for word and database?
	void menu()
	{
		cout << endl;
		cout << "Bienvenido al motor de búsqueda...." << endl;

		cout << "  ,--,                            ,-.            " << endl;
		cout << ",--.'|                        ,--/ /|            " << endl;
		cout << "|  | :     ,---.     ,---.  ,--. :/ |            " << endl;
		cout << ":  : '    '   ,'\\   '   ,'\\ :  : ' /             " << endl;
		cout << "|  ' |   /   /   | /   /   ||  '  /        .--,  " << endl;
		cout << "'  | |  .   ; ,. :.   ; ,. :'  |  :      /_ ./|  " << endl;
		cout << "|  | :  '   | |: :'   | |: :|  |   \\  , ' , ' :  " << endl;
		cout << "'  : |__'   | .; :'   | .; :'  : |. \\/___/ \\: |  " << endl;
		cout << "|  | '.'|   :    ||   :    ||  | ' \\ \\.  \\  ' |  " << endl;
		cout << ";  :    ;\\   \\  /  \\   \\  / '  : |--'  \\  ;   :  " << endl;
		cout << "|  ,   /  `----'    `----'  ;  |,'      \\  \\  ;  " << endl;
		cout << " ---`-'                     '--'         :  \\  \\ " << endl;
		cout << "                                          \\  ' ; " << endl;
		cout << "                                           `--`  " << endl;
	}
};

int main()
{
	// InvertedIndex movies("moviesdb/");
	InvertedIndex plants("baby-dataset-flowers/");

	plants.getFilesAmount();
	plants.search("flowers", true);
	plants.search("and", true);

	plants.menu();

	return 0;
}