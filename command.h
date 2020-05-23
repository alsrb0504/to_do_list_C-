#ifndef COMMAND_H
#define COMMAND_H

#include "category.h"
#include <iostream>
#include <string>
using namespace std;


void init_setting();
void show_important();
void show_all();

// ���� �����
void load_add_todo(string imsi_todo);
void split(string& imsi_todo, string& s);

/*void cate_menu();*/											 // category ���� �Լ���
void create_category();
void show_category();											// select_cate ���� ��, show_cate_todos ����.
void remove_category();
category* select_cate();										// �ʿ��� ī�װ��� �ּҸ� �޴� �Լ�.
void add_to_cate(category* ptr_cate);
void show_cate_list();
category* search_cate(int n);									// �����ε�( �̸��� ��ȣ )
category* search_cate(string name);					
bool cate_name_overlap(string imsi_name);

// ���� �����
void load_add_todo(string imsi_todo);
void split(string& imsi_todo, string& s);



/*void todo_menu();*/											// todo ���� �Լ���
void create_todo();								
void sort_todo_to_cate(todo* ptr_todo, int n);					// �� ���� ī�װ��� �з��ϴ� �Լ�.
string set_todo_title();
string set_todo_time();
string set_todo_detail();
void show_cate_todos(category* ptr_cate);
todo* remove_search_todo(category* p);
void search_todo();
void remove_todo();


void load();
//void save();


#endif
