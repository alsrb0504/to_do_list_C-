#include "command.h"
#include "category.h"
#include <iostream>
using namespace std;


void start_program();									// ���� ���� ���α׷��� �����ϴ� �Լ�.
void menu();											// �ʱ� �޴�ȭ���� ������ִ� �Լ�.
void cate_menu();										// ī�װ� ���� ó���� �����ϴ� �Լ�.
void todo_menu();										// �� �� ���� ó���� �����ϴ� �Լ�.


int main() {

	init_setting();										// �ʱ� ���� ( 1.�̺з�		2.�߿�  ī�װ� ����) ����.

	start_program();									// ���� ���� ���α׷� ����.
}

void start_program() {																	// ���� ���� ���α׷�.

	while (1) {
		menu();											// �ʱ� �޴� ���.

		int command = 0;								// ����� �����ϱ� ���� ����.

		if (cin.fail()) {								// ���� ó�� : ���ڰ� �ƴ� ���ڸ� �Է����� ��, ���ѷ��� ����.
			cin.clear();
			cin.ignore(256, '\n');
		}

		cout << "���� �Է�: ";
		cout << "$: ";
		cin >> command;

		if (command == 1) {													// (1) >> �߿��� ī�װ�(�׻� 2�� category)�� ���.
			cout << "(1) >>  �߿� ī�װ� ���� ����" << endl << endl;
			show_important();
		}	
		else if (command == 2) {											// (2) >> category �޴��� ����.
			cout << "(2) >>  ī�װ� �޴� ����" << endl << endl;
			cate_menu();
		}
		else if (command == 3) {											// (3) >> todo �޴��� ����.
			cout << "(3) >>  �� �� �޴� ����" << endl << endl;
			todo_menu();
		}
		else if (command == 4) {											// (4) >> ��� category�� todo�� ���.
			cout << "(4) >>  ��� ī�װ��� �� �� ���� ����" << endl << endl;
			show_all();
		}
		else if (command == 5) {											// (5) >> to_do_list.txt�� ����� ī�װ��� �� �ϵ��� �Է�.
			cout << "(5) >>  ���Ͽ��� �ҷ����� ����" << endl << endl;
			load();
		}
		else if (command == 6) {											// (6) >> to_do_list.txt�� �ֿܼ��� �ٷ� ī�װ��� �� �ϵ��� ����.
			cout << "(6) >>  ���Ͽ� �����ϱ� ����" << endl << endl;
			save();
		}
		else if (command == 10) {											// (10) >> ���α׷� ����.
			cout << "(10) >>  ���α׷��� �����մϴ�." << endl << endl;
			exit(-1);
		}
		else {
			cout << "�߸� �Է��߽��ϴ�. �ٽ� �Է����ּ���." << endl << endl;
			continue;
		}
	}
}

void menu() {																		// �ʱ� �޴�ȭ���� ������ִ� �Լ�.
	cout << "\t\tTo_Do_List_Program" << endl;
	cout << "==========================================================" << endl;
	cout << "\t\t��ɾ� ���:" << endl << endl;
	cout << "\t\t(1) >> �߿��� �� ����" << endl;
	cout << "\t\t(2) >> category menu" << endl;
	cout << "\t\t(3) >> todo menu" << endl;
	cout << "\t\t(4) >> all list" << endl;
	cout << "\t\t(5) >> ���� �ҷ�����" << endl;
	cout << "\t\t(6) >> ���� �����ϱ�" << endl;
	cout << "\t\t(10) >> exit" << endl << endl;;
	cout << "==========================================================" << endl << endl;
}

