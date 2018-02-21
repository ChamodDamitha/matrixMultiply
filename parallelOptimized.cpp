#include <iostream>
#include "matrix.h"
#include <omp.h>
#include "timer.h"

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

    populateMatrix(n, mat1);
    populateMatrix(n, mat2);

    double **transMat2 = transposeMatrix(n, mat2);

//    flatten matrices
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

#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        int dimI = i * n;
        for (int j = 0; j < n; ++j) {
            double tempSum = 0;
            int dimJ = j * n;
            for (int k = 0; k < n; ++k) {
                tempSum += flat1[dimI + k] * flat2[dimJ + k];
            }
            resMat[i][j] = tempSum;
        }
    }

//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            double tempSum = 0;
//            for (int k = 0; k < n; k++) {
//                tempSum += mat1[i][k] * transMat2[j][k];
//
//            }
//            resMat[i][j] = tempSum;
//        }
//    }

    GET_TIME(endTime);

    delete mat1;     //Free the memory allocated for matA
    delete mat2;     //Free the memory allocated for matB
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

        double time = parallelOptimizedMultiplyMatrix(n, matA, matB);
        sum += time;
        squareSum += (time * time);
        cout << time << endl;
    }

    calculateStatistics(sum, squareSum, rounds);

    return 0;
}