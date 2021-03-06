#include "command.h"
#include "category.h"
#include <iostream>
using namespace std;


void start_program();									// 일정 관리 프로그램을 실행하는 함수.
void menu();											// 초기 메뉴화면을 출력해주는 함수.
void cate_menu();										// 카테고리 관련 처리를 실행하는 함수.
void todo_menu();										// 할 일 관련 처리를 실행하는 함수.

int checking_load = 0;									// main.cpp 에서만 쓰일 (5) 파일 불러오기 실행 횟수.

int main() {

	init_setting();										// 초기 설정 ( 1.미분류		2.중요  카테고리 생성) 실행.

	start_program();									// 일정 관리 프로그램 실행.
}

void start_program() {																	// 일정 관리 프로그램.

	while (1) {
		menu();											// 초기 메뉴 출력.

		int command = 0;								// 명령을 실행하기 위한 변수.

		if (cin.fail()) {								// 예외 처리 : 숫자가 아닌 문자를 입력했을 때, 무한루프 방지.
			cin.clear();
			cin.ignore(256, '\n');
		}

		cout << "숫자 입력: ";
		cout << "$: ";
		cin >> command;

		if (command == 1) {													// (1) >> 중요함 카테고리(항상 2번 category)를 출력.
			cout << "(1) >>  중요 카테고리 보기 실행" << endl << endl;
			show_important();
		}	
		else if (command == 2) {											// (2) >> category 메뉴를 실행.
			cout << "(2) >>  카테고리 메뉴 실행" << endl << endl;
			cate_menu();
		}
		else if (command == 3) {											// (3) >> todo 메뉴를 실행.
			cout << "(3) >>  할 일 메뉴 실행" << endl << endl;
			todo_menu();
		}
		else if (command == 4) {											// (4) >> 모든 category와 todo를 출력.
			cout << "(4) >>  모든 카테고리와 할 일 보기 실행" << endl << endl;
			show_all();
		}
		else if (command == 5) {											// (5) >> to_do_list.txt에 저장된 카테고리와 할 일들을 입력.
			cout << "(5) >>  파일에서 불러오기 실행" << endl << endl;

			if (checking_load != 0) {												// 파일 불러오기를 실행한 상태에서 한 번더 실행하면 할 일들이 두 번씩 추가됨.
				cout << "이미 파일 불러오기를 실행한 적이 있습니다." << endl;		// 또 실행하기 전에 물어보는 과정.
				cout << "한 번 더 파일 불러오기를 실행하시겠습니까? (y/n)>>";
				char ch;
				cin >> ch;
				if (ch != 'y') {													// y나 n이 아닌 다른 문자 입력해도 취소.
					cout << "파일 불러오기를 취소합니다." << endl << endl;
					continue;
				}
			}

			load();

			checking_load++;			// 파일 불러오기 횟수를 기록할 변수.
		}
		else if (command == 6) {											// (6) >> to_do_list.txt에 콘솔에서 다룬 카테고리와 할 일들을 저장.
			cout << "(6) >>  파일에 저장하기 실행" << endl << endl;

			if (checking_load == 0) {												// 파일 불러오기의 횟수가 0일 때, 파일 저장하기를 할 것인지 경고문 출력.
				cout << "파일 불러오기를 실행한 적이 없습니다." << endl;
				cout << "지금 파일 저장하기를 실행하면 기존의 기록들이 모두 지워집니다." << endl;
				cout << "그래도 실행하시겠습니까? (y/n)>>";
				char ch;
				cin >> ch;
				if (ch != 'y') {													// y나 n이 아닌 다른 문자 입력해도 취소
					cout << "파일 저장하기를 취소합니다." << endl << endl;
					continue;
				}
			}
	
			save();
		}
		else if (command == 10) {											// (10) >> 프로그램 종료.
			cout << "(10) >>  프로그램을 종료합니다." << endl << endl;
			exit(-1);
		}
		else {
			cout << "잘못 입력했습니다. 다시 입력해주세요." << endl << endl;
			continue;
		}
	}
}

void menu() {																		// 초기 메뉴화면을 출력해주는 함수.
	cout << "\t\tTo_Do_List_Program" << endl;
	cout << "==========================================================" << endl;
	cout << "\t\t명령어 목록:" << endl << endl;
	cout << "\t\t(1) >> 중요한 일 보기" << endl;
	cout << "\t\t(2) >> category menu" << endl;
	cout << "\t\t(3) >> todo menu" << endl;
	cout << "\t\t(4) >> all list" << endl;
	cout << "\t\t(5) >> 파일 불러오기" << endl;
	cout << "\t\t(6) >> 파일 저장하기" << endl;
	cout << "\t\t(10) >> exit" << endl << endl;;
	cout << "==========================================================" << endl;
}

