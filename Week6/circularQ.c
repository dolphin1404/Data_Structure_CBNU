/**
 * circularQ.c
 *
 * School of Computer Science,
 * Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4  // 원형 큐의 최대 크기를 4로 정의

typedef char element;  // 큐에 저장되는 데이터 타입을 char로 정의
typedef struct {       // 큐의 구조체 타입을 정의.
  element queue[MAX_QUEUE_SIZE];
  int front, rear;
} QueueType;

// 큐 관련 함수 선언
QueueType *createQueue();      // 원형큐를 생성하는 함수
int freeQueue(QueueType *cQ);  // 동적할당한 큐를 해제하는 함수
int isEmpty(QueueType *cQ);    // 큐가 비어있는 지 확인하는 함수
int isFull(QueueType *cQ);     // 큐가 다 찼는 지 확인하는 함수
void enQueue(QueueType *cQ, element item);  // 큐에 데이터 삽입하는 함수
void deQueue(QueueType *cQ);  // 큐에서 데이터 삭제하는 함수
void printQ(QueueType *cQ);   // 큐의 내용을 출력하는 함수
void debugQ(QueueType *cQ);   // 큐의 상태를 디버깅하는 함수
element getElement();  // 사용자로부터 데이터를 입력받는 함수

int main(void) {  // 사용자는 i, d, p, b, q 를 입력하여 각각의 함수를 이용
  // i = insert, d = delete, p = print, b = debug, q = quit
  QueueType *cQ = createQueue();  // 빈 큐를 생성. 그러나 각 큐에는 쓰레기값
                                  // 저장. 왜냐하면 front, rear만 초기화함.
  // 그러나 debug 할 때만 보이고 print에선 문제발생하지 않음.
  element data;  // 이용자로부터 입력 받을 데이터 값
  char command;  // 이용자로부터 입력 받을 커맨드 값 >> 프로그램 조작

  do {  // do while 문을 이용해 먼저 메뉴를 띄운다.
    // 유저에게 보여줄 메인 화면
    printf("\n-----------------------------------------------------\n");
    printf("                     Circular Q                   \n");
    printf("------------------------------------------------------\n");
    printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
    printf("------------------------------------------------------\n");

    printf("Command = ");
    scanf(" %c", &command);  // 이용자로부터 커맨드 값을 입력받는다.

    switch (command) {  // 입력 받은 커맨드 값으로(대소문자 구별 안함) 각 할당된
                        // 함수를 실행한다.
      case 'i':
      case 'I':
        data = getElement();
        enQueue(cQ, data);
        break;
      case 'd':
      case 'D':
        deQueue(cQ);
        break;
      case 'p':
      case 'P':
        printQ(cQ);
        break;
      case 'b':
      case 'B':
        debugQ(cQ);
        break;
      case 'q':
      case 'Q':
        freeQueue(cQ);
        break;
      default:  // 이용자가 잘못 입력했을 때 출력하도록 설정.
        printf("\n       >>>>>   Concentration!!   <<<<<     \n");
        break;
    }

  } while (command != 'q' &&
           command != 'Q');  // quit를 의미하는 q, Q 값을 호출하기 전까지 반복

  printf("[----- [이규민] [2021039002] -----]");
  return 1;  // int main의 리턴 값.
}

QueueType *createQueue()  // 원형 큐를 생성하는 함수
{
  QueueType *cQ;
  cQ = (QueueType *)malloc(
      sizeof(QueueType));  // 원형 큐의 크기만큼 메모리를 할당한다. 단 초기화는
                           // 하지 않아 쓰레기 값 출력.
  cQ->front = 0;  // front 값을 초기화한다.
  cQ->rear = 0;   // rear 값을 초기화한다.
  return cQ;
}

int freeQueue(QueueType *cQ)  // 원형 큐에 동적 할당된 메모릴 해제하는 함수
{
  if (cQ == NULL) return 0;  // 큐가 비어있을 때, 종료
  free(cQ);                  // 할당된 메모리를 해제.
  return 1;
}

element getElement()  // 큐에 저장하는 함수
{
  element item;
  printf("Input element = ");
  scanf(" %c", &item);  // char 형 문자형에 저장
  return item;          // 입력 받은 문자 반환
}

/* complete the function */
int isEmpty(QueueType *cQ) {
  if (cQ->front == cQ->rear) {  // front와 rear의 값이 같다는 것은 큐에 아무
                                // 요소가 존재하지 않음을 의미한다.
    return 1;  // Queue is empty.. :(
  } else
    return 0;  // 같지 않다면 거짓인 0을 리턴한다.
}

