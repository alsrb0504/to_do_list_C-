#define  _CRT_SECURE_NO_WARNINGS

#include "command.h"
#include <iostream>
#include <string>

//#include <fstream>
using namespace std;

#define BUFFER_SIZE 100

Cate_Struct cate_struct;						// ī�װ� ���Ḯ��Ʈ�� head, tail, ī�װ��� ���� �����ϱ� ���� ����ü ���� ����.	

category* unclassified;						// 0. �̺з� ī�װ� ����.
category* important;						// 1. �߿��� ī�װ� ����.

void init_setting() {

	cate_struct.size = 0;										// 
	cate_struct.cate_head = NULL;
	cate_struct.cate_tail = NULL;

	unclassified = unclassified->create_cate("�̺з�");		// 0. �̺з� ī�װ� ����.
	add_to_cate(unclassified);

	important = important->create_cate("�߿�");				// 1. �߿��� ī�װ� ����.
	add_to_cate(important);
	
	cout << "�ʱ� ����: " << endl;
	cout << "1�� ī�װ��� \"�̺з�\" 2�� ī�װ��� \"�߿�\"�� ����" << endl << endl;
}

void show_important() {

	cout << "�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�" << endl;
	cout << "\t(�׻� 2��° ī�װ��� ����ŵ�ϴ�.)" << endl << endl;
		
	category* p = search_cate(2);

	if (p == NULL) {													// ���� ó��.						
		cout << "\t�߿��� ī�װ��� �����ϴ�." << endl;
	}

	/*cout << "\t\t" << p->get_cate_name() << endl;*/
	
	show_cate_todos(p);

	cout << "�ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�" << endl << endl << endl;
}

void show_all() {
	category* p = cate_struct.cate_tail;

	if (p == NULL) {										// ���� ó��
		cout << "\t�� ���� �����ϴ�." << endl << endl;
	}

	while (p != NULL) {
		show_cate_todos(p);
		p = p->get_prev_cate();
	}
}


void search_todo() {
	// ī�װ����� ����� ����ְ� ��� �ִ��� �����.
	// ī�װ��� ��ȣ�� �Է��ϸ� �� ī�װ��� �� �ϵ��� ����� ��ȣ�� �Բ� ����ش�.
	// ��ȣ�� �Է��ϸ� int num�� �̿��ؼ� �׳� for�� ���� ã�� ������ �ش�.

	// �ٵ� ���⼭ ���� �� ���� �ϳ��� ���ų� ī�װ��鵵 �ƹ��͵� ���ٸ� ���޽��� ��� �� �ʱ�ȭ������ ���°� ���� ��.

	category* p = select_cate();			// ��ɷ� ī�װ� ��� ��� �� �ʿ��� ī�װ��� �ּ� ����.

	show_cate_todos(p);

}

todo* remove_search_todo(category* p) {
	//category* p = select_cate();			// ��ɷ� ī�װ� ��� ��� �� �ʿ��� ī�װ��� �ּ� ����.

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

void remove_todo() {

	category* ptr_cate = select_cate();					// ��ɷ� ī�װ� ��� ��� �� �ʿ��� ī�װ��� �ּ� ����.

	todo* p = remove_search_todo(ptr_cate);				// ��� ���ؼ� ���� todo�� ã��.

	if (p == NULL) {							// ���� ó��.
		cout << "���� ����!!" << endl;
		return;
	}
	
	todo* p_next = p->get_next_todo();					// ���� �� ���� ������ ���� �ּ�.
	todo* p_prev = p->get_prev_todo();
	
	// ����� ���
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
	cout << "\t" << title << " ���� ����" << endl;
}

string set_todo_title() {

	string title;

	// �� �� �Է�.
	int first = 0;									// ó���� �Է¹��۸� �����ϱ� ���� ����.
	while (1) {

		cout << "	�� ���� �����ּ���.(ù ���� ����x): ";

		if (first == 0) {
			getchar();
			first++;
		}
		getline(cin, title);

		if (title.empty() || title[0] == ' ') {
			cout << "\t�Է��� �����ϴ�.\n" << endl;
			continue;
		}

		break;
	}

	return title;

}

string set_todo_time() {

	// ���� ���� ���� �޾Ƽ� �˻��ϰ� string time �迭�� append�� ��ġ��.

	string time;
	// �ð� �Է� 
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
		return time;
	}
}

