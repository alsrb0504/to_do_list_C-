#define  _CRT_SECURE_NO_WARNINGS

#include "command.h"
#include <iostream>
#include <string>

//#include <fstream>
using namespace std;

#define BUFFER_SIZE 100

Cate_Struct cate_struct;						// 카테고리 연결리스트의 head, tail, 카테고리의 수를 저장하기 위한 구조체 변수 선언.	

category* unclassified;						// 0. 미분류 카테고리 선언.
category* important;						// 1. 중요함 카테고리 선언.

void init_setting() {

	cate_struct.size = 0;										// 
	cate_struct.cate_head = NULL;
	cate_struct.cate_tail = NULL;

	unclassified = unclassified->create_cate("미분류");		// 0. 미분류 카테고리 생성.
	add_to_cate(unclassified);

	important = important->create_cate("중요");				// 1. 중요함 카테고리 생성.
	add_to_cate(important);
	
	cout << "초기 설정: " << endl;
	cout << "1번 카테고리를 \"미분류\" 2번 카테고리를 \"중요\"로 설정" << endl << endl;
}

void show_important() {

	cout << "★★★★★★★★★★★★★★★★★★★★★★★" << endl;
	cout << "\t(항상 2번째 카테고리를 가르킵니다.)" << endl << endl;
		
	category* p = search_cate(2);

	if (p == NULL) {													// 예외 처리.						
		cout << "\t중요함 카테고리가 없습니다." << endl;
	}

	/*cout << "\t\t" << p->get_cate_name() << endl;*/
	
	show_cate_todos(p);

	cout << "★★★★★★★★★★★★★★★★★★★★★★★" << endl << endl << endl;
}

void show_all() {
	category* p = cate_struct.cate_tail;

	if (p == NULL) {										// 예외 처리
		cout << "\t할 일이 없습니다." << endl << endl;
	}

	while (p != NULL) {
		show_cate_todos(p);
		p = p->get_prev_cate();
	}
}


void search_todo() {
	// 카테고리들의 목록을 띄어주고 어디에 있는지 물어본다.
	// 카테고리의 번호를 입력하면 그 카테고의 할 일들의 목록을 번호와 함께 띄어준다.
	// 번호를 입력하면 int num을 이용해서 그냥 for문 돌려 찾아 리턴해 준다.

	// 근데 여기서 만약 할 일이 하나도 없거나 카테고리들도 아무것도 없다면 경고메시지 출력 후 초기화면으로 가는게 좋을 듯.

	category* p = select_cate();			// 요걸로 카테고리 목록 출력 및 필요한 카테고리의 주소 받음.

	show_cate_todos(p);

}

todo* remove_search_todo(category* p) {
	//category* p = select_cate();			// 요걸로 카테고리 목록 출력 및 필요한 카테고리의 주소 받음.

	show_cate_todos(p);

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

void remove_todo() {

	category* ptr_cate = select_cate();					// 요걸로 카테고리 목록 출력 및 필요한 카테고리의 주소 받음.

	todo* p = remove_search_todo(ptr_cate);				// 요걸 통해서 지울 todo를 찾음.

	if (p == NULL) {							// 예외 처리.
		cout << "제거 실패!!" << endl;
		return;
	}
	
	todo* p_next = p->get_next_todo();					// 지울 할 일의 다음과 이전 주소.
	todo* p_prev = p->get_prev_todo();
	
	// 지우는 경우
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
	cout << "\t" << title << " 제거 성공" << endl;
}

string set_todo_title() {

	string title;

	// 할 일 입력.
	int first = 0;									// 처음만 입력버퍼를 실행하기 위한 변수.
	while (1) {

		cout << "	할 일을 적어주세요.(첫 글자 공백x): ";

		if (first == 0) {
			getchar();
			first++;
		}
		getline(cin, title);

		if (title.empty() || title[0] == ' ') {
			cout << "\t입력이 없습니다.\n" << endl;
			continue;
		}

		break;
	}

	return title;

}

string set_todo_time() {

	// 월과 일을 따로 받아서 검사하고 string time 배열에 append로 합치자.

	string time;
	// 시간 입력 
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
		return time;
	}
}

