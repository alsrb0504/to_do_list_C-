#define  _CRT_SECURE_NO_WARNINGS

#include "command.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


Cate_Struct cate_struct;					// ī�װ� ���Ḯ��Ʈ�� head, tail, ī�װ��� ���� �����ϱ� ���� ����ü ���� ����.	

category* unclassified;						// 1. �̺з� ī�װ� ����.
category* important;						// 2. �߿��� ī�װ� ����.

void init_setting() {						// �ʱ� ���� ( ����ü �ʱ�ȭ ��  1.�̺з�		2.�߿� category ����).

	cate_struct.size = 0;									// cate_struct ����ü �ʱ�ȭ.
	cate_struct.cate_head = NULL;
	cate_struct.cate_tail = NULL;

	unclassified = unclassified->create_cate("�̺з�");		// 1. �̺з� ī�װ� ����.
	add_to_cate(unclassified);

	important = important->create_cate("�߿�");				// 2. �߿��� ī�װ� ����.
	add_to_cate(important);
	
	cout << "�ʱ� ����: " << endl;
	cout << "1�� ī�װ��� \"�̺з�\" 2�� ī�װ��� \"�߿�\"�� ����" << endl << endl;
}

void save() {																	// ���� ���� ���.

	ofstream fp("to_do_list.txt");

	if (!(fp.is_open())) {							// ���� ó��.
		cout << "not found file. " << endl;
		return;
	}

	category* ptr_cate = cate_struct.cate_tail;

	if (ptr_cate == NULL) {
		cout << "\tī�װ��� �����ϴ�. �����ϱ� ����!!" << endl;
		return;
	}

	while (ptr_cate != NULL) {
		string print_cate = "@";												// ���Ͽ� ī�װ� ���.
		print_cate.append(ptr_cate->get_cate_name());							// "@ī�װ��̸�" ���
		print_cate.append("\n");
		fp.write( print_cate.c_str(), print_cate.size());

		todo* ptr_todo = ptr_cate->get_first_todo();
		while (ptr_todo != NULL) {												// ���Ͽ� ī�װ��� �� �� ���.
			string print_todo = save_to_todo(ptr_todo, ptr_cate);				// ����� ���� ���� �Լ�.
			fp.write(print_todo.c_str(), print_todo.size());					// "#ī�װ���#����#��#��#���λ���#" ���� ���.

			ptr_todo = ptr_todo->get_next_todo();
		}

		ptr_cate = ptr_cate->get_prev_cate();
	}
	cout << "\t������� ����!!" << endl << endl;
	fp.close();
}

string save_to_todo(todo* p, category* ptr_cate) {								// save()���� ����� ���� ���� �Լ�.
	
	string print_todo = "#";							// �����ڷ� �� ����

	string cate, title, time, month, date, detail;

	cate = ptr_cate->get_cate_name();
	title = p->get_title();
	time = p->get_due_data();
	detail = p->get_detail();

	month = time.substr(0, 2);
	date = time.substr(2, 4);

	// �����ϴ� �κ� �Լ� ����.
	link(print_todo, cate);								// ���� ���� �Լ�.
	link(print_todo, title);
	link(print_todo, month);
	link(print_todo, date);
	link(print_todo, detail);

	print_todo.append("\n");

	return print_todo;									// "#ī�װ���#����#��#��#���λ���#" ���� ������ ���ڿ� ��ȯ.
}

void link(string& s, string part) {								// save()�� ���� ���ڿ� ���� �Լ�.
																// ���� ���ڿ� + �߰��� ���ڿ� + #
	s.append(part);
	s.append("#");
}

void load() {																				// ���� �ҷ����� �Լ�.
	
	ifstream fp("to_do_list.txt");						// �б�� ��ü ����.

	if (!(fp.is_open())) {								// ���� ó��.
		cout << "not found file. " << endl;
		return;
	}

	string s;

	while (fp) {
		getline(fp, s);

		if (s[0] == '@') {									// ī�װ� ������.

			string imsi_name = s.substr(1, s.size());			// '@' ���� ����.

			if (!(cate_name_overlap(imsi_name))) {				// ���� �̸��� ī�װ� �ִ��� �ߺ� �˻�. (������ �ǳʶٱ�).
				continue;
			}
			
			category* ptr_cate = NULL;
			ptr_cate = ptr_cate->create_cate(imsi_name);		// ī�װ� ��ü ���� �� ���Ḯ��Ʈ�� �߰�.
			
			add_to_cate(ptr_cate);
		}
		else if (s[0] == '#') {								// �� �� ������.

			string imsi_todo = s.substr(1, s.size());			// '#' ���� ����.
			load_add_todo(imsi_todo);							// �о�� �� �� �߰� �Լ�.
		}

	}
	cout << "\t�ҷ����� ����!!" << endl << endl;
	fp.close();
}

