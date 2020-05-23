#include "command.h"

#include <iostream>
using namespace std;


void read_command();
void cate_menu();
void todo_menu();

void menu();

int main() {

	init_setting();

	read_command();
	

}

void read_command() {

	int command;										// ����� �����ϱ� ���� ����.

	while (1) {
		menu();
		cout << "���� �Է�: ";
		cout << "$: ";
		cin >> command;

		if (command == 1) {								// ���߿� �߿��� �� ����� �ٲ� ����.
			show_important();
		}
		else if (command == 2) {
			cate_menu();
		}
		else if (command == 3) {
			todo_menu();
		}
		else if (command == 4) {
			show_all();
		}
		else if (command == 5) {
			load();
		}
		//else if (command == "save") {
		//	save();
		//}

		else if (command == 10) {
			return;
		}

	}

}

void menu() {												 // 4. all list �κ� �����ؾ� ��.
	cout << "\t\tTo_Do_List_Program" << endl;
	cout << "==========================================================" << endl;
	cout << "\t\t��ɾ� ���: \n\t\t1. �߿��� �� ����	\n\t\t2. category\n\t\t3. todo\n\t\t4. all list\n\t\t5. ���� �ҷ�����\n\t\t10. exit\n" << endl;
	cout << "==========================================================" << endl;

}

void cate_menu() {					// cate_menu ���â ���� ��, ������ ������� ���� �� �ʱ�ȭ������ ���ư�.

	while (1) {
		cout << "\t\tCategory Menu" << endl;
		cout << "==========================================================" << endl;
		cout << "\t\t Category ��ɾ� ���: \n\t\t1. ī�װ� �߰�\n\t\t2. ī�װ� ����"
			<< "\n\t\t3. ī�װ� ����\n\t\t4. ī�װ� ��� ����\n\t\t5. ó��ȭ������ ���ư���\n\t\t" << endl;
		cout << "==========================================================" << endl;
		cout << "category_command" << endl;
		cout << "���� �Է�: $: ";

		int category_command;
		cin >> category_command;

		if (category_command == 1) {					// ī�װ� ���� �Լ�.
			create_category();
		}
		else if (category_command == 2) {				// ���߿� show_categorys �� ����
			show_category();
		}
		else if (category_command == 3) {				// ī�װ� ���� �Լ�.
			remove_category();
		}
		else if (category_command == 4) {
			show_cate_list();
		}
		else if (category_command == 5) {
			cout << "\t�ʱ� �޴��� ���ư��ϴ�." << endl << endl;
			cout << "==========================================================" << endl;
			break;
		}
		else {
			cout << "�߸� �Է��߽��ϴ�. �ٽ� �Է����ּ���." << endl;
			continue;
		}
	}
}

void todo_menu() {						// todo ���â ���� ��, ������ ������� ���� �� todo_menuȭ������ ���ư�.
										// �߿������� ��ȯ �߰��ұ�??
	while (1) {
		cout << "\t\tTo_Do_Menu" << endl;
		cout << "==========================================================" << endl;
		cout << "\t\t To_Do_Menu ��ɾ� ���: \n\t\t1. �� �� �߰�\n\t\t2. �� �� ����(ī�װ��� �̵�)"
			<< "\n\t\t3. �� �� ����\n\t\t4. (�߿��� �� �� ����)\n\t\t5. ó��ȭ������ ���ư���\n\t\t" << endl;
		cout << "==========================================================" << endl;
		cout << "todo_command" << endl;
		cout << "���� �Է�: $: ";

		int todo_command;
		cin >> todo_command;

		if (todo_command == 1) {
			create_todo();
		}
		else if (todo_command == 2) {
			search_todo();
		}
		else if (todo_command == 3) {
			remove_todo();
		}
		else if (todo_command == 4) {
			show_important();
		}
		else if (todo_command == 5) {
			cout << "\t�ʱ� �޴��� ���ư��ϴ�." << endl << endl;
			break;
		}
	}
}