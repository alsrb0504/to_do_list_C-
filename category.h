#pragma once

#include "todo.h"

#include <iostream>
#include <string>
using namespace std;

typedef struct cate_struct Cate_struct;		
//extern Cate_Struct cate_struct;					// 카테고리 연결리스트의 head, tail, 카테고리의 수를 저장하기 위한 구조체 변수 선언.

// 문제점 : category.h와 todo.h가 교차로 인클루드? 안하던데??

class category {

	int index;									// 카테고리들의 일련번호 ( 0: 미분류, 1: 중요로 미리 생성)
	string cate_name;

	todo* first_todo;							// 카테고리별 처음 할 일의 주소.(카테고리 연결리스트의 시작.)

	category* next_cate;						// 다음 카테고리의 주소.
	category* prev_cate;


	

public:

	// 원래 cate_Struct에 있던 애들인데 이것들을 static으로 만들어서 써보자.
	//int size;
	static category* cate_head;
	static category* cate_tail;
	// 구조체

	static int cate_num;								// 카테고리 객체들이 공유할 일련번호 변수.

	
	category(string cate_name);							// 생성자
	category* create_cate(string cate_name);			// 카테고리 객체 동적 생성 함수.	

	void set_next_cate(category* p);					// 카테고리의 다음 주소를 입력받는 함수.
	void set_prev_cate(category* p);					// 카테고리의 이전 주소를 입력받는 함수.

	category* get_next_cate();							// 카테고리의 다음 주소를 반환하는 함수.
	category* get_prev_cate();							// 카테고리의 이전 주소를 반환하는 함수.

	int get_cate_index();								// 카테고리의 인덱스 번호(생성 순서)를 반환.
	string get_cate_name();								// 카테고리의 이름을 반환하는 함수.

	void set_first_todo(todo* p);						// 첫 번째 todo의 주소를 입력
	todo* get_first_todo();								// 첫 번째 todo의 주소를 반환

	void increase_index();								// remove에서 필요. 카테고리들의 index를 1씩 감소시켜주는 함수.

	// ================================================

	void add_to_cate(category* ptr_cate);

	void create_cate();									// 저 위에 매개변수 있는 친구하고 같이 둬야 할 듯.

	bool cate_name_overlap(string imsi_name);
	void show_cate_list();
	category* search_cate();
	void remove_category();
	void show_category();
	void show_cate_todos(category* ptr_cate);
	// 수정 전
	
	// 필요한 지 애매

	category* search_cate(string name);					// 이름을 가지고 필요한 카테고리를 찾아주는 함수. 파일 입력 시 필요.

	// todo 객체로 옮겨야 하나??
	void sort_todo_to_cate(todo* ptr_todo, int n);

};


//typedef struct cate_struct {					// 카테고리들의 연결리스트의 첫 부분과 마지막 부분, 카테고리의 개수를 저장하기 위한 구조체 선언.
//	int size;
//	category* cate_head;
//	category* cate_tail;
//} Cate_Struct;