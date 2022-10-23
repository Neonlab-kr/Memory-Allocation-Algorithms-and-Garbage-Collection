#include <stdio.h>
#include <stdlib.h>

int count;
int* FreeArea;

typedef struct LinkedNode {
	int DataAddr; // 데이터 시작주소
	int DataSize; // 데이터의 크기
	char *Data;//저장 데이터
	struct LinkedNode* link;        // 다음 노드를 가리키는 포인터 변수
} Node;
Node* top = NULL;            // 연결 리스트의 헤드 포인터

void init_list() { top = NULL; }//리스트 초기화

CalcFreeArea()
{
	free(FreeArea);//앞서 할당받은 배열 해제
	count = 0;//카운트를 0으로 초기화
	for (Node *p = top;p != NULL;p = p->link)//공백 공간의 수 세기
	{
		count++;
	}
	FreeArea = (int*)malloc(sizeof(int) * count);//공백공간의 수만큼 배열 동적 할당
	int i = 0;
	for (Node *p = top;p != NULL;p = p->link, i++)
	{
		if (p->link == NULL)
		{
			FreeArea[i] = 100 - (p->DataAddr + p->DataSize);//마지막엔 최대 크기인 100에서 끝주소를 뻄
		}
		else
		{
			FreeArea[i] = (p->link)->DataAddr - (p->DataAddr + p->DataSize);//다음 데이터의 시작주소에서 앞 데이터의 끝주소를 뺌
		}
	}
}

AddFileFirst(int size, char *data)
{
	CalcFreeArea();//여유공간 계산

	Node* q = (Node*)malloc(sizeof(Node));//노드 동적 할당
	q->DataSize = size;//데이터 크기 저장
	q->Data = data;//데이터 저장
	int num;
	for (int i = 0;i < count;i++)
	{
		if (FreeArea[i] - size >= 0)//여유 공간에 들어간다면 종료
		{
			num = i;
			break;
		}
	}
	Node* p = top;
	for (int i = 0;i < num;i++)//데이터가 연결될 여유공간 앞 데이터로 이동
	{
		p = p->link;
	}
	q->DataAddr = p->DataAddr + p->DataSize;//앞데이터의 끝주소가 신규 데이터의 시작주소
	q->link = p->link;//앞데이터의 다음 데이터를 신규데이터와 연결
	p->link = q;//앞데이터와 신규데이터를 연결
}

AddFileBest(int size,char *data)
{
	CalcFreeArea();//여유공간 계산

	Node* q = (Node*)malloc(sizeof(Node));//노드 동적 할당
	q->DataSize = size;//데이터 크기 저장
	q->Data = data;//데이터 저장
	int min = 1000;
	int minnum;
	for (int i = 0;i < count;i++)			//여유공간이 가장 적게 남는 곳에 데이터 삽입
	{
		if (min > FreeArea[i] - size && FreeArea[i] - size >= 0)
		{
			min = FreeArea[i] - size;
			minnum = i;
		}
	}
	Node* p = top;
	for (int i = 0;i < minnum;i++)//데이터가 연결될 여유공간 앞 데이터로 이동
	{
		p = p->link;
	}
	q->DataAddr = p->DataAddr + p->DataSize;//앞데이터의 끝주소가 신규 데이터의 시작주소
	q->link = p->link;//앞데이터의 다음 데이터를 신규데이터와 연결
	p->link = q;//앞데이터와 신규데이터를 연결
}

AddFileWorst(int size, char *data)
{
	CalcFreeArea();

	Node* q = (Node*)malloc(sizeof(Node));//노드 동적 할당
	q->DataSize = size;//데이터 크기 저장
	q->Data = data;//데이터 저장
	int max = -1;
	int maxnum;
	for (int i = 0;i < count;i++)			//여유공간이 가장 많이 남는 곳에 데이터 삽입
	{
		if (max < FreeArea[i] - size && FreeArea[i] - size >= 0)
		{
			max = FreeArea[i] - size;
			maxnum = i;
		}
	}
	Node* p = top;
	for (int i = 0;i < maxnum;i++)//데이터가 연결될 여유공간 앞 데이터로 이동
	{
		p = p->link;
	}
	q->DataAddr = p->DataAddr + p->DataSize;//앞데이터의 끝주소가 신규 데이터의 시작주소
	q->link = p->link;//앞데이터의 다음 데이터를 신규데이터와 연결
	p->link = q;//앞데이터와 신규데이터를 연결
}

