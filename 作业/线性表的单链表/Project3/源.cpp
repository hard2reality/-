#include <stdio.h>
#include <stdlib.h>
#define bool int
#define true 1
#define false 0
#define ok 1
#define error 0

typedef int ElemType;
typedef int Status;

typedef struct Node {//���Ա�ĵ�����洢�ṹ 
	ElemType data;//������ 
	struct Node* next;//ָ���� 
} Node;

typedef struct Node* LinkList;//����LinkList:struct Node* 

//�������� 
void InitList(LinkList* L);
bool ListEmpty(LinkList L);
void ClearList(LinkList* L);
Status GetElem(LinkList L, int i, ElemType* e);
int LocateElem(LinkList L, ElemType e);
Status ListInsert(LinkList* L, int i, ElemType e);
Status ListDelete(LinkList* L, int i, ElemType* e);
int ListLength(LinkList L);
void PrintList(LinkList L);

int main(int argc, char* argv[]) {//������������в��� 
	ElemType e;//�������e�������汻ɾ�������� 
	LinkList list;//����һ������list 
	InitList(&list);//��ʼ���� 
	printf("�����Ƿ�Ϊ��? %d\n", ListEmpty(list));//ʹ��ListEmpty�ж������Ƿ�Ϊ��,��ʱ��Ϊ����û��Ԫ��,���Եõ�1��ʾΪ�� 
	ListInsert(&list, 1, 1);//ʹ��ListInsert����3���ڵ�,���ݷֱ�Ϊ1,2,3;��Ϊ���Ǵӵ�һ��λ�ò���Ԫ��,�൱��ͷ�巨 
	ListInsert(&list, 1, 2);
	ListInsert(&list, 1, 3);
	PrintList(list);//��ӡһ�µ�ǰ����,���3,2,1 
	printf("����2��λ���� %d\n", LocateElem(list, 2)); //ʹ��LocateElem��������Ϊ2��Ԫ��,����ӡ��λ�� 
	printf("����4��λ���� %d\n", LocateElem(list, 4)); //ʹ��LocateElem��������Ϊ4��Ԫ��,����ӡ��λ��,���ڴ�ʱ������û������4,���Դ�ӡ��ֵΪ0 
	printf("����ĳ���: %d\n", ListLength(list));//ʹ��ListLength��ӡ����ĳ���,��ʱΪ3 
	ListInsert(&list, 1, 4);//ʹ��ListInsert������������Ԫ�� 
	ListInsert(&list, 1, 5);
	PrintList(list);//��ʱ��ӡ��ֵΪ5,4,3,2,1 
	printf("����4��λ���� %d\n", LocateElem(list, 4));//��ʱ����ʹ��LocateElem���ҵ�����4��λ�� 
	printf("�����Ƿ�Ϊ��? %d\n", ListEmpty(list));//ʹ��ListEmpty�ж������Ƿ�Ϊ��,��Ϊ�Ѿ���5��Ԫ��,���Դ�ӡ0 
	printf("����ĳ���: %d\n", ListLength(list));//��ʱ����ĳ���Ϊ5
	ListInsert(&list, 3, 100);//���м����һ��Ԫ��100 
	PrintList(list);//��ӡ��ʾ5,4,100,3,2,1 
	ListDelete(&list, 3, &e);//ʹ�� ListDeleteɾ��������Ԫ�ؼ�100 
	PrintList(list);//�ٴδ�ӡ����100�Ѿ���ɾ��,��ʾ5,4,3,2,1 
	printf("��ɾ����Ԫ��Ϊ:%d\n", e);//ͨ������ո�ɾ����Ԫ�صı���e��ӡɾ����Ԫ�ص����� 
	ClearList(&list);//������� 
	printf("�����Ƿ�Ϊ��? %d\n", ListEmpty(list));//��ʱ����Ϊ��,��ӡ1 
	printf("����ĳ���: %d\n", ListLength(list));//����պ�����ĳ���Ϊ0 
	return 0;
}

void InitList(LinkList* L) {//��ʼ������ 
	*L = (LinkList)malloc(sizeof(Node));//Ϊ���������ͷ��� 
	(*L)->next = NULL;//ָ��������Ϊ�� 
}

bool ListEmpty(LinkList L) {//�ж������Ƿ�Ϊ�� 
	return L->next == NULL;//���ͷ����ָ����Ϊ��,���ʾ�ǿ����� 
}

void ClearList(LinkList* L) {//������� 
	LinkList p, q;//������������ָ�� 
	p = (*L)->next;//pָ���һ�����,�ӵ�һ����㿪ʼɾ�� 
	while (p) {//û����β�ͼ���ѭ�� 
		q = p->next;//q����¼��һ����� 
		free(p);//ɾ��pָ��Ľ�� 
		p = q;//��qָ�����һ����㸳ֵ��p 
	}
	(*L)->next = NULL;//ָ��������Ϊ�� 
}

