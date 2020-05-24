#ifndef COMMAND_H
#define COMMAND_H

#include "category.h"
#include <iostream>
#include <string>
using namespace std;

// 초기 설정 및 메인 메뉴에서 보여지는 함수.
void init_setting();
void show_important();
void show_all();

// 파일 입출력 관련.
void load();
void save();
void load_add_todo(string imsi_todo);
void split(string& imsi_todo, string& s);
void load_add_todo(string imsi_todo);
void split(string& imsi_todo, string& s);
string save_to_todo(todo* p, category* ptr_cate);
void link(string& s, string part);

/*void cate_menu();*/											 // category 관련 함수들
void create_category();
void show_category();											// select_cate 실행 후, show_cate_todos 실행.
void remove_category();
category* select_cate();										// 필요한 카테고리의 주소를 받는 함수.
void add_to_cate(category* ptr_cate);
void show_cate_list();
category* search_cate(int n);									// 오버로딩( 이름과 번호 )
category* search_cate(string name);					
bool cate_name_overlap(string imsi_name);

/*void todo_menu();*/											// todo 관련 함수들
void create_todo();								
void sort_todo_to_cate(todo* ptr_todo, int n);					// 할 일을 카테고리에 분류하는 함수.
string set_todo_title();
string set_todo_time();
string set_todo_detail();
void show_cate_todos(category* ptr_cate);
todo* remove_search_todo(category* p);
void search_todo();
void remove_todo();


#endif