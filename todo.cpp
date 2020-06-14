#include "todo.h"
#include "category.h"
#include <iostream>


todo::todo(string title, string due_date, string detail) {					// 생성자.
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

void todo::create_todo() {																		// 할 일 생성 함수.

	category* p = NULL;			// 카테고리 함수들을 다루기 위한 객체 생성.

	if (p->cate_num == 0) {														// 예외처리 : 카테고리가 하나도 없다면 할 일을 만들 수 없음.
		cout << "카테고리가 비었습니다. 카테고리를 먼저 생성하세요." << endl << endl;
		cout << "==========================================================" << endl;
		
		return;
	}
	 
	cout << "\t1. 할 일 추가." << endl;

	rewind(stdin);														// 입력버퍼를 지우기 위해.

	string title = set_todo_title();									// 필요한 정보들(title, duedata, detail)을 받는 과정.
	string time = set_todo_time();
	string detail = set_todo_detail();

	todo* ptr_todo = NULL;
	ptr_todo = ptr_todo->create_todo(title, time, detail);				// 할 일 생성 객체 생성.

	if (ptr_todo == NULL) {												// 예외처리 : todo 객체 생성 실패.
		cout << "\t할 일 추가 실패!!" << endl << endl;
	}

	p->show_cate_list();												// 카테고리 목록들 출력

	while (true) {

		cout << "할 일을 추가할 카테코리의 번호를 입력해주세요.: ";
		p= p->search_cate();


		if (p == NULL) {												// 예외처리 : 번호 잘못 입력 시.
			cout << "다시 입력해주세요 " << endl;						// 다시 입력해달라 하고 제대로 된 값 입력받을 때까지 반복.
			continue;
		}
		break;
	}

	p->sort_todo_to_cate(ptr_todo, p);									// 생성된 todo 객체를 카테고리의 todo 연결리스트에 마감일 순으로 정렬.

	cout << "\t할 일 추가 성공!!" << endl << endl;
}

string todo::set_todo_title() {														// 할 일의 제목을 입력받는 함수.(빈 칸은 제외).

	string title;

	while (1) {

		cout << "	할 일을 적어주세요.(첫 글자 공백x): ";

		getline(cin, title);

		if (title.empty() || title[0] == ' ') {				
			cout << "\t입력이 없습니다.\n" << endl;
			continue;
		}
		break;
	}
	return title;									// 할 일의 제목 반환.
}

string todo::set_todo_time() {														// 할 일의 시간을 입력받는 함수.

	// 월과 일을 따로 받아서 검사.
	// 후에 string.append로 합쳐서 time에 입력.

	string time;
	while (1) {

		bool check = true;											// 제대로 된 month와 date의 값을 입력했는지 확인할 변수.

		string month;
		cout << "\t마감일의 달을 입력(01~12) : ";					// month 입력 (00 ~ 12);
		cin >> month;

		if (month.size() != 2)
			check = false;

		if (month[0] != '0' && month[0] != '1' && month[1] >= '0' && month[1] <= '9')
			check = false;

		if ((month[0] == '1' && month[1] > '2') || (month[0] == '0' && month[1] == '0'))
			check = false;

		if (check == false) {
			cout << "\t잘못 입력" << endl;	continue;
		}

		string date;
		cout << "\t마감일의 일을 입력(01~31) : ";					// date 입력 (00 ~ 31);
		cin >> date;

		if (date.size() != 2)
			check = false;

		if (!(date[0] >= '0' && date[0] <= '3') && !(date[1] >= '0' && date[1] <= '9'))
			check = false;

		if ((date[0] == '3' && date[1] > '1') || (date[0] == '0' && date[1] == '0'))
			check = false;

		if (check == false) {
			cout << "\t잘못 입력" << endl;	continue;
		}

		if (month == "02") {														// 2월 검사.
			if (date == "29" || date == "30" || date == "31") {
				cout << "\t2월은 28일까지 " << endl;	continue;
			}
		}

		if (month == "04" || month == "06" || month == "09" || month == "11") {		// 30일 검사.
			if (date == "31") {
				cout << "\t" << month << "는 30일까지 " << endl;	continue;
			}
		}

		time = month;
		time.append(date);
		return time;																// 마감 시간 반환.
	}
}

string todo::set_todo_detail() {																	// 세부사항 입력 함수.
	string detail;
	cout << "\t자세한 설명을 적어주세요.:";

	getchar();										// 입력 버피 지우기.
	getline(cin, detail);

	return detail;									// 세부사항 반환.
}

void todo::remove_todo() {															// 할 일을 지우는 함수.

	category* ptr_cate = NULL;						

	ptr_cate->show_cate_list();						// 카테고리 목록들 출력.


	cout << "지울 할 일이 들어있는 카테고리의 번호를 입력하세요. :";
	ptr_cate = ptr_cate->search_cate();

	if (ptr_cate == NULL) {
		cout << endl << "\t제거 실패(카테고리가 없습니다.)" << endl << endl;			// 예외 처리 : 카테고리가 없거나 입력한 번호가 잘못 되었을 경우.
		cout << "==========================================================" << endl;
		return;
	}

	ptr_cate->show_cate_todos(ptr_cate);												// 현재 카테고리에 연결된 할 일들의 목록을 출력.

	if (ptr_cate->get_todo_num() == 0) {												// 예외 처리 : 연결된 할 일의 개수가 0개이면 경고물 출력.
		cout << "\t제거 실패(todo 관련 에러)" << endl << endl;
		cout << "==========================================================" << endl;
		return;
	}

	int num;
	while (true) {
		cout << "\t제거할 todo의 번호 입력(취소: 0) :";
		cin >> num;

		if (num == 0) {															// 예외 처리 : 0 입력 시 제거 취소.
			return;
		}

		if (num < 0 || num > ptr_cate->get_todo_num()) {						// 예외 처리 : 잘못된 값 입력 시 제대로 된 값 받을 때까지 반복.
			cout << "\t잘못입력했습니다. 다시 입력해 주세요." << endl;
			continue;
		}
		break;
	}

	// todo들을 num 만큼 순회하여 지울 todo를 찾음.
	todo* ptr_todo = ptr_cate->get_first_todo();
	int i = 1;
	while (ptr_todo != NULL && i < num) {						// num 만큼 todo 연결리스트 순회. 
		i++;
		ptr_todo = ptr_todo->get_next_todo();
	}

	todo* p_next = ptr_todo->get_next_todo();					// 지울 할 일의 다음과 이전 주소.
	todo* p_prev = ptr_todo->get_prev_todo();

	// 지우는 경우 todo 연결리스트가
	// 1. 유일한 경우.		2. 맨 앞인 경우.		3. 맨 뒤인 경우.		4. 중간에 있는 경우.

	if (p_next == NULL && p_prev == NULL) {										// 1. 유일한 경우.
		ptr_cate->set_first_todo(NULL);
	}
	else if (p_prev == NULL && ptr_cate->get_first_todo() == ptr_todo) {		// 2. 맨 앞인 경우.
		p_next->set_prev_todo(NULL);
		ptr_cate->set_first_todo(p_next);
	}
	else if (p_next == NULL) {													// 3. 맨 뒤인 경우.
		p_prev->set_next_todo(NULL);
	}
	else {																		// 4. 중간에 있는 경우.
		p_prev->set_next_todo(p_next);
		p_next->set_prev_todo(p_prev);
	}
	string title = ptr_todo->get_title();
	delete(ptr_todo);
	ptr_cate->decrease_todo_num();												// 카테고리의 todo_num--;
	cout << "\t" << title << " 제거 성공" << endl << endl;
}


void todo::search_todo() {

	category* ptr_cate = ptr_cate->cate_head;

	if (ptr_cate == NULL) {																// 예외 처리 : 카테고리가 없는 경우.
		cout << "카테고리와 할 일이 없습니다. 카테고리부터 추가해주세요." << endl;
		return;
	}

	rewind(stdin);											// 미리 입력버퍼를 비워둠.

	string word;
	cout << "검색할 할 일에 포함된 단어를 입력해주세요. : ";
	getline(cin, word);

	cout << endl;

	int count = 0;											// 찾은 할 일의 개수를 출력해줄 변수.

	while (ptr_cate != NULL) {

		todo* ptr_todo = ptr_cate->get_first_todo();

		while (ptr_todo != NULL) {

			string title = ptr_todo->get_title();		// 비교할 문자열을 받음.
			
			if (title.find(word) != string::npos) {				// 만약 title에서 입력한 word를 찾았으면 string::npos를 반환 안함.

				cout << "\t" << ++count <<  ". 소속 카테고리: " << ptr_cate->get_cate_name() << endl;			// 찾은 개수 ++count
				cout << "\t\t제목: " << ptr_todo->get_title() << endl;
				cout << "\t\t마감 일자: " << ptr_todo->get_due_data() << endl;
				cout << "\t\t설명: " << ptr_todo->get_detail() << endl << endl;
			}
			ptr_todo = ptr_todo->get_next_todo();
		}
		// 할 일이 없거나 찾는 할 일이 없으면 다음 카테고리로 넘어감.
		ptr_cate = ptr_cate->get_next_cate();
	}

	cout << "\t찾은 할 일의 개수 :" << count << endl << endl;

	cout << "==========================================================" << endl << endl;
}
