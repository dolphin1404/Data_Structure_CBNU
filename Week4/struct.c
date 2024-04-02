#include <stdio.h>

// student1 구조체 선언
struct student1 {
  char lastName;  // 이름
  int studentId;  //학번
  char grade; // 학점
};
// student2 구조체를 typedef를 통해 선언
typedef struct {
  char lastName;
  int studentId;
  char grade;
} student2;

int main() {
  
  struct student1 st1 = {'A', 100, 'A'};  // 구조체 student1의 st1의 요소들을 넣어 초기화.
  printf("st1.lastName = %c\n", st1.lastName);  // 위에서 초기화한 요소들을 출력
  printf("st1.studentId = %d\n", st1.studentId);
  printf("st1.grade = %c\n", st1.grade);
  student2 st2 = {'B', 200, 'B'};   // 구조체 student2의 st2의 요소들을 넣어 초기화.
  printf("\nst2.lastName = %c\n", st2.lastName);  // 마찬가지로 위에서 초기화한 요소들을 출력
  printf("st2.studentId = %d\n", st2.studentId);
  printf("st2.grade = %c\n", st2.grade);
  student2 st3; // 구조체 student2 st3을 초기화없이 선언.
  st3 = st2;  // st3에 st2을 넣음
  printf("\nst3.lastName = %c\n", st3.lastName);  // st3의 요소들을 출력
  printf("st3.studentId = %d\n", st3.studentId);
  printf("st3.grade = %c\n", st3.grade);
  /* equality test */
  if (st3.grade == st2.grade && st3.lastName == st2.lastName && st3.studentId == st2.studentId)
    printf("equal\n");  // 위 조건문 모두를 만족하면 equal을 출력(st3에 st2가 제대로 복사되었는 지 확인)
  else
    printf("not equal\n");  // 하나라도 틀리면 서로 다른 것을 의미.
  printf("[----- [이규민] [2021039002] -----]\n");
  return 0;
  // for 2nd commit
}