Status GetElem(LinkList L, int i, ElemType* e) {//�����Ա�L�еĵ�i��Ԫ��ֵ���ظ�e 
	int j;//���������j 
	LinkList p;//���帨��ָ��p 
	p = L->next;//pָ������ĵ�һ�����,�ӵ�һ����㿪ʼ���� 
	j = 1;//��������ʼ��Ϊ1 
	while (p && j < i) {//���û����β���߼�����������i�ͼ���ѭ�� 
		p = p->next;//pָ����һ����� 
		++j;//�������Լ� 
	}
	if (!p || j > i) {//����β��Ƿ�ֵ,j > i ���ڷǷ�ֵ����,���紫��i = 0 
		return error;//���ش���ֵ 
	}
	*e = p->data;//�ѵõ���ֵ������ָ��eָ��Ŀռ� 
	return ok;//���سɹ� 
}

int LocateElem(LinkList L, ElemType e) {//�����Ա�L �в��������ֵe��ȵ�Ԫ��,������ҳɹ�,���ظ�Ԫ���ڱ�����ű�ʾ�ɹ�;����,����0��ʾʧ��. 
	int j;//���������j 
	LinkList p;//���帨��ָ��p 
	p = L->next;//pָ������ĵ�һ�����,�ӵ�һ����㿪ʼ���� 
	j = 1;//��������ʼ��Ϊ1 
	while (p && p->data != e) {//���û����β���߻�û�в�ѯ������Ԫ�ؼ���ѭ�� 
		p = p->next;//pָ����һ����� 
		++j;//�������Լ� 
	}
	if (!p) {//�������β 
		return 0;//����0��ʾ����ʧ�� 
	}
	return j;//���ز��ҵ���Ԫ�ص����,���ڼ�����j��ֵ 
}

Status ListInsert(LinkList* L, int i, ElemType e) {//������L�ĵ�i��λ�ò���Ԫ��e 
	int j;//���������j 
	LinkList p, s;//������������ָ��p,s 
	p = *L;//pָ�������ͷ���,���������Ҫ�ҵ�ָ��λ�õ�ǰһ��λ��,ͷ����ǵ�һ��λ�õ�ǰ�� 
	j = 1;//��������ʼ��Ϊ1 
	while (p && j < i) {//���û����β����j<i�ͼ���ѭ��,��Ϊpָ��ͷ���,���Ե�j=iʱpָ���i������ǰһ����� 
		p = p->next;//pָ���һ����� 
		++j;//�������Լ�1 
	}
	if (!p || j > i) {//��������β��������Ƿ�,j>i ���ڷǷ�ֵ����,���紫��i=0 
		return error;//���ش��� 
	}
	s = (LinkList)malloc(sizeof(Node));//��s����ռ� 
	s->data = e;//s�����򱣴�Ԫ��e, 
	s->next = p->next;//sָ��p����һ��������NULL,��ԭ����i��λ�õĽ�����β�� 
	p->next = s;//ԭ����i��λ�õ�ǰһ�����pָ���½��s 
	return ok; //���سɹ� 
}

Status ListDelete(LinkList* L, int i, ElemType* e) {//ɾ������L�ĵ�i�����,����e������ֵ 
	int j;//��������� 
	LinkList p, q;//������������ָ��p,q 
	p = *L;//pָ��ͷ���,��Ϊɾ��������Ҫ�ҵ���Ҫɾ���Ľ���ǰһ�����,ͷ����ǵ�һ������ǰһ����� 
	j = 1;// ��ʼ��������Ϊ1 
	while (p->next && j < i) {//���������һ��Ԫ��,�����ҵ���i������ǰһ�����ʱ����ѭ�� 
		p = p->next;//pָ����һ���ڵ� 
		++j;//�������Լ�1 
	}
	if (!(p->next) || j > i) {//����������һ��Ԫ�ػ��߷Ƿ�����,j>i ���ڷǷ�ֵ����,���紫��i=0 
		return error;//���ش��� 
	}
	q = p->next;//qָ��Ҫɾ���Ľ��,��p����һ����� 
	p->next = q->next;//ǰһ�����pԽ��Ҫɾ���Ľ��qָ��q����һ����� 
	*e = q->data;//��Ҫɾ���Ľ��p�����ݸ�����e 
	free(q);//ɾ�����q 
	return ok;//���سɹ� 
}

int ListLength(LinkList L) {//��������L�ĳ��� 
	int j;//���������j 
	LinkList p;//���帨��ָ��P 
	p = L->next;//pָ���һ����� 
	j = 0;//��������ʼ��Ϊ0 
	while (p) {//������βʱ�˳�ѭ�� 
		p = p->next;//pָ����һ����� 
		++j;//�������Լ�1 
	}
	return j;//��������Ԫ�صĸ���,��������j��ֵ 
}

void PrintList(LinkList L) {//������ӡ���� 
	int i;//����ѭ������i 
	ElemType e;//����һ�����ݱ�������������ҵ���ֵ 
	for (i = 1; i < ListLength(L) + 1; i++) {//ѭ����1��ʼ,�����һ��Ԫ�ؽ���,������ĳ���ֵ��ͬλ�õ�Ԫ�� 
		if (GetElem(L, i, &e)) {//������ҵ�i��Ԫ�سɹ� 
			printf("%d ", e);//��ӡ��������e�е�Ԫ������ 
		}
	}
	printf("\n");
}
