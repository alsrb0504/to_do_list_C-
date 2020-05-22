#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <string>



//#include "linkedlist.h"
#include "category.h"

using namespace std;


void init_setting();
void show_important();

void show_all();
void add_to_cate(category* ptr_cate);

void show_cate_list();
category* search_cate(int n);

void menu();
void create_category();
void show_category();						// select_cate ���� ��, show_cate_todos ����.
void remove_category();

category* select_cate();					// �ʿ��� ī�װ��� �ּҸ� �޴� �Լ�.

/*void cate_menu();*/							 // category ���� �Լ���



/*void todo_menu();*/												// todo ���� �Լ���

void create_todo();								
void sort_todo_to_cate(todo* ptr_todo, int n);					// �� ���� ī�װ��� �з��ϴ� �Լ�.
string set_todo_title();
string set_todo_time();
string set_todo_detail();
void show_cate_todos(category* ptr_cate);

todo* remove_search_todo(category* p);


void search_todo();

void remove_todo();



//
//void show_cate_todo();




//void load();
//void save();


#endif