void cate_menu() {																	// 카테고리 관련 처리를 실행하는 함수.
																					// 선택한 명령 실행 후 cate_menu 초기화면으로 돌아감.
	while (1) {
		cout << "\t\tCategory Menu" << endl;
		cout << "==========================================================" << endl;

		cout << "\t\tCategory 명령어 목록:" << endl << endl;
		cout << "\t\t(1) >> 카테고리 추가" << endl;
		cout << "\t\t(2) >> 카테고리 검색" << endl;
		cout << "\t\t(3) >> 카테고리 제거" << endl;
		cout << "\t\t(4) >> 카테고리 보기" << endl;
		cout << "\t\t(5) >> todo menu로 이동하기" << endl;
		cout << "\t\t(6) >> 처음화면으로 돌아가기" << endl << endl;

		cout << "==========================================================" << endl;
		cout << "category_command" << endl;
		cout << "숫자 입력: $: ";

		if (cin.fail()) {						// 예외 처리 : 숫자가 아닌 문자를 입력했을 때, 무한루프 에러 방지.
			cin.clear();
			cin.ignore(256, '\n');
		}

		category* p = NULL;						// 카테고리 클래스의 멤버 함수들을 호출하기 위해 선언.

		int category_command;
		cin >> category_command;

		if (category_command == 1) {												// (1) >> 카테고리 생성 함수.
			cout << "(1) >>  카테고리 생성 실행" << endl << endl;
			p->create_cate();
		}
		else if (category_command == 2) {											// (2) >> 카테고리 검색 함수.
			cout << "(2) >>  카테고리 검색 실행" << endl << endl;
			p->search_name_cate();
		}
		else if (category_command == 3) {											// (3) >> 카테고리 제거 함수.
			cout << "(3) >>  카테고리 제거 실행" << endl << endl;
			p->remove_category();
		}
		else if (category_command == 4) {											// (4) >> 카테고리와 연결된 할 일들 출력 함수.
			cout << "(4) >>  카테고리 보기 실행" << endl << endl;
			p->show_category();
		}
		else if (category_command == 5) {											// (5) >> 현재 category들의 이름만 출력.
			cout << "(5) >>  todo menu로 이동하기 실행" << endl << endl;
			todo_menu();
		}
		else if (category_command == 6) {											// (6) >> 프로그램 시작 화면으로 돌아감.
			cout << "\t초기 메뉴로 돌아갑니다." << endl << endl;
			cout << "==========================================================" << endl;
			start_program();
		}
		else {
			cout << "잘못 입력했습니다. 다시 입력해주세요." << endl << endl;
			continue;
		}
	}
}

void todo_menu() {													// 할 일 관련 처리를 실행하는 함수.
																	// 선택한 명령 실행 후 todo_menu화면으로 돌아감.
	while (1) {
		cout << "\t\tTo_Do_Menu" << endl;
		cout << "==========================================================" << endl;

		cout << "\t\tTo_Do_Menu 명령어 목록:" << endl << endl;
		cout << "\t\t(1) >> 할 일 추가" << endl;
		cout << "\t\t(2) >> 할 일 검색" << endl;
		cout << "\t\t(3) >> 할 일 제거" << endl;
		cout << "\t\t(4) >> category menu로 이동하기" << endl;
		cout << "\t\t(5) >> 처음화면으로 돌아가기" << endl << endl;

		cout << "==========================================================" << endl;
		cout << "todo_command" << endl;
		cout << "숫자 입력: $: ";

		if (cin.fail()) {								// 예외 처리 : 숫자가 아닌 문자를 입력했을 때, 무한루프 에러 방지.
			cin.clear();
			cin.ignore(256, '\n');
		}

		todo* p = NULL;					// todo 클래스의 멤버 함수 호출을 위해 선언.

		int todo_command;
		cin >> todo_command;

		if (todo_command == 1) {												// (1) >> 할 일 생성.
			cout << "(1) >> 할 일 생성 실행" << endl << endl;
			p->create_todo();
		}
		else if (todo_command == 2) {											// (2) >> 할 일 찾기.
			cout << "(2) >> 할 일 검색 실행" << endl << endl;
			p->search_todo();
		}
		else if (todo_command == 3) {											// (3) >> 할 일 제거.
			cout << "(3) >> 할 일 제거 실행" << endl << endl;
			p->remove_todo();
		}
		else if (todo_command == 4) {											// (4) >> 할 일 제거.
			cout << "(4) >> category menu로 이동하기" << endl << endl;
			cate_menu();
		}
		else if (todo_command == 5) {											// (5) >> 프로그램 시작 화면으로 돌아감.
			cout << "\t초기 메뉴로 돌아갑니다." << endl << endl;
			cout << "==========================================================" << endl;
			start_program();
		}
		else {
			cout << "잘못 입력했습니다. 다시 입력해주세요." << endl << endl;
			continue;
		}
	}
}