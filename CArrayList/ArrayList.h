#pragma once

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define DEFAULT_SIZE 10;


enum Type { NONE = 0 , CHAR , INT , LONG , FLOAT , DOUBLE , STRING , REFERENCE};

enum Bool {FALSE , TRUE};

typedef struct arrayList
{

	int capacity;
	int size;
	void** box;
	enum Type* typeArr; //c�� �ݵ�� �տ� enum Ű���带 �ٿ��־����

}ArrayList;
//����ü �ȿ����� �ʱ�ȭ�� ������� �ʴ´�

#pragma region Functions

ArrayList newArrayList(ArrayList* arr , enum Bool isCopy, ...);
/*
newArrayList(����� ArrayList �ּ� , ���� ���� , ũ�� or ������ ArrayList)

ArrayList ������ ���� ����
�Ѱܹ��� arrayList����ü�� �޸𸮸� �Ҵ�
���翩�ο� ���� true �̸� ����° ���ڿ� �� arrayList�� ����� arrayList�� ����
false�̸� ����° ���ڿ��� int���� ���� ũ�⸦ ����

*/
void al_add(ArrayList* list, enum Type type, ...);
/*
al_add(����� ArrayList �ּ�, Ÿ�� , ��)

�Ѱ� ���� ArrayList�� Ÿ�Կ� ���� ���� ����

*/
void* al_get(ArrayList* list, int index);
/*
al_get(����� ArrayList �ּ� , �ε���)

�ε����� ��ġ�� ���� (void*)Ÿ������ ���� �ε����� ������ ��������
Null�� ����
(���� �Ǽ��� �ڷ�� �˼����� ������ �߸��� ���� ���ϵ�..)

*/
void al_clear(ArrayList* list);
/*
al_clear(����� ArrayList �ּ�)

ArrayList�� ����Ǿ� �ִ� ���� ��� ���(�޸𸮴� ������ ����)

*/
int al_size(ArrayList* list);
/*
al_size(����� ArrayList �ּ�)

ArrayList�� ����� ���� ������ ����

*/
int al_isEmpty(ArrayList* list);
/*
al_isEmpty(����� ArrayList �ּ�);

ArrayList�� ��� ����ִ��� Ȯ�� ����ִٸ� true�� ����

*/
void al_allRemove(ArrayList* list);
/*
al_allRemove(����� ArrayList �ּ�);

ArrayList ��� ����(�޸� ����)

*/
void al_remove(ArrayList* list, int index);
/*
al_remove(����� ArrayList �ּ�);

�Ѱܹ��� �ε����� ��ġ�� ���� ����(�޸� ����)

*/
void printArray(ArrayList* list);
/*
al_printArray(����� ArrayList �ּ�);

ArrayList�� ����Ǿ� �ִ� ������ ���

*/
int al_indexOf(ArrayList* list, enum Type type, ...);
/*
al_printArray(����� ArrayList �ּ� , Ÿ��, ��);

�Ѱ� ���� Ÿ�԰� �´� ���� �ε��� ���� ���� ���ٸ� -1�� ����

*/
int al_contains(ArrayList* list, enum Type type, ...);
/*
al_printArray(����� ArrayList �ּ� , Ÿ��, ��);

�Ѱ� ���� Ÿ�԰� �´� ���� �����ϴ��� Ȯ���ϴ� �Լ�
�����ϸ� true�� ����

*/

#pragma endregion


ArrayList newArrayList(ArrayList* arr, enum Bool isCopy, ...) { //������ �������� Ÿ�Ե��� �ٸ���� �������ڸ� ���� ������ ��� �Ѵ�.

	va_list ap;
	va_start(ap, isCopy); //bool

	switch (isCopy)
	{
		case FALSE:
		{
			int size = va_arg(ap, int);
			arr->size = 0;

			if ((arr->capacity = size) <= 0) {
				arr->box = (void**)malloc(sizeof(void*) * 10);
				arr->typeArr = (enum Type*)malloc(sizeof(enum Type) * 10);

			}
			else {
				arr->box = (void**)malloc(sizeof(void*) * size);
				arr->typeArr = (enum Type*)malloc(sizeof(enum Type) * size);
			}
		}
		break;

		case TRUE: {
			ArrayList* copy = va_arg(ap, ArrayList*);
			arr = copy;
		}
			break;

	default:
		break;
	}


	return *arr;
}

void al_add(ArrayList* list , enum Type type, ...) {

	va_list ap;
	va_start(ap,  type); //type �ڿ������� �������ڰ� ���۵ȴٴ� ����


	

	int pos = list->size;

	if (pos >= list->capacity) {
		list->box = (void**)realloc(list->box, sizeof(void*) * list->size * 2);
		list->typeArr = (enum Type*)realloc(list->box, sizeof(enum Type) * list->size * 2);
		list->size *= 2;
	}

	
	
#pragma region InputByType

	switch (type)
	{
	case CHAR:
	{
		char* ap_char = (char*)malloc(sizeof(char));
		*ap_char = va_arg(ap, char);
		list->box[pos] = ap_char;
		list->typeArr[pos] = CHAR;

		break;
	}
	case INT:
	{

		int* ap_int = (int*)malloc(sizeof(int));
		*ap_int = va_arg(ap, int);
		list->box[pos] = ap_int;
		list->typeArr[pos] = INT;
		break;
	}
	case LONG:

	{
		long* ap_long = (long*)malloc(sizeof(long));
		*ap_long = va_arg(ap, long);
		list->box[pos] = ap_long;
		list->typeArr[pos] = LONG;

		break;
	}
	case FLOAT:
	{
		float* ap_float = (float*)malloc(sizeof(float));
		*ap_float = va_arg(ap, float);
		//printf("%f", *ap_float);
		list->box[pos] = ap_float;
		list->typeArr[pos] = FLOAT;

		break;
	}
	case DOUBLE:
	{
		double* ap_double = (double*)malloc(sizeof(double));
		*ap_double = va_arg(ap, double);
		list->box[pos] = ap_double;
		list->typeArr[pos] = DOUBLE;

		break;
	}
	case STRING:
	{
		char** ap_str = (char**)malloc(sizeof(char*));
		*ap_str = va_arg(ap, char*);
		list->box[pos] = ap_str;
		list->typeArr[pos] = STRING;
		break;
	}
	case REFERENCE:
	{ 
		list->box[pos] = va_arg(ap, void*);
		list->typeArr[pos] = REFERENCE;
	}
	default:
		break;
	}
#pragma endregion

	list->size++;
}



