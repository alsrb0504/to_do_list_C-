#pragma once

#include "todo.h"

#include <iostream>
#include <string>
using namespace std;


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
	
		
	
	// ���� ���� �͵�.


	
	

	void set_cate_name(string cate_name);		// ī�װ��� �̸��� �����ϴ� �Լ�.



	//void add_to_cate(category* ptr_cate);			// ī�װ� ���Ḯ��Ʈ�� ī�װ��� �߰��ϴ� �Լ�.

	void show_cate_name();						// ī�װ��� �̸��� �����ִ� �Լ�.
	

	void remove_linkedlist_cate(category* cate);		// ī�װ� ���Ḯ��Ʈ���� ī�װ��� �����ϴ� �Լ�.
	void empty_category();								// ��� ī�װ��� ����� �Լ�.

	bool is_empty_cate();						// ī�װ��� ������� Ȯ���ϴ� �Լ�.

	void add_todo_cate(todo* ptr_todo);			// imsi_cate�� �� ���� cate ���Ḯ��Ʈ�� �߰����ִ� �Լ�.

	todo* getFirsttodo();



	static int cate_num;						// ī�װ� ��ü���� ������ �Ϸù�ȣ ����.

	static category* head_cate;					// ī�װ� ���Ḯ��Ʈ���� ������ ����.		// 0, 1�� �̹� ���, 2���� ���� �����Ǵ� ī�װ��� ���� ��.
};



// �� ����ü�� command�� �Űܾ� �ұ�??


typedef struct cate {					// ī�װ����� ���Ḯ��Ʈ�� ù �κа� ������ �κ�, ī�װ��� ������ �����ϱ� ���� ����ü ����.
	int size;
	category* cate_head;
	category* cate_tail;
} Cate_Struct;