string set_todo_detail() {
	string detail;
	cout << "\t�ڼ��� ������ �����ּ���.:";

	getchar();										// �Է� ���� ��������.
	getline(cin, detail);

	return detail;
}

void create_todo() {
	
	cout << "\t1. �� �� �߰�." << endl;

	string title = set_todo_title();
	string time = set_todo_time();
	string detail = set_todo_detail();

	todo* ptr_todo = NULL;
	ptr_todo = ptr_todo->create_todo(title, time, detail);

	if (ptr_todo == NULL) {												// ����ó��.
		cout << "\t�� �� �߰� ����!!" << endl << endl;
	}

	show_cate_list();								// ���� ī�װ��� ����� �����ش�.
	
	int n;
	while (1) {
		
		cout << "\t������ �߰��� ī�װ��� ��ȣ�� �Է����ּ���.: ";
		cin >> n;

		if (cate_struct.size == 0) {
			cout << "\tī�װ� ����� ������ϴ�. ī�װ��� ���� ����� �ּ���." << endl << endl;
		}
		if (n <= 0 || n > cate_struct.size) {
			cout << "\t�߸� �Է�!!" << endl;
			continue;
		}
		break;
	}

	sort_todo_to_cate(ptr_todo, n);							// ������ todo ��ü�� ī�װ��� ��ȣ�� �Ű������� ī�װ��� ���ĵǾ� ����.
}

