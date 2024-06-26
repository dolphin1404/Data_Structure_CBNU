#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 10

// 인접 리스트 선언부
// 인접 리스트의 노드 구조를 구조체로 정의한다.
typedef struct graphNode {
  int vertex;              // 정점 나타내는 데이터
  struct graphNode* next;  // 다음 노드를 가리키는 링크
} graphNode;

// 그래프를 인접 리스트로 표현하기 위한 구조체
typedef struct graphType {
  int n;                             // 그래프의 정점 개수
  graphNode* adjList_H[MAX_VERTEX];  // 그래프의 인접 리스트 헤드 포인터 배열
  int visited[MAX_VERTEX];  // 정점 방문 여부를 나타내는 배열
} graphType;

// 함수 선언부
graphType* initializeGraph();
void insertVertex(graphType* g, int v);
void insertEdge(graphType* g, int u, int v);
void printList(graphType* g);
void DFS_adjList(graphType* g, int v);
void BFS_adjList(graphType* g, int v);

// 스택 구현 (DFS에서 사용)

typedef int element;  // 정수형 데이터 타입 정의

typedef struct stackNode {
  element data;
  struct stackNode* link;
} stackNode;

stackNode* top = NULL;

int isEmpty() {
  if (top == NULL)
    return 1;
  else
    return 0;
}

void push(element item) {
  stackNode* tmp = (stackNode*)malloc(sizeof(stackNode));
  tmp->data = item;
  tmp->link = top;
  top = tmp;
}

int pop() {
  int item;
  stackNode* tmp = top;
  if (isEmpty()) {
    printf("Stack is Empty\n");
    return 0;
  } else {
    item = tmp->data;
    top = tmp->link;
    free(tmp);
    return item;
  }
}

// 큐 구현 (BFS에서 사용)
typedef struct queueNode {
  element data;
  struct queueNode* link;
} queueNode;

queueNode* front = NULL;
queueNode* rear = NULL;

int isQueueEmpty() { return front == NULL; }

void enqueue(element item) {
  queueNode* temp = (queueNode*)malloc(sizeof(queueNode));
  temp->data = item;
  temp->link = NULL;
  if (isQueueEmpty()) {
    front = temp;
    rear = temp;
  } else {
    rear->link = temp;
    rear = temp;
  }
}

element dequeue() {
  element item;
  queueNode* temp = front;
  if (isQueueEmpty()) {
    printf("Queue is Empty\n");
    return 0;
  } else {
    item = temp->data;
    front = front->link;
    if (front == NULL) {
      rear = NULL;
    }
    free(temp);
    return item;
  }
}

// 그래프를 초기화하는 함수
graphType* initializeGraph() {
  graphType* g =
      (graphType*)malloc(sizeof(graphType));  // 그래프 헤더 노드 동적할당
  g->n = 0;
  for (int i = 0; i < MAX_VERTEX;
       i++) {  // 미리 지정한 그래프의 최대 정점 개수만큼 반복
    g->adjList_H[i] = NULL;  // 인접 리스트 헤드 포인터를 NULL로 초기화
    g->visited[i] = 0;  // 방문 여부를 나타내는 배열을 0으로 초기화
  }
  return g;
}

// 그래프에 정점 v를 삽입하는 함수
void insertVertex(graphType* g, int v) {
  g->n = v;  // 정점 개수 설정
  for (int i = 0; i < v; i++) {
    g->adjList_H[i] = NULL;  // 인접 리스트를 빈 상태로 초기화
  }
  printf("Insert %d vertices.\n", v);
}

void insertEdge(graphType* g, int u, int v) {
  graphNode* node;  // 새로운 노드를 동적할당할 포인터
  graphNode* curr; // 현재 노드를 가리킬 포인터
  graphNode* prev = NULL;   // 이전 노드를 가리킬 포인터

  // 간선 (u, v)를 삽입 전 현재 그래프에 존재하는지 확인
  if (u >= g->n || v >= g->n) {
    printf("This N isn't on graph.\n");
    return;
  }

  node = (graphNode*)malloc(sizeof(graphNode)); // 새로운 노드 동적할당
  node->vertex = v; // 노드에 정점 번호 저장
  node->next = NULL;    // 노드의 다음 노드를 NULL로 초기화

  // 인접 리스트에 정점 번호 순으로 삽입
  curr = g->adjList_H[u];
  while (curr != NULL && curr->vertex < v) {    // 정점 번호 순으로 삽입
    prev = curr;
    curr = curr->next;
  }
  if (prev == NULL) {   // 첫 번째 노드로 삽입
    node->next = g->adjList_H[u];
    g->adjList_H[u] = node;
  } else {
    node->next = prev->next;
    prev->next = node;
  }
}

