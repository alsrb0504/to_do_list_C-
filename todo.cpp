#include "category.h"



todo::todo(string title, string due_date, string detail)						// ������.
{
	this->title = title;
	this->due_date = due_date;
	this->detail = detail;
	next = NULL;
	prev = NULL;
}

todo* todo::create_todo(string title, string due_date, string detail)			// todo ��ü ���� �Լ�.
{
	todo* ptr_todo = new todo(title, due_date, detail);							// todo ��ü ���� ����.

	return ptr_todo;								
}

todo* todo::get_next_todo() {					// ���� �ּ� ��ȯ
	return next;
}

void todo::set_next_todo(todo* p) {				// ���� �ּ� �Է�.
	this->next = p;
}

string todo::get_due_data() {					// ������ ��ȯ
	return due_date;
}

todo* todo::get_prev_todo() {					// ���� �ּ� ��ȯ
	return prev;
}

void todo::set_prev_todo(todo* p) {				// ���� �ּ� �Է�.
	this->prev = p;
}

string todo::get_title() {						// ���� ��ȯ �Լ�.
	return title;
}

string todo::get_detail() {						// ���λ��� ��ȯ.
	return detail;
}