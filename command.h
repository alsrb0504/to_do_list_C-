#pragma once;

#include "category.h"
#include "todo.h"

void init_setting();											// �ʱ� ������ �������ִ� �Լ�.
void show_all();												// ��� ī�װ��� �� ���� ����ϴ� �Լ�.
void show_important();											// �߿��� ī�װ�(2�� ī�װ�)�� ������ִ� �Լ�.

// ���� �ҷ����� �Լ�.
void load();									// "to_do_list.txt"���� ī�װ��� �� ���� �о���̴� �Լ�.
void split(string& imsi_todo, string& s);						// �� ���� �����ִ� ���忡�� �ʿ��� ������� �����ϴ� �Լ�.
void load_add_todo(string imsi_todo);							// load()�Լ����� ������ todo ������ ī�װ��� �߰����ִ� �Լ�.
category* search_cate(string name);								// load_add_todo()�Լ����� todo�� �߰��� ī�װ��� ã���ִ� �Լ�.

// ���� �����ϱ� �Լ�.
void save();									// "to_do_list.txt"�� ī�װ��� �� ���� �����ϴ� �Լ�.
string save_to_todo(todo* p, category* ptr_cate);				// save()�Լ����� todo�� ����� ����(#ī�װ�#�� ��....) ���� �Լ�.
void link(string& s, string part);								// ������ "#"�� �Է����ִ� �Լ�.