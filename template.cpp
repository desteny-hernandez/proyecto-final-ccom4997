#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;
namespace fs = filesystem;

class InvertedIndex
{
private:
	unordered_map<string, unordered_map<string, int>> inverted_index;
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
		return indexSize; // guarda la cantidad de palabras que se encuantra en el inverted_index
	}

	// use: iterate through the string and create a new string without the commas or periods
	string rebuild(string key)
	{
		string res;
		for (char c : key)
		{
			if (c != ',' && c != ';' && c != '.' && c != '(' && c != ')' && c != ':' && c != '!' && c != '?' && c != '[' && c != ']' && c != '{' && c != '}')
			{
				res += c;
			}
		}
		return res;
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
					string new_word = rebuild(word);
					inverted_index[new_word][entry.path().filename().string()]++;
				}
				countFiles++; // incrementa el contador de files
			}
		}
	}

	// uso: busca "word" adentro del inverted_index
	// input: word := palabra que se va a buscar
	void singleSearch(const string &word) const
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

	void doubleSearch(const string &word1, const string &word2) const
	{
		cout << "\nBuscando \"" << word1 << "\" y \"" << word2 << "\" en el inverted index..." << endl;

		// verifica si ambas palabras se encuantran en el inverted_index
		if (inverted_index.find(word1) == inverted_index.end() || (inverted_index.find(word2) == inverted_index.end()))
		{
			if (inverted_index.find(word1) == inverted_index.end() && (inverted_index.find(word2) == inverted_index.end()))
				cout << "\"" << word1 << "\" ni \"" << word2 << "\" fueron encontradas en ningún archivo (T_T)" << endl;
			else if (inverted_index.find(word1) == inverted_index.end())
				cout << "\"" << word1 << "\" no fue encontrada en ningún archivo (T_T) pero \"" << word2 << "\" si fue encontrada." << endl;
			else if ((inverted_index.find(word2) == inverted_index.end()))
				cout << "\"" << word2 << "\" no fue encontrada en ningún archivo (T_T) pero \"" << word1 << "\" si fue encontrada." << endl;
			return; // se sale de la busqueda
		}

		unordered_map<string, int> docsWord1;		 // se crea un unordered_map que guarda en cuales documentos se encuantra word1
		for (auto &i : inverted_index.at(word1)) // iteramos por el valor de la llave "word1" del inverted_index
			docsWord1.insert({i.first, i.second});

		unordered_map<string, int> docsWord2; // y word2
		for (auto &i : inverted_index.at(word2))
			docsWord2.insert({i.first, i.second});

		// se crea un multimap con las frecuencias mas altas de ambas palabras
		multimap<int, string, greater<int>> searchedWord;
		int contador = 0;					// cuenta las veces que se encontró ambas palabras en el mismo documento
		for (auto &i : docsWord1) // se itera por cualquier de los dos mapas
		{
			auto it = docsWord2.find(i.first); // iterador que apunta a la llave (documento) encontrado en docsWord2
			if (it != docsWord2.end())
			{ // si se encuantra la misma llave (documento) que tiene docsWord1 en docsWord2
				// le suma la cantidad de veces que ambas palabras aparecen en el mismo documento
				searchedWord.insert({it->second + i.second, i.first});
				contador++;
			}
		}

		// desplega cantidad de veces que la palabra fue encontrada
		cout << "la palabra \"" << word1 << "\" y \"" << word2 << "\" fueron encontradas en ";
		if (contador == 1)
			cout << "solo un archivo: " << endl;
		else if (contador == 2)
			cout << "dos archivos: " << endl;
		else
			cout << contador << " archivos y fue utilizada con mayor frecuencia en los siquientes: " << endl;

		// se imprime las primeras 3 instancias encontradas
		auto it = searchedWord.begin();
		contador = 0; // reset el contador
		while (it != searchedWord.end() && contador < 3)
		{
			cout << "\t" << ++contador << ". " << it->second << " | cantidad: " << it->first << endl;
			it++; // se mueve al proximo nodo
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

	// le pregunta al usuario si desea hacer otra busqueda
	void menuLoop()
	{
		int selection;
		do
		{
			cout << "\nDesea buscar de nuevo?" << endl;
			cout << "\t1. Si." << endl;
			cout << "\t2. No." << endl;
			cout << "\t\tSeleccione el número: ";
			char space;
			cin >> selection;
			cin.get(space); //  atrapa el [enter] cuando seleciona el número
			switch (selection)
			{
			case 1:
				getSearchWord();
				break;
			case 2:
				cout << "Adios!" << endl;
				break;
			default:
				cout << "Selección erronea. Intente denuevo!" << endl;
				break;
			}
		} while (selection == 1);
	}

	// uso: toma de input la busqueda
	void getSearchWord()
	{
		string searchWord;
		cout << "\nEscriba su busqueda: ";
		getline(cin, searchWord);
		WordSearchAmount(searchWord);
	}

	// uso: determina si la busqueda es de una palabra o dos
	void WordSearchAmount(string &word)
	{
		if (word.find(' ') == -1)
			singleSearch(word);
		else
		{
			string word1;
			string word2;
			bool word2start = false;
			for (char &c : word)
			{
				if (c == ' ')
				{
					word2start = true;
					continue;
				}
				if (word2start)
					word2 += c;
				else
					word1 += c;
			}
			doubleSearch(word1, word2);
		}
	}

	// prints out the logo of looky
	void welcomeScreen()
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
		cout << endl;
	}

	// uso: crea una pausa para que el usuario presione [ENTER] antes de continuar
	void enterPrompt()
	{
		cout << "\nPresione [ENTER] para continuar..." << endl;
		char space;
		cin.get(space); //  espera a que el usuario precione [ENTER] para continuar
	}
};

int main()
{
	InvertedIndex movies("moviesdb/");
	movies.welcomeScreen();
	movies.getSearchWord();
	movies.enterPrompt();
	movies.menuLoop();
	return 0;
}