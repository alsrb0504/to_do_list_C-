#include "command.h"
#include <iostream>
#include <fstream>

using namespace std;

void init_setting() {						// 초기 설정 ( 구조체 초기화 및  1.미분류		2.중요 category 생성).

	category* p = NULL;
	p = p->create_cate("미분류");			// 1번 미분류 카테고리 생성.
	p->add_to_cate(p);

	p = p->create_cate("중요");				// 2번 중요 카테고리 생성.
	p->add_to_cate(p);

	cout << "초기 설정: " << endl;
	cout << "1번 카테고리를 \"미분류\" 2번 카테고리를 \"중요\"로 설정" << endl << endl;
}


void show_all() {																// 모든 카테고리와 할 일들을 출력하는 함수.
	category* p = p->cate_head;

	if (p == NULL) {															// 예외 처리 : 카테고리가 하나도 없는 경우.
		cout << "\t할 일이 없습니다. 일정을 추가해주세요." << endl << endl;
		return;
	}

	while (p != NULL) {
		p->show_cate_todos(p);

		p = p->get_next_cate();
	}
}


void show_important() {															// 중요 카테고리(항상 2번 카테고리)를 출력하는 함수.
																				// 2번 카테고리가 "중요"가 아니더라도 현재 2번 카테고리를 출력.
	cout << "★★★★★★★★★★★★★★★★★★★★★★★" << endl;
	cout << "\t(항상 2번째 카테고리를 가르킵니다.)" << endl << endl;

	category* p = p->cate_head;

	if (p == NULL) {															// 예외 처리 : 카테고리가 하나도 없을 경우.
		cout << "현재 카테고리가 없습니다. 카테고리를 먼저 추가해주세요. " << endl << endl;
	}

	p = p->get_next_cate();												// 2번째 카테고리의 주소를 받음.

	if (p == NULL) {															// 예외 처리 : 2번 카테고리가 없는 경우.					
		cout << "\t중요함 카테고리가 없습니다." << endl << endl;
	}

	p->show_cate_todos(p);

	cout << "★★★★★★★★★★★★★★★★★★★★★★★" << endl << endl << endl;
}


void load() {																				// 파일 불러오기 함수.

	ifstream fp("to_do_list.txt");						// 읽기용 객체 생성.

	if (!(fp.is_open())) {								// 예외 처리 : 파일 열기 실패.
		cout << "not found file. " << endl;
		return;
	}

	string s;
	category* ptr_cate = NULL;							// 카테고리 함수들을 다루기 위해 선언.

	while (fp) {
		getline(fp, s);

		if (s[0] == '@') {									// 카테고리 구분자.

			string imsi_name = s.substr(1, s.size());					// '@' 문자 제거.

			if (!(ptr_cate->cate_name_overlap(imsi_name))) {			// 같은 이름의 카테고리 있는지 중복 검사. (있으면 건너뛰기).
				continue;
			}
			ptr_cate = ptr_cate->create_cate(imsi_name);				// 카테고리 객체 생성 후 연결리스트에 추가.

			ptr_cate->add_to_cate(ptr_cate);
		}
		else if (s[0] == '#') {								// 할 일 구분자.

			string imsi_todo = s.substr(1, s.size());					// '#' 문자 제거.
			load_add_todo(imsi_todo);									// 읽어온 할 일 추가 함수.
		}
	}
	cout << "\t불러오기 성공!!" << endl << endl;
	fp.close();
}


