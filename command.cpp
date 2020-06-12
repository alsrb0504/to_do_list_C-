#define  _CRT_SECURE_NO_WARNINGS

#include "command.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;



category* cate;								// 카테고리 클래스 안의 함수들을 사용하기 위한 더미 포인터.

category* unclassified;						// 1. 미분류 카테고리 선언.
category* important;						// 2. 중요함 카테고리 선언.

void init_setting() {						// 초기 설정 ( 구조체 초기화 및  1.미분류		2.중요 category 생성).

	cate_struct.size = 0;									// cate_struct 구조체 초기화.
	cate_struct.cate_head = NULL;
	cate_struct.cate_tail = NULL;

	unclassified = unclassified->create_cate("미분류");		// 1. 미분류 카테고리 생성.
	add_to_cate(unclassified);

	important = important->create_cate("중요");				// 2. 중요함 카테고리 생성.
	add_to_cate(important);
	
	cout << "초기 설정: " << endl;
	cout << "1번 카테고리를 \"미분류\" 2번 카테고리를 \"중요\"로 설정" << endl << endl;
}



void show_important() {															// 중요한 일 카테고리(항상 2번 카테고리)를 출력하는 함수.

	cout << "★★★★★★★★★★★★★★★★★★★★★★★" << endl;
	cout << "\t(항상 2번째 카테고리를 가르킵니다.)" << endl << endl;
		
	category* p = search_cate(2);

	if (p == NULL) {													// 예외 처리.						
		cout << "\t중요함 카테고리가 없습니다." << endl;
	}
	
	cate->show_cate_todos(p);

	cout << "★★★★★★★★★★★★★★★★★★★★★★★" << endl << endl << endl;
}

void show_all() {																// 모든 카테고리와 할 일들을 출력하는 함수.
	category* p = cate_struct.cate_tail;

	if (p == NULL) {										// 예외 처리
		cout << "\t할 일이 없습니다." << endl << endl;
	}

	while (p != NULL) {
		cate->show_cate_todos(p);
		p = p->get_prev_cate();
	}
}

void search_todo() {															// 할 일을 찾는 함수.
	// 카테고리들의 목록을 출력.
	// 카테고리의 번호를 입력하면 그 카테고의 할 일들의 목록을 번호와 함께 출력.

	category* p = cate->select_cate();

	cate->show_cate_todos(p);
}

todo* remove_search_todo(category* p) {											// 지우기 위한 할 일을 찾는 함수.

	cate->show_cate_todos(p);

	// 일단 항상 양수만 입력 받음.
	int num;
	while (true) {
		cout << "\t선택할 todo의 번호 입력 " << endl;
		cout << "\t(비었으면 아무 숫자 입력) :";
		cin >> num;

		if (num <= 0) {
			cout << "\t잘못입력" << endl;
			continue;
		}
		break;
	}

	// todo들을 n만큼 순회하는 데 만약 todo 포인터가 null이 되면 못 찾고 종료.
	todo* ptr_todo = p->get_first_todo();
	int i = 1;
	while (ptr_todo != NULL && i < num) {					// num 만큼 todo들 순회. 
		i++;
		ptr_todo = ptr_todo->get_next_todo();
	}

	if (ptr_todo == NULL) {
		cout << "입력한 번호의 할 일이 없습니다." << endl;
		return NULL;
	}

	return ptr_todo;
}

void remove_todo() {															// 할 일을 지우는 함수.

	category* ptr_cate = cate->select_cate();					// 카테고리 목록 출력 및 필요한 카테고리의 주소 받음.

	if (ptr_cate == NULL) {
		cout << "\t제거 실패!!" << endl << endl;		// 예외 처리.
		return;
	}

	todo* p = remove_search_todo(ptr_cate);				// 지울 todo를 찾아 그 주소를 반환.

	if (p == NULL) {									// 예외 처리.
		cout << "\t제거 실패!!" << endl << endl;
		return;
	}
	
	todo* p_next = p->get_next_todo();					// 지울 할 일의 다음과 이전 주소.
	todo* p_prev = p->get_prev_todo();
	
	// 지우는 경우
	// 연결리스트의
	// 1. 유일한 경우.		2. 맨 앞인 경우.		3. 맨 뒤인 경우.		4. 중간에 있는 경우.

	if (p_next == NULL && p_prev == NULL) {								// 1. 유일한 경우.
		ptr_cate->set_first_todo(NULL);
	}
	else if (p_prev == NULL && ptr_cate->get_first_todo() == p) {		// 2. 맨 앞인 경우.
		// p_next->prev를 null로 그리고 
		p_next->set_prev_todo(NULL);
		ptr_cate->set_first_todo(p_next);
	}
	else if (p_next == NULL) {											// 3. 맨 뒤인 경우.
		p_prev->set_next_todo(NULL);
	}
	else {																// 4. 중간에 있는 경우.
		p_prev->set_next_todo(p_next);
		p_next->set_prev_todo(p_prev);
	}
	string title = p->get_title();
	delete(p);
	cout << "\t" << title << " 제거 성공" << endl << endl;
}

string set_todo_title() {														// 할 일의 제목을 입력받는 함수.(빈 칸은 제외).

	string title;

	// 할 일 입력.
	int first = 0;									// 처음만 입력버퍼 지우기를 실행하기 위한 변수.
	while (1) {

		cout << "	할 일을 적어주세요.(첫 글자 공백x): ";

		if (first == 0) {
			getchar();								// 입력버퍼 제거.
			first++;
		}
		getline(cin, title);

		if (title.empty() || title[0] == ' ') {
			cout << "\t입력이 없습니다.\n" << endl;
			continue;
		}
		break;
	}
	return title;									// 할 일의 제목 반환.
}

