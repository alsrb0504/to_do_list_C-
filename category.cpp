#include "category.h"

// static 멤버들 초기화.
int category::cate_num = 0;
category* category::cate_head = NULL;
category* category::cate_tail = NULL;


category::category(string cate_name) {					// 생성자.
	this->cate_name = cate_name;
	this->index = ++cate_num;
	this->first_todo = NULL;
	this->next_cate = NULL;
	this->prev_cate = NULL;
	this->todo_num = 0;
}

category* category::create_cate(string cate_name) {

	category* ptr_cate = new category(cate_name);		// 이름과 순서만 초기화된 카테고리 객체 생성.

	return ptr_cate;
}

void category::set_next_cate(category* p) {				// 다음 category의 주소를 받는 함수.

	this->next_cate = p;
}

void category::set_prev_cate(category* p) {				// 이전 category의 주소를 받는 함수.

	this->prev_cate = p;
}

category* category::get_prev_cate() {					// 이전 category의 주소 반환.
	return prev_cate;
}

int category::get_cate_index() {						// category의 번호(index)를 반환.
	return index;
}

void category::set_first_todo(todo* p) {				// 이 카테고리의 첫 번째 할 일의 주소 입력.
	this->first_todo = p;
}

todo* category::get_first_todo() {						// 이 카테고리의 첫 번째 할 일의 주소 반환.
	return first_todo;
}

void category::increase_index() {						// category의 번호(index) 1 감소.
	this->index--;
}

category* category::get_next_cate() {					// 다음 category의 주소 반환.
	return next_cate;
}

string category::get_cate_name() {						// category의 이름 반환.
	return cate_name;
}


void category::add_to_cate(category* ptr_cate) {									// cate 구조체의 head와 tail에 생성된 category들을 연결시켜주는 함수.

	if (ptr_cate == NULL) {												// 예외 처리.
		cout << "전달된 category 객체가 없습니다." << endl;
		return;
	}

	// 생성된 category 객체를 받아서 연결리스트에 추가할 때.
	// 연결리스트가
	// 1. 빈 리스트(처음 세팅 때 필요).	2. 빈 연결리스트가 아닌 경우.			

	if (cate_num == 1 && cate_head == NULL) {							// 1. 연결리스트가 빈 경우.	 // (생성자에서 cate_num을 +1 해주기 때문에 cate_num == 1)

		cate_head = ptr_cate;
		cate_tail = ptr_cate;
	}
	else {																// 2. 빈 연결리스트가 아닌 경우.																// (끝부분에 새로운 카테고리 추가).
		ptr_cate->set_prev_cate(category::cate_tail);					// (끝부분에 새로운 카테고리 추가).
		cate_tail->set_next_cate(ptr_cate);
		cate_tail = ptr_cate;
	}
}

void category::create_cate() {															// 카테고리 생성 함수(이름 입력 받는 과정 포함).

	string name;

	rewind(stdin);

	while (1) {																			// 이름 중복 검사 부분.

		cout << endl << "생성할 카테고리의 이름을 입력해주세요.: ";									
		getline(cin, name);

		if (!(cate_name_overlap(name))) {												// 이름 중복 검사 해주는 함수 호출.
			cout << "\t중복된 카테고리가 존재. 카테고리 생성 실패." << endl << endl;
			return;
		}
		break;
	}

	category* ptr_cate = NULL;
	ptr_cate = ptr_cate->create_cate(name);						// 카테고리 객체 생성.

	add_to_cate(ptr_cate);
	cout << "\t" << name << " 카테고리 생성 성공" << endl << endl;
}

bool category::cate_name_overlap(string imsi_name) {												// 카테고리 이름 중복 검사 함수.

	category* p = cate_head;								// 1번 카테고리 부터 검사.

	if (p == NULL) {										// 예외 처리 : 현재 카테고리가 없는 경우.
		cout << "\t현재 카테고리가 비었습니다." << endl;
		return true;
	}

	while (p != NULL) {

		if (imsi_name == p->get_cate_name()) {
			return false;
		}
		p = p->get_next_cate();
	}
	return true;
}

