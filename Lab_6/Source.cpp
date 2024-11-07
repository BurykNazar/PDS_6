#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include<string>
#include<Windows.h>

using namespace std;


unsigned int N, M;

bool readGraph(const string& inputFile, vector<vector<int>>& edges) {
	ifstream file(inputFile);
	if (!file.is_open()) {
		cerr << "Помилка при зчитуванні файла графа."
			<< endl;
		return false;
	}
	file >> N >> M;
	edges.clear();
	edges.resize(M, vector<int>(2));
	for (int i = 0; i < M; i++) {
		file >> edges[i][0] >> edges[i][1];
		edges[i][0]--;
		edges[i][1]--;
	}
	file.close();
}

void getAdjacencyMatrix(const vector<vector<int>>& edges, vector<vector<int>>& matrix) {
	matrix.clear();
	matrix.resize(N, vector<int>(N, 0));
	
	for (size_t i = 0; i < edges.size(); i++) {
		int u = edges[i][0];
		int v = edges[i][1];
		matrix[u][v] = 1;
	}
}

void getIncidenceMatrix(const vector<vector<int>>& edges, vector<vector<int>>& matrix) {
	matrix.clear();
	matrix.resize(N, vector<int>(M, 0));
	
	for (size_t i = 0; i < edges.size(); i++) {
		int u = edges[i][0];
		int v = edges[i][1];
		matrix[u][i] = 1;
		matrix[v][i] = -1;
	}
}

void printAdjacencyMatrix(const vector<vector<int>>& matrix, ostream& out) {
    out << "Матриця суміжності:\n";

    out << "|---------";
    for (size_t i = 0; i < N; i++) {
        out << "-----";
    }
    out << "|\n";

    out << "|      |" << setw(4);
    for (size_t i = 0; i < N; i++) {
        out << setw(4) << i + 1 << setw(2) << "|";
    }
    out << "\n";

    out << "|---------";
    for (size_t i = 0; i < N; i++) {
        out << "-----";
    }
    out << "|\n";

    for (size_t i = 0; i < N; i++) {
        out << "|  " << setw(2) << i + 1 << "  ";
        for (size_t j = 0; j < N; j++) {
            out << "| " << setw(3) << matrix[i][j] << " ";
        }
        out << "|\n";

        out << "|---------";
        for (size_t j = 0; j < N; j++) {
            out << "-----";
        }
        out << "|\n";
    }
}

void printIncidenceMatrix(const vector<vector<int>>& matrix, ostream& out) {
    out << "Матриця інцидентності:\n";

    out << "|----------";
    for (size_t i = 0; i < M; i++) {
        out << "-----";
    }
    out << "|\n";

    out << "|      |" << setw(4);
    for (size_t i = 0; i < M; i++) {
        out << setw(4) << i + 1 << setw(2) << "|";
    }
    out << "\n";

    out << "|----------";
    for (size_t i = 0; i < M; i++) {
        out << "-----";
    }
    out << "|\n";

    for (size_t i = 0; i < N; i++) {
        out << "|  " << setw(2) << i + 1 << "  ";
        for (size_t j = 0; j < M; j++) {
            out << "| " << setw(3) << matrix[i][j] << " ";
        }
        out << "|\n";

        out << "|----------";
        for (size_t j = 0; j < M; j++) {
            out << "-----";
        }
        out << "|\n";
    }
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string filePath;
	cout << "Введіть шлях до файлу графа: ";
	getline(cin, filePath);
	vector<vector<int>> edges;
	if (!readGraph(filePath, edges))
		return 1;
	
	cout << "Граф має " << N << " вершини і " << M << " ребер." << endl;
	cout << "Ребра графа:" << endl;

	for (size_t i = 0; i < edges.size(); i++) {
		cout << edges[i][0] + 1 << " - " << edges[i][1] + 1 << endl;
	}

	vector<vector<int>> adjacencyMatrix;
	getAdjacencyMatrix(edges, adjacencyMatrix);
	vector<vector<int>> incidenceMatrix;
	getIncidenceMatrix(edges, incidenceMatrix);
	printAdjacencyMatrix(adjacencyMatrix, cout);
	printIncidenceMatrix(incidenceMatrix, cout);
    
    string savePath;
    cout << "Введіть шлях для збереження матриць: ";
    getline(cin, savePath);
    ofstream outFile(savePath);
    if (!outFile.is_open()) {
        cerr << "Помилка при відкритті файла для збереження матриць."
            << endl;
        return 2;
    }
    printAdjacencyMatrix(adjacencyMatrix, outFile);
    printIncidenceMatrix(incidenceMatrix, outFile);
    outFile.close();
    cout << "Матриця успішно збережена." << endl;
	return 0;
}