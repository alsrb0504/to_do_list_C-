#ifndef TODO_H
#define TODO_H


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
	todo* create_todo(string title, string due_date, string detail);

	todo* get_next_todo();						// ���� �� ���� �ּ� ��ȯ
	void set_next_todo(todo* p);				// ���� �� ���� �ּ� �Է�.

	todo* get_prev_todo();
	void set_prev_todo(todo* p);				// ���� �� ���� �ּ� �Է�.

	string get_title();							// �� ���� ���� ��ȯ.
	string get_due_data();						// �������� ��ȯ.
	string get_detail();


	// ���� ��

	static todo* head_todo;					// �ܺο��� �����ϱ� ���� �׸��� todo���� �����ϱ� ����

	static todo* imsi_todo;					// �� ������ todo ��ü�� ��� �������� ������ static ����.
	
	
	~todo();


	void setdetails(string details);

	void add_todolist(todo* p);						// ���� ���Ḯ��Ʈ�� �� ���� �߰��ϴ� �Լ�.
	
	
	void get_todo_data();

	void remove_todo(todo* p);					// ī�װ� ���Ḯ��Ʈ���� �� ���� �����ϴ� �Լ�.

	void check_important(todo* p);				// �߿��� ǥ�ð� �ȵǾ� ������ �̸� �� ���� *** �߰�, �Ǿ� ������ ***����.

};


#endif
