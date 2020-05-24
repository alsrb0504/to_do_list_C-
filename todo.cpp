#include "category.h"



todo::todo(string title, string due_date, string detail)						// 생성자.
{
	this->title = title;
	this->due_date = due_date;
	this->detail = detail;
	next = NULL;
	prev = NULL;
}

todo* todo::create_todo(string title, string due_date, string detail)			// todo 객체 생성 함수.
{
	todo* ptr_todo = new todo(title, due_date, detail);							// todo 객체 동적 생성.

	return ptr_todo;								
}

todo* todo::get_next_todo() {					// 다음 주소 반환
	return next;
}

void todo::set_next_todo(todo* p) {				// 다음 주소 입력.
	this->next = p;
}

string todo::get_due_data() {					// 마감일 반환
	return due_date;
}

todo* todo::get_prev_todo() {					// 이전 주소 반환
	return prev;
}

void todo::set_prev_todo(todo* p) {				// 이전 주소 입력.
	this->prev = p;
}

string todo::get_title() {						// 제목 반환 함수.
	return title;
}

string todo::get_detail() {						// 세부사항 반환.
	return detail;
}