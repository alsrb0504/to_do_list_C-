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


// ===============================
void create_category() {															// ī�װ� ���� �Լ�.

	string name;

	while (1) {													// �̸� �ߺ� �˻� �κ�.

		cout << "������ ī�װ��� �̸��� �Է����ּ���.: ";
		getchar();												// �Է� ���� ����.
		getline(cin, name);

		if (!(cate_name_overlap(name))) {						// �̸� �ߺ� �˻� ���ִ� �Լ� ȣ��.
			cout << "\t�ߺ��� ī�װ��� ����." << endl << endl;
			return;
		}
		break;
	}

	category* ptr_cate = NULL;
	ptr_cate = ptr_cate->create_cate(name);						// ī�װ� ��ü ����.

	add_to_cate(ptr_cate);
	cout << "\t" << name << " ī�װ� ���� ����" << endl << endl;
}


bool cate_name_overlap(string imsi_name) {												// ī�װ� �̸� �ߺ� �˻� �Լ�.

	category* p = cate_struct.cate_head;

	if (p == NULL) {
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

void add_to_cate(category* ptr_cate) {									// cate ����ü�� head�� tail�� ������ category���� ��������ִ� �Լ�.

	// ������ category ��ü�� �޾Ƽ� ���Ḯ��Ʈ�� �߰��� ��. ( �Է� ������ �ܹ����̴�. )
	// ���Ḯ��Ʈ��
	// 1. �� ����Ʈ(ó�� ���� �� �ʿ�).	2. �� ���Ḯ��Ʈ�� �ƴ� ���.			

	if (cate_struct.size == 0 && cate_struct.cate_head == NULL) {		// 1. ���Ḯ��Ʈ�� �� ���.

		cate_struct.cate_head = ptr_cate;
		cate_struct.cate_tail = ptr_cate;
	}
	else {																// 2. �� ���Ḯ��Ʈ�� �ƴ� ���.

		ptr_cate->set_next_cate(cate_struct.cate_head);
		cate_struct.cate_head->set_prev_cate(ptr_cate);
		cate_struct.cate_head = ptr_cate;
	}

	cate_struct.size++;								// ī�װ����� ��ȣ�� ī�װ� ����ü�� ����� Ű���ֱ� ����.
}


void show_cate_list() {																// ī�װ� ��� ����.

	category* p = cate_struct.cate_tail;						// ���߿� ������ �ͺ��� ���� ���� tail�� ����������.

	cout << "ī�װ� ���" << endl;
	int i = 1;

	while (p != NULL) {
		cout << "\t" << i << ". " << p->get_cate_name() << endl;
		p = p->get_prev_cate();
		i++;
	}
	cout << endl;
}

category* search_cate(int n) {														// ī�װ��� index�� ī�װ��� ã�� �Լ�.

	category* p = cate_struct.cate_head;

	while (p != NULL && n > 0 && n <= cate_struct.size) {

		if (p->get_cate_index() == n) {							// ī�װ��� �Ϸù�ȣ�� �Է¹��� n�� ������ �� ī������ �ּ� ����.
			return p;
		}
		p = p->get_next_cate();
	}

	return NULL;												// �� ã������ NULL �� ��ȯ.
}

void show_cate_todos(category* ptr_cate) {											// ī�װ��� ����� �� �ϵ��� ������ִ� �Լ�.

	if (ptr_cate == NULL) {															// ���� ó��.
		return;
	}

	todo* ptr_todo = ptr_cate->get_first_todo();

	cout << "\t" << ptr_cate->get_cate_name() << endl;

	cout << "==========================================================" << endl;

	if (ptr_todo == NULL)															// ���� ó��.
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

category* select_cate() {											// ī�װ��� index�� ī�װ��� ã�� �Լ�.

	show_cate_list();

	int n;
	cout << "�ٷ� ī�װ� ��ȣ �Է�(������ �ƹ� ���� �Է�): ";
	cin >> n;

	category* p = search_cate(n);

	if (p == NULL) {												// ����ó�� ã�� ������ ���.
		cout << "\t�Է��� ��ȣ�� ī�װ��� �����ϴ�." << endl << endl;
		cout << "==========================================================" << endl;
		return NULL;
	}

	return p;
}

void sort_todo_to_cate(todo* ptr_todo, int n) {								// ������ todo ��ü�� ī�װ��� �Է��ϴ� �Լ�.

	category* ptr_cate = search_cate(n);							// ī�װ��� ã����. �̶� n�� �˻��ؼ� �������Ƿ� ���� �˻� x.

	// �� ���� ī�װ��� ����
	// ��¥ ������� ����
	// �� ���� ���Ḯ��Ʈ�� 
	// 1. ����� ��,	2. �� �տ� �� ��,	3. �� �ڿ� �� ��,	�߰��� ���Ե� ��.

	// �� ��ġ�� ã�� ���� ����.
	todo* p = ptr_cate->get_first_todo();
	todo* q = NULL;

	while (p != NULL) {												// ���Ḯ��Ʈ ���� ��ġ ã�� ����.
																	// �������� ��
		if (ptr_todo->get_due_data() < p->get_due_data()) {
			break;
		}
		q = p;
		p = p->get_next_todo();
	}

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
}

void remove_category() {												// ī�װ� �����.

	show_cate_list();

	int n;
	cout << "\t����� ���� ī�װ��� ��ȣ�� �Է�: ";
	cin >> n;

	// ī�װ��� ���Ḯ��Ʈ���� ��ȸ�ϸ� �Էµ� ��ȣ�� ī�װ��� ã�� �� �ּҸ� ��ȯ����.
	// �� ī�װ��� ����� todo���� ���� delete.
	// �� �� �� ������ �� Ȯ���� ����. category�� ����. �� ������ ���Ḯ��Ʈ���� ��ȣ�� 1�� ���ҽ����ش�.

	category* ptr_cate = search_cate(n);

	if (ptr_cate == NULL) {												// ����ó�� ã�� ������ ���.
		cout << "\t�Է��� ��ȣ�� ī�װ��� �����ϴ�." << endl;
		cout << "==========================================================" << endl;
		return;
	}

	// todo�� ������ �ٷ� delete ������ �ϳ��� ��ȸ�ϸ� delete �� ī�װ� delete.

	todo* ptr_todo = ptr_cate->get_first_todo();

	while (ptr_todo != NULL) {
		todo* q = ptr_todo;
		ptr_todo = ptr_todo->get_next_todo();
		delete(q);
	}

	// cate delete �ϴµ� 
	// ī�װ� ���Ḯ��Ʈ��
	// 1. �����.		2.  ������ ī�װ�.		3. �� ��(�ٵ� 0,1�� �� ���� ����.)	4. �� ��		5. �߰�		

	if (cate_struct.cate_head == NULL && cate_struct.size == 0) {								// 1. �� ���.

		cout << "\tī�װ��� �̹� ������ϴ�." << endl << endl;
		return;
	}
	else if (ptr_cate == cate_struct.cate_head && ptr_cate == cate_struct.cate_tail) {			// 2. ������ 1��

		cate_struct.cate_head = NULL;
		cate_struct.cate_tail = NULL;
	}
	else if (ptr_cate == cate_struct.cate_head) {												// 3. ó��

		category* q = ptr_cate->get_next_cate();
		q->set_prev_cate(NULL);
		cate_struct.cate_head = q;
	}
	else if (ptr_cate == cate_struct.cate_tail) {												// 4. ������

		category* q = ptr_cate->get_prev_cate();
		q->set_next_cate(NULL);
		cate_struct.cate_tail = q;
	}
	else {																						// 5. �߰�

		category* next_p = ptr_cate->get_next_cate();
		category* prev_p = ptr_cate->get_prev_cate();

		next_p->set_prev_cate(prev_p);
		prev_p->set_next_cate(next_p);
	}

	// ���� ī�װ��� ���� ī�װ����� index�� 1�� ���ҽ��� �ش�. ( �ʰ� ������ ���� index ��ȣ�� ���� ������.)
	category* prev_p = ptr_cate->get_prev_cate();

	while (prev_p != NULL) {										// �߰��̰ų� �� ���� ���� ����. (���� ī�װ��� ���� ī�װ����� ��ȣ(index) 1�� ����.

		prev_p->increase_index();									// ī�װ����� ��ü index�� 1�� ���� �����ִ� �Լ�.
		prev_p = prev_p->get_prev_cate();
	}

	string imsi = ptr_cate->get_cate_name();

	category::cate_num--;
	cate_struct.size--;
	delete(ptr_cate);
	cout << "\t" << imsi << " ī�װ� ���� ����" << endl << endl;
	cout << "==========================================================" << endl;
}


void show_category() {												// ī�װ� �̸��� �׿� ����� todo�� ����.			

	// ī�װ� ����� �̸��� ���� �����ش�.
	// �� �Ŀ� ī�װ��� ��ȣ�� �Է��ϰ� �Ѵ�.
	// ī�װ��� ���Ḯ��Ʈ���� ��ȸ�ϸ� �Էµ� ��ȣ�� ī�װ��� ã�´�.
	// �׷��� ī�װ��� �̸��� �׿� ����� todo���� �����ش�.

	category* p = select_cate();

	show_cate_todos(p);

}

category* search_cate(string name) {											// ī�װ� �̸��� ������ ī�װ��� ã�� �Լ�.

	category* p = cate_struct.cate_head;

	if (p == NULL) {
		cout << "\tī�װ��� ������ϴ�." << endl;
		return NULL;
	}

	while (p != NULL) {

		if (name == p->get_cate_name()) {
			return p;
		}
		p = p->get_next_cate();
	}
	return NULL;							// �� ã�� ���. �޸��忡 �߸� ���� �ִ� ��.
}