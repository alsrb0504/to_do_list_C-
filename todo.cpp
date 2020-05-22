#include "category.h"

todo* todo::head_todo = NULL;					// �� �ϵ� ��ü�� ���Ḯ��Ʈ�� ���� static ���� �ʱ�ȭ.
todo* todo::imsi_todo = NULL;					// �� �� ��ü �߰� ��, ó���ϱ� ������ ��� ���� static ���� �ʱ�ȭ.

// ���� �� �� ���ֵ� �ɤ� ��.

todo::todo(string title, string due_date, string detail)						// �⺻ ������.
{
	this->title = title;
	this->due_date = due_date;
	this->detail = detail;
	next = NULL;
	prev = NULL;
}

todo* todo::create_todo(string title, string due_date, string detail)
{
	todo* ptr_todo = new todo(title, due_date, detail);				// todo ��ü ���� ����.

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

void todo::set_prev_todo(todo* p) {					// ���� �ּ� �Է�.
	this->prev = p;
}

string todo::get_title() {
	return title;
}

string todo::get_detail() {
	return detail;
}



// ���� ��.



todo::~todo()
{
	cout << "�� ���� �����Ǿ����ϴ�." << endl;
}

void todo::setdetails(string details) {
	this->detail = detail;
}

void todo::add_todolist(todo* p) {											

	// ���� �ֱٿ� �߰��� �� �� ���� �;� �ϹǷ� �Է��� �� �������θ�.
	// 1. head_todo�� ����� ���  2. �ƴ� ���.  ����� ���Ḯ��Ʈ���� �Է��� ���� �������.
	
	if (head_todo == NULL) {			// 1. ó������ �߰��� �� ���� ���.
		head_todo = p;
	}
	else {								// 2, �ƴ� ���.
		p->next = head_todo;
		head_todo->prev = p;
		head_todo = p;
	}
}

void todo::remove_todo(todo* p) {

	// category���� �� �� ����.
}




void todo::get_todo_data() {

	cout << "�� ��: " << title << endl;
	cout << "	��������: " << due_date << endl;
	cout << "	���λ���: " << detail << endl;
}