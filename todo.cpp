#include "todo.h"
#include "category.h"
#include <iostream>


todo::todo(string title, string due_date, string detail) {					// ������.
	this->title = title;
	this->due_date = due_date;
	this->detail = detail;
	next = NULL;
	prev = NULL;
}

todo* todo::create_todo(string title, string due_date, string detail)			// todo ��ü ���� �Լ�.
{
	todo* ptr_todo = new todo(title, due_date, detail);							// todo ��ü ���� ����.

	return ptr_todo;
}

todo* todo::get_next_todo() {					// ���� �ּ� ��ȯ
	return next;
}

void todo::set_next_todo(todo* p) {				// ���� �ּ� �Է�.
	this->next = p;
}

string todo::get_due_data() {					// ������ ��ȯ
	return due_date;
}

todo* todo::get_prev_todo() {					// ���� �ּ� ��ȯ
	return prev;
}

void todo::set_prev_todo(todo* p) {				// ���� �ּ� �Է�.
	this->prev = p;
}

string todo::get_title() {						// ���� ��ȯ �Լ�.
	return title;
}

string todo::get_detail() {						// ���λ��� ��ȯ.
	return detail;
}

void todo::create_todo() {																		// �� �� ���� �Լ�.

	category* p = NULL;			// ī�װ� �Լ����� �ٷ�� ���� ��ü ����.

	if (p->cate_num == 0) {														// ����ó�� : ī�װ��� �ϳ��� ���ٸ� �� ���� ���� �� ����.
		cout << "ī�װ��� ������ϴ�. ī�װ��� ���� �����ϼ���." << endl << endl;
		cout << "==========================================================" << endl;
		
		return;
	}
	 
	cout << "\t1. �� �� �߰�." << endl;

	rewind(stdin);														// �Է¹��۸� ����� ����.

	string title = set_todo_title();									// �ʿ��� ������(title, duedata, detail)�� �޴� ����.
	string time = set_todo_time();
	string detail = set_todo_detail();

	todo* ptr_todo = NULL;
	ptr_todo = ptr_todo->create_todo(title, time, detail);				// �� �� ���� ��ü ����.

	if (ptr_todo == NULL) {												// ����ó�� : todo ��ü ���� ����.
		cout << "\t�� �� �߰� ����!!" << endl << endl;
	}

	p->show_cate_list();												// ī�װ� ��ϵ� ���

	while (true) {

		cout << "�� ���� �߰��� ī���ڸ��� ��ȣ�� �Է����ּ���.: ";
		p= p->search_cate();


		if (p == NULL) {												// ����ó�� : ��ȣ �߸� �Է� ��.
			cout << "�ٽ� �Է����ּ��� " << endl;						// �ٽ� �Է��ش޶� �ϰ� ����� �� �� �Է¹��� ������ �ݺ�.
			continue;
		}
		break;
	}

	p->sort_todo_to_cate(ptr_todo, p);									// ������ todo ��ü�� ī�װ��� todo ���Ḯ��Ʈ�� ������ ������ ����.

	cout << "\t�� �� �߰� ����!!" << endl << endl;
}

string todo::set_todo_title() {														// �� ���� ������ �Է¹޴� �Լ�.(�� ĭ�� ����).

	string title;

	while (1) {

		cout << "	�� ���� �����ּ���.(ù ���� ����x): ";

		getline(cin, title);

		if (title.empty() || title[0] == ' ') {				
			cout << "\t�Է��� �����ϴ�.\n" << endl;
			continue;
		}
		break;
	}
	return title;									// �� ���� ���� ��ȯ.
}

