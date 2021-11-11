#include <stdio.h>
#include <stdlib.h>
#define bool int
#define true 1
#define false 0
#define ok 1
#define error 0

typedef int ElemType;
typedef int Status;

typedef struct Node {//线性表的单链表存储结构 
	ElemType data;//数据域 
	struct Node* next;//指针域 
} Node;

typedef struct Node* LinkList;//定义LinkList:struct Node* 

//函数声明 
void InitList(LinkList* L);
bool ListEmpty(LinkList L);
void ClearList(LinkList* L);
Status GetElem(LinkList L, int i, ElemType* e);
int LocateElem(LinkList L, ElemType e);
Status ListInsert(LinkList* L, int i, ElemType e);
Status ListDelete(LinkList* L, int i, ElemType* e);
int ListLength(LinkList L);
void PrintList(LinkList L);

int main(int argc, char* argv[]) {//在主函数里进行测试 
	ElemType e;//定义变量e用来保存被删除的数据 
	LinkList list;//定义一个链表list 
	InitList(&list);//初始化它 
	printf("链表是否为空? %d\n", ListEmpty(list));//使用ListEmpty判断链表是否为空,此时因为链表没有元素,所以得到1表示为空 
	ListInsert(&list, 1, 1);//使用ListInsert插入3个节点,数据分别为1,2,3;因为都是从第一个位置插入元素,相当于头插法 
	ListInsert(&list, 1, 2);
	ListInsert(&list, 1, 3);
	PrintList(list);//打印一下当前链表,输出3,2,1 
	printf("数据2的位置是 %d\n", LocateElem(list, 2)); //使用LocateElem查找数据为2的元素,并打印其位置 
	printf("数据4的位置是 %d\n", LocateElem(list, 4)); //使用LocateElem查找数据为4的元素,并打印其位置,由于此时链表中没有数据4,所以打印的值为0 
	printf("链表的长度: %d\n", ListLength(list));//使用ListLength打印链表的长度,此时为3 
	ListInsert(&list, 1, 4);//使用ListInsert继续插入两个元素 
	ListInsert(&list, 1, 5);
	PrintList(list);//此时打印的值为5,4,3,2,1 
	printf("数据4的位置是 %d\n", LocateElem(list, 4));//此时可以使用LocateElem查找到数据4的位置 
	printf("链表是否为空? %d\n", ListEmpty(list));//使用ListEmpty判断链表是否为空,因为已经有5个元素,所以打印0 
	printf("链表的长度: %d\n", ListLength(list));//此时链表的长度为5
	ListInsert(&list, 3, 100);//在中间插入一个元素100 
	PrintList(list);//打印显示5,4,100,3,2,1 
	ListDelete(&list, 3, &e);//使用 ListDelete删除第三个元素即100 
	PrintList(list);//再次打印发现100已经被删除,显示5,4,3,2,1 
	printf("被删除的元素为:%d\n", e);//通过保存刚刚删除的元素的变量e打印删除的元素的数据 
	ClearList(&list);//清空链表 
	printf("链表是否为空? %d\n", ListEmpty(list));//此时链表为空,打印1 
	printf("链表的长度: %d\n", ListLength(list));//被清空后链表的长度为0 
	return 0;
}

void InitList(LinkList* L) {//初始化链表 
	*L = (LinkList)malloc(sizeof(Node));//为单链表分配头结点 
	(*L)->next = NULL;//指针域设置为空 
}

bool ListEmpty(LinkList L) {//判断链表是否为空 
	return L->next == NULL;//如果头结点的指针域为空,则表示是空链表 
}

void ClearList(LinkList* L) {//清空链表 
	LinkList p, q;//定义两个辅助指针 
	p = (*L)->next;//p指向第一个结点,从第一个结点开始删除 
	while (p) {//没到表尾就继续循环 
		q = p->next;//q来记录下一个结点 
		free(p);//删除p指向的结点 
		p = q;//把q指向的下一个结点赋值给p 
	}
	(*L)->next = NULL;//指针域设置为空 
}

