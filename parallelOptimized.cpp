#include <iostream>
#include "matrix.h"
#include <omp.h>
#include "timer.h"

//get transpose of matrix
double **transposeMatrix(int n, double **mat) {
    double **transMat = initMatrix(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            transMat[i][j] = mat[j][i];
        }
    }
    return transMat;
}


double parallelOptimizedMultiplyMatrix(int n, double **mat1, double **mat2) {

    double startTime, endTime;
    double **resMat = initMatrix(n);

//  randomly populate matrices
    populateMatrix(n, mat1);
    populateMatrix(n, mat2);

    double **transMat2 = transposeMatrix(n, mat2);

//  flatten matrices
    double *flat1, *flat2;
    flat1 = (double *)malloc(sizeof(double) * n * n);
    flat2 = (double *)malloc(sizeof(double) * n * n);

#pragma omp parallel for
    for (int l = 0; l < n; ++l) {
        for (int i = 0; i < n; ++i) {
            flat1[l * n + i] = mat1[l][i];
            flat2[l * n + i] = transMat2[l][i];
        }
    }


    GET_TIME(startTime);
//  run omp parallel loop
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        int dimI = i * n;
        for (int j = 0; j < n; ++j) {
            double tempSum;
            int dimJ = j * n;
//          skip loop by steps of 5
            for (int k = 0; k < n; k += 5) {
                tempSum += flat1[dimI + k] * flat2[dimJ + k];
                tempSum += flat1[dimI + k + 1] * flat2[dimJ + k + 1];
                tempSum += flat1[dimI + k + 2] * flat2[dimJ + k + 2];
                tempSum += flat1[dimI + k + 3] * flat2[dimJ + k + 3];
                tempSum += flat1[dimI + k + 4] * flat2[dimJ + k + 4];
            }
            resMat[i][j] = tempSum;
        }
    }

    GET_TIME(endTime);

    delete mat1;     //Free the memory allocated for mat1
    delete mat2;     //Free the memory allocated for mat2
    delete resMat;   //Free the memory allocated for resMat

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

        double time = parallelOptimizedMultiplyMatrix(n, matA, matB);
        sum += time;
        squareSum += (time * time);
        cout << time << endl;
    }

    calculateStatistics(sum, squareSum, rounds);

    return 0;
}