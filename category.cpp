#include "category.h"

// static ����� �ʱ�ȭ.
int category::cate_num = 0;
category* category::cate_head = NULL;
category* category::cate_tail = NULL;


category::category(string cate_name) {					// ������.
	this->cate_name = cate_name;
	this->index = ++cate_num;
	this->first_todo = NULL;
	this->next_cate = NULL;
	this->prev_cate = NULL;
	this->todo_num = 0;
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


void category::add_to_cate(category* ptr_cate) {									// cate ����ü�� head�� tail�� ������ category���� ��������ִ� �Լ�.

	if (ptr_cate == NULL) {												// ���� ó��.
		cout << "���޵� category ��ü�� �����ϴ�." << endl;
		return;
	}

	// ������ category ��ü�� �޾Ƽ� ���Ḯ��Ʈ�� �߰��� ��.
	// ���Ḯ��Ʈ��
	// 1. �� ����Ʈ(ó�� ���� �� �ʿ�).	2. �� ���Ḯ��Ʈ�� �ƴ� ���.			

	if (cate_num == 1 && cate_head == NULL) {							// 1. ���Ḯ��Ʈ�� �� ���.	 // (�����ڿ��� cate_num�� +1 ���ֱ� ������ cate_num == 1)

		cate_head = ptr_cate;
		cate_tail = ptr_cate;
	}
	else {																// 2. �� ���Ḯ��Ʈ�� �ƴ� ���.																// (���κп� ���ο� ī�װ� �߰�).
		ptr_cate->set_prev_cate(category::cate_tail);					// (���κп� ���ο� ī�װ� �߰�).
		cate_tail->set_next_cate(ptr_cate);
		cate_tail = ptr_cate;
	}
}

void category::create_cate() {															// ī�װ� ���� �Լ�(�̸� �Է� �޴� ���� ����).

	string name;

	rewind(stdin);

	while (1) {																			// �̸� �ߺ� �˻� �κ�.

		cout << endl << "������ ī�װ��� �̸��� �Է����ּ���.: ";									
		getline(cin, name);

		if (!(cate_name_overlap(name))) {												// �̸� �ߺ� �˻� ���ִ� �Լ� ȣ��.
			cout << "\t�ߺ��� ī�װ��� ����. ī�װ� ���� ����." << endl << endl;
			return;
		}
		break;
	}

	category* ptr_cate = NULL;
	ptr_cate = ptr_cate->create_cate(name);						// ī�װ� ��ü ����.

	add_to_cate(ptr_cate);
	cout << "\t" << name << " ī�װ� ���� ����" << endl << endl;
}

bool category::cate_name_overlap(string imsi_name) {												// ī�װ� �̸� �ߺ� �˻� �Լ�.

	category* p = cate_head;								// 1�� ī�װ� ���� �˻�.

	if (p == NULL) {										// ���� ó�� : ���� ī�װ��� ���� ���.
		cout << "\t���� ī�װ��� ������ϴ�." << endl;
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

void category::show_cate_list() {																// ī�װ� ��� ����.

	category* p = cate_head;

	if (p == NULL) {
		cout << "ī�װ��� ������ϴ�." << endl << endl;
		return;
	}

	cout << "ī�װ� ���" << endl;
	while (p != NULL) {
		cout << "\t" << p->get_cate_index() << ". " << p->get_cate_name() << endl;
		p = p->get_next_cate();
	}
	cout << endl;
}

category* category::search_cate() {														// ī�װ��� index�� ī�װ��� ã�� �Լ�.

	if (cate_num == 0) {						// ���� ó�� : ī�װ��� �ϳ��� ���� ���.
		return NULL;
	}

	int n;
	cin >> n;

	if (n<=0 || n> cate_num) {												// ���� ó�� : n���� �߸� �Է��� ���.
		cout << "\t�Է��� ��ȣ�� ī�װ��� �����ϴ�. " << endl << endl;				
		return NULL;
	}

	category* p = cate_head;
	while (p != NULL) {
		if (p->get_cate_index() == n) {
			return p;
		}
		p = p->get_next_cate();
	}
	return p;						// ���� ó�� : ���� �� ã������ null�� ��ȯ.
}

void category::remove_category() {												// ī�װ� �����.

	if (cate_num == 0) {														// ���� ó�� : ī�װ��� ���� ���.
		cout << "\t���� ī�װ� ����� ������ϴ�." << endl << endl;
		cout << "==========================================================" << endl;
		return;
	}

	show_cate_list();															// ���� ī�װ����� ��� ���.
	cout << "\t����� ���� ī�װ��� ��ȣ�� �Է�: ";

	category* ptr_cate = search_cate();											// �ʿ��� ī�װ��� ã�� ���Ϲ���.

	
	if (ptr_cate == NULL) {														// ���� ó�� : �߸��� �Է��� �޾��� ���.
		cout << "\tcategory_menu�� ���ư��ϴ�." << endl << endl;							
		cout << "==========================================================" << endl;
		return;
	}

	// ī�װ� ���Ḯ��Ʈ��
	// 1. �����.		2.  ������ ī�װ�.		3. �� ��		4. �� ��		5. �߰�		

	if (cate_head == NULL && cate_num == 0) {													// 1. �� ���.

		cout << "\tī�װ��� �̹� ������ϴ�." << endl << endl;
		return;
	}
	else if (ptr_cate == cate_head && ptr_cate == cate_tail) {									// 2. ������ 1��

		cate_head = NULL;
		cate_tail = NULL;
	}
	else if (ptr_cate == cate_head) {															// 3. ó��

		category* q = ptr_cate->get_next_cate();
		q->set_prev_cate(NULL);
		cate_head = q;
	}
	else if (ptr_cate == cate_tail) {															// 4. ������

		category* q = ptr_cate->get_prev_cate();
		q->set_next_cate(NULL);
		cate_tail = q;
	}
	else {																						// 5. �߰�

		category* next_p = ptr_cate->get_next_cate();
		category* prev_p = ptr_cate->get_prev_cate();

		next_p->set_prev_cate(prev_p);
		prev_p->set_next_cate(next_p);
	}

	// ���� ī�װ��� ���� ī�װ����� index�� 1�� ���ҽ��� �ش�. ( �ʰ� ������ ���� index ��ȣ�� ���� ������.)
	category* p_next = ptr_cate->get_next_cate();

	while (p_next != NULL) {						// ���� ī�װ��� �߰� or �� ���� ���� ����. 
													// (���� ī�װ��� ���� ī�װ����� ��ȣ(index) 1�� ����.)
		p_next->index--;
		p_next = p_next->get_next_cate();
	}

	string imsi = ptr_cate->get_cate_name();

	cate_num--;
	delete(ptr_cate);
	cout << "\t" << imsi << " ī�װ� ���� ����" << endl << endl;
	cout << "==========================================================" << endl;
}


void category::show_category() {												// ī�װ� �̸��� �׿� ����� todo�� ����.			

	// ī�װ� ����� �̸��� ���� �����ش�.
	// �� �Ŀ� ī�װ��� ��ȣ�� �Է��ϰ� �Ѵ�.
	// ī�װ��� ���Ḯ��Ʈ���� ��ȸ�ϸ� �Էµ� ��ȣ�� ī�װ��� ã�´�.
	// ã�� ī�װ��� �̸��� �׿� ����� todo�� ���.

	category* p = NULL;

	try {
		if (cate_num == 0) {														// ���� : ī�װ��� �ϳ��� ���ٸ�.
			throw - 1;
		}

		show_cate_list();															// ���� ī�װ� ��� ���.

		cout << "������� ī�װ��� ��ȣ�� �Է��ϼ���. :";
		p = search_cate();

		if (p == NULL)																// ���� : ī�װ��� ��ȣ�� �߸� �Է�.
			throw 3.14;
	}
	catch (int x) {																	// ���� ó�� : ��� ��� ��. cate_menu�� ���ư�.	
		cout << "\t���� ī�װ� ����� ������ϴ�." << endl << endl;
		cout << "==========================================================" << endl;
		return;
	}
	catch (double pi) {
		cout << "==========================================================" << endl;
		return;
	}

	show_cate_todos(p);						// todo�� ����ϴ� �Լ�.
}


void category::show_cate_todos(category* ptr_cate) {											// ī�װ��� ����� �� �ϵ��� ������ִ� �Լ�.


	todo* ptr_todo = ptr_cate->get_first_todo();

	cout << "\t" << ptr_cate->get_cate_name() << endl;

	cout << "==========================================================" << endl;

	if (ptr_todo == NULL)															// ���� ó�� : �� ���� ���ٸ�
		cout << "\tī�װ��� �� ���� ������ϴ�." << endl << endl;

	int i = 1;																		// �� �ϵ��� ��ȣ�� ���� ���.(���߿� �˻��ϱ� ����.)

	while (ptr_todo != NULL) {														// todo���� ��� ���.
		cout << "\t" << i++ << ". ���� : " << ptr_todo->get_title() << endl;
		cout << "\t  ���� ����: " << ptr_todo->get_due_data() << endl;
		cout << "\t  ����: " << ptr_todo->get_detail() << endl;

		ptr_todo = ptr_todo->get_next_todo();
	}
	cout << endl;
	cout << "==========================================================" << endl;
}


void category::sort_todo_to_cate(todo* ptr_todo, category* ptr_cate) {									// ������ todo ��ü�� ī�װ��� �Է��ϴ� �Լ�.

	if (ptr_cate == NULL) {
		return;
	}

	// �� ���� ī�װ��� ����. (������ ������� ����.)
	// �� ���� ���Ḯ��Ʈ�� 
	// 1. ����� ��,	2. �� �տ� �� ��,	3. �� �ڿ� �� ��,	�߰��� ���Ե� ��.

	// �� ��ġ�� ã�� ���� ����.
	todo* p = ptr_cate->get_first_todo();
	todo* q = NULL;

	while (p != NULL) {													// ���Ḯ��Ʈ ���� ��ġ ã�� ����.
																		// �������� ��
		if (ptr_todo->get_due_data() < p->get_due_data()) {
			break;
		}
		q = p;
		p = p->get_next_todo();
	}
																		// todo ���Ḯ��Ʈ��
	if (p == NULL && ptr_cate->get_first_todo() == NULL) {				// 1. ����� ��.
		ptr_cate->set_first_todo(ptr_todo);
	}
	else if (p == ptr_cate->get_first_todo()) {							// 2. ó���� ���� ��.

		p->set_prev_todo(ptr_todo);
		ptr_todo->set_next_todo(p);
		ptr_cate->set_first_todo(ptr_todo);
	}
	else if (p == NULL) {												// 3. �� ��.
		ptr_todo->set_prev_todo(q);
		q->set_next_todo(ptr_todo);
	}
	else {																// 4. �߰�.
		ptr_todo->set_next_todo(p);
		ptr_todo->set_prev_todo(q);
		p->set_prev_todo(ptr_todo);
		q->set_next_todo(ptr_todo);
	}

	ptr_cate->increase_todo_num();									// ī�װ� ��ü�� �� ���� ����(todo_num)�� 1 ����.
}

int category::get_todo_num() {														// ���� ī�װ��� ����� �� ���� ������ ����.
	return todo_num;
}

void category::increase_todo_num() {												// ���� ī�װ��� ����� �� ���� ����++.		
	this->todo_num++;
}

void category::decrease_todo_num() {												// ���� ī�װ��� ����� �� ���� ����--.
	this->todo_num--;
}