// 깃커밋용 주석
void printList(graphType* g) {  // 인접 리스트 출력
  int i;
  graphNode* p;
  for (i = 0; i < g->n; i++) {
    printf("정점 %c의 인접 리스트", i + 65);
    p = g->adjList_H[i];
    while (p) {
      printf("-> %c", p->vertex + 65);  // 정점을 알파벳으로 출력
      p = p->next;
    }
    printf("\n");
  }
}

// 깊이 우선 탐색
void DFS_adjList(graphType* g, int v) {
  graphNode* w;  // 인접 리스트 노드를 가리킬 포인터
  top = NULL;
  push(v);
  g->visited[v] = 1;
  printf("정점 %c -> ", v + 65);  // 정점을 알파벳으로 출력

  // 스택이 비어있지 않은 동안 반복
  while (!isEmpty()) {
    v = pop();            // 스택에서 정점을 꺼내 v에 저장
    w = g->adjList_H[v];  // v의 인접 리스트 헤드 포인터를 w에 저장
    while (w) {
      if (!g->visited[w->vertex]) {
        if (isEmpty()) push(v);
        push(w->vertex);
        g->visited[w->vertex] = 1;  // true
        printf("%c -> ", w->vertex + 65);
        v = w->vertex;        // v를 w로 변경
        w = g->adjList_H[v];  // w를 v의 인접 리스트 헤드 포인터로 변경
      } else {                // 이미 방문한 정점인 경우
        w = w->next;
      }
    }
  }
  printf("\n");
}

void BFS_adjList(graphType* g, int v) {
  graphNode* w;
  front = rear = NULL;
  enqueue(v);
  g->visited[v] = 1;
  printf("정점 %c -> ", v + 65);  // 정점을 알파벳으로 출력

  while (!isQueueEmpty()) {
    v = dequeue();
    w = g->adjList_H[v];
    while (w) { // 인접 리스트를 탐색
      if (!g->visited[w->vertex]) { // 방문하지 않은 정점인 경우
        enqueue(w->vertex); // 큐에 삽입
        g->visited[w->vertex] = 1;
        printf("%c -> ", w->vertex + 65);
      }
      w = w->next;  // 다음 인접 정점으로 이동
    }
  }
  printf("\n");
}

int main() {
  char command;   // 이용자로부터 입력받을 커맨드 값
  int key, u, v;  // 이후 함수에서 사용될, 값을 찾고 수정하기 위한 입력 값을
                  // 저장하는 변수
  graphType* graph = initializeGraph();  // 그래프의 헤더 노드를 동적할당

  printf("[----- [이규민] [2021039002] -----]\n");
  do {
    printf(
        "----------------------------------------------------------------\n");
    printf(
        "                           Graph Search                         \n");
    printf(
        "----------------------------------------------------------------\n");
    printf(
        " Initialize Graph   = z                                         \n");
    printf(
        " Insert Vertex      = v           Insert Edge           = e     \n");
    printf(
        " Depth Frist Search = d           Breadth First Search  = b     \n");
    printf(
        " Print Graph        = p           Quit                  = q     \n");
    printf(
        "----------------------------------------------------------------\n");
    // 메인 메뉴
    printf("Command = ");
    scanf(" %c", &command);

    switch (command) {
      case 'z':
      case 'Z':
        graph = initializeGraph();
        printf("Graph initialized.\n");
        break;
      case 'v':
      case 'V':
        printf("Enter the vertex number: ");
        scanf("%d", &key);
        if (key >= MAX_VERTEX) {
          printf("최대 vertex 수를 넘겼습니다.\n");
          break;
        }
        insertVertex(graph, key);
        break;
      case 'e':
      case 'E':
        printf("Enter the source and destination : ");
        scanf("%d %d", &u, &v);
        insertEdge(graph, u, v);
        break;
      case 'd':
      case 'D':
        printf("Enter the starting vertex for DFS: ");
        scanf("%d", &key);
        if (key >= graph->n) {
          printf("This vertex isn't on graph.\n");
          break;
        }
        DFS_adjList(graph, key);
        for (int i = 0; i < MAX_VERTEX; i++)
          graph->visited[i] = 0;  // 방문한 곳 다시 초기화
        break;
      case 'b':
      case 'B':
        printf("Enter the starting vertex for BFS: ");
        scanf("%d", &key);
        if (key >= graph->n) {
          printf("This vertex isn't on graph.\n");
          break;
        }
        BFS_adjList(graph, key);
        for (int i = 0; i < MAX_VERTEX; i++)
          graph->visited[i] = 0;  // 방문한 곳 다시 초기화
        break;
      case 'p':
      case 'P':
        printList(graph);
        break;
      case 'q':
      case 'Q':
        break;
      default:
        printf("\n       >>>>>   Concentration!!   <<<<<     \n");
        break;
    }
  } while (command != 'q' && command != 'Q');  // q, Q를 입력하기 전까지 반복

  return 1;
}
