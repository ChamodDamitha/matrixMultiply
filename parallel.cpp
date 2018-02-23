#include <iostream>
#include "matrix.h"
#include <omp.h>
#include "timer.h"

double parallelMultiplyMatrix(int n, double **mat1, double **mat2) {

    double startTime, endTime;
    double **resMat = initMatrix(n);

//  randomly populate matrices
    populateMatrix(n, mat1);
    populateMatrix(n, mat2);

    GET_TIME(startTime);

//  run omp parallel loop
#pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            resMat[i][j] = 0.0;
            for (int k = 0; k < n; k++) {
                resMat[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    GET_TIME(endTime);

    delete  mat1;     //Free the memory allocated for mat1
    delete  mat2;     //Free the memory allocated for mat2
    delete resMat;    //Free the memory allocated for resMat

    return (endTime - startTime);
}


int main() {
    int n, rounds;
    cout << "Parallel Approach" << endl;
    cout << "Enter n (dimension of matrix) : ";
    cin >> n;
    cout << "Enter number of rounds :";
    cin >> rounds;

    double sum = 0, squareSum = 0;

    for (int i = 0; i < rounds; i++) {
        double **matA = initMatrix(n);
        double **matB = initMatrix(n);

        double time = parallelMultiplyMatrix(n, matA, matB);
        sum += time;
        squareSum += (time * time);
        cout << time << endl;
    }

    calculateStatistics(sum, squareSum, rounds);

    return 0;
}