void cate_menu() {																	// ī�װ� ���� ó���� �����ϴ� �Լ�.
																					// ������ ��� ���� �� cate_menu �ʱ�ȭ������ ���ư�.
	while (1) {
		cout << "\t\tCategory Menu" << endl;
		cout << "==========================================================" << endl;

		cout << "\t\tCategory ��ɾ� ���:" << endl << endl;
		cout << "\t\t(1) >> ī�װ� �߰�" << endl;
		cout << "\t\t(2) >> ī�װ� ����" << endl;
		cout << "\t\t(3) >> ī�װ� ����" << endl;
		cout << "\t\t(4) >> ī�װ� ��� ����" << endl;
		cout << "\t\t(5) >> ó��ȭ������ ���ư���" << endl << endl;

		cout << "==========================================================" << endl;
		cout << "category_command" << endl;
		cout << "���� �Է�: $: ";

		if (cin.fail()) {						// ���� ó�� : ���ڰ� �ƴ� ���ڸ� �Է����� ��, ���ѷ��� ���� ����.
			cin.clear();
			cin.ignore(256, '\n');
		}

		category* p = NULL;						// ī�װ� Ŭ������ ��� �Լ����� ȣ���ϱ� ���� ����.

		int category_command;
		cin >> category_command;

		if (category_command == 1) {												// (1) >> ī�װ� ���� �Լ�.
			cout << "(1) >>  ī�װ� ���� ����" << endl << endl;
			p->create_cate();
		}
		else if (category_command == 2) {											// (2) >> ���߿� show_categorys �� ����
			cout << "(2) >>  ī�װ� ���� ����" << endl << endl;
			p->show_category();
		}
		else if (category_command == 3) {											// (3) >> ī�װ� ���� �Լ�.
			cout << "(3) >>  ī�װ� ���� ����" << endl << endl;
			p->remove_category();
		}
		else if (category_command == 4) {											// (4) >> ���� category���� �̸��� ���.
			cout << "(4) >>  ī�װ� ��� ���� ����" << endl << endl;
			p->show_cate_list();
		}
		else if (category_command == 5) {											// (5) >> ���α׷� ���� ȭ������ ���ư�.
			cout << "\t�ʱ� �޴��� ���ư��ϴ�." << endl << endl;
			cout << "==========================================================" << endl;
			break;
		}
		else {
			cout << "�߸� �Է��߽��ϴ�. �ٽ� �Է����ּ���." << endl << endl;
			continue;
		}
	}
}

void todo_menu() {													// �� �� ���� ó���� �����ϴ� �Լ�.
																	// ������ ��� ���� �� todo_menuȭ������ ���ư�.
	while (1) {
		cout << "\t\tTo_Do_Menu" << endl;
		cout << "==========================================================" << endl;

		cout << "\t\tTo_Do_Menu ��ɾ� ���:" << endl << endl;
		cout << "\t\t(1) >> �� �� �߰�" << endl;
		cout << "\t\t(2) >> �� �� �˻�" << endl;
		cout << "\t\t(3) >> �� �� ����" << endl;
		cout << "\t\t(4) >> ó��ȭ������ ���ư���" << endl << endl;

		cout << "==========================================================" << endl;
		cout << "todo_command" << endl;
		cout << "���� �Է�: $: ";

		if (cin.fail()) {								// ���� ó�� : ���ڰ� �ƴ� ���ڸ� �Է����� ��, ���ѷ��� ���� ����.
			cin.clear();
			cin.ignore(256, '\n');
		}

		todo* p = NULL;					// todo Ŭ������ ��� �Լ� ȣ���� ���� ����.

		int todo_command;
		cin >> todo_command;

		if (todo_command == 1) {												// (1) >> �� �� ����.
			cout << "(1) >> �� �� ���� ����" << endl << endl;
			p->create_todo();
		}
		else if (todo_command == 2) {											// (2) >> �� �� ã��.
			cout << "(2) >> �� �� �˻� ����" << endl << endl;
			p->search_todo();
		}
		else if (todo_command == 3) {											// (3) >> �� �� ����.
			cout << "(3) >> �� �� ���� ����" << endl << endl;
			p->remove_todo();
		}
		else if (todo_command == 4) {											// (4) >> ���α׷� ���� ȭ������ ���ư�.
			cout << "\t�ʱ� �޴��� ���ư��ϴ�." << endl << endl;
			break;
		}
		else {
			cout << "�߸� �Է��߽��ϴ�. �ٽ� �Է����ּ���." << endl << endl;
			continue;
		}
	}
}