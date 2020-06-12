#define  _CRT_SECURE_NO_WARNINGS

#include "command.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;



category* cate;								// ī�װ� Ŭ���� ���� �Լ����� ����ϱ� ���� ���� ������.

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



void show_important() {															// �߿��� �� ī�װ�(�׻� 2�� ī�װ�)�� ����ϴ� �Լ�.

	cout << "�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�" << endl;
	cout << "\t(�׻� 2��° ī�װ��� ����ŵ�ϴ�.)" << endl << endl;
		
	category* p = search_cate(2);

	if (p == NULL) {													// ���� ó��.						
		cout << "\t�߿��� ī�װ��� �����ϴ�." << endl;
	}
	
	cate->show_cate_todos(p);

	cout << "�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�" << endl << endl << endl;
}

void show_all() {																// ��� ī�װ��� �� �ϵ��� ����ϴ� �Լ�.
	category* p = cate_struct.cate_tail;

	if (p == NULL) {										// ���� ó��
		cout << "\t�� ���� �����ϴ�." << endl << endl;
	}

	while (p != NULL) {
		cate->show_cate_todos(p);
		p = p->get_prev_cate();
	}
}

void search_todo() {															// �� ���� ã�� �Լ�.
	// ī�װ����� ����� ���.
	// ī�װ��� ��ȣ�� �Է��ϸ� �� ī�װ��� �� �ϵ��� ����� ��ȣ�� �Բ� ���.

	category* p = cate->select_cate();

	cate->show_cate_todos(p);
}

todo* remove_search_todo(category* p) {											// ����� ���� �� ���� ã�� �Լ�.

	cate->show_cate_todos(p);

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

	category* ptr_cate = cate->select_cate();					// ī�װ� ��� ��� �� �ʿ��� ī�װ��� �ּ� ����.

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

			string imsi_name = s.substr(1, s.size());		// '@' ���� ����.

			if (!(cate_name_overlap(imsi_name))) {			// ���� �̸��� ī�װ� �ִ��� �ߺ� �˻�. (������ �ǳʶٱ�).
				continue;
			}

			category* ptr_cate = NULL;
			ptr_cate = ptr_cate->create_cate(imsi_name);	// ī�װ� ��ü ���� �� ���Ḯ��Ʈ�� �߰�.

			add_to_cate(ptr_cate);
		}
		else if (s[0] == '#') {								// �� �� ������.

			string imsi_todo = s.substr(1, s.size());		// '#' ���� ����.
			load_add_todo(imsi_todo);						// �о�� �� �� �߰� �Լ�.
		}
	}
	cout << "\t�ҷ����� ����!!" << endl << endl;
	fp.close();
}

void load_add_todo(string imsi_todo) {											// load()���� �о�� �� �� �߰� �Լ�.

	string cate, title, month, date, detail;

	split(imsi_todo, cate);											 // split �Լ��� �ּҸ� �޾� ���忡�� �ʿ��� �͵� ����.
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
	ptr_todo = ptr_todo->create_todo(title, time, detail);			// ���� ��ü ����.

	sort_todo_to_cate(ptr_todo, ptr_cate->get_cate_index());		// ī�װ��� ����.
}

void split(string& imsi_todo, string& s) {										// load()�Լ� �� �� ���忡�� �ʿ��� ������ �����ϴ� �Լ�.

	int length = imsi_todo.find("#");								// ������ "#";
	s = imsi_todo.substr(0, length);

	imsi_todo = imsi_todo.substr(length + 1, (imsi_todo.size()- length));
}

void save() {																	// ���� ���� �Լ�.

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
		string print_cate = "@";										// ���Ͽ� ī�װ� ���.
		print_cate.append(ptr_cate->get_cate_name());					// "@ī�װ��̸�" ���
		print_cate.append("\n");
		fp.write(print_cate.c_str(), print_cate.size());

		todo* ptr_todo = ptr_cate->get_first_todo();
		while (ptr_todo != NULL) {										// ���Ͽ� ī�װ��� �� �� ���.
			string print_todo = save_to_todo(ptr_todo, ptr_cate);		// ����� ���� ���� �Լ�.
			fp.write(print_todo.c_str(), print_todo.size());			// "#ī�װ���#����#��#��#���λ���#" ���� ���.

			ptr_todo = ptr_todo->get_next_todo();
		}

		ptr_cate = ptr_cate->get_prev_cate();
	}
	cout << "\t�����ϱ� ����!!" << endl << endl;
	fp.close();
}

string save_to_todo(todo* p, category* ptr_cate) {								// save()���� ����� �� �� ���� ���� �Լ�.

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