void load_add_todo(string imsi_todo) {									// load()���� �о�� �� �� �߰� �Լ�.
	
	string cate, title, month, date, detail;

	split(imsi_todo, cate);									 // split �Լ��� �ּҸ� �޾� ���忡�� �ʿ��� �͵� ����.
	split(imsi_todo, title);
	split(imsi_todo, month);
	split(imsi_todo, date);
	split(imsi_todo, detail);

	string time = month;
	time.append(date);

	category* ptr_cate = search_cate(cate);							// �о�� ������ category�� ã��.

	if (ptr_cate == NULL) {											// ����ó�� null
		cout << "\t�޸��忡 �߸� �����̽��ϴ�." << endl;
		return;
	}

	todo* ptr_todo = NULL;
	ptr_todo = ptr_todo->create_todo(title, time, detail);						// ���� ��ü ����.

	sort_todo_to_cate(ptr_todo, ptr_cate->get_cate_index());
}

void split(string& imsi_todo, string& s) {										// load()�Լ����� �� �� ���忡�� �ʿ��� ������ �����ϴ� �Լ�.

	int length = imsi_todo.find("#");								// ������ "#";
	s = imsi_todo.substr(0, length);

	imsi_todo = imsi_todo.substr(length + 1, imsi_todo.size());
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

void show_important() {															// �߿��� �� ī�װ�(�׻� 2�� ī�װ�)�� ����ϴ� �Լ�.

	cout << "�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�" << endl;
	cout << "\t(�׻� 2��° ī�װ��� ����ŵ�ϴ�.)" << endl << endl;
		
	category* p = search_cate(2);

	if (p == NULL) {													// ���� ó��.						
		cout << "\t�߿��� ī�װ��� �����ϴ�." << endl;
	}
	
	show_cate_todos(p);

	cout << "�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�" << endl << endl << endl;
}

void show_all() {																// ��� ī�װ��� �� �ϵ��� ����ϴ� �Լ�.
	category* p = cate_struct.cate_tail;

	if (p == NULL) {										// ���� ó��
		cout << "\t�� ���� �����ϴ�." << endl << endl;
	}

	while (p != NULL) {
		show_cate_todos(p);
		p = p->get_prev_cate();
	}
}

void search_todo() {															// �� ���� ã�� �Լ�.
	// ī�װ����� ����� ���.
	// ī�װ��� ��ȣ�� �Է��ϸ� �� ī�װ��� �� �ϵ��� ����� ��ȣ�� �Բ� ���.

	category* p = select_cate();			

	show_cate_todos(p);
}

todo* remove_search_todo(category* p) {											// ����� ���� �� ���� ã�� �Լ�.

	show_cate_todos(p);

	// �ϴ� �׻� ����� �Է� ����.
	int num;
	while (true) {
		cout << "\t������ todo�� ��ȣ �Է� " << endl;
		cout << "\t(������� �ƹ� ���� �Է�) :";
		cin >> num;

		if (num <= 0) {
			cout << "\t�߸��Է�" << endl;
			continue;
		}
		break;
	}

	// todo���� n��ŭ ��ȸ�ϴ� �� ���� todo �����Ͱ� null�� �Ǹ� �� ã�� ����.
	todo* ptr_todo = p->get_first_todo();
	int i = 1;
	while (ptr_todo != NULL && i < num) {					// num ��ŭ todo�� ��ȸ. 
		i++;
		ptr_todo = ptr_todo->get_next_todo();
	}

	if (ptr_todo == NULL) {
		cout << "�Է��� ��ȣ�� �� ���� �����ϴ�." << endl;
		return NULL;
	}

	return ptr_todo;
}

void remove_todo() {															// �� ���� ����� �Լ�.

	category* ptr_cate = select_cate();					// ī�װ� ��� ��� �� �ʿ��� ī�װ��� �ּ� ����.

	if (ptr_cate == NULL) {
		cout << "\t���� ����!!" << endl << endl;		// ���� ó��.
		return;
	}

	todo* p = remove_search_todo(ptr_cate);				// ���� todo�� ã�� �� �ּҸ� ��ȯ.

	if (p == NULL) {									// ���� ó��.
		cout << "\t���� ����!!" << endl << endl;
		return;
	}
	
	todo* p_next = p->get_next_todo();					// ���� �� ���� ������ ���� �ּ�.
	todo* p_prev = p->get_prev_todo();
	
	// ����� ���
	// ���Ḯ��Ʈ��
	// 1. ������ ���.		2. �� ���� ���.		3. �� ���� ���.		4. �߰��� �ִ� ���.

	if (p_next == NULL && p_prev == NULL) {								// 1. ������ ���.
		ptr_cate->set_first_todo(NULL);
	}
	else if (p_prev == NULL && ptr_cate->get_first_todo() == p) {		// 2. �� ���� ���.
		// p_next->prev�� null�� �׸��� 
		p_next->set_prev_todo(NULL);
		ptr_cate->set_first_todo(p_next);
	}
	else if (p_next == NULL) {											// 3. �� ���� ���.
		p_prev->set_next_todo(NULL);
	}
	else {																// 4. �߰��� �ִ� ���.
		p_prev->set_next_todo(p_next);
		p_next->set_prev_todo(p_prev);
	}
	string title = p->get_title();
	delete(p);
	cout << "\t" << title << " ���� ����" << endl << endl;
}

string set_todo_title() {														// �� ���� ������ �Է¹޴� �Լ�.(�� ĭ�� ����).

	string title;

	// �� �� �Է�.
	int first = 0;									// ó���� �Է¹��� ����⸦ �����ϱ� ���� ����.
	while (1) {

		cout << "	�� ���� �����ּ���.(ù ���� ����x): ";

		if (first == 0) {
			getchar();								// �Է¹��� ����.
			first++;
		}
		getline(cin, title);

		if (title.empty() || title[0] == ' ') {
			cout << "\t�Է��� �����ϴ�.\n" << endl;
			continue;
		}
		break;
	}
	return title;									// �� ���� ���� ��ȯ.
}

string set_todo_time() {														// �� ���� �ð��� �Է¹޴� �Լ�.

	// ���� ���� ���� �޾Ƽ� �˻�.
	// �Ŀ� string.append�� ���ļ� time�� �Է�.

	string time;
	while (1) {

		bool check = true;											// ����� �� month�� date�� ���� �Է��ߴ��� Ȯ���� ����.

		string month;
		cout << "\t�������� ���� �Է�(01~12) : ";					// month �Է� (00 ~ 12);
		cin >> month;

		if (month.size() != 2)
			check = false;

		if (month[0] != '0' && month[0] != '1' && month[1] >= '0' && month[1] <= '9')
			check = false;

		if ((month[0] == '1' && month[1] > '2') || (month[0] == '0' && month[1] == '0'))
			check = false;

		if (check == false) {
			cout << "\t�߸� �Է�" << endl;	continue;
		}
		
		string date;
		cout << "\t�������� ���� �Է�(01~31) : ";					// date �Է� (00 ~ 31);
		cin >> date;

		if (date.size() != 2)
			check = false;

		if (!(date[0] >= '0' && date[0] <= '3') && !(date[1] >= '0' && date[1] <= '9'))
			check = false;
		
		if ((date[0] == '3' && date[1] > '1')|| (date[0] == '0' && date[1] == '0'))
			check = false;

		if (check == false) {
			cout << "\t�߸� �Է�" << endl;	continue;
		}

		if (month == "02") {														// 2�� �˻�.
			if (date == "29" || date == "30" || date == "31") {
				cout << "\t2���� 28�ϱ��� " << endl;	continue;
			}
		}

		if (month == "04" || month == "06" || month == "09" || month == "11") {		// 30�� �˻�.
			if (date == "31") {
				cout << "\t" << month << "�� 30�ϱ��� " << endl;	continue;
			}
		}
		
		time = month;
		time.append(date);		
		return time;																// ���� �ð� ��ȯ.
	}
}

string set_todo_detail() {																	// ���λ��� �Է� �Լ�.
	string detail;
	cout << "\t�ڼ��� ������ �����ּ���.:";

	getchar();										// �Է� ���� �����.
	getline(cin, detail);

	return detail;									// ���λ��� ��ȯ.
}

void create_todo() {																		// �� �� ���� �Լ�.
	
	cout << "\t1. �� �� �߰�." << endl;

	string title = set_todo_title();
	string time = set_todo_time();
	string detail = set_todo_detail();

	todo* ptr_todo = NULL;
	ptr_todo = ptr_todo->create_todo(title, time, detail);				// �� �� ����.

	if (ptr_todo == NULL) {												// ����ó��.
		cout << "\t�� �� �߰� ����!!" << endl << endl;
	}

	// ���� ī�װ����� ����� ���.
	// �� ���� �� ī�װ��� ����.
	
	int n;
	while (1) {
		
		show_cate_list();										// ���� ī�װ��� ����� ���.
		cout << "\t������ �߰��� ī�װ��� ��ȣ�� �Է����ּ���.: ";
		cin >> n;

		if (cate_struct.size == 0) {
			cout << "\tī�װ� ����� ������ϴ�. ī�װ��� ���� ����� �ּ���." << endl << endl;
			// ���⿡ ī�װ��� �߰��ϴ� �Լ��� ����.
			create_category();

			// 

			continue;
		}
		if (n <= 0 || n > cate_struct.size) {
			cout << "\t�߸� �Է�!!" << endl;
			continue;
		}
		break;
	}

	sort_todo_to_cate(ptr_todo, n);							// ������ todo ��ü�� ī�װ��� ��ȣ�� �Ű������� ī�װ��� ���ĵǾ� �Է�.
	cout << "\t�� �� �߰� ����!!" << endl << endl;
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

void show_cate_todos(category* ptr_cate) {											// ī�װ��� ����� �� �ϵ��� ������ִ� �Լ�.

	if (ptr_cate== NULL) {															// ���� ó��.
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