/* complete the function */
int isFull(QueueType *cQ) {
  if ((cQ->rear + 1) % MAX_QUEUE_SIZE == cQ->front) {
    // 현 rear에 +1을 한 것이 front index와 같다면, 더 이상 요소를 추가할 수
    // 없음을 의미한다. 또한 % MAX_QUEUE_SIZE를 한 이유는, rear+1가 위
    // MAX_QUEUE_SIZE를 초과하면 인 덱스가 배열의 처음으로 돌아가도록 설정한
    // 것이다. (circular queue) 작으면 이 연산의 영향을 받지 않으며 인덱스가
    // 변경되지 않는다.
    return 1;  // Queue is full..! :X
  } else
    return 0;  // 같지 않다면 거짓인 0을 리턴한다.
}

/* complete the function */
void enQueue(QueueType *cQ, element item) {
  if (isFull(cQ)) {  // isFull 값이 1인지 감지
    printf(
        "WARNING : Queue is full. Cannot enqueue. :(\n");  // 맞다면 경고 출력
  } else {
    cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;  // rear를 다음으로 움직인다.
    // 만약 크기를 넘긴다면 배열의 처음으로 인덱스를 변경한다.
    cQ->queue[cQ->rear] = item;  // 새로운 요소를 현 rear의 위치에 저장한다.
  }
}

/* complete the function */
void deQueue(QueueType *cQ) {
  if (isEmpty(cQ)) printf("WARNING : Queue is empty. Cannot dequeue. :(\n");
  // 큐가 비어있는 지 확인하고 그렇다면 경고를 출력한다.
  else {
    cQ->front = (cQ->front + 1) %
                MAX_QUEUE_SIZE;  // front의 다음 인덱스를 현 front로 할당합니다.
    // 이 함수는 실제로는 요소를 큐에서 제거하지 않는다. 단순히 front 인덱스를
    // 움직여 요소에 접근할 수 없게만 한다.
  }
}

void printQ(QueueType *cQ) {
  int i, first, last;

  first = (cQ->front + 1) % MAX_QUEUE_SIZE;  // cQ의 first 값을 받아온다.
  last = (cQ->rear + 1) % MAX_QUEUE_SIZE;    // cQ의 rear 값을 받아온다.

  printf("Circular Queue : [");

  i = first;  // 반복문에 사용할 변수 i에 first 값으로 초기화한다.
  while (i != last) {  // i가 last 값에 도달할 떄까지 반복한다.
    printf(
        "%3c",
        cQ->queue[i]);  // %3c을 통해 간격을 벌리면서 큐의 i번째 값을 출력한다.
    i = (i + 1) % MAX_QUEUE_SIZE;  // i에 1을 더한다. 만약 사이즈보다 크면
                                   // 첫번재로 돌아간다.
  }
  printf(" ]\n");
}

void debugQ(QueueType *cQ) {
  printf("\n---DEBUG\n");
  for (int i = 0; i < MAX_QUEUE_SIZE; i++)  // 큐 배열의 전체를 0부터 돌아본다.
  {
    if (i == cQ->front) {  // 만약 현 인덱스 값이 front의 인덱스 값과 같다면
      printf("  [%d] = front\n", i);  // front 값을 출력한다.
      continue;  // 그리고 현 반복문을 스킵하고 인덱스 값을 증가한다.
    }
    printf("  [%d] = %c\n", i,
           cQ->queue[i]);  // 현 인덱스의 큐의 요소를 출력한다.
    // 만약 시작하자마자 이 함수를 돌리면 큐의 요소들은 쓰레기값으로 가득할
    // 것이다.
  }
  printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}
