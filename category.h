#pragma once

#include "todo.h"

#include <iostream>
#include <string>
using namespace std;

typedef struct cate Cate_Struct;


class category {

	int index;									// ī�װ����� �Ϸù�ȣ ( 0: �̺з�, 1: �߿�� �̸� ����)
	string cate_name;

	todo* first_todo;							// ī�װ��� ó�� �� ���� �ּ�.(ī�װ� ���Ḯ��Ʈ�� ����.)

	category* next_cate;						// ���� ī�װ��� �ּ�.
	category* prev_cate;

public:
	category(string cate_name);							// ������
	category* create_cate(string cate_name);			// ī�װ� ��ü ���� ���� �Լ�.	

	void set_next_cate(category* p);					// ī�װ��� ���� �ּҸ� �Է¹޴� �Լ�.
	void set_prev_cate(category* p);					// ī�װ��� ���� �ּҸ� �Է¹޴� �Լ�.

	category* get_next_cate();							// ī�װ��� ���� �ּҸ� ��ȯ�ϴ� �Լ�.
	category* get_prev_cate();							// ī�װ��� ���� �ּҸ� ��ȯ�ϴ� �Լ�.

	int get_cate_index();								// ī�װ��� �ε��� ��ȣ(���� ����)�� ��ȯ.
	string get_cate_name();								// ī�װ��� �̸��� ��ȯ�ϴ� �Լ�.

	void set_first_todo(todo* p);						// ù ��° todo�� �ּҸ� �Է�
	todo* get_first_todo();								// ù ��° todo�� �ּҸ� ��ȯ

	void increase_index();								// remove���� �ʿ�. ī�װ����� index�� 1�� ���ҽ����ִ� �Լ�.
	
	static int cate_num;								// ī�װ� ��ü���� ������ �Ϸù�ȣ ����.
};


typedef struct cate {					// ī�װ����� ���Ḯ��Ʈ�� ù �κа� ������ �κ�, ī�װ��� ������ �����ϱ� ���� ����ü ����.
	int size;
	category* cate_head;
	category* cate_tail;
} Cate_Struct;