#include "category.h"

todo* todo::head_todo = NULL;					// 할 일들 자체의 연결리스트를 위한 static 변수 초기화.
todo* todo::imsi_todo = NULL;					// 할 일 객체 추가 후, 처리하기 전까지 담고 있을 static 변수 초기화.

// 위에 두 개 없애도 될ㄷ 듯.

todo::todo(string title, string due_date, string detail)						// 기본 생성자.
{
	this->title = title;
	this->due_date = due_date;
	this->detail = detail;
	next = NULL;
	prev = NULL;
}

todo* todo::create_todo(string title, string due_date, string detail)
{
	todo* ptr_todo = new todo(title, due_date, detail);				// todo 객체 동적 생성.

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

void todo::set_prev_todo(todo* p) {					// 이전 주소 입력.
	this->prev = p;
}

string todo::get_title() {
	return title;
}

string todo::get_detail() {
	return detail;
}



// 수정 전.



todo::~todo()
{
	cout << "할 일이 삭제되었습니다." << endl;
}

void todo::setdetails(string details) {
	this->detail = detail;
}

void todo::add_todolist(todo* p) {											

	// 가장 최근에 추가한 게 젤 위에 와야 하므로 입력은 한 방향으로만.
	// 1. head_todo가 비었을 경우  2. 아닐 경우.  양방향 연결리스트지만 입력은 들어온 순서대로.
	
	if (head_todo == NULL) {			// 1. 처음으로 추가한 할 일일 경우.
		head_todo = p;
	}
	else {								// 2, 아닐 경우.
		p->next = head_todo;
		head_todo->prev = p;
		head_todo = p;
	}
}

void todo::remove_todo(todo* p) {

	// category에서 할 일 제거.
}




void todo::get_todo_data() {

	cout << "할 일: " << title << endl;
	cout << "	마감일자: " << due_date << endl;
	cout << "	세부사항: " << detail << endl;
}