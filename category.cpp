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

category* category::get_next_cate() {
	return next_cate;
}

string category::get_cate_name() {
	return cate_name;
}

// 수정 안 한 것들.