string todo::set_todo_time() {														// �� ���� �ð��� �Է¹޴� �Լ�.

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

		if ((date[0] == '3' && date[1] > '1') || (date[0] == '0' && date[1] == '0'))
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

string todo::set_todo_detail() {																	// ���λ��� �Է� �Լ�.
	string detail;
	cout << "\t�ڼ��� ������ �����ּ���.:";

	getchar();										// �Է� ���� �����.
	getline(cin, detail);

	return detail;									// ���λ��� ��ȯ.
}

void todo::remove_todo() {															// �� ���� ����� �Լ�.

	category* ptr_cate = NULL;						

	ptr_cate->show_cate_list();						// ī�װ� ��ϵ� ���.


	cout << "���� �� ���� ����ִ� ī�װ��� ��ȣ�� �Է��ϼ���. :";
	ptr_cate = ptr_cate->search_cate();

	if (ptr_cate == NULL) {
		cout << endl << "\t���� ����(ī�װ��� �����ϴ�.)" << endl << endl;			// ���� ó�� : ī�װ��� ���ų� �Է��� ��ȣ�� �߸� �Ǿ��� ���.
		cout << "==========================================================" << endl;
		return;
	}

	ptr_cate->show_cate_todos(ptr_cate);												// ���� ī�װ��� ����� �� �ϵ��� ����� ���.

	if (ptr_cate->get_todo_num() == 0) {												// ���� ó�� : ����� �� ���� ������ 0���̸� ��� ���.
		cout << "\t���� ����(todo ���� ����)" << endl << endl;
		cout << "==========================================================" << endl;
		return;
	}

	int num;
	while (true) {
		cout << "\t������ todo�� ��ȣ �Է�(���: 0) :";
		cin >> num;

		if (num == 0) {															// ���� ó�� : 0 �Է� �� ���� ���.
			return;
		}

		if (num < 0 || num > ptr_cate->get_todo_num()) {						// ���� ó�� : �߸��� �� �Է� �� ����� �� �� ���� ������ �ݺ�.
			cout << "\t�߸��Է��߽��ϴ�. �ٽ� �Է��� �ּ���." << endl;
			continue;
		}
		break;
	}

	// todo���� num ��ŭ ��ȸ�Ͽ� ���� todo�� ã��.
	todo* ptr_todo = ptr_cate->get_first_todo();
	int i = 1;
	while (ptr_todo != NULL && i < num) {						// num ��ŭ todo ���Ḯ��Ʈ ��ȸ. 
		i++;
		ptr_todo = ptr_todo->get_next_todo();
	}

	todo* p_next = ptr_todo->get_next_todo();					// ���� �� ���� ������ ���� �ּ�.
	todo* p_prev = ptr_todo->get_prev_todo();

	// ����� ��� todo ���Ḯ��Ʈ��
	// 1. ������ ���.		2. �� ���� ���.		3. �� ���� ���.		4. �߰��� �ִ� ���.

	if (p_next == NULL && p_prev == NULL) {										// 1. ������ ���.
		ptr_cate->set_first_todo(NULL);
	}
	else if (p_prev == NULL && ptr_cate->get_first_todo() == ptr_todo) {		// 2. �� ���� ���.
		p_next->set_prev_todo(NULL);
		ptr_cate->set_first_todo(p_next);
	}
	else if (p_next == NULL) {													// 3. �� ���� ���.
		p_prev->set_next_todo(NULL);
	}
	else {																		// 4. �߰��� �ִ� ���.
		p_prev->set_next_todo(p_next);
		p_next->set_prev_todo(p_prev);
	}
	string title = ptr_todo->get_title();
	delete(ptr_todo);
	ptr_cate->decrease_todo_num();												// ī�װ��� todo_num--;
	cout << "\t" << title << " ���� ����" << endl << endl;
}


void todo::search_todo() {

	category* ptr_cate = ptr_cate->cate_head;

	if (ptr_cate == NULL) {																// ���� ó�� : ī�װ��� ���� ���.
		cout << "ī�װ��� �� ���� �����ϴ�. ī�װ����� �߰����ּ���." << endl;
		return;
	}

	rewind(stdin);											// �̸� �Է¹��۸� �����.

	string word;
	cout << "�˻��� �� �Ͽ� ���Ե� �ܾ �Է����ּ���. : ";
	getline(cin, word);

	cout << endl;

	int count = 0;											// ã�� �� ���� ������ ������� ����.

	while (ptr_cate != NULL) {

		todo* ptr_todo = ptr_cate->get_first_todo();

		while (ptr_todo != NULL) {

			string title = ptr_todo->get_title();		// ���� ���ڿ��� ����.
			
			if (title.find(word) != string::npos) {				// ���� title���� �Է��� word�� ã������ string::npos�� ��ȯ ����.

				cout << "\t" << ++count <<  ". �Ҽ� ī�װ�: " << ptr_cate->get_cate_name() << endl;			// ã�� ���� ++count
				cout << "\t\t����: " << ptr_todo->get_title() << endl;
				cout << "\t\t���� ����: " << ptr_todo->get_due_data() << endl;
				cout << "\t\t����: " << ptr_todo->get_detail() << endl << endl;
			}
			ptr_todo = ptr_todo->get_next_todo();
		}
		// �� ���� ���ų� ã�� �� ���� ������ ���� ī�װ��� �Ѿ.
		ptr_cate = ptr_cate->get_next_cate();
	}

	cout << "\tã�� �� ���� ���� :" << count << endl << endl;

	cout << "==========================================================" << endl << endl;
}
