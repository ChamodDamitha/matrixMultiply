#include <iostream>
#include <random>

using namespace std;


// initialize a 2D matrix
double **initMatrix(int n) {
    double **mat = new double *[n];
    for (int i = 0; i < n; i++) {
        mat[i] = new double[n];
    }
    return mat;
}

// populate a 2D matrix by random double values
void populateMatrix(int n, double **mat) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mat[i][j] = (rand() % 1000) / 10.0;
        }
    }
}

// calculate mean and standard deviation of time values
void calculateStatistics(double sum, double squareSum, int count) {
    double mean = sum / count;
    double stdev = sqrt((squareSum / count) - (mean * mean));

    cout << "Mean : " << mean << endl;
    cout << "STD : " << stdev << endl;
}