void load_add_todo(string imsi_todo) {											// load()에서 읽어온 할 일 문장(imsi_todo) 추가 함수.

	string cate, title, month, date, detail;

	split(imsi_todo, cate);									 // split 함수로 주소를 받아 문장에서 필요한 것들 추출.
	split(imsi_todo, title);
	split(imsi_todo, month);
	split(imsi_todo, date);
	split(imsi_todo, detail);

	int check = atoi(month.c_str());
	string time;
	category* ptr_cate = NULL;

	try {														// 읽어온 문장의 마감일과 카테고리 명 검사.
		if (check <= 0 || check > 12)							// 예외 : 월이 1~12월 아닌 경우.
			throw - 1;

		check = atoi(date.c_str());

		if (check <= 0 || check > 31)							// 예외 : 일이 1~31일이 아닌 경우.
			throw - 1;

		time = month;
		time.append(date);

		ptr_cate = search_cate(cate);							// 읽어온 문장의 category를 찾음.

		if (ptr_cate == NULL)									// 예외 : 카테고리명이 잘못된 경우.
			throw - 2;
	}
	catch (int x) {																				// 예외 처리 : 추가 실패한 문장을 알려줌.
		cout << "\t\"" << title << "\"이 있는 적혀있는 문장을 load하지 못했습니다." << endl;
		cout << "\tsave를 실행하면 이 문장을 지웁니다. " << endl;
		return;
	}

	todo* ptr_todo = NULL;
	ptr_todo = ptr_todo->create_todo(title, time, detail);		// 할일 객체 생성.

	ptr_cate->sort_todo_to_cate(ptr_todo, ptr_cate);			// 카테고리에 연결.
}


void split(string& imsi_todo, string& s) {										// load()함수 할 일 문장에서 필요한 문장을 추출하는 함수.

	int length = imsi_todo.find("#");								// 구분자 "#";
	s = imsi_todo.substr(0, length);

	imsi_todo = imsi_todo.substr(length + 1, (imsi_todo.size() - length));
}


category* search_cate(string name) {											// 카테고리 이름을 가지고 카테고리를 찾는 함수.

	category* p = p->cate_head;

	if (p == NULL) {									// 예외 처리 : 카테고리가 빈 경우.
		cout << "\t카테고리가 비었습니다." << endl;
		return NULL;
	}

	while (p != NULL) {
		if (name == p->get_cate_name()) {
			return p;
		}
		p = p->get_next_cate();
	}
	return NULL;										// 못 찾은 경우.(모든 경로 반환 경고 메시지 방지용).
}


void save() {																	// 파일 저장 함수.

	ofstream fp("to_do_list.txt");

	if (!(fp.is_open())) {												// 예외 처리 : 파일 열기를 실패한 경우.
		cout << "not found file. " << endl;
		return;
	}

	category* ptr_cate = ptr_cate->cate_head;

	if (ptr_cate == NULL) {												// 예외 처리 : 현재 카레고리가 비었을 경우(저장할 것이 없는 경우).
		cout << "\t카테고리가 없습니다. 저장하기 실패!!" << endl;
		return;
	}

	while (ptr_cate != NULL) {
		string print_cate = "@";										// 파일에 카테고리 출력.
		print_cate.append(ptr_cate->get_cate_name());					// "@카테고리이름" 출력 과정.
		print_cate.append("\n");
		fp.write(print_cate.c_str(), print_cate.size());

		todo* ptr_todo = ptr_cate->get_first_todo();
		while (ptr_todo != NULL) {										// 파일에 카테고리의 할 일 출력.
			string print_todo = save_to_todo(ptr_todo, ptr_cate);		// 출력할 문장 생성 함수.
			fp.write(print_todo.c_str(), print_todo.size());			// "#카테고리명#제목#월#일#세부사항#" 으로 출력.

			ptr_todo = ptr_todo->get_next_todo();
		}
		ptr_cate = ptr_cate->get_next_cate();
	}
	cout << "\t저장하기 성공!!" << endl << endl;
	fp.close();
}


string save_to_todo(todo* p, category* ptr_cate) {								// save()에서 출력할 할 일 문장 생성 함수.

	string print_todo = "#";							// 구분자로 쓸 문자

	string cate, title, time, month, date, detail;

	cate = ptr_cate->get_cate_name();
	title = p->get_title();
	time = p->get_due_data();
	detail = p->get_detail();

	month = time.substr(0, 2);
	date = time.substr(2, 4);

	// 연결하는 부분 함수 구현.
	link(print_todo, cate);								// 문장 연결 함수.
	link(print_todo, title);
	link(print_todo, month);
	link(print_todo, date);
	link(print_todo, detail);

	print_todo.append("\n");

	return print_todo;									// "#카테고리명#제목#월#일#세부사항#" 으로 수정한 문자열 반환.
}


void link(string& s, string part) {								// save()를 위한 문자열 편집 함수.
																// 현재 문자열 + 추가할 문자열 + #
	s.append(part);
	s.append("#");
}