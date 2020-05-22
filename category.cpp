#include "category.h"

// �� �� ī�װ� ��ü�� ���������� ����� ����.
category* category::head_cate = NULL;				// extern�� �ٿ��� linkedlist.cpp���� �� �� �ִ��� Ȯ���غ���.

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

	/*add_to_cate(ptr_cate);*/		// ������ �� ��.

	return ptr_cate;									// ���� Ÿ�� ��ĳ�� �� ����.
}

void category::set_next_cate(category* p) {				// ���� category�� �ּҸ� �޴� �Լ�.
	
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

// ���� �� �� �͵�.




void category::set_cate_name(string cate_name) {
	this->cate_name = cate_name;
}


void category::show_cate_name() {						// ī�װ� �̸� ��� �Լ�.

	cout << this->cate_name << endl;
}

category* category::get_next_cate() {								// ���� ī�װ��� �ּ� ��ȯ �Լ�.
	return this->next_cate;
}

string category::get_cate_name() {

	return this->cate_name;
}

void category::remove_linkedlist_cate(category* ptr_cate) {			// ī�װ� ���Ḯ��Ʈ���� ī�װ��� �����ϴ� �Լ�.

	// ���� ī�װ��� �̹� ã�� ��Ȳ ���� ���Ḯ��Ʈ���� ���Ÿ� ���ָ� ��.
	// 1. ������ ī�װ���.	2. �� �� ī�װ�.		3. �� �� ī�װ�.		4. �߰��� �� ī�װ�.
	// -> �� �ϵ��� ����Ǿ� �ִٸ� �װ͵鵵 ��������� ��.(���߿� ����).

	category* p = category::head_cate;				// �ܹ��� ���Ḯ��Ʈ�� �� �� �ּҰ� �ʿ��ؼ� �˻� �� �� �� ��....(todo�� �������� ��������.)
	category* q = NULL;

	while (p != NULL) {

		if (p == ptr_cate) {
			break;
		}
		q = p;
		p = p->next_cate;
	}

	category* tmp = p;		// 2. 3. 4 ��쿡 ���.

	if (q == NULL && cate_num == 1) {								// 1. ������ ī�װ���

		// ���⿡ ����� �� �ϵ� free ������� ��.
		head_cate = NULL;
		free(p);
	}
	else if (q == NULL && p == head_cate) {							// 2. �� ���� ī�װ����.

		// ���⿡ ����� �� �ϵ� free ������� ��.
		head_cate = p->next_cate;
		free(tmp);
	}
	else if (p == NULL) {											// 3. ������ ī�װ����.

		// ���⿡ ����� �� �ϵ� free ������� ��.
		q->next_cate = NULL;
		free(tmp);
	}
	else {															// 4. �߰��� �������� ��.

		// ���⿡ ����� �� �ϵ� free ������� ��.
		q->next_cate = p->next_cate;
		free(tmp);
	}
	cout << "���� ����!" << endl;
	cate_num--;
}

void category::empty_category() {

	category* p = head_cate;
	category* q = NULL;

	if (p == NULL) {
		cout << "ī�װ� ����� �̹� ������ϴ�." << endl;

	}

	while (p != NULL && cate_num >= 0) {

		// p�� ����� �� �ϵ� free �����ִ� �Լ�.
		q = p;
		p = p->next_cate;
		free(q);
	}

	cout << "ī�װ� ��� ���� ����." << endl;
	head_cate = NULL;				// ī�װ� ���Ḯ��Ʈ�� ��������� null�� ����Ŵ.
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
//	// �� ī�װ��� 1. �� ���,	2. �ƴ� ���.
//	// ������ ���� ����� ���� �;� �ϴ�, ������� ��.
//
//	// �� ī�װ��� todo ���� ����� ������� Ȯ���ؾ� ��.
//
//
//	if (this->first_todo == NULL) {					// �� ī�װ��� �� ���.
//		first_todo = ptr_todo;
//	}
//	else {											// �� ī�װ��� �̹� �� ���� �ִ� ��� �о�� �Է�.		
//		ptr_todo->next_cate_todo = first_todo;
//		first_todo = ptr_todo;
//	}
//}

todo* category::getFirsttodo() {
	return first_todo;
}