#pragma once

#include <iostream>
#include <string>
using namespace std;


class todo {
private:
	string title;							// 할 일의 이름.
	string due_date;						// 마감일
	string detail;							// 세부사항.

	todo* next;								// todo 끼리의 연결리스트의 다음.
	todo* prev;								// todo 끼리의 연결리스트의 이전.

public:

	todo(string title, string due_date, string detail);
	todo* create_todo(string title, string due_date, string detail);	// 할 일 객체 생성 함수.
	void create_todo();													// 할 일 객체 추가할 때. 필요한 인자들을 받는 함수.

	todo* get_next_todo();												// 다음 할 일의 주소 반환.
	void set_next_todo(todo* p);										// 다음 할 일의 주소 입력.

	todo* get_prev_todo();												// 이전 할 일의 주소 반환.
	void set_prev_todo(todo* p);										// 이전 할 일의 주소 입력.

	string get_title();													// 할 일의 제목 반환.
	string get_due_data();												// 마감일자 반환.
	string get_detail();												// 세부사항 반환.

	string set_todo_title();											// 할 일의 제목을 입력받는 함수.
	string set_todo_time();												// 할 일의 마감일을 입력받는 함수.
	string set_todo_detail();											// 할 일의 세부사항을 입력받는 함수.

	void remove_todo();													// 할 일을 제거하는 함수.
	void search_todo();													// 할 일을 검색하는 함수.
};
