#pragma once

#include "todo.h"
#include <iostream>
#include <string>
using namespace std;


class category {

	int index;									// 카테고리들의 일련번호 ( 0: 미분류, 1: 중요로 미리 생성)
	string cate_name;

	todo* first_todo;							// 카테고리별 처음 할 일의 주소.(카테고리 연결리스트의 시작.)

	category* next_cate;						// 다음 카테고리의 주소.
	category* prev_cate;						// 이전 카테고리의 주소.

	// 처음 제출한 보고서에 없던 변수 추가.
	int todo_num;								// 카테고리가 가지고 있는 할 일들의 개수.

public:

	// 처음 제출한 보고서에서 cate_Struct 구조체에 있던 멤버들.
	// static으로 바꾸어 사용.
	static category* cate_head;										// 카테고리 연결리스트의 시작부분.
	static category* cate_tail;										// 카테고리 연결리스트의 끝 부분.

	static int cate_num;											// 카테고리 객체들이 공유할 일련번호 변수.


	category(string cate_name);										// 생성자
	category* create_cate(string cate_name);						// 카테고리 객체 동적 생성 함수.	
	void create_cate();												// 이름이 중복(매개변수로 이름을 안주면 이름 받는 과정 실행)

	void set_next_cate(category* p);								// 카테고리의 다음 주소를 입력받는 함수.
	void set_prev_cate(category* p);								// 카테고리의 이전 주소를 입력받는 함수.

	category* get_next_cate();										// 카테고리의 다음 주소를 반환하는 함수.
	category* get_prev_cate();										// 카테고리의 이전 주소를 반환하는 함수.

	int get_cate_index();											// 카테고리의 인덱스 번호(생성 순서)를 반환.
	string get_cate_name();											// 카테고리의 이름을 반환하는 함수.

	void set_first_todo(todo* p);									// 첫 번째 todo의 주소를 입력
	todo* get_first_todo();											// 첫 번째 todo의 주소를 반환

	int get_todo_num();												// todo_num의 값을 반환해주는 함수.
	void increase_todo_num();										// todo_num을 1 증가 시키는 함수.
	void decrease_todo_num();										// todo_num을 1 감소 시키는 함수.

	void increase_index();											// remove에서 필요. 카테고리들의 index를 1씩 감소시켜주는 함수.
	void add_to_cate(category* ptr_cate);							// 카테고리 연결리스트에 연결 함수.
	bool cate_name_overlap(string imsi_name);						// 카테고리 이름 중복 검사 함수.
	void show_cate_list();											// 현재 카테고리들의 목록 출력 함수.
	category* search_cate();										// 선택한 번호의 카테고리의 주소를 반환해주는 함수.
	void remove_category();											// 카테고리 삭제 함수.

	void show_category();											// 선택한 카테고리와 그에 연결된 할 일들을 출력 함수.
	void show_cate_todos(category* ptr_cate);						// 카테고리에 연결된 할 일들을 출력 함수.
	void sort_todo_to_cate(todo* ptr_todo, category* ptr_cate);		// 카테고리에 할 일을 추가할 때 마감일 순으로 정렬해서 추가하는 함수.

	void search_name_cate();										// 카테고리의 이름으로 검색하는 함수.
};