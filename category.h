#pragma once

#include "todo.h"

#include <iostream>
#include <string>
using namespace std;

typedef struct cate Cate_Struct;


class category {

	int index;									// 카테고리들의 일련번호 ( 0: 미분류, 1: 중요로 미리 생성)
	string cate_name;

	todo* first_todo;							// 카테고리별 처음 할 일의 주소.(카테고리 연결리스트의 시작.)

	category* next_cate;						// 다음 카테고리의 주소.
	category* prev_cate;

public:
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
	
	static int cate_num;								// 카테고리 객체들이 공유할 일련번호 변수.
};


typedef struct cate {					// 카테고리들의 연결리스트의 첫 부분과 마지막 부분, 카테고리의 개수를 저장하기 위한 구조체 선언.
	int size;
	category* cate_head;
	category* cate_tail;
} Cate_Struct;