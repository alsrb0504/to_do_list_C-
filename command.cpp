#include "command.h"
#include <iostream>
#include <fstream>

using namespace std;

void init_setting() {						// �ʱ� ���� ( ����ü �ʱ�ȭ ��  1.�̺з�		2.�߿� category ����).

	category* p = NULL;
	p = p->create_cate("�̺з�");			// 1�� �̺з� ī�װ� ����.
	p->add_to_cate(p);

	p = p->create_cate("�߿�");				// 2�� �߿� ī�װ� ����.
	p->add_to_cate(p);

	cout << "�ʱ� ����: " << endl;
	cout << "1�� ī�װ��� \"�̺з�\" 2�� ī�װ��� \"�߿�\"�� ����" << endl << endl;
}


void show_all() {																// ��� ī�װ��� �� �ϵ��� ����ϴ� �Լ�.
	category* p = p->cate_head;

	if (p == NULL) {															// ���� ó�� : ī�װ��� �ϳ��� ���� ���.
		cout << "\t�� ���� �����ϴ�. ������ �߰����ּ���." << endl << endl;
		return;
	}

	while (p != NULL) {
		p->show_cate_todos(p);

		p = p->get_next_cate();
	}
}


void show_important() {															// �߿� ī�װ�(�׻� 2�� ī�װ�)�� ����ϴ� �Լ�.
																				// 2�� ī�װ��� "�߿�"�� �ƴϴ��� ���� 2�� ī�װ��� ���.
	cout << "�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�" << endl;
	cout << "\t(�׻� 2��° ī�װ��� ����ŵ�ϴ�.)" << endl << endl;

	category* p = p->cate_head;

	if (p == NULL) {															// ���� ó�� : ī�װ��� �ϳ��� ���� ���.
		cout << "���� ī�װ��� �����ϴ�. ī�װ��� ���� �߰����ּ���. " << endl << endl;
	}

	p = p->get_next_cate();												// 2��° ī�װ��� �ּҸ� ����.

	if (p == NULL) {															// ���� ó�� : 2�� ī�װ��� ���� ���.					
		cout << "\t�߿��� ī�װ��� �����ϴ�." << endl << endl;
	}

	p->show_cate_todos(p);

	cout << "�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�" << endl << endl << endl;
}


void load() {																				// ���� �ҷ����� �Լ�.

	ifstream fp("to_do_list.txt");						// �б�� ��ü ����.

	if (!(fp.is_open())) {								// ���� ó�� : ���� ���� ����.
		cout << "not found file. " << endl;
		return;
	}

	string s;
	category* ptr_cate = NULL;							// ī�װ� �Լ����� �ٷ�� ���� ����.

	while (fp) {
		getline(fp, s);

		if (s[0] == '@') {									// ī�װ� ������.

			string imsi_name = s.substr(1, s.size());					// '@' ���� ����.

			if (!(ptr_cate->cate_name_overlap(imsi_name))) {			// ���� �̸��� ī�װ� �ִ��� �ߺ� �˻�. (������ �ǳʶٱ�).
				continue;
			}
			ptr_cate = ptr_cate->create_cate(imsi_name);				// ī�װ� ��ü ���� �� ���Ḯ��Ʈ�� �߰�.

			ptr_cate->add_to_cate(ptr_cate);
		}
		else if (s[0] == '#') {								// �� �� ������.

			string imsi_todo = s.substr(1, s.size());					// '#' ���� ����.
			load_add_todo(imsi_todo);									// �о�� �� �� �߰� �Լ�.
		}
	}
	cout << "\t�ҷ����� ����!!" << endl << endl;
	fp.close();
}


void load_add_todo(string imsi_todo) {											// load()���� �о�� �� �� ����(imsi_todo) �߰� �Լ�.

	string cate, title, month, date, detail;

	split(imsi_todo, cate);									 // split �Լ��� �ּҸ� �޾� ���忡�� �ʿ��� �͵� ����.
	split(imsi_todo, title);
	split(imsi_todo, month);
	split(imsi_todo, date);
	split(imsi_todo, detail);

	int check = atoi(month.c_str());
	string time;
	category* ptr_cate = NULL;

	try {														// �о�� ������ �����ϰ� ī�װ� �� �˻�.
		if (check <= 0 || check > 12)							// ���� : ���� 1~12�� �ƴ� ���.
			throw - 1;

		check = atoi(date.c_str());

		if (check <= 0 || check > 31)							// ���� : ���� 1~31���� �ƴ� ���.
			throw - 1;

		time = month;
		time.append(date);

		ptr_cate = search_cate(cate);							// �о�� ������ category�� ã��.

		if (ptr_cate == NULL)									// ���� : ī�װ����� �߸��� ���.
			throw - 2;
	}
	catch (int x) {																				// ���� ó�� : �߰� ������ ������ �˷���.
		cout << "\t\"" << title << "\"�� �ִ� �����ִ� ������ load���� ���߽��ϴ�." << endl;
		cout << "\tsave�� �����ϸ� �� ������ ����ϴ�. " << endl;
		return;
	}

	todo* ptr_todo = NULL;
	ptr_todo = ptr_todo->create_todo(title, time, detail);		// ���� ��ü ����.

	ptr_cate->sort_todo_to_cate(ptr_todo, ptr_cate);			// ī�װ��� ����.
}


void split(string& imsi_todo, string& s) {										// load()�Լ� �� �� ���忡�� �ʿ��� ������ �����ϴ� �Լ�.

	int length = imsi_todo.find("#");								// ������ "#";
	s = imsi_todo.substr(0, length);

	imsi_todo = imsi_todo.substr(length + 1, (imsi_todo.size() - length));
}


category* search_cate(string name) {											// ī�װ� �̸��� ������ ī�װ��� ã�� �Լ�.

	category* p = p->cate_head;

	if (p == NULL) {									// ���� ó�� : ī�װ��� �� ���.
		cout << "\tī�װ��� ������ϴ�." << endl;
		return NULL;
	}

	while (p != NULL) {
		if (name == p->get_cate_name()) {
			return p;
		}
		p = p->get_next_cate();
	}
	return NULL;										// �� ã�� ���.(��� ��� ��ȯ ��� �޽��� ������).
}


void save() {																	// ���� ���� �Լ�.

	ofstream fp("to_do_list.txt");

	if (!(fp.is_open())) {												// ���� ó�� : ���� ���⸦ ������ ���.
		cout << "not found file. " << endl;
		return;
	}

	category* ptr_cate = ptr_cate->cate_head;

	if (ptr_cate == NULL) {												// ���� ó�� : ���� ī������ ����� ���(������ ���� ���� ���).
		cout << "\tī�װ��� �����ϴ�. �����ϱ� ����!!" << endl;
		return;
	}

	while (ptr_cate != NULL) {
		string print_cate = "@";										// ���Ͽ� ī�װ� ���.
		print_cate.append(ptr_cate->get_cate_name());					// "@ī�װ��̸�" ��� ����.
		print_cate.append("\n");
		fp.write(print_cate.c_str(), print_cate.size());

		todo* ptr_todo = ptr_cate->get_first_todo();
		while (ptr_todo != NULL) {										// ���Ͽ� ī�װ��� �� �� ���.
			string print_todo = save_to_todo(ptr_todo, ptr_cate);		// ����� ���� ���� �Լ�.
			fp.write(print_todo.c_str(), print_todo.size());			// "#ī�װ���#����#��#��#���λ���#" ���� ���.

			ptr_todo = ptr_todo->get_next_todo();
		}
		ptr_cate = ptr_cate->get_next_cate();
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