string set_todo_detail() {
	string detail;
	cout << "\t자세한 설명을 적어주세요.:";

	getchar();										// 입력 버피 지워주자.
	getline(cin, detail);

	return detail;
}

void create_todo() {
	
	cout << "\t1. 할 일 추가." << endl;

	string title = set_todo_title();
	string time = set_todo_time();
	string detail = set_todo_detail();

	todo* ptr_todo = NULL;
	ptr_todo = ptr_todo->create_todo(title, time, detail);

	if (ptr_todo == NULL) {												// 예외처리.
		cout << "\t할 일 추가 실패!!" << endl << endl;
	}

	show_cate_list();								// 현재 카테고리의 목록을 보여준다.
	
	int n;
	while (1) {
		
		cout << "\t할일을 추가할 카테고리의 번호를 입력해주세요.: ";
		cin >> n;

		if (cate_struct.size == 0) {
			cout << "\t카테고리 목록이 비었습니다. 카테고리를 먼저 만들어 주세요." << endl << endl;
		}
		if (n <= 0 || n > cate_struct.size) {
			cout << "\t잘못 입력!!" << endl;
			continue;
		}
		break;
	}

	sort_todo_to_cate(ptr_todo, n);							// 생성된 todo 객체와 카테고리의 번호를 매개변수로 카테고리에 정렬되어 들어간다.
}

void sort_todo_to_cate(todo* ptr_todo, int n) {

	category* ptr_cate = search_cate(n);							// 카테고리를 찾아줌. 이때 n은 검사해서 들어왔으므로 따로 검사 x.

	// 이제 이 할 일을 카테고리에 연결시켜줘야 함.
	// 날짜 순서대로 정렬할 건데.
	// 1. 비었을 때,	2. 맨 앞에 올 때,	3. 맨 뒤에 올 때,	중간에 삽입될 때.

	todo* p = ptr_cate->get_first_todo();
	todo* q = NULL;
	// 들어갈 위치를 먼저 찾아줘야 겠지..?
	


	while (p != NULL) {
		// 마감일을 비교해서

		if (ptr_todo->get_due_data() < p->get_due_data()) {					// 문자열인데 string이라 비교 되겠지..?
			break;
		}
		q = p;
		p = p->get_next_todo();
	}


	if (p == NULL && ptr_cate->get_first_todo() == NULL) {				// 1. 비었을 때.
		ptr_cate->set_first_todo(ptr_todo);
	}
	else if (p == ptr_cate->get_first_todo()) {							// 2. 처음에 들어가야 함.
		
		// p의 이전 주소가 ptr_todo
		// ptr_todo의 다음 주소가 p
		// first_todo가 ptr_todo
		p->set_prev_todo(ptr_todo);
		ptr_todo->set_next_todo(p);
		ptr_cate->set_first_todo(ptr_todo);
	}
	else if (p == NULL) {												// 3. 맨 뒤.
		ptr_todo->set_prev_todo(q);
		q->set_next_todo(ptr_todo);
	}
	else {																// 4. 중간.
		ptr_todo->set_next_todo(p);
		ptr_todo->set_prev_todo(q);
		p->set_prev_todo(ptr_todo);
		q->set_next_todo(ptr_todo);
	}
}



// 수정 덜 끝남.						// 카테고리들 



