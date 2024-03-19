#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm> 
#include <map> 

using namespace std;
using namespace std::chrono;


vector<int> readData(const string filename) {
    vector<int> data;
    int value;
    ifstream file(filename);

    while (file >> value) {
        data.push_back(value);
    }

    return data;
}

void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) {
        return;
    }
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}



void rikiuotiIrMatuoti(const string& filename, int algoritmoPasirinkimas, vector<long long>& results) {
    vector<int> data = readData(filename + ".csv"); 
    int iterations = 10;
    long long totalDuration = 0;

    for (int i = 0; i < iterations; i++) {
        vector<int> dataCopy = data; 
        auto start = high_resolution_clock::now();
        if (algoritmoPasirinkimas == 1) {
            bubbleSort(dataCopy);
        }
        else if (algoritmoPasirinkimas == 2) {
            mergeSort(dataCopy, 0, dataCopy.size() - 1);
        }
        auto stop = high_resolution_clock::now();
        totalDuration += duration_cast<nanoseconds>(stop - start).count();
    }
    long long avgDuration = totalDuration / iterations;
    results.push_back(avgDuration); 
}

void writeResults(const string& filename,
    const map<string, long long>& bubbleSortResults,
    const map<string, long long>& mergeSortResults) {
    ofstream file(filename);

    file << "Duomenys, Burbulo algoritmo vidutinis greitis (nanosekundes), Suliejimo algoritmo vidutinis greitis (nanosekundes)\n";


    for (const auto& pair : bubbleSortResults) {
        file << pair.first << ", " << pair.second << ", " << mergeSortResults.at(pair.first) << "\n";
    }
}


int main() {

    int burbulas = 1;
    int suliejimo = 2;

    map<string, long long> bubbleSortResults;
    map<string, long long> mergeSortResults;

    vector<string> filenames = {
        "5000_Nesurusiuoti_Duomenys",
        "10000_Nesurusiuoti_Duomenys",
        "50000_Nesurusiuoti_Duomenys",
        "100000_Nesurusiuoti_Duomenys",
        "10000_Atvirksciai_Surusiuoti_Duomenys",
        "5000_Atvirksciai_Surusiuoti_Duomenys",
        "50000_Atvirksciai_Surusiuoti_Duomenys",
        "100000_Atvirksciai_Surusiuoti_Duomenys",
        "5000_Surusiuoti_Duomenys",
        "10000_Surusiuoti_Duomenys",
        "50000_Surusiuoti_Duomenys",
        "100000_Surusiuoti_Duomenys"
    };

    

    for (const auto& filename : filenames) {
        cout << "Analyzing: " << filename << endl;

        vector<long long> tempBubbleResults;
        vector<long long> tempMergeResults;

        rikiuotiIrMatuoti(filename, burbulas, tempBubbleResults);
        rikiuotiIrMatuoti(filename, suliejimo, tempMergeResults);

        bubbleSortResults[filename] = tempBubbleResults.front();
        mergeSortResults[filename] = tempMergeResults.front();
    }

    writeResults("RikiavimoAlgoritmuRezultatai001.csv", bubbleSortResults, mergeSortResults);

    return 0;
}