string set_todo_time() {														// 할 일의 시간을 입력받는 함수.

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
		
		if ((date[0] == '3' && date[1] > '1')|| (date[0] == '0' && date[1] == '0'))
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

string set_todo_detail() {																	// 세부사항 입력 함수.
	string detail;
	cout << "\t자세한 설명을 적어주세요.:";

	getchar();										// 입력 버피 지우기.
	getline(cin, detail);

	return detail;									// 세부사항 반환.
}

void create_todo() {																		// 할 일 생성 함수.
	
	cout << "\t1. 할 일 추가." << endl;

	string title = set_todo_title();
	string time = set_todo_time();
	string detail = set_todo_detail();

	todo* ptr_todo = NULL;
	ptr_todo = ptr_todo->create_todo(title, time, detail);				// 할 일 생성.

	if (ptr_todo == NULL) {												// 예외처리.
		cout << "\t할 일 추가 실패!!" << endl << endl;
	}

	// 현재 카테고리들의 목록을 출력.
	// 할 일이 들어갈 카테고리를 선택.
	
	int n;
	while (1) {
		
		show_cate_list();										// 현재 카테고리의 목록을 출력.
		cout << "\t할일을 추가할 카테고리의 번호를 입력해주세요.: ";
		cin >> n;

		if (cate_struct.size == 0) {
			cout << "\t카테고리 목록이 비었습니다. 카테고리를 먼저 만들어 주세요." << endl << endl;
			// 여기에 카테고리를 추가하는 함수를 실행.
			create_category();

			// 

			continue;
		}
		if (n <= 0 || n > cate_struct.size) {
			cout << "\t잘못 입력!!" << endl;
			continue;
		}
		break;
	}

	sort_todo_to_cate(ptr_todo, n);							// 생성된 todo 객체와 카테고리의 번호를 매개변수로 카테고리에 정렬되어 입력.
	cout << "\t할 일 추가 성공!!" << endl << endl;
}







void load() {																				// 파일 불러오기 함수.

	ifstream fp("to_do_list.txt");						// 읽기용 객체 생성.

	if (!(fp.is_open())) {								// 예외 처리.
		cout << "not found file. " << endl;
		return;
	}

	string s;

	while (fp) {
		getline(fp, s);

		if (s[0] == '@') {									// 카테고리 구분자.

			string imsi_name = s.substr(1, s.size());		// '@' 문자 제거.

			if (!(cate_name_overlap(imsi_name))) {			// 같은 이름의 카테고리 있는지 중복 검사. (있으면 건너뛰기).
				continue;
			}

			category* ptr_cate = NULL;
			ptr_cate = ptr_cate->create_cate(imsi_name);	// 카테고리 객체 생성 후 연결리스트에 추가.

			add_to_cate(ptr_cate);
		}
		else if (s[0] == '#') {								// 할 일 구분자.

			string imsi_todo = s.substr(1, s.size());		// '#' 문자 제거.
			load_add_todo(imsi_todo);						// 읽어온 할 일 추가 함수.
		}
	}
	cout << "\t불러오기 성공!!" << endl << endl;
	fp.close();
}

void load_add_todo(string imsi_todo) {											// load()에서 읽어온 할 일 추가 함수.

	string cate, title, month, date, detail;

	split(imsi_todo, cate);											 // split 함수로 주소를 받아 문장에서 필요한 것들 추출.
	split(imsi_todo, title);
	split(imsi_todo, month);
	split(imsi_todo, date);
	split(imsi_todo, detail);

	string time = month;
	time.append(date);

	category* ptr_cate = search_cate(cate);							// 읽어온 문장의 category를 찾음.

	if (ptr_cate == NULL) {											// 예외처리 null
		cout << "\t메모장에 잘못 적으셨습니다." << endl;
		return;
	}

	todo* ptr_todo = NULL;
	ptr_todo = ptr_todo->create_todo(title, time, detail);			// 할일 객체 생성.

	sort_todo_to_cate(ptr_todo, ptr_cate->get_cate_index());		// 카테고리에 연결.
}

void split(string& imsi_todo, string& s) {										// load()함수 할 일 문장에서 필요한 문장을 추출하는 함수.

	int length = imsi_todo.find("#");								// 구분자 "#";
	s = imsi_todo.substr(0, length);

	imsi_todo = imsi_todo.substr(length + 1, (imsi_todo.size()- length));
}

void save() {																	// 파일 저장 함수.

	ofstream fp("to_do_list.txt");

	if (!(fp.is_open())) {							// 예외 처리.
		cout << "not found file. " << endl;
		return;
	}

	category* ptr_cate = cate_struct.cate_tail;

	if (ptr_cate == NULL) {
		cout << "\t카테고리가 없습니다. 저장하기 실패!!" << endl;
		return;
	}

	while (ptr_cate != NULL) {
		string print_cate = "@";										// 파일에 카테고리 출력.
		print_cate.append(ptr_cate->get_cate_name());					// "@카테고리이름" 출력
		print_cate.append("\n");
		fp.write(print_cate.c_str(), print_cate.size());

		todo* ptr_todo = ptr_cate->get_first_todo();
		while (ptr_todo != NULL) {										// 파일에 카테고리의 할 일 출력.
			string print_todo = save_to_todo(ptr_todo, ptr_cate);		// 출력할 문장 생성 함수.
			fp.write(print_todo.c_str(), print_todo.size());			// "#카테고리명#제목#월#일#세부사항#" 으로 출력.

			ptr_todo = ptr_todo->get_next_todo();
		}

		ptr_cate = ptr_cate->get_prev_cate();
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