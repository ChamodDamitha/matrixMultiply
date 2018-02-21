#include <iostream>
#include <random>

using namespace std;


double **initMatrix(int n) {
    double **mat = new double *[n];
    for (int i = 0; i < n; i++) {
        mat[i] = new double[n];
    }
    return mat;
}


void populateMatrix(int n, double **mat) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mat[i][j] = (rand() % 100) + 1;
        }
    }
}


void calculateStatistics(double sum, double squareSum, int count) {
    double mean = sum / count;
    double stdev = sqrt((squareSum / count) - (mean * mean));

    cout << "Mean : " << mean << endl;
    cout << "STD : " << stdev << endl;
}