void category::show_cate_list() {																// 카테고리 목록 보기.

	category* p = cate_head;

	if (p == NULL) {
		cout << "카테고리가 비었습니다." << endl << endl;
		return;
	}

	cout << "카테고리 목록" << endl;
	while (p != NULL) {
		cout << "\t" << p->get_cate_index() << ". " << p->get_cate_name() << endl;
		p = p->get_next_cate();
	}
	cout << endl;
}

category* category::search_cate() {														// 카테고리의 index로 카테고리를 찾는 함수.

	if (cate_num == 0) {						// 예외 처리 : 카테고리가 하나도 없는 경우.
		return NULL;
	}

	int n;
	cin >> n;

	if (n<=0 || n> cate_num) {												// 예외 처리 : n값을 잘못 입력한 경우.
		cout << "\t입력한 번호의 카테고리가 없습니다. " << endl << endl;				
		return NULL;
	}

	category* p = cate_head;
	while (p != NULL) {
		if (p->get_cate_index() == n) {
			return p;
		}
		p = p->get_next_cate();
	}
	return p;						// 예외 처리 : 만약 못 찾았으면 null값 반환.
}

void category::remove_category() {												// 카테고리 지우기.

	if (cate_num == 0) {														// 예외 처리 : 카테고리가 없을 경우.
		cout << "\t현재 카테고리 목록이 비었습니다." << endl << endl;
		cout << "==========================================================" << endl;
		return;
	}

	show_cate_list();															// 현재 카테고리들의 목록 출력.
	cout << "\t지우고 싶은 카테고리의 번호를 입력: ";

	category* ptr_cate = search_cate();											// 필요한 카테고리를 찾아 리턴받음.

	
	if (ptr_cate == NULL) {														// 예외 처리 : 잘못된 입력을 받았을 경우.
		cout << "\tcategory_menu로 돌아갑니다." << endl << endl;							
		cout << "==========================================================" << endl;
		return;
	}

	// 카테고리 연결리스트가
	// 1. 비었다.		2.  유일한 카테고리.		3. 맨 앞		4. 맨 뒤		5. 중간		

	if (cate_head == NULL && cate_num == 0) {													// 1. 빈 경우.

		cout << "\t카테고리가 이미 비었습니다." << endl << endl;
		return;
	}
	else if (ptr_cate == cate_head && ptr_cate == cate_tail) {									// 2. 유일한 1개

		cate_head = NULL;
		cate_tail = NULL;
	}
	else if (ptr_cate == cate_head) {															// 3. 처음

		category* q = ptr_cate->get_next_cate();
		q->set_prev_cate(NULL);
		cate_head = q;
	}
	else if (ptr_cate == cate_tail) {															// 4. 마지막

		category* q = ptr_cate->get_prev_cate();
		q->set_next_cate(NULL);
		cate_tail = q;
	}
	else {																						// 5. 중간

		category* next_p = ptr_cate->get_next_cate();
		category* prev_p = ptr_cate->get_prev_cate();

		next_p->set_prev_cate(prev_p);
		prev_p->set_next_cate(next_p);
	}

	// 지울 카테고리의 다음 카테고리들의 index를 1씩 감소시켜 준다. ( 늦게 생성될 수록 index 번호가 높기 때문에.)
	category* p_next = ptr_cate->get_next_cate();

	while (p_next != NULL) {						// 지울 카테고리가 중간 or 맨 앞일 때만 실행. 
													// (지울 카테고리의 다음 카테고리들의 번호(index) 1씩 감소.)
		p_next->index--;
		p_next = p_next->get_next_cate();
	}

	string imsi = ptr_cate->get_cate_name();

	cate_num--;
	delete(ptr_cate);
	cout << "\t" << imsi << " 카테고리 제거 성공" << endl << endl;
	cout << "==========================================================" << endl;
}