void* al_get(ArrayList* list, int index) {
	if (index < 0 || index > list->size - 1) 
		return NULL;

	

	void *value = list->box[index];


	return value;

}

void al_clear(ArrayList* list) {
	for (int i = 0; i < list->size; i++)
	{
		list->box[i] = NULL;
		list->typeArr[i] = NONE;
	}
	list->size = 0;
}

void al_remove(ArrayList* list, int index) {

	
	int lth = al_size(list);

	for (int i = index ; i < lth-1; i++) {		
		list->box[i] = list->box[i + 1];
		list->typeArr[i] = list->typeArr[i + 1];

	}
	list->box[lth-1] = NULL;
	free(list->box[lth - 1]);	
	//free((void*)(list->typeArr+(lth-1))); ��� ������ ��� ����ü ���� �������� �𸣰ڴ� ������ �̰� �ȵǵ� size���� �پ��� ������ ���ϱ⶧���� ��� X

	list->size--;
}

void al_allRemove(ArrayList* list) {

	for (int i = 0; i < list->size; i++)
	{
		list->box[i] = NULL;
		free(list->box[i]);
		//free(&list->typeArr[i]); //���� ����
	}
	free(list);

	list->size = 0;
}


void printArray(ArrayList* list) {

	printf("[");
	for (int i = 0; i < list->size; i++) {
		switch (list->typeArr[i])
		{
		case CHAR:
			printf("%c,", *(char*)list->box[i]);
			break;
		case INT:
			printf("%d,", *(int*)list->box[i]);
			break;
		case LONG:
			printf("%d,", *(long*)list->box[i]);
			break;
		case FLOAT:
			printf("%f,", *(float*)list->box[i]);
			break;
		case DOUBLE:
			printf("%f,", *(double*)list->box[i]);
			break;
		case STRING:
			printf("%s,", *(char**)list->box[i]);
			break;
		case REFERENCE:
			printf("%p(%dByte),", list->box[i],sizeof(list->box[i]));
			break;
		default:
			printf("NULL,");
			break;
		}
	}

	printf("]\n");
}

int al_indexOf(ArrayList* list, enum Type type, ...) {

	va_list ap;
	va_start(ap, type);

    const int size = list->size;
	int index = 0;
	for (index = 0; index < size; index++) {
	
		if (list->typeArr[index] == type) {


			switch (type)
			{
			case CHAR:
				if (*(char*)list->box[index] == va_arg(ap, char))
					goto result;
				break;
			case INT:
				if (*(int*)list->box[index] == va_arg(ap, int))
					goto result;
				break;
			case LONG:
				if (*(long*)list->box[index] == va_arg(ap, long))
					goto result;
				break;
			case FLOAT:
				if (*(float*)list->box[index] == va_arg(ap, float))
					goto result;
				break;
			case DOUBLE:
				if (*(double*)list->box[index] == va_arg(ap, double))
					goto result;
				break;
			case STRING:
				if (strcmp(*(char**)list->box[index], va_arg(ap, char*)) == 0)
					goto result;
				break;
			case REFERENCE:
				if (list->box[index] == va_arg(ap, void*))
					goto result;
				break;
			default:
				break;
			}

		}
	}

result:
	if (index == size) {
		return -1;
	}
	else {
		return index;
	}
	}

int al_contains(ArrayList* list, enum Type type, ...) { 
	
	va_list ap;
	va_start(ap, type);

	switch (type)
	{
	case CHAR:
		return al_indexOf(list, type, va_arg(ap, char)) != -1 ? 1 : 0;
		break;
	case INT:
		return al_indexOf(list, type, va_arg(ap, int)) != -1 ? 1 : 0;
		break;
	case LONG:
		return al_indexOf(list, type, va_arg(ap, long)) != -1 ? 1 : 0;
		break;
	case FLOAT:
		return al_indexOf(list, type, va_arg(ap, float)) != -1 ? 1 : 0;
		break;
	case DOUBLE:
		return al_indexOf(list, type, va_arg(ap, double)) != -1 ? 1 : 0;
		break;
	case STRING:
		return al_indexOf(list, type, va_arg(ap, char*)) != -1 ? 1 : 0;
		break;
	case REFERENCE:
		return al_indexOf(list, type, va_arg(ap, void*)) != -1 ? 1 : 0;
		break;
	default:
		return 0;
		break;
	}

}


int al_size(ArrayList* list) { return list->size; }
int al_isEmpty(ArrayList* list) { return list->size == 0; }










