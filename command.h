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
void show_category();						// select_cate 실행 후, show_cate_todos 실행.
void remove_category();

category* select_cate();					// 필요한 카테고리의 주소를 받는 함수.

/*void cate_menu();*/							 // category 관련 함수들



/*void todo_menu();*/												// todo 관련 함수들

void create_todo();								
void sort_todo_to_cate(todo* ptr_todo, int n);					// 할 일을 카테고리에 분류하는 함수.
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