DeleteNode(char *data)//가비지 컬렉션시 데이터 삭제
{
	printf("\n\n%s를(을) 삭제합니다.\n", data);
	Node *p, *q;
	if (top->Data == data)//top이 가르키는 노드 삭제시
	{
		p = top;
		top = p->link;//top을 다음 노드와 연결
		free(p);//데이터 삭제
	}
	else//그외 노드 삭제시
	{
		for (p = top;p != NULL;p = p->link)//해당 데이터의 전 노드 찾기
		{
			if ((p->link)->Data == data)
			{
				break;
			}
		}
		q = p->link;
		p->link = (p->link)->link;//전 노드를 해당 데이터 다음 노드와 연결
		free(q);//데이터 삭제
	}
}

Setup()//문제에 제시된 P1,P2,P3를 생성 및 연결하는 코드
{
	Node* p = (Node*)malloc(sizeof(Node));//노드 동적 할당
	p->DataAddr = 57;
	p->DataSize = 25;
	p->Data = "P3";
	p->link = top;
	top = p;

	Node* q = (Node*)malloc(sizeof(Node));//노드 동적 할당
	q->DataAddr = 25;
	q->DataSize = 12;
	q->Data = "P2";
	q->link = top;
	top = q;

	Node* r = (Node*)malloc(sizeof(Node));//노드 동적 할당
	r->DataAddr = 0;
	r->DataSize = 10;
	r->Data = "P1";
	r->link = top;
	top = r;
}

GarbageCollect()//가비지 컬렉션
{
	for (Node *p = top;p != NULL;p = p->link)//다음 노드의 시작주소를 앞에서부터 여유공간없이 배치
	{
		if(p->link!=NULL)
			(p->link)->DataAddr = p->DataAddr + p->DataSize;
	}

}

void main()
{
	init_list();
	Setup();
	AddFileFirst(18, "P4");
	AddFileFirst(10, "P5");
	AddFileFirst(9, "P6");
	AddFileFirst(8, "P7");
	printf("<first fit>\n|   ");//순차적으로 가능하면 바로 삽입한 경우
	for (Node *p = top;p != NULL;p = p->link)
	{
		printf("%s   |   ", p->Data);
	}

	init_list();
	Setup();
	AddFileBest(18, "P4");
	AddFileBest(10, "P5");
	AddFileBest(9, "P6");
	AddFileBest(8, "P7");
	printf("\n<Best fit>\n|   ");//최상의 경우
	for (Node *p = top;p != NULL;p = p->link)
	{
		printf("%s   |   ", p->Data);
	}

	init_list();
	Setup();
	AddFileWorst(18, "P4");
	AddFileWorst(10, "P5");
	AddFileWorst(9, "P6");
	AddFileWorst(8, "P7");
	printf("\n<Worst fit>\n|   ");//최악의 경우
	for (Node *p = top;p != NULL;p = p->link)
	{
		printf("%s   |   ", p->Data);
	}

	CalcFreeArea();
	printf("\n<<BeforeGC FreeArea>\n   ");//현재 여유공간출력
	for (int i = 0;i < count;i++)
	{
		printf("	%d", FreeArea[i]);
	}
	GarbageCollect();
	CalcFreeArea();
	printf("\n<AfterGC FreeArea>\n   ");//가비지 컬렉션 이후 여유공간출력
	for (int i = 0;i < count;i++)
	{
		printf("	%d", FreeArea[i]);
	}

	DeleteNode("P1");
	DeleteNode("P2");
	printf("\n<After Delete>\n|   ");//P1,P2삭제 이후
	for (Node *p = top;p != NULL;p = p->link)
	{
		printf("%s   |   ", p->Data);
	}
}