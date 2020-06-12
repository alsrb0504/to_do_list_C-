#pragma once

#include "todo.h"

#include <iostream>
#include <string>
using namespace std;

typedef struct cate_struct Cate_struct;		
//extern Cate_Struct cate_struct;					// ī�װ� ���Ḯ��Ʈ�� head, tail, ī�װ��� ���� �����ϱ� ���� ����ü ���� ����.

// ������ : category.h�� todo.h�� ������ ��Ŭ���? ���ϴ���??

class category {

	int index;									// ī�װ����� �Ϸù�ȣ ( 0: �̺з�, 1: �߿�� �̸� ����)
	string cate_name;

	todo* first_todo;							// ī�װ��� ó�� �� ���� �ּ�.(ī�װ� ���Ḯ��Ʈ�� ����.)

	category* next_cate;						// ���� ī�װ��� �ּ�.
	category* prev_cate;


	

public:

	// ���� cate_Struct�� �ִ� �ֵ��ε� �̰͵��� static���� ���� �Ẹ��.
	//int size;
	static category* cate_head;
	static category* cate_tail;
	// ����ü

	static int cate_num;								// ī�װ� ��ü���� ������ �Ϸù�ȣ ����.

	
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

	// ================================================

	void add_to_cate(category* ptr_cate);

	void create_cate();									// �� ���� �Ű����� �ִ� ģ���ϰ� ���� �־� �� ��.

	bool cate_name_overlap(string imsi_name);
	void show_cate_list();
	category* search_cate();
	void remove_category();
	void show_category();
	void show_cate_todos(category* ptr_cate);
	// ���� ��
	
	// �ʿ��� �� �ָ�

	category* search_cate(string name);					// �̸��� ������ �ʿ��� ī�װ��� ã���ִ� �Լ�. ���� �Է� �� �ʿ�.

	// todo ��ü�� �Űܾ� �ϳ�??
	void sort_todo_to_cate(todo* ptr_todo, int n);

};


//typedef struct cate_struct {					// ī�װ����� ���Ḯ��Ʈ�� ù �κа� ������ �κ�, ī�װ��� ������ �����ϱ� ���� ����ü ����.
//	int size;
//	category* cate_head;
//	category* cate_tail;
//} Cate_Struct;