void category::show_category() {												// 카테고리 이름과 그에 연결된 todo들 보기.			

	// 카테고리 목록의 이름을 먼저 보여준다.
	// 그 후에 카테고리의 번호를 입력하게 한다.
	// 카테고리의 연결리스트들을 순회하며 입력된 번호의 카테고리를 찾는다.
	// 찾은 카테고리의 이름과 그와 연결된 todo들 출력.

	category* p = NULL;

	try {
		if (cate_num == 0) {														// 예외 : 카테고리가 하나도 없다면.
			throw - 1;
		}

		show_cate_list();															// 현재 카테고리 목록 출력.

		cout << "보고싶은 카테고리의 번호를 입력하세요. :";
		p = search_cate();

		if (p == NULL)																// 예외 : 카테고리의 번호를 잘못 입력.
			throw 3.14;
	}
	catch (int x) {																	// 예외 처리 : 경고문 출력 후. cate_menu로 돌아감.	
		cout << "\t현재 카테고리 목록이 비었습니다." << endl << endl;
		cout << "==========================================================" << endl;
		return;
	}
	catch (double pi) {
		cout << "==========================================================" << endl;
		return;
	}

	show_cate_todos(p);						// todo들 출력하는 함수.
}


void category::show_cate_todos(category* ptr_cate) {											// 카테고리에 연결된 할 일들을 출력해주는 함수.


	todo* ptr_todo = ptr_cate->get_first_todo();

	cout << "\t" << ptr_cate->get_cate_name() << endl;

	cout << "==========================================================" << endl;

	if (ptr_todo == NULL)															// 예외 처리 : 할 일이 없다면
		cout << "\t카테고리의 할 일이 비었습니다." << endl << endl;

	int i = 1;																		// 할 일들의 번호를 옆에 출력.(나중에 검색하기 위해.)

	while (ptr_todo != NULL) {														// todo들의 목록 출력.
		cout << "\t" << i++ << ". 제목 : " << ptr_todo->get_title() << endl;
		cout << "\t  마감 일자: " << ptr_todo->get_due_data() << endl;
		cout << "\t  설명: " << ptr_todo->get_detail() << endl;

		ptr_todo = ptr_todo->get_next_todo();
	}
	cout << endl;
	cout << "==========================================================" << endl;
}


void category::sort_todo_to_cate(todo* ptr_todo, category* ptr_cate) {									// 생성된 todo 객체를 카테고리에 입력하는 함수.

	if (ptr_cate == NULL) {
		return;
	}

	// 할 일을 카테고리에 연결. (마감일 순서대로 정렬.)
	// 할 일의 연결리스트가 
	// 1. 비었을 때,	2. 맨 앞에 올 때,	3. 맨 뒤에 올 때,	중간에 삽입될 때.

	// 들어갈 위치를 찾기 위한 변수.
	todo* p = ptr_cate->get_first_todo();
	todo* q = NULL;

	while (p != NULL) {													// 연결리스트 상의 위치 찾는 과정.
																		// 마감일을 비교
		if (ptr_todo->get_due_data() < p->get_due_data()) {
			break;
		}
		q = p;
		p = p->get_next_todo();
	}
																		// todo 연결리스트가
	if (p == NULL && ptr_cate->get_first_todo() == NULL) {				// 1. 비었을 때.
		ptr_cate->set_first_todo(ptr_todo);
	}
	else if (p == ptr_cate->get_first_todo()) {							// 2. 처음에 들어가야 함.

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

	ptr_cate->increase_todo_num();									// 카테고리 객체에 할 일의 개수(todo_num)을 1 증가.
}

int category::get_todo_num() {														// 현재 카테고리에 연결된 할 일의 개수를 리턴.
	return todo_num;
}

void category::increase_todo_num() {												// 현재 카테고리에 연결된 할 일의 개수++.		
	this->todo_num++;
}

void category::decrease_todo_num() {												// 현재 카테고리에 연결된 할 일의 개수--.
	this->todo_num--;
}