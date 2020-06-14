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
	category* prev_cate;						// ���� ī�װ��� �ּ�.

	// ó�� ������ ������ ���� ���� �߰�.
	int todo_num;								// ī�װ��� ������ �ִ� �� �ϵ��� ����.

public:

	// ó�� ������ �������� cate_Struct ����ü�� �ִ� �����.
	// static���� �ٲپ� ���.
	static category* cate_head;										// ī�װ� ���Ḯ��Ʈ�� ���ۺκ�.
	static category* cate_tail;										// ī�װ� ���Ḯ��Ʈ�� �� �κ�.

	static int cate_num;											// ī�װ� ��ü���� ������ �Ϸù�ȣ ����.


	category(string cate_name);										// ������
	category* create_cate(string cate_name);						// ī�װ� ��ü ���� ���� �Լ�.	
	void create_cate();												// �̸��� �ߺ�(�Ű������� �̸��� ���ָ� �̸� �޴� ���� ����)

	void set_next_cate(category* p);								// ī�װ��� ���� �ּҸ� �Է¹޴� �Լ�.
	void set_prev_cate(category* p);								// ī�װ��� ���� �ּҸ� �Է¹޴� �Լ�.

	category* get_next_cate();										// ī�װ��� ���� �ּҸ� ��ȯ�ϴ� �Լ�.
	category* get_prev_cate();										// ī�װ��� ���� �ּҸ� ��ȯ�ϴ� �Լ�.

	int get_cate_index();											// ī�װ��� �ε��� ��ȣ(���� ����)�� ��ȯ.
	string get_cate_name();											// ī�װ��� �̸��� ��ȯ�ϴ� �Լ�.

	void set_first_todo(todo* p);									// ù ��° todo�� �ּҸ� �Է�
	todo* get_first_todo();											// ù ��° todo�� �ּҸ� ��ȯ

	int get_todo_num();												// todo_num�� ���� ��ȯ���ִ� �Լ�.
	void increase_todo_num();										// todo_num�� 1 ���� ��Ű�� �Լ�.
	void decrease_todo_num();										// todo_num�� 1 ���� ��Ű�� �Լ�.

	void increase_index();											// remove���� �ʿ�. ī�װ����� index�� 1�� ���ҽ����ִ� �Լ�.
	void add_to_cate(category* ptr_cate);							// ī�װ� ���Ḯ��Ʈ�� ���� �Լ�.
	bool cate_name_overlap(string imsi_name);						// ī�װ� �̸� �ߺ� �˻� �Լ�.
	void show_cate_list();											// ���� ī�װ����� ��� ��� �Լ�.
	category* search_cate();										// ������ ��ȣ�� ī�װ��� �ּҸ� ��ȯ���ִ� �Լ�.
	void remove_category();											// ī�װ� ���� �Լ�.

	void show_category();											// ������ ī�װ��� �׿� ����� �� �ϵ��� ��� �Լ�.
	void show_cate_todos(category* ptr_cate);						// ī�װ��� ����� �� �ϵ��� ��� �Լ�.
	void sort_todo_to_cate(todo* ptr_todo, category* ptr_cate);		// ī�װ��� �� ���� �߰��� �� ������ ������ �����ؼ� �߰��ϴ� �Լ�.

	void search_name_cate();										// ī�װ��� �̸����� �˻��ϴ� �Լ�.
};