void remove_category() {											// 카테고리 메뉴 3번 카테고리 지우기.

	show_cate_list();

	int n;
	cout << "\t지우고 싶은 카테고리의 번호를 입력: ";
	cin >> n;

	// 카테고리의 연결리스트들을 순회하며 입력된 번호의 카테고리를 찾아 그 주소를 받는다.
	// 그 카테고리와 연결된 todo들을 먼저 delete 해준다.
	// 그 후 다 지워진 걸 확인한 다음. category를 지우고 연결리스트들을 다시 연결해주고 그 이후의 연결리스트들의 번호를 1씩 감소시켜준다.

	category* ptr_cate = search_cate(n);

	if (ptr_cate == NULL) {												// 예외처리 찾지 못햇을 경우.
		cout << "\t입력한 번호의 카테고리가 없습니다." << endl;
		cout << "==========================================================" << endl;
		return;
	}

	// todo가 없으면 바로 delete 있으면 하나씩 순회하며 delete 후 카테고리 delete.
	
	todo* ptr_todo = ptr_cate->get_first_todo();	
	
	while (ptr_todo != NULL) {
		todo* q = ptr_todo;
		ptr_todo = ptr_todo->get_next_todo();	
		delete(q);
	}
	// 왜 하나 삭제하고 그냥 끝나버릴까??
	// ptr_todo는 분명 다음 것을 가르키고 잇었는데....


	// cate delete 하는데 
	// 카테고리 연결리스트가
	// 1. 비었다.		2.  유일한 카테고리.		3. 맨 앞(근데 0,1은 안 지울 것임.)	4. 맨 뒤		5. 중간		
	
	if (cate_struct.cate_head == NULL && cate_struct.size == 0) {			// 빈 경우.

		cout << "\t카테고리가 이미 비었습니다." << endl << endl;
		return;
	}
	else if (ptr_cate == cate_struct.cate_head && ptr_cate == cate_struct.cate_tail) {			// 유일한 1개

		cate_struct.cate_head = NULL;
		cate_struct.cate_tail = NULL;
	}
	else if (ptr_cate == cate_struct.cate_head) {							// 처음
		// 다음 ptr_cate의 다음 카테고리의 이전 주소를 NULL로 초기화.		cate_head가 다음 카테고리를 가르키개.
		
		category* q = ptr_cate->get_next_cate();
		q->set_prev_cate(NULL);
		cate_struct.cate_head = q;
	}
	else if (ptr_cate == cate_struct.cate_tail) {							// 마지막
		
		category* q = ptr_cate->get_prev_cate();
		q->set_next_cate(NULL);
		cate_struct.cate_tail = q;
	}
	else {																	// 중간

		category* next_p = ptr_cate->get_next_cate();	
		category* prev_p = ptr_cate->get_prev_cate();

		next_p->set_prev_cate(prev_p);
		prev_p->set_next_cate(next_p);
	}
	
	// 지울 카테고리의 이전 카테고리들의 index를 1씩 감소시켜 준다. ( 늦게 생성될 수록 index 번호가 높기 때문에.)
	category* prev_p = ptr_cate->get_prev_cate();

	while (prev_p != NULL) {				// 중간이거나 맨 앞일 때만 실행.

		prev_p->increase_index();									// 카테고리들의 자체 index를 1씩 감소 시켜주는 함수.
		prev_p = prev_p->get_prev_cate();
	}

	string imsi = ptr_cate->get_cate_name();

	cate_struct.size--;
	delete(ptr_cate);
	cout << "\t" << imsi << " 카테고리 제거 성공" << endl << endl;
	cout << "==========================================================" << endl;
}


void show_category() {							// 카테고리 메뉴 2번 카테고리 이름과 그에 연결된 todo들 보기.			
												// 나중엔 특정 한 카테고리 검색하고 그 카테고리의 할 일들 쭉 나열하는 것으로 바꿀 것.

	// 카테고리 목록의 이름을 먼저 보여준다.
	// 그 후에 카테고리의 번호를 입력하게 한다.

	// 카테고리의 연결리스트들을 순회하며 입력된 번호의 카테고리를 찾는다. (함수로 구현해야 함.)

	// 그러면 카테고리의 이름과 그와 연결된 todo들을 보여준다.

	category* p = select_cate();

	show_cate_todos(p);

}

category* select_cate() {

	show_cate_list();

	int n;
	cout << "\t다룰 카테고리의 번호를 입력: ";
	cin >> n;

	category* p = search_cate(n);

	if (p == NULL) {												// 예외처리 찾지 못햇을 경우.
		cout << "\t입력한 번호의 카테고리가 없습니다." << endl << endl;
		cout << "==========================================================" << endl;
		return NULL;
	}

	return p;
}

