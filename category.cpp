#include "category.h"

// �� �� ī�װ� ��ü�� ���������� ����� ����.

int category::cate_num = 0;


category::category(string cate_name) {
	this->cate_name = cate_name;
	this->index = ++cate_num;
	this->first_todo = NULL;
	this->next_cate = NULL;
	this->prev_cate = NULL;
}

category* category::create_cate(string cate_name) {

	category* ptr_cate = new category(cate_name);		// �̸��� ������ �ʱ�ȭ�� ī�װ� ��ü ����.

	return ptr_cate;									
}

void category::set_next_cate(category* p) {				// ���� category�� �ּҸ� �޴� �Լ�.
	
	this->next_cate = p;
}

void category::set_prev_cate(category* p) {				// ���� category�� �ּҸ� �޴� �Լ�.

	this->prev_cate = p;
}

category* category::get_prev_cate() {					// ���� category�� �ּ� ��ȯ.
	return prev_cate;
}

int category::get_cate_index() {						// category�� ��ȣ(index)�� ��ȯ.
	return index;
}

void category::set_first_todo(todo* p) {				// �� ī�װ��� ù ��° �� ���� �ּ� �Է�.
	this->first_todo = p;
}

todo* category::get_first_todo() {						// �� ī�װ��� ù ��° �� ���� �ּ� ��ȯ.
	return first_todo;
}

void category::increase_index() {						// category�� ��ȣ(index) 1 ����.
	this->index--;
}

category* category::get_next_cate() {					// ���� category�� �ּ� ��ȯ.
	return next_cate;
}

string category::get_cate_name() {						// category�� �̸� ��ȯ.
	return cate_name;
}