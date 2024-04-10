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
void random_Matrix(int** matrix, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i][j] = rand() % 10; // 랜덤 값에서 10으로 나눴을 때 나머지로 하였다. 0~9
    }
  }
  printf("Randomization is complete\n");
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

  // isEqual, isEqual_cr로 행렬 A,B의 크기가 같은 지, 행렬 A의 열과 행렬 B의 행의 크기가 같은 지를 판단하여
  // 덧셈, 뺄셈이 가능한 지와 행렬곱이 가능한 지를 판단한다. 
  // 이후 함수에서 if문을 통해 계산을 할 지 말지를 결정한다.
  int isEqual = 1;  // true >> can do addition and subtraction of matrix A, B
  if(colsA != colsB || rowsA != rowsB){
    printf("\nNot equal both matrix's m, n\n\n");
    isEqual = 0;  // false >> can't do addition and subtraction.
  }
  int isEqual_cr = 1; // true >> can do multiplication.
  if(colsA != rowsB){
    printf("\nNot equal matrixA's cols and matrixB's rows\n\n");
    isEqual_cr = 0; // can't do multiplication.
  }

  // 행렬 A를 생성하고 채운다.
  int** matrixA = createMatrix(rowsA, colsA);
  printf("Randomize matrix A >\n");
  random_Matrix(matrixA, rowsA, colsA);  

  // 행렬 B를 생성하고 채운다.
  int** matrixB = createMatrix(rowsB, colsB);
  printf("Randomize matrix B >\n");
  random_Matrix(matrixB, rowsB, colsB);

  // 입력받은 행렬 A를 출력
  printf("Matrix A:\n");
  print_Matrix(matrixA, rowsA, colsA);

  // 입력받은 행렬 B를 출력
  printf("Matrix B:\n");
  print_Matrix(matrixB, rowsB, colsB);

  // 행렬 A, B의 합
  int** addMatrix = addition_Matrix(matrixA, matrixB, rowsA, colsA);
  printf("Addition of matrix A and B:\n");
  if(isEqual != 1){ // 같지 않으면 행렬합은 불가능
    printf("SRY, Can't addition\n");
  }else print_Matrix(addMatrix, rowsA, colsA);

  // 행렬 A, B의 뺄셈
  int** subtMatrix = subtraction_Matrix(matrixA, matrixB, rowsA, colsA);
  printf("Subtraction of matrix A and B:\n");
  if(isEqual != 1){ // 같지 않으면 행렬뺄셈은 불가능
    printf("SRY, Can't subtraction\n");
  }else print_Matrix(subtMatrix, rowsA, colsA);

  // 행렬 A를 전치행렬로 바꾼다.
  int** tranMatrixA = transpose_Matrix(matrixA, rowsA, colsA);
  printf("Transpose of matrix A:\n");
  print_Matrix(tranMatrixA, colsA, rowsA);

  // 행렬 A와 B를 곱한다.
  int** multiMatrix = multiply_Matrix(matrixA, matrixB, rowsA, colsA, colsB);
  printf("Multiplication of matrix A and B:\n");
  if(isEqual_cr != 1) printf("SRY, Can't Multiplication\n");  
  // A의 열과 B의 행의 크기가 같지 않으면 행렬곱 불가능
  else print_Matrix(multiMatrix, rowsA, colsB);

  // 지금까지 선언한 행렬들에 할당된 메모리를 해제한다.
  free_Matrix(matrixA, rowsA);
  free_Matrix(matrixB, rowsB);
  free_Matrix(addMatrix, rowsA);
  free_Matrix(subtMatrix, rowsA);
  free_Matrix(tranMatrixA, colsA);
  free_Matrix(multiMatrix, rowsA);

  return 0;
  printf("[----- [이규민] [2021039002] -----]");
}