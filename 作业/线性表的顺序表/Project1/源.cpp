#include <stdio.h>
#include <stdlib.h>
#define Size 4

//�Զ���˳���Ľṹ
typedef struct Table {
	int* head; //������һ����Ϊhead�ĳ��Ȳ�ȷ��������
	int length;//��¼�˵�ǰ˳���ĳ���
	int size;//��¼��˳���Ĵ洢����
}table;

//˳���Ĵ�������ʼ��
table initTable() {
	table t;
	t.head = (int*)malloc(Size * sizeof(int));//����һ���յ�˳�����̬����洢�ռ�,
	if (!t.head) //�������ʧ�ܣ�������ʾ��ֱ���˳�����
	{
		printf("��ʼ��ʧ��");
		exit(0);
	}
	t.length = 0;//�ձ�ĳ��ȳ�ʼ��Ϊ0
	t.size = Size;//�ձ�ĳ�ʼ�洢�ռ�ΪSize
	return t;
}

//����˳���Ԫ��
int selectTable(table t, int elem) {
	for (int i = 0; i < t.length; i++) {
		if (t.head[i] = elem) {
			return i + 1;
		}
	}
	return -1;//�������ʧ�ܣ�����-1

}

//���ĺ��������ò����㷨�ҵ�������Ԫ�ص�λ�ã�ֱ���ڸ�λ���ϸ��ġ�
table amendTable(table t, int elem, int newElem) {
	int add = selectTable(t, elem);
	t.head[add - 1] = newElem;//���ڷ��ص���Ԫ����˳����е�λ�ã�����-1���Ǹ�Ԫ���������е��±�
	return t;
}

//���뺯�������У�elemΪ�����Ԫ�أ�addΪ���뵽˳����λ��
table addTable(table t, int elem, int add)
{
	//�жϲ��뱾���Ƿ�������⣨�������Ԫ��λ�ñ����ű�ĳ���+1���������ȣ���β����������
	//���߲����λ�ñ������ڣ�������Ϊ��ʾ���Զ��˳���
	if (add > t.length + 1 || add < 1) {
		printf("����λ��������");
		return t;
	}
	//���������ʱ��������Ҫ��˳����Ƿ��ж���Ĵ洢�ռ��ṩ�������Ԫ�أ����û�У���Ҫ����
	if (t.length == t.size) {
		t.head = (int*)realloc(t.head, (t.size + 1) * sizeof(int));
		if (!t.head) {
			printf("�洢����ʧ��");
			return t;
		}
		t.size += 1;
	}
	//�����������Ҫ���Ӳ���λ�ÿ�ʼ�ĺ���Ԫ�أ��������
	for (int i = t.length - 1; i >= add - 1; i--) {
		t.head[i + 1] = t.head[i];
	}
	//������ɺ�ֱ�ӽ��������Ԫ�أ���ӵ�˳������Ӧλ��
	t.head[add - 1] = elem;
	//���������Ԫ�أ����Գ���+1
	t.length++;
	return t;
}

//��������ɾ��Ԫ��ʱ
table delTable(table t, int add) {
	if (add > t.length || add < 1) {
		printf("��ɾ��Ԫ�ص�λ������");
		exit(0);
	}
	//ɾ������
	for (int i = add; i < t.length; i++) {
		t.head[i - 1] = t.head[i];
	}
	t.length--;
	return t;
}


void displayTable(table t) {
	for (int i = 0; i < t.length; i++) {
		printf("%d", t.head[i]);
	}
	printf("\n");
}
int main() {
	table t1 = initTable();//��������
	for (int i = 1; i <= Size; i++) {
		t1.head[i - 1] = i;
		t1.length++;
	}
	printf("ԭ˳���\n");
	displayTable(t1);

	printf("ɾ��Ԫ��1:\n");
	t1 = delTable(t1, 1);
	displayTable(t1);

	printf("�ڵ�2��λ�ò���Ԫ��5:\n");
	t1 = addTable(t1, 5, 2);
	displayTable(t1);

	printf("����Ԫ��3��λ��:\n");
	int add = selectTable(t1, 3);
	printf("%d\n", add);

	printf("��Ԫ��3��Ϊ6:\n");
	t1 = amendTable(t1, 3, 6);
	displayTable(t1);
	return 0;
}