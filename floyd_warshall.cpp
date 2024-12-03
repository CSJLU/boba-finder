using namespace std;
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <chrono>
#include <time.h>
#include <climits>

#define INF 999

void floydWarshallAlgorithm(vector<vector<float>>& D, vector<vector<int>>& P, int n) {
    //predecessor table
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i != j && D[i][j] != INF) {
                P[i][j] = i + 1;
            }
            else {
                P[i][j] = -1;
            }
        }
    }

    //D table
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(D[i][j] > (D[i][k] + D[k][j]) && (D[i][k] != INF && D[k][j] != INF)) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = P[k][j];
                }
            }
        }
    }
}

void getPath(int i, int j, vector<vector<int>>& P, ofstream& outputFile) {
    if(i == j) {
        outputFile << i + i << " ";
    }   
    else if (P[i][j] == -1) {
        outputFile << "No path that goes from " << i << " to " << j << endl;
    }
    else {
        getPath(i, P[i][j]-1, P, outputFile);
        outputFile << j + 1 << " ";
    }
}

//escapsulates the getPath and floydWarshallAlgorithm functions + their running time and also prints/writes final D and P tables
void runTestCases(vector<vector<float>> D, vector<vector<int>> P, int n, ofstream& outputFile) {
    printf("Running test cases");
    auto start = std::chrono::high_resolution_clock::now();
    floydWarshallAlgorithm(D, P, n);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
    for(int r = 0; r < n; r++) {
        for(int c = 0; c < n; c++) {
            outputFile << P[r][c] << " ";
        }
        outputFile << endl;
    }
    outputFile << endl;
    for(int r = 0; r < n; r++) {
        for(int c = 0; c < n; c++) {
            outputFile << D[r][c] << " ";
        }
        outputFile << endl;
    }
    outputFile << endl;
    for(int r = 0; r < n; r++) {
        for(int c = 0; c < n; c++) {
            outputFile << "From intersection " << r + 1 << " to intersection " << c + 1 << ": ";
            getPath(r, c, P, outputFile);
            outputFile << "; Distance: " << D[r][c] << endl;
        }
    }
    outputFile << "Running time: " << duration_milliseconds.count() << "ms" << endl << endl;
}

//instantiates matrices and read inputFile values into matrix
int main(int argc, char* argv[]) {

    if(argc!=3) {
        cout << "Commandline arguments should be: submission inputFile.txt outputFile.txt" << endl;
        return 0;
    }

    ifstream file(argv[1]);
    ofstream outputFile(argv[2]);
    string line;
    

    int i, j;
    float val;
    int n = 47;

    vector<vector<float>> distance;
    vector<vector<int>> predecessor;
    distance.resize(n, vector<float>(n, INF)); 
    predecessor.resize(n, vector<int>(n, -1)); 
    while(getline(file, line)) {
        if(line.find("//") == 0) {
            continue;
        }
        if(line.empty()) {
            for(int r = 0; r < n; r++) {
                for(int c = 0; c < n; c++) {
                    if(r==c) {
                        distance[r][c] = 0;
                    }
                }
            }
            runTestCases(distance, predecessor, n, outputFile);
        }
        if(n!=-1) {
            istringstream iss(line);
            while(iss >> i >> j >> val) {
                if (i <= 0 || i > n || j <= 0 || j > n) {
                    cerr << "Error: indices out of bounds (" << i << ", " << j << ")\n";
                    return 1;
                }
            distance[i-1][j-1] = val;
            }
        }
    }

    file.close();
    outputFile.close();

}