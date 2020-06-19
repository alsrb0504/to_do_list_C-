#pragma once;

#include "category.h"
#include "todo.h"

void init_setting();											// 초기 설정을 실행해주는 함수.
void show_all();												// 모든 카테고리와 할 일을 출력하는 함수.
void show_important();											// 중요함 카테고리(2번 카테고리)를 출력해주는 함수.

// 파일 불러오기 함수.
void load();									// "to_do_list.txt"에서 카테고리와 할 일을 읽어들이는 함수.
void split(string& imsi_todo, string& s);						// 할 일이 적혀있는 문장에서 필요한 문장들을 추출하는 함수.
void load_add_todo(string imsi_todo);							// load()함수에서 추출한 todo 문장을 카테고리에 추가해주는 함수.
category* search_cate(string name);								// load_add_todo()함수에서 todo를 추가할 카테고리를 찾아주는 함수.

// 파일 저장하기 함수.
void save();									// "to_do_list.txt"에 카테고리와 할 일을 저장하는 함수.
string save_to_todo(todo* p, category* ptr_cate);				// save()함수에서 todo를 출력할 문장(#카테고리#할 일....) 생성 함수.
void link(string& s, string part);								// 구분자 "#"을 입력해주는 함수.