void show_cate_todos(category* ptr_cate) {

	if (ptr_cate== NULL) {
		return;
	}

	todo* ptr_todo = ptr_cate->get_first_todo();

	// todo들의 목록 출력.											// todo 관련 수정할 때 get_todo 할 함수 추가.
	cout << "\t" << ptr_cate->get_cate_name() << endl;

	cout << "==========================================================" << endl;
	
	if (ptr_todo == NULL)
		cout << "\t카테고리의 할 일이 비었습니다." << endl << endl;

	int i = 1;					// 할 일들의 번호를 옆에 출력.(나중에 검색하기 위해.)

	while (ptr_todo != NULL) {
		cout << "\t" << i++ << ". 제목 : " << ptr_todo->get_title() << endl;						// 나중에 마감일자와 세부사항도 볼수 있게.
		cout << "\t  마감 일자: " << ptr_todo->get_due_data() << endl;
		cout << "\t  설명: " << ptr_todo->get_detail() << endl;

		ptr_todo = ptr_todo->get_next_todo();
	}
	cout << endl;
	cout << "==========================================================" << endl;

}

category* search_cate(int n) {

	category* p = cate_struct.cate_head;

	while (p != NULL && n > 0 && n <= cate_struct.size) {
		
		if (p->get_cate_index() == n) {							// 카테고리의 일련번호와 입력받은 n이 같으면 그 카레고리의 주소 리턴.
			return p;
		}
		p = p->get_next_cate();
	}
	
	return NULL;						// 못 찾았으면 NULL 값 반환.
}

void show_cate_list() {											// 카테고리 메뉴 6번 카테고리 목록 보기.

	category* p = cate_struct.cate_tail;						// 나중에 생성된 것부터 보기 위해 tail을 시작점으로.
	
	cout << "카테고리 목록" << endl;
	int i = 1;

	while (p != NULL) {
		cout << "\t" << i << ". " << p->get_cate_name() << endl;
		p = p->get_prev_cate();
		i++;
	}
	cout << endl;
}

void create_category() {										// 카테고리 생성 함수.

	string name;

	while (1) {													// 이 안에서 이름 중복 검사 부분 추가.

		cout << "생성할 카테고리의 이름을 입력해주세요.: ";
		cin >> name;

		break;

		//	// 기존의 카테고리에서 같은 이름 있는지 검색.
		//	// null이 아닌 값 반환시 중복있는 거임.
		//	category* overlap = search_cate(name);									// 요거 수정 필요.

		//	if (overlap == NULL)
		//		break;
		//	else {
		//		cout << "중복된 이름의 카테고리가 있습니다. 이름을 다시 입력해주세요." << endl;
		//	}

		//}

		//category 객체를 하나 만들어서 접근해야 하는데, 어떻게 만들어야 하나.
	}

	category* ptr_cate = NULL;
	ptr_cate = ptr_cate->create_cate(name);					// 카테고리 객체 하나 생성.

	add_to_cate(ptr_cate);
	
}



void add_to_cate(category* ptr_cate) {				// cate 구조체의 head와 tail에 생성된 category들을 연결시켜주는 함수.

	// 생성된 category 객체를 받아서 연결리스트에 추가해야 하는데.
	// 경우의 수
	// 1. 빈 리스트(처음 세팅 때 필요).	2. 비지 않은 경우.				//  나중에 빈 리스트인지 검사 하는 함수 구현해서 바꿔줄 것.

	if (cate_struct.size == 0 && cate_struct.cate_head == NULL) {

		cate_struct.cate_head = ptr_cate;
		cate_struct.cate_tail = ptr_cate;
	}
	else {
		// ptr_cate의 다음 주소를 입력하고, 
		// 그 다음주소는 이전 주소로 ptr_cate를 받는다.
		// cate_struct.head가 ptr_cate를 가르킨다.

		ptr_cate->set_next_cate(cate_struct.cate_head);
		cate_struct.cate_head->set_prev_cate(ptr_cate);
		cate_struct.cate_head = ptr_cate;
	}

	cate_struct.size++;
}

