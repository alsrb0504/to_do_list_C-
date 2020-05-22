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


	todo* next;								// todo 끼리의 연결리스트의 다음.
	todo* prev;								// todo 끼리의 연결리스트의 이전.


public:

	todo(string title, string due_date, string detail);
	todo* create_todo(string title, string due_date, string detail);

	todo* get_next_todo();						// 다음 할 일의 주소 반환
	void set_next_todo(todo* p);				// 다음 할 일의 주소 입력.

	todo* get_prev_todo();
	void set_prev_todo(todo* p);				// 이전 할 일의 주소 입력.

	string get_title();							// 할 일의 제목 반환.
	string get_due_data();						// 마감일자 반환.
	string get_detail();


	// 수정 전

	static todo* head_todo;					// 외부에서 참조하기 위해 그리고 todo끼리 공유하기 위한

	static todo* imsi_todo;					// 막 생성된 todo 객체를 어떻게 할지까지 보관할 static 변수.
	
	
	~todo();


	void setdetails(string details);

	void add_todolist(todo* p);						// 할일 연결리스트에 할 일을 추가하는 함수.
	
	
	void get_todo_data();

	void remove_todo(todo* p);					// 카테고리 연결리스트에서 할 일을 제거하는 함수.

	void check_important(todo* p);				// 중요함 표시가 안되어 있으면 이름 양 옆에 *** 추가, 되어 있으면 ***제거.

};


#endif
