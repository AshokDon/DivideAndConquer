#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> Matrix;

// Function to add two matrices
Matrix add(const Matrix &A, const Matrix &B, int size) {
    Matrix result(size, vector<int>(size));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            result[i][j] = A[i][j] + B[i][j];
    return result;
}

// Function to split the matrix into four submatrices
void splitMatrix(const Matrix &A, Matrix &A11, Matrix &A12, Matrix &A21, Matrix &A22, int mid) {
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            A11[i][j] = A[i][j];                // Top-left
            A12[i][j] = A[i][j + mid];          // Top-right
            A21[i][j] = A[i + mid][j];          // Bottom-left
            A22[i][j] = A[i + mid][j + mid];    // Bottom-right
        }
    }
}

// Function to combine four submatrices into one result matrix
void combineMatrix(Matrix &C, const Matrix &C11, const Matrix &C12, const Matrix &C21, const Matrix &C22, int mid) {
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            C[i][j] = C11[i][j];                 // Top-left
            C[i][j + mid] = C12[i][j];           // Top-right
            C[i + mid][j] = C21[i][j];           // Bottom-left
            C[i + mid][j + mid] = C22[i][j];     // Bottom-right
        }
    }
}

// Divide and conquer matrix multiplication
Matrix MM(const Matrix &A, const Matrix &B, int n) {
    Matrix C(n, vector<int>(n, 0));
    
    if (n == 1) {
        // Base case: simple multiplication when the matrix is 1x1
        C[0][0] = A[0][0] * B[0][0];
        return C;
    } else {
        int mid = n / 2;

        // Initialize submatrices
        Matrix A11(mid, vector<int>(mid));
        Matrix A12(mid, vector<int>(mid));
        Matrix A21(mid, vector<int>(mid));
        Matrix A22(mid, vector<int>(mid));

        Matrix B11(mid, vector<int>(mid));
        Matrix B12(mid, vector<int>(mid));
        Matrix B21(mid, vector<int>(mid));
        Matrix B22(mid, vector<int>(mid));

        // Split A and B into 4 submatrices each
        splitMatrix(A, A11, A12, A21, A22, mid);
        splitMatrix(B, B11, B12, B21, B22, mid);

        // Recursively calculate the submatrices of the result matrix
        Matrix C11 = add(MM(A11, B11, mid), MM(A12, B21, mid), mid);
        Matrix C12 = add(MM(A11, B12, mid), MM(A12, B22, mid), mid);
        Matrix C21 = add(MM(A21, B11, mid), MM(A22, B21, mid), mid);
        Matrix C22 = add(MM(A21, B12, mid), MM(A22, B22, mid), mid);

        // Combine the submatrices into the result matrix
        combineMatrix(C, C11, C12, C21, C22, mid);

        return C;
    }
}

int main() {
    int n = 4; // Size of the matrix (must be a power of 2 for simplicity)
    
    Matrix A = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    Matrix B = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    Matrix result = MM(A, B, n);

    cout << "Result matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << result[i][j] << " ";
        cout << "\n";
    }

    return 0;
}