Status GetElem(LinkList L, int i, ElemType* e) {//将线性表L中的第i个元素值返回给e 
	int j;//定义计数器j 
	LinkList p;//定义辅助指针p 
	p = L->next;//p指向单链表的第一个结点,从第一个结点开始遍历 
	j = 1;//计数器初始化为1 
	while (p && j < i) {//如果没到表尾或者计数器不等于i就继续循环 
		p = p->next;//p指向下一个结点 
		++j;//计数器自加 
	}
	if (!p || j > i) {//到表尾或非法值,j > i 用于非法值处理,比如传入i = 0 
		return error;//返回错误值 
	}
	*e = p->data;//把得到的值给参数指针e指向的空间 
	return ok;//返回成功 
}

int LocateElem(LinkList L, ElemType e) {//在线性表L 中查找与给定值e相等的元素,如果查找成功,返回该元素在表中序号表示成功;否则,返回0表示失败. 
	int j;//定义计数器j 
	LinkList p;//定义辅助指针p 
	p = L->next;//p指向单链表的第一个结点,从第一个结点开始查找 
	j = 1;//计数器初始化为1 
	while (p && p->data != e) {//如果没到表尾或者还没有查询到给定元素继续循环 
		p = p->next;//p指向下一个结点 
		++j;//计数器自加 
	}
	if (!p) {//如果到表尾 
		return 0;//返回0表示查找失败 
	}
	return j;//返回查找到的元素的序号,等于计数器j的值 
}

Status ListInsert(LinkList* L, int i, ElemType e) {//在链表L的第i个位置插入元素e 
	int j;//定义计数器j 
	LinkList p, s;//定义两个辅助指针p,s 
	p = *L;//p指向链表的头结点,插入操作需要找到指定位置的前一个位置,头结点是第一个位置的前驱 
	j = 1;//计数器初始化为1 
	while (p && j < i) {//如果没到表尾或者j<i就继续循环,因为p指向头结点,所以当j=i时p指向第i个结点的前一个结点 
		p = p->next;//p指向后一个结点 
		++j;//计数器自加1 
	}
	if (!p || j > i) {//如果到达表尾或者输入非法,j>i 用于非法值处理,比如传入i=0 
		return error;//返回错误 
	}
	s = (LinkList)malloc(sizeof(Node));//给s分配空间 
	s->data = e;//s数据域保存元素e, 
	s->next = p->next;//s指向p的下一个结点或者NULL,即原来第i个位置的结点或者尾部 
	p->next = s;//原来第i个位置的前一个结点p指向新结点s 
	return ok; //返回成功 
}

Status ListDelete(LinkList* L, int i, ElemType* e) {//删除链表L的第i个结点,并用e返回其值 
	int j;//定义计数器 
	LinkList p, q;//定义两个辅助指针p,q 
	p = *L;//p指向头结点,因为删除操作需要找到需要删除的结点的前一个结点,头结点是第一个结点的前一个结点 
	j = 1;// 初始化计数器为1 
	while (p->next && j < i) {//当到达最后一个元素,或者找到第i个结点的前一个结点时结束循环 
		p = p->next;//p指向下一个节点 
		++j;//计数器自加1 
	}
	if (!(p->next) || j > i) {//如果到达最后一个元素或者非法输入,j>i 用于非法值处理,比如传入i=0 
		return error;//返回错误 
	}
	q = p->next;//q指向要删除的结点,即p的下一个结点 
	p->next = q->next;//前一个结点p越过要删除的结点q指向q的下一个结点 
	*e = q->data;//把要删除的结点p的数据给参数e 
	free(q);//删除结点q 
	return ok;//返回成功 
}

int ListLength(LinkList L) {//返回链表L的长度 
	int j;//定义计数器j 
	LinkList p;//定义辅助指针P 
	p = L->next;//p指向第一个结点 
	j = 0;//计数器初始化为0 
	while (p) {//当到表尾时退出循环 
		p = p->next;//p指向下一个结点 
		++j;//计数器自加1 
	}
	return j;//返回链表元素的个数,即计数器j的值 
}

void PrintList(LinkList L) {//遍历打印链表 
	int i;//定义循环变量i 
	ElemType e;//定义一个数据变量用来保存查找到的值 
	for (i = 1; i < ListLength(L) + 1; i++) {//循环从1开始,到最后一个元素结束,即链表的长度值相同位置的元素 
		if (GetElem(L, i, &e)) {//如果查找第i个元素成功 
			printf("%d ", e);//打印被保存在e中的元素数据 
		}
	}
	printf("\n");
}