void menu() {												 // 4. all list 부분 구현해야 함.
	cout << "\t\tTo_Do_List_Program" << endl;
	cout << "==========================================================" << endl;
	cout << "\t\t명령어 목록: \n\t\t1. 중요한 일 보기	\n\t\t2. category\n\t\t3. todo\n\t\t4. all list\n\t\t10. exit\n" << endl;
	cout << "==========================================================" << endl;

}

// 수정 전.															==========================




//void add_todo_to_cate() {
//	char ch;
//	while (1) {
//		cout << "추가한 할 일을 카테고리에 분류하시겠습니다?(y/n):";
//		cin >> ch;
//
//		if (ch == 'n') {
//			cout << "카테고리가 아닌 todo들 자체의 연결리스트에 분류했습니다." << endl;
//			break;
//		}
//		else if (ch == 'y') {
//			// 카테고리가 비었는지부터 확인.
//			// 비었으면 todo들 자체 알리기.
//			// 카테고리 있으면 카테고리명 입력받고 찾아서 입력하기.
//			bool empty = category::head_cate->is_empty_cate();				// 카테고리가 비었는지 확인.
//			if (empty == true) {
//				cout << "카테고리가 비었습니다. todo들 자체의 연결리스트에 분류했습니다." << endl;
//				break;
//			}
//			
//			while (1) {											// 제대로 된 카테고리들의 이름을 입력할 때까지 반복.
//				show_category();						// 현재 카테고리들의 이름을 보여줌.
//
//				string cate_name;
//				cout << "분류할 카테고리의 이름을 입력하세요.:";
//				cin >> cate_name;
//
//				category* ptr_cate = search_cate(cate_name);
//
//				if (ptr_cate == NULL) {
//					cout << "그런 이름의 카테고리가 없습니다." << endl;
//					continue;
//				}
//
//				ptr_cate->add_todo_cate(todo::imsi_todo);					// 찾은 카테고리를 통해 todo를 연결.
//				break;
//			}
//
//		}
//		else {
//			cout << "잘못 입력했습니다. 다시 입력하세요. " << endl;
//			continue;
//		}
//		break;
//	}
//}



//void show_cate_todo() {
//	
//	string name;
//	cout << "할 일의 목록을 볼 카테고리의 이름을 입력해주세요.:";
//	cin >> name;
//
//	category* ptr_cate = search_cate(name);
//
//	if (ptr_cate == NULL) {
//		cout << "입력한 이름의 카테고리가 없습니다." << endl;
//		cout << "category 메뉴의 처음으로 돌아갑니다." << endl;
//		return;
//	}
//
//	show_cate_todos(ptr_cate);
//}

//void show_cate_todos(category* ptr_cate) {
//
//	todo* p = ptr_cate->getFirsttodo();				// 이 카테고리의 첫 번째 할 일을 반환하는 함수.
//	todo* q = NULL;
//
//	if (p == NULL) {
//		cout << "이 카테고리에 할 일이 없습니다." << endl;
//		return;
//	}
//
//	while (p != NULL) {
//		
//		p->get_todo_data();
//
//		q = p;
//		p = p->next_cate_todo;
//	}
//
//}







//void load() {												// 파일 열기 함수.
//	
//	FILE *fp = fopen("to_do_list.txt", "r");
//
//	if (fp == NULL) {
//		cout << "파일 열기 실패." << endl;					// 예외 처리.
//		return;
//	}
//
//	char sen[BUFFER_SIZE];
//	while (fgets(sen, BUFFER_SIZE, fp)) {
//		
//
//		cout << sen;
//
//		if (feof(fp))
//			break;
//	}
//	cout << endl;
//	
//	fclose(fp);
//
//}
//
//void save() {
//	
//	FILE* fp = fopen("to_do_list.txt", "r");
//	FILE* fp2 = fopen("copy.txt", "w");
//
//	char sen[BUFFER_SIZE];
//	while (fgets(sen, BUFFER_SIZE, fp)) {
//		cout << sen;
//
//		fprintf(fp2, "%s", sen);
//
//		if (feof(fp))
//			break;
//	}
//	cout << endl;
//
//	
//	fclose(fp);
//	fclose(fp2);
//}