void sort_todo_to_cate(todo* ptr_todo, int n) {

	category* ptr_cate = search_cate(n);							// ī�װ��� ã����. �̶� n�� �˻��ؼ� �������Ƿ� ���� �˻� x.

	// ���� �� �� ���� ī�װ��� ���������� ��.
	// ��¥ ������� ������ �ǵ�.
	// 1. ����� ��,	2. �� �տ� �� ��,	3. �� �ڿ� �� ��,	�߰��� ���Ե� ��.

	todo* p = ptr_cate->get_first_todo();
	todo* q = NULL;
	// �� ��ġ�� ���� ã����� ����..?
	


	while (p != NULL) {
		// �������� ���ؼ�

		if (ptr_todo->get_due_data() < p->get_due_data()) {					// ���ڿ��ε� string�̶� �� �ǰ���..?
			break;
		}
		q = p;
		p = p->get_next_todo();
	}


	if (p == NULL && ptr_cate->get_first_todo() == NULL) {				// 1. ����� ��.
		ptr_cate->set_first_todo(ptr_todo);
	}
	else if (p == ptr_cate->get_first_todo()) {							// 2. ó���� ���� ��.
		
		// p�� ���� �ּҰ� ptr_todo
		// ptr_todo�� ���� �ּҰ� p
		// first_todo�� ptr_todo
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



// ���� �� ����.						// ī�װ��� 



void remove_category() {											// ī�װ� �޴� 3�� ī�װ� �����.

	show_cate_list();

	int n;
	cout << "\t����� ���� ī�װ��� ��ȣ�� �Է�: ";
	cin >> n;

	// ī�װ��� ���Ḯ��Ʈ���� ��ȸ�ϸ� �Էµ� ��ȣ�� ī�װ��� ã�� �� �ּҸ� �޴´�.
	// �� ī�װ��� ����� todo���� ���� delete ���ش�.
	// �� �� �� ������ �� Ȯ���� ����. category�� ����� ���Ḯ��Ʈ���� �ٽ� �������ְ� �� ������ ���Ḯ��Ʈ���� ��ȣ�� 1�� ���ҽ����ش�.

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
	// �� �ϳ� �����ϰ� �׳� ����������??
	// ptr_todo�� �и� ���� ���� ����Ű�� �վ��µ�....


	// cate delete �ϴµ� 
	// ī�װ� ���Ḯ��Ʈ��
	// 1. �����.		2.  ������ ī�װ�.		3. �� ��(�ٵ� 0,1�� �� ���� ����.)	4. �� ��		5. �߰�		
	
	if (cate_struct.cate_head == NULL && cate_struct.size == 0) {			// �� ���.

		cout << "\tī�װ��� �̹� ������ϴ�." << endl << endl;
		return;
	}
	else if (ptr_cate == cate_struct.cate_head && ptr_cate == cate_struct.cate_tail) {			// ������ 1��

		cate_struct.cate_head = NULL;
		cate_struct.cate_tail = NULL;
	}
	else if (ptr_cate == cate_struct.cate_head) {							// ó��
		// ���� ptr_cate�� ���� ī�װ��� ���� �ּҸ� NULL�� �ʱ�ȭ.		cate_head�� ���� ī�װ��� ����Ű��.
		
		category* q = ptr_cate->get_next_cate();
		q->set_prev_cate(NULL);
		cate_struct.cate_head = q;
	}
	else if (ptr_cate == cate_struct.cate_tail) {							// ������
		
		category* q = ptr_cate->get_prev_cate();
		q->set_next_cate(NULL);
		cate_struct.cate_tail = q;
	}
	else {																	// �߰�

		category* next_p = ptr_cate->get_next_cate();	
		category* prev_p = ptr_cate->get_prev_cate();

		next_p->set_prev_cate(prev_p);
		prev_p->set_next_cate(next_p);
	}
	
	// ���� ī�װ��� ���� ī�װ����� index�� 1�� ���ҽ��� �ش�. ( �ʰ� ������ ���� index ��ȣ�� ���� ������.)
	category* prev_p = ptr_cate->get_prev_cate();

	while (prev_p != NULL) {				// �߰��̰ų� �� ���� ���� ����.

		prev_p->increase_index();									// ī�װ����� ��ü index�� 1�� ���� �����ִ� �Լ�.
		prev_p = prev_p->get_prev_cate();
	}

	string imsi = ptr_cate->get_cate_name();

	cate_struct.size--;
	delete(ptr_cate);
	cout << "\t" << imsi << " ī�װ� ���� ����" << endl << endl;
	cout << "==========================================================" << endl;
}


void show_category() {							// ī�װ� �޴� 2�� ī�װ� �̸��� �׿� ����� todo�� ����.			
												// ���߿� Ư�� �� ī�װ� �˻��ϰ� �� ī�װ��� �� �ϵ� �� �����ϴ� ������ �ٲ� ��.

	// ī�װ� ����� �̸��� ���� �����ش�.
	// �� �Ŀ� ī�װ��� ��ȣ�� �Է��ϰ� �Ѵ�.

	// ī�װ��� ���Ḯ��Ʈ���� ��ȸ�ϸ� �Էµ� ��ȣ�� ī�װ��� ã�´�. (�Լ��� �����ؾ� ��.)

	// �׷��� ī�װ��� �̸��� �׿� ����� todo���� �����ش�.

	category* p = select_cate();

	show_cate_todos(p);

}

category* select_cate() {

	show_cate_list();

	int n;
	cout << "\t�ٷ� ī�װ��� ��ȣ�� �Է�: ";
	cin >> n;

	category* p = search_cate(n);

	if (p == NULL) {												// ����ó�� ã�� ������ ���.
		cout << "\t�Է��� ��ȣ�� ī�װ��� �����ϴ�." << endl << endl;
		cout << "==========================================================" << endl;
		return NULL;
	}

	return p;
}

void show_cate_todos(category* ptr_cate) {

	if (ptr_cate== NULL) {
		return;
	}

	todo* ptr_todo = ptr_cate->get_first_todo();

	// todo���� ��� ���.											// todo ���� ������ �� get_todo �� �Լ� �߰�.
	cout << "\t" << ptr_cate->get_cate_name() << endl;

	cout << "==========================================================" << endl;
	
	if (ptr_todo == NULL)
		cout << "\tī�װ��� �� ���� ������ϴ�." << endl << endl;

	int i = 1;					// �� �ϵ��� ��ȣ�� ���� ���.(���߿� �˻��ϱ� ����.)

	while (ptr_todo != NULL) {
		cout << "\t" << i++ << ". ���� : " << ptr_todo->get_title() << endl;						// ���߿� �������ڿ� ���λ��׵� ���� �ְ�.
		cout << "\t  ���� ����: " << ptr_todo->get_due_data() << endl;
		cout << "\t  ����: " << ptr_todo->get_detail() << endl;

		ptr_todo = ptr_todo->get_next_todo();
	}
	cout << endl;
	cout << "==========================================================" << endl;

}

category* search_cate(int n) {

	category* p = cate_struct.cate_head;

	while (p != NULL && n > 0 && n <= cate_struct.size) {
		
		if (p->get_cate_index() == n) {							// ī�װ��� �Ϸù�ȣ�� �Է¹��� n�� ������ �� ī������ �ּ� ����.
			return p;
		}
		p = p->get_next_cate();
	}
	
	return NULL;						// �� ã������ NULL �� ��ȯ.
}

void show_cate_list() {											// ī�װ� �޴� 6�� ī�װ� ��� ����.

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

void create_category() {										// ī�װ� ���� �Լ�.

	string name;

	while (1) {													// �� �ȿ��� �̸� �ߺ� �˻� �κ� �߰�.

		cout << "������ ī�װ��� �̸��� �Է����ּ���.: ";
		cin >> name;

		break;

		//	// ������ ī�װ����� ���� �̸� �ִ��� �˻�.
		//	// null�� �ƴ� �� ��ȯ�� �ߺ��ִ� ����.
		//	category* overlap = search_cate(name);									// ��� ���� �ʿ�.

		//	if (overlap == NULL)
		//		break;
		//	else {
		//		cout << "�ߺ��� �̸��� ī�װ��� �ֽ��ϴ�. �̸��� �ٽ� �Է����ּ���." << endl;
		//	}

		//}

		//category ��ü�� �ϳ� ���� �����ؾ� �ϴµ�, ��� ������ �ϳ�.
	}

	category* ptr_cate = NULL;
	ptr_cate = ptr_cate->create_cate(name);					// ī�װ� ��ü �ϳ� ����.

	add_to_cate(ptr_cate);
	
}



void add_to_cate(category* ptr_cate) {				// cate ����ü�� head�� tail�� ������ category���� ��������ִ� �Լ�.

	// ������ category ��ü�� �޾Ƽ� ���Ḯ��Ʈ�� �߰��ؾ� �ϴµ�.
	// ����� ��
	// 1. �� ����Ʈ(ó�� ���� �� �ʿ�).	2. ���� ���� ���.				//  ���߿� �� ����Ʈ���� �˻� �ϴ� �Լ� �����ؼ� �ٲ��� ��.

	if (cate_struct.size == 0 && cate_struct.cate_head == NULL) {

		cate_struct.cate_head = ptr_cate;
		cate_struct.cate_tail = ptr_cate;
	}
	else {
		// ptr_cate�� ���� �ּҸ� �Է��ϰ�, 
		// �� �����ּҴ� ���� �ּҷ� ptr_cate�� �޴´�.
		// cate_struct.head�� ptr_cate�� ����Ų��.

		ptr_cate->set_next_cate(cate_struct.cate_head);
		cate_struct.cate_head->set_prev_cate(ptr_cate);
		cate_struct.cate_head = ptr_cate;
	}

	cate_struct.size++;
}

void menu() {												 // 4. all list �κ� �����ؾ� ��.
	cout << "\t\tTo_Do_List_Program" << endl;
	cout << "==========================================================" << endl;
	cout << "\t\t��ɾ� ���: \n\t\t1. �߿��� �� ����	\n\t\t2. category\n\t\t3. todo\n\t\t4. all list\n\t\t10. exit\n" << endl;
	cout << "==========================================================" << endl;

}

// ���� ��.															==========================




//void add_todo_to_cate() {
//	char ch;
//	while (1) {
//		cout << "�߰��� �� ���� ī�װ��� �з��Ͻðڽ��ϴ�?(y/n):";
//		cin >> ch;
//
//		if (ch == 'n') {
//			cout << "ī�װ��� �ƴ� todo�� ��ü�� ���Ḯ��Ʈ�� �з��߽��ϴ�." << endl;
//			break;
//		}
//		else if (ch == 'y') {
//			// ī�װ��� ����������� Ȯ��.
//			// ������� todo�� ��ü �˸���.
//			// ī�װ� ������ ī�װ��� �Է¹ް� ã�Ƽ� �Է��ϱ�.
//			bool empty = category::head_cate->is_empty_cate();				// ī�װ��� ������� Ȯ��.
//			if (empty == true) {
//				cout << "ī�װ��� ������ϴ�. todo�� ��ü�� ���Ḯ��Ʈ�� �з��߽��ϴ�." << endl;
//				break;
//			}
//			
//			while (1) {											// ����� �� ī�װ����� �̸��� �Է��� ������ �ݺ�.
//				show_category();						// ���� ī�װ����� �̸��� ������.
//
//				string cate_name;
//				cout << "�з��� ī�װ��� �̸��� �Է��ϼ���.:";
//				cin >> cate_name;
//
//				category* ptr_cate = search_cate(cate_name);
//
//				if (ptr_cate == NULL) {
//					cout << "�׷� �̸��� ī�װ��� �����ϴ�." << endl;
//					continue;
//				}
//
//				ptr_cate->add_todo_cate(todo::imsi_todo);					// ã�� ī�װ��� ���� todo�� ����.
//				break;
//			}
//
//		}
//		else {
//			cout << "�߸� �Է��߽��ϴ�. �ٽ� �Է��ϼ���. " << endl;
//			continue;
//		}
//		break;
//	}
//}



//void show_cate_todo() {
//	
//	string name;
//	cout << "�� ���� ����� �� ī�װ��� �̸��� �Է����ּ���.:";
//	cin >> name;
//
//	category* ptr_cate = search_cate(name);
//
//	if (ptr_cate == NULL) {
//		cout << "�Է��� �̸��� ī�װ��� �����ϴ�." << endl;
//		cout << "category �޴��� ó������ ���ư��ϴ�." << endl;
//		return;
//	}
//
//	show_cate_todos(ptr_cate);
//}

//void show_cate_todos(category* ptr_cate) {
//
//	todo* p = ptr_cate->getFirsttodo();				// �� ī�װ��� ù ��° �� ���� ��ȯ�ϴ� �Լ�.
//	todo* q = NULL;
//
//	if (p == NULL) {
//		cout << "�� ī�װ��� �� ���� �����ϴ�." << endl;
//		return;
//	}
//
//	while (p != NULL) {
//		
//		p->get_todo_data();
//
//		q = p;
//		p = p->next_cate_todo;
//	}
//
//}







//void load() {												// ���� ���� �Լ�.
//	
//	FILE *fp = fopen("to_do_list.txt", "r");
//
//	if (fp == NULL) {
//		cout << "���� ���� ����." << endl;					// ���� ó��.
//		return;
//	}
//
//	char sen[BUFFER_SIZE];
//	while (fgets(sen, BUFFER_SIZE, fp)) {
//		
//
//		cout << sen;
//
//		if (feof(fp))
//			break;
//	}
//	cout << endl;
//	
//	fclose(fp);
//
//}
//
//void save() {
//	
//	FILE* fp = fopen("to_do_list.txt", "r");
//	FILE* fp2 = fopen("copy.txt", "w");
//
//	char sen[BUFFER_SIZE];
//	while (fgets(sen, BUFFER_SIZE, fp)) {
//		cout << sen;
//
//		fprintf(fp2, "%s", sen);
//
//		if (feof(fp))
//			break;
//	}
//	cout << endl;
//
//	
//	fclose(fp);
//	fclose(fp2);
//}
