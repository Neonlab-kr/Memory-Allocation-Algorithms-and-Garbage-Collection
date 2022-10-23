#include <stdio.h>
#include <stdlib.h>

int count;
int* FreeArea;

typedef struct LinkedNode {
	int DataAddr; // ������ �����ּ�
	int DataSize; // �������� ũ��
	char *Data;//���� ������
	struct LinkedNode* link;        // ���� ��带 ����Ű�� ������ ����
} Node;
Node* top = NULL;            // ���� ����Ʈ�� ��� ������

void init_list() { top = NULL; }//����Ʈ �ʱ�ȭ

CalcFreeArea()
{
	free(FreeArea);//�ռ� �Ҵ���� �迭 ����
	count = 0;//ī��Ʈ�� 0���� �ʱ�ȭ
	for (Node *p = top;p != NULL;p = p->link)//���� ������ �� ����
	{
		count++;
	}
	FreeArea = (int*)malloc(sizeof(int) * count);//��������� ����ŭ �迭 ���� �Ҵ�
	int i = 0;
	for (Node *p = top;p != NULL;p = p->link, i++)
	{
		if (p->link == NULL)
		{
			FreeArea[i] = 100 - (p->DataAddr + p->DataSize);//�������� �ִ� ũ���� 100���� ���ּҸ� �M
		}
		else
		{
			FreeArea[i] = (p->link)->DataAddr - (p->DataAddr + p->DataSize);//���� �������� �����ּҿ��� �� �������� ���ּҸ� ��
		}
	}
}

AddFileFirst(int size, char *data)
{
	CalcFreeArea();//�������� ���

	Node* q = (Node*)malloc(sizeof(Node));//��� ���� �Ҵ�
	q->DataSize = size;//������ ũ�� ����
	q->Data = data;//������ ����
	int num;
	for (int i = 0;i < count;i++)
	{
		if (FreeArea[i] - size >= 0)//���� ������ ���ٸ� ����
		{
			num = i;
			break;
		}
	}
	Node* p = top;
	for (int i = 0;i < num;i++)//�����Ͱ� ����� �������� �� �����ͷ� �̵�
	{
		p = p->link;
	}
	q->DataAddr = p->DataAddr + p->DataSize;//�յ������� ���ּҰ� �ű� �������� �����ּ�
	q->link = p->link;//�յ������� ���� �����͸� �űԵ����Ϳ� ����
	p->link = q;//�յ����Ϳ� �űԵ����͸� ����
}

AddFileBest(int size,char *data)
{
	CalcFreeArea();//�������� ���

	Node* q = (Node*)malloc(sizeof(Node));//��� ���� �Ҵ�
	q->DataSize = size;//������ ũ�� ����
	q->Data = data;//������ ����
	int min = 1000;
	int minnum;
	for (int i = 0;i < count;i++)			//���������� ���� ���� ���� ���� ������ ����
	{
		if (min > FreeArea[i] - size && FreeArea[i] - size >= 0)
		{
			min = FreeArea[i] - size;
			minnum = i;
		}
	}
	Node* p = top;
	for (int i = 0;i < minnum;i++)//�����Ͱ� ����� �������� �� �����ͷ� �̵�
	{
		p = p->link;
	}
	q->DataAddr = p->DataAddr + p->DataSize;//�յ������� ���ּҰ� �ű� �������� �����ּ�
	q->link = p->link;//�յ������� ���� �����͸� �űԵ����Ϳ� ����
	p->link = q;//�յ����Ϳ� �űԵ����͸� ����
}

AddFileWorst(int size, char *data)
{
	CalcFreeArea();

	Node* q = (Node*)malloc(sizeof(Node));//��� ���� �Ҵ�
	q->DataSize = size;//������ ũ�� ����
	q->Data = data;//������ ����
	int max = -1;
	int maxnum;
	for (int i = 0;i < count;i++)			//���������� ���� ���� ���� ���� ������ ����
	{
		if (max < FreeArea[i] - size && FreeArea[i] - size >= 0)
		{
			max = FreeArea[i] - size;
			maxnum = i;
		}
	}
	Node* p = top;
	for (int i = 0;i < maxnum;i++)//�����Ͱ� ����� �������� �� �����ͷ� �̵�
	{
		p = p->link;
	}
	q->DataAddr = p->DataAddr + p->DataSize;//�յ������� ���ּҰ� �ű� �������� �����ּ�
	q->link = p->link;//�յ������� ���� �����͸� �űԵ����Ϳ� ����
	p->link = q;//�յ����Ϳ� �űԵ����͸� ����
}

DeleteNode(char *data)//������ �÷��ǽ� ������ ����
{
	printf("\n\n%s��(��) �����մϴ�.\n", data);
	Node *p, *q;
	if (top->Data == data)//top�� ����Ű�� ��� ������
	{
		p = top;
		top = p->link;//top�� ���� ���� ����
		free(p);//������ ����
	}
	else//�׿� ��� ������
	{
		for (p = top;p != NULL;p = p->link)//�ش� �������� �� ��� ã��
		{
			if ((p->link)->Data == data)
			{
				break;
			}
		}
		q = p->link;
		p->link = (p->link)->link;//�� ��带 �ش� ������ ���� ���� ����
		free(q);//������ ����
	}
}

Setup()//������ ���õ� P1,P2,P3�� ���� �� �����ϴ� �ڵ�
{
	Node* p = (Node*)malloc(sizeof(Node));//��� ���� �Ҵ�
	p->DataAddr = 57;
	p->DataSize = 25;
	p->Data = "P3";
	p->link = top;
	top = p;

	Node* q = (Node*)malloc(sizeof(Node));//��� ���� �Ҵ�
	q->DataAddr = 25;
	q->DataSize = 12;
	q->Data = "P2";
	q->link = top;
	top = q;

	Node* r = (Node*)malloc(sizeof(Node));//��� ���� �Ҵ�
	r->DataAddr = 0;
	r->DataSize = 10;
	r->Data = "P1";
	r->link = top;
	top = r;
}

GarbageCollect()//������ �÷���
{
	for (Node *p = top;p != NULL;p = p->link)//���� ����� �����ּҸ� �տ������� ������������ ��ġ
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
	printf("<first fit>\n|   ");//���������� �����ϸ� �ٷ� ������ ���
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
	printf("\n<Best fit>\n|   ");//�ֻ��� ���
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
	printf("\n<Worst fit>\n|   ");//�־��� ���
	for (Node *p = top;p != NULL;p = p->link)
	{
		printf("%s   |   ", p->Data);
	}

	CalcFreeArea();
	printf("\n<<BeforeGC FreeArea>\n   ");//���� �����������
	for (int i = 0;i < count;i++)
	{
		printf("	%d", FreeArea[i]);
	}
	GarbageCollect();
	CalcFreeArea();
	printf("\n<AfterGC FreeArea>\n   ");//������ �÷��� ���� �����������
	for (int i = 0;i < count;i++)
	{
		printf("	%d", FreeArea[i]);
	}

	DeleteNode("P1");
	DeleteNode("P2");
	printf("\n<After Delete>\n|   ");//P1,P2���� ����
	for (Node *p = top;p != NULL;p = p->link)
	{
		printf("%s   |   ", p->Data);
	}
}