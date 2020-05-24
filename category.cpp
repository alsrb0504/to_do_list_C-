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