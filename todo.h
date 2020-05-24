#pragma once

#include <iostream>
#include <string>
using namespace std;


class todo {
private:
	string title;
	string due_date;
	string detail;

	todo* next;								// todo ������ ���Ḯ��Ʈ�� ����.
	todo* prev;								// todo ������ ���Ḯ��Ʈ�� ����.

public:

	todo(string title, string due_date, string detail);
	todo* create_todo(string title, string due_date, string detail);	// �� �� ��ü ���� �Լ�.

	todo* get_next_todo();												// ���� �� ���� �ּ� ��ȯ.
	void set_next_todo(todo* p);										// ���� �� ���� �ּ� �Է�.

	todo* get_prev_todo();												// ���� �� ���� �ּ� ��ȯ.
	void set_prev_todo(todo* p);										// ���� �� ���� �ּ� �Է�.

	string get_title();													// �� ���� ���� ��ȯ.
	string get_due_data();												// �������� ��ȯ.
	string get_detail();												// ���λ��� ��ȯ.

};