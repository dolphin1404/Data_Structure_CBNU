#include <stdio.h>
struct student {
  char lastName[13]; // 13 bytes 크기의 문자형 변수
  int studentId;     // 4 bytes 크기의 정수형 변수
  short grade;       // 2 bytes 크기의 정수형 변수
};
int main() {
  struct student pst; // student 구조체 pst 선언, 초기화는 하지 않음.
  printf("size of student = %ld\n", sizeof(struct student));  // student 구조체 크기를 출력한다.
  // 24byte = (13 + 4 + 2 + 5(padding))
  printf("size of int = %ld\n", sizeof(int)); // int형의 크기 출력
  printf("size of short = %ld\n", sizeof(short)); // short형의 크기 출력
  printf("[----- [이규민] [2021039002] -----]\n");
  return 0;
}