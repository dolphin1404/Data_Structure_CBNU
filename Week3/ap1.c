#include <stdio.h>
#include <stdlib.h>

void main() {
  int list[5];  // 정수형 배열 list 선언, 초기화를 안했기 때문에 쓰레기값이 저장됨.
  int *plist[5] = { // 포인터 배열 plist 선언 및 NULL로 초기화.
      NULL,
  };

  plist[0] = (int *)malloc(sizeof(int));  // plist 첫번째에 동적 메모리 (int 크기만큼) 할당
  list[0] = 1;    // list[0]에 1 저장
  list[1] = 100;  // list[1]에 100 저장

  //*plist[0] = 200; // EXTRA 동적 할당된 메모리(=plist[0]가 가리키는 메모리)에 200 저장

  // list 배열과 plist 배열의 주소와 값을 출력.
  printf("list[0] = %d\n", list[0]);    // output : 1
  printf("&list[0] = %p\n", &list[0]);  // list[0]의 주소 출력
  printf("list = %p\n", list);
  printf("&list = %p\n", &list);  // &list[0] == &list >> list의 주소 자체는 첫번째 요소의 주소와 같다. >> 배열은 주소
  printf("----------------------------------------\n\n");
  printf("list[1] = %d\n", list[1]);    // output : 100
  printf("&list[1] = %p\n", &list[1]);  // &list + 4bytes
  printf("*(list+1) = %d\n", *(list + 1));  // 역참조 연산자를 통해 list[1]의 값을 불러옴
  printf("list+1 = %p\n", list + 1);  // list[0] + 4bytes (int = 4bytes)
  printf("----------------------------------------\n\n");
  printf("*plist[0] = %d\n", *plist[0]);  // plist[0]가 가리키는 메모리에 저장된 200 출력
  printf("&plist[0] = %p\n", &plist[0]);  // plist[0]의 주소
  /* EXTRA
  printf("&plist[1] = %p\n", &plist[1]); // plist[1]의 주소 출력 plist[0]의 주소값 + 8 bytes
  plist[1] = (int *)malloc(sizeof(int));  // plist 두번째에 동적 메모리 (int 크기만큼) 할당
  *plist[1] = 250;
  printf("*plist[1] = %d\n", *plist[1]);  // plist[1]가 가리키는 메모리에 저장된 250 출력
  */
  printf("&plist = %p\n", &plist);      // plist 배열의 주소 = plist[0]의 주소
  printf("plist = %p\n", plist);        // 그냥 plist를 호출했을 때는 배열의 시작 주소를 의미하고 plist[0]와 같다.
  printf("plist[0] = %p\n", plist[0]);  // plist[0]은 heap 영역의 주소를 가리키고 있다.
  printf("plist[1] = %p\n", plist[1]);  // plist[0]을 제외한 나머지는 NULL로 초기화
  printf("plist[2] = %p\n", plist[2]);
  printf("plist[3] = %p\n", plist[3]);
  printf("plist[4] = %p\n", plist[4]);
  free(plist[0]);  // 동적 할당 메모리 해제
  // free(plist[1]);   // Extra 동적 할당 메모리 해제
  printf("[----- [이 규 민] [2021039002] -----]");
}