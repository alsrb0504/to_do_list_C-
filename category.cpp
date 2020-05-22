#include "category.h"

// 한 번 카테고리 객체를 전역변수로 만들어 보자.
category* category::head_cate = NULL;				// extern을 붙여서 linkedlist.cpp에서 쓸 수 있는지 확인해보자.

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

	/*add_to_cate(ptr_cate);*/		// 지워야 할 듯.

	return ptr_cate;									// 리턴 타입 어캐할 지 생각.
}

void category::set_next_cate(category* p) {				// 다음 category의 주소를 받는 함수.
	
	this->next_cate = p;
}

void category::set_prev_cate(category* p) {

	this->prev_cate = p;
}

category* category::get_prev_cate() {
	return prev_cate;
}

int category::get_cate_index() {
	return index;
}

void category::set_first_todo(todo* p) {
	this->first_todo = p;
}

todo* category::get_first_todo() {
	return first_todo;
}

void category::increase_index() {
	this->index--;
}

// 수정 안 한 것들.




void category::set_cate_name(string cate_name) {
	this->cate_name = cate_name;
}


void category::show_cate_name() {						// 카테고리 이름 출력 함수.

	cout << this->cate_name << endl;
}

category* category::get_next_cate() {								// 다음 카테고리의 주소 반환 함수.
	return this->next_cate;
}

string category::get_cate_name() {

	return this->cate_name;
}

void category::remove_linkedlist_cate(category* ptr_cate) {			// 카테고리 연결리스트에서 카테고리를 제거하는 함수.

	// 지울 카테고리는 이미 찾은 상황 이제 연결리스트에서 제거만 해주면 됨.
	// 1. 유일한 카테고리임.	2. 맨 앞 카테고리.		3. 맨 뒤 카테고리.		4. 중간에 낀 카테고리.
	// -> 할 일들이 연결되어 있다면 그것들도 제거해줘야 함.(나중에 구현).

	category* p = category::head_cate;				// 단방향 연결리스트라 그 전 주소가 필요해서 검색 한 번 더 함....(todo는 이중으로 수정하자.)
	category* q = NULL;

	while (p != NULL) {

		if (p == ptr_cate) {
			break;
		}
		q = p;
		p = p->next_cate;
	}

	category* tmp = p;		// 2. 3. 4 경우에 사용.

	if (q == NULL && cate_num == 1) {								// 1. 유일한 카테고리임

		// 여기에 연결된 할 일들 free 시켜줘야 함.
		head_cate = NULL;
		free(p);
	}
	else if (q == NULL && p == head_cate) {							// 2. 맨 앞의 카테고리라면.

		// 여기에 연결된 할 일들 free 시켜줘야 함.
		head_cate = p->next_cate;
		free(tmp);
	}
	else if (p == NULL) {											// 3. 마지막 카테고리라면.

		// 여기에 연결된 할 일들 free 시켜줘야 함.
		q->next_cate = NULL;
		free(tmp);
	}
	else {															// 4. 중간에 끼어있을 때.

		// 여기에 연결된 할 일들 free 시켜줘야 함.
		q->next_cate = p->next_cate;
		free(tmp);
	}
	cout << "제거 성공!" << endl;
	cate_num--;
}

void category::empty_category() {

	category* p = head_cate;
	category* q = NULL;

	if (p == NULL) {
		cout << "카테고리 목록이 이미 비었습니다." << endl;

	}

	while (p != NULL && cate_num >= 0) {

		// p에 연결되 할 일들 free 시켜주는 함수.
		q = p;
		p = p->next_cate;
		free(q);
	}

	cout << "카테고리 목록 비우기 성공." << endl;
	head_cate = NULL;				// 카테고리 연결리스트가 비어졌으니 null을 가르킴.
}

bool category::is_empty_cate() {
	category* p = head_cate;

	if (p == NULL)
		return true;
	else
		return false;
}

//void category::add_todo_cate(todo* ptr_todo) {
//	
//	// 이 카테고리가 1. 빈 경우,	2. 아닌 경우.
//	// 순서는 새로 생긴게 위에 와야 하니, 순서대로 들어감.
//
//	// 이 카테고리의 todo 연결 목록이 비었는지 확인해야 함.
//
//
//	if (this->first_todo == NULL) {					// 이 카테고리가 빈 경우.
//		first_todo = ptr_todo;
//	}
//	else {											// 이 카테고리에 이미 할 일이 있는 경우 밀어내고 입력.		
//		ptr_todo->next_cate_todo = first_todo;
//		first_todo = ptr_todo;
//	}
//}

todo* category::getFirsttodo() {
	return first_todo;
}