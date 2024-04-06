#include <stdio.h>
#include <stdlib.h> // malloc 사용을 위해.

// 행렬에 메모리 할당
int** createMatrix(int rows, int cols) {
  int** matrix = (int**)malloc(rows * sizeof(int*));  
  // 정수형 이중 포인터 matrix 선언하고, malloc을 통해 rows * 8 (= sizeof(int*)) 만큼 할당한다. 이는 rows에 관해서만 heap에 할당했다.
  for (int i = 0; i < rows; i++) {
    matrix[i] = (int*)malloc(cols * sizeof(int)); 
    //  malloc을 통해 cols * 4 만큼 할당한다. 이는 cols에 관해서 값이 저장될 메모리를 heap에 할당했다.
  }
  return matrix;
}

// 행렬에 입력 받은 rows, cols 이중 for문을 통해 행렬을 랜덤한 수로 채운다.
void fillMatrix(int** matrix, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] = rand() % 10; // 랜덤 값에서 10으로 나눴을 때 나머지로 하였다. 0~9
    }
  }
}

// 이중 for문을 통해 행렬을 출력한다.
void print_Matrix(int** matrix, int rows, int cols) { // 행렬의 값을 받는다.
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%d ", matrix[i][j]);  // 각 요소를 공백으로 구분하여 출력
    }
    printf("\n");     // 다음 행으로 넘어갈 때 줄 바꿈
  }
}

// 두 행렬을 더하는 함수
int** addition_Matrix(int** matrixA, int** matrixB, int rows, int cols) {
  int** result = createMatrix(rows, cols);  
  // 결과로 받을 행렬을 이중 포인터로 선언하고 createMatrix을 통해 계산 결과로 받을 메모리를 동적할당한다.
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      result[i][j] = matrixA[i][j] + matrixB[i][j]; // 합을 result에 저장한다.
    }
  }
  return result;
}

// 두 행렬을 빼는 함수
int** subtraction_Matrix(int** matrixA, int** matrixB, int rows, int cols) {
  int** result = createMatrix(rows, cols);
  // 결과로 받을 행렬을 이중 포인터로 선언하고 createMatrix을 통해 계산 결과로 받을 메모리를 동적할당한다.
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      result[i][j] = matrixA[i][j] - matrixB[i][j]; // 차를 result에 저장한다.
    }
  }
  return result;
}

// 전치행렬로 바꾸는 함수
int** transpose_Matrix(int** matrix, int rows, int cols) {
  int** result = createMatrix(cols, rows); // 위와 동일
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      result[j][i] = matrix[i][j];  // i와 j의 순서를 바꾸어 저장하여 전치행렬로 바꾼다.
    }
  }
  return result;
}

// 행렬곱 함수
int** multiply_Matrix(int** matrixA, int** matrixB, int rowsA, int colsA, int colsB) {
  int** result = createMatrix(rowsA, colsB);  // 위와 동일
  for (int i = 0; i < rowsA; i++) {
    for (int j = 0; j < colsB; j++) {
      result[i][j] = 0; // 초기화. 다음 코드가 초기화가 아닌 추가하는 연산이기에 쓰레기 값 방지
      for (int k = 0; k < colsA; k++) {
        result[i][j] += matrixA[i][k] * matrixB[k][j];  
        // 곱 연산 수행. 행렬 곱셈은 첫 행렬의 행과 뒷 행렬의 열에 있는 요소들을 곱한 후 그 합을 계산한다.
      }
    }
  }
  return result;
}

// 동적할당한 메모리를 해제한다.
void free_Matrix(int** matrix, int rows) {
  for (int i = 0; i < rows; i++) {
    free(matrix[i]);  // 각 행을 메모리 해제한다.
  }
  free(matrix); // 인자로 받은 행렬을 메모리 해제한다.
}

int main() {
  // 연산을 수행할 두 행렬의 열과 행을 받는다.
  int rowsA, colsA, rowsB, colsB;
  printf("Enter matrix A (m, n) : ");
  scanf("%d %d", &rowsA, &colsA);
  printf("Enter matrix B (m, n) : ");
  scanf("%d %d", &rowsB, &colsB);

  // 행렬 A를 생성하고 채운다.
  int** matrixA = createMatrix(rowsA, colsA);
  printf("Enter the values for matrix A:\n");
  fillMatrix(matrixA, rowsA, colsA);  

  // 행렬 B를 생성하고 채운다.
  int** matrixB = createMatrix(rowsB, colsB);
  printf("Enter the values for matrix B:\n");
  fillMatrix(matrixB, rowsB, colsB);

  // 입력받은 행렬 A를 출력
  printf("Matrix A:\n");
  print_Matrix(matrixA, rowsA, colsA);

  // 입력받은 행렬 B를 출력
  printf("Matrix B:\n");
  print_Matrix(matrixB, rowsB, colsB);

  // 행렬 A, B의 합
  int** sumMatrix = addition_Matrix(matrixA, matrixB, rowsA, colsA);
  printf("Sum of matrix A and B:\n");
  print_Matrix(sumMatrix, rowsA, colsA);

  // 행렬 A, B의 뺄셈
  int** diffMatrix = subtraction_Matrix(matrixA, matrixB, rowsA, colsA);
  printf("Subtraction of matrix A and B:\n");
  print_Matrix(diffMatrix, rowsA, colsA);

  // 행렬 A를 전치행렬로 바꾼다.
  int** transposeA = transpose_Matrix(matrixA, rowsA, colsA);
  printf("Transpose of matrix A:\n");
  print_Matrix(transposeA, colsA, rowsA);

  // 행렬 A와 B를 곱한다.
  int** productMatrix = multiply_Matrix(matrixA, matrixB, rowsA, colsA, colsB);
  printf("Product of matrix A and B:\n");
  print_Matrix(productMatrix, rowsA, colsB);

  // 지금까지 선언한 행렬들에 할당된 메모리를 해제한다.
  free_Matrix(matrixA, rowsA);
  free_Matrix(matrixB, rowsB);
  free_Matrix(sumMatrix, rowsA);
  free_Matrix(diffMatrix, rowsA);
  free_Matrix(transposeA, colsA);
  free_Matrix(productMatrix, rowsA);

  return 0;
  printf("[----- [이규민] [2021039002] -----]");
  printf("Second Commit");
}