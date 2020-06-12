#include "category.h"

// 한 번 카테고리 객체를 전역변수로 만들어 보자.

int category::cate_num = 0;


category::category(string cate_name) {
	this->cate_name = cate_name;
	this->index = ++cate_num;
	this->first_todo = NULL;
	this->next_cate = NULL;
	this->prev_cate = NULL;
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


// ===============================
void create_category() {															// 카테고리 생성 함수.

	string name;

	while (1) {													// 이름 중복 검사 부분.

		cout << "생성할 카테고리의 이름을 입력해주세요.: ";
		getchar();												// 입력 버퍼 제거.
		getline(cin, name);

		if (!(cate_name_overlap(name))) {						// 이름 중복 검사 해주는 함수 호출.
			cout << "\t중복된 카테고리가 존재." << endl << endl;
			return;
		}
		break;
	}

	category* ptr_cate = NULL;
	ptr_cate = ptr_cate->create_cate(name);						// 카테고리 객체 생성.

	add_to_cate(ptr_cate);
	cout << "\t" << name << " 카테고리 생성 성공" << endl << endl;
}


bool cate_name_overlap(string imsi_name) {												// 카테고리 이름 중복 검사 함수.

	category* p = cate_struct.cate_head;

	if (p == NULL) {
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

void add_to_cate(category* ptr_cate) {									// cate 구조체의 head와 tail에 생성된 category들을 연결시켜주는 함수.

	// 생성된 category 객체를 받아서 연결리스트에 추가할 때. ( 입력 방향이 단방향이다. )
	// 연결리스트가
	// 1. 빈 리스트(처음 세팅 때 필요).	2. 빈 연결리스트가 아닌 경우.			

	if (cate_struct.size == 0 && cate_struct.cate_head == NULL) {		// 1. 연결리스트가 빈 경우.

		cate_struct.cate_head = ptr_cate;
		cate_struct.cate_tail = ptr_cate;
	}
	else {																// 2. 빈 연결리스트가 아닌 경우.

		ptr_cate->set_next_cate(cate_struct.cate_head);
		cate_struct.cate_head->set_prev_cate(ptr_cate);
		cate_struct.cate_head = ptr_cate;
	}

	cate_struct.size++;								// 카테고리들의 번호와 카테고리 구조체의 사이즈를 키워주기 위해.
}


void show_cate_list() {																// 카테고리 목록 보기.

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

category* search_cate(int n) {														// 카테고리의 index로 카테고리를 찾는 함수.

	category* p = cate_struct.cate_head;

	while (p != NULL && n > 0 && n <= cate_struct.size) {

		if (p->get_cate_index() == n) {							// 카테고리의 일련번호와 입력받은 n이 같으면 그 카레고리의 주소 리턴.
			return p;
		}
		p = p->get_next_cate();
	}

	return NULL;												// 못 찾았으면 NULL 값 반환.
}

void show_cate_todos(category* ptr_cate) {											// 카테고리에 연결된 할 일들을 출력해주는 함수.

	if (ptr_cate == NULL) {															// 예외 처리.
		return;
	}

	todo* ptr_todo = ptr_cate->get_first_todo();

	cout << "\t" << ptr_cate->get_cate_name() << endl;

	cout << "==========================================================" << endl;

	if (ptr_todo == NULL)															// 예외 처리.
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

category* select_cate() {											// 카테고리의 index로 카테고리를 찾는 함수.

	show_cate_list();

	int n;
	cout << "다룰 카테고리 번호 입력(없으면 아무 숫자 입력): ";
	cin >> n;

	category* p = search_cate(n);

	if (p == NULL) {												// 예외처리 찾지 못햇을 경우.
		cout << "\t입력한 번호의 카테고리가 없습니다." << endl << endl;
		cout << "==========================================================" << endl;
		return NULL;
	}

	return p;
}

void sort_todo_to_cate(todo* ptr_todo, int n) {								// 생성된 todo 객체를 카테고리에 입력하는 함수.

	category* ptr_cate = search_cate(n);							// 카테고리를 찾아줌. 이때 n은 검사해서 들어왔으므로 따로 검사 x.

	// 할 일을 카테고리에 연결
	// 날짜 순서대로 정렬
	// 할 일의 연결리스트가 
	// 1. 비었을 때,	2. 맨 앞에 올 때,	3. 맨 뒤에 올 때,	중간에 삽입될 때.

	// 들어갈 위치를 찾기 위한 변수.
	todo* p = ptr_cate->get_first_todo();
	todo* q = NULL;

	while (p != NULL) {												// 연결리스트 상의 위치 찾는 과정.
																	// 마감일을 비교
		if (ptr_todo->get_due_data() < p->get_due_data()) {
			break;
		}
		q = p;
		p = p->get_next_todo();
	}

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
}

void remove_category() {												// 카테고리 지우기.

	show_cate_list();

	int n;
	cout << "\t지우고 싶은 카테고리의 번호를 입력: ";
	cin >> n;

	// 카테고리의 연결리스트들을 순회하며 입력된 번호의 카테고리를 찾아 그 주소를 반환받음.
	// 그 카테고리와 연결된 todo들을 먼저 delete.
	// 그 후 다 지워진 걸 확인한 다음. category를 삭제. 그 이후의 연결리스트들의 번호를 1씩 감소시켜준다.

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

	// cate delete 하는데 
	// 카테고리 연결리스트가
	// 1. 비었다.		2.  유일한 카테고리.		3. 맨 앞(근데 0,1은 안 지울 것임.)	4. 맨 뒤		5. 중간		

	if (cate_struct.cate_head == NULL && cate_struct.size == 0) {								// 1. 빈 경우.

		cout << "\t카테고리가 이미 비었습니다." << endl << endl;
		return;
	}
	else if (ptr_cate == cate_struct.cate_head && ptr_cate == cate_struct.cate_tail) {			// 2. 유일한 1개

		cate_struct.cate_head = NULL;
		cate_struct.cate_tail = NULL;
	}
	else if (ptr_cate == cate_struct.cate_head) {												// 3. 처음

		category* q = ptr_cate->get_next_cate();
		q->set_prev_cate(NULL);
		cate_struct.cate_head = q;
	}
	else if (ptr_cate == cate_struct.cate_tail) {												// 4. 마지막

		category* q = ptr_cate->get_prev_cate();
		q->set_next_cate(NULL);
		cate_struct.cate_tail = q;
	}
	else {																						// 5. 중간

		category* next_p = ptr_cate->get_next_cate();
		category* prev_p = ptr_cate->get_prev_cate();

		next_p->set_prev_cate(prev_p);
		prev_p->set_next_cate(next_p);
	}

	// 지울 카테고리의 이전 카테고리들의 index를 1씩 감소시켜 준다. ( 늦게 생성될 수록 index 번호가 높기 때문에.)
	category* prev_p = ptr_cate->get_prev_cate();

	while (prev_p != NULL) {										// 중간이거나 맨 앞일 때만 실행. (지운 카테고리의 다음 카테고리들의 번호(index) 1씩 감소.

		prev_p->increase_index();									// 카테고리들의 자체 index를 1씩 감소 시켜주는 함수.
		prev_p = prev_p->get_prev_cate();
	}

	string imsi = ptr_cate->get_cate_name();

	category::cate_num--;
	cate_struct.size--;
	delete(ptr_cate);
	cout << "\t" << imsi << " 카테고리 제거 성공" << endl << endl;
	cout << "==========================================================" << endl;
}


void show_category() {												// 카테고리 이름과 그에 연결된 todo들 보기.			

	// 카테고리 목록의 이름을 먼저 보여준다.
	// 그 후에 카테고리의 번호를 입력하게 한다.
	// 카테고리의 연결리스트들을 순회하며 입력된 번호의 카테고리를 찾는다.
	// 그러면 카테고리의 이름과 그와 연결된 todo들을 보여준다.

	category* p = select_cate();

	show_cate_todos(p);

}

category* search_cate(string name) {											// 카테고리 이름을 가지고 카테고리를 찾는 함수.

	category* p = cate_struct.cate_head;

	if (p == NULL) {
		cout << "\t카테고리가 비었습니다." << endl;
		return NULL;
	}

	while (p != NULL) {

		if (name == p->get_cate_name()) {
			return p;
		}
		p = p->get_next_cate();
	}
	return NULL;							// 못 찾은 경우. 메모장에 잘못 적혀 있는 것.
}