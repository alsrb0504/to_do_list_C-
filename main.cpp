#include "command.h"

#include <iostream>
using namespace std;


void read_command();
void cate_menu();
void todo_menu();
void menu();

int main() {
		
	init_setting();										// 초기 설정 ( 1.미분류		2.중요 category 생성).

	read_command();										// 명령을 실행하기 위한 함수.
	
}

void read_command() {

	int command;										// 명령을 실행하기 위한 변수.

	while (1) {
		menu();
		cout << "숫자 입력: ";
		cout << "$: ";
		cin >> command;

		if (command == 1) {								// 중요함 카테고리(항상 2번 category)를 출력.
			show_important();
		}
		else if (command == 2) {						// category 메뉴를 실행.
			cate_menu();
		}
		else if (command == 3) {						// todo 메뉴를 실행.
			todo_menu();
		}
		else if (command == 4) {						// 모든 category와 todo를 출력.
			show_all();
		}
		else if (command == 5) {						// to_do_list.txt에 저장된 카테고리와 할 일들을 입력.
			load();
		}
		else if (command == 6) {						// to_do_list.txt에 콘솔에서 다룬 카테고리와 할 일들을 저장.
			save();
		}
		else if (command == 10) {						// 프로그램 종료.
			return;
		}
	}
}

void menu() {												 
	cout << "\t\tTo_Do_List_Program" << endl;
	cout << "==========================================================" << endl;
	cout << "\t\t명령어 목록: \n\t\t1. 중요한 일 보기	\n\t\t2. category\n\t\t3. todo\n\t\t4. all list\n\t\t5. 파일 불러오기\n\t\t6. 파일 저장하기\n\t\t10. exit\n" << endl;
	cout << "==========================================================" << endl;

}

void cate_menu() {										// 선택한 명령 실행 후 cate_menu 초기화면으로 돌아감.

	while (1) {
		cout << "\t\tCategory Menu" << endl;
		cout << "==========================================================" << endl;
		cout << "\t\t Category 명령어 목록: \n\t\t1. 카테고리 추가\n\t\t2. 카테고리 보기"
			<< "\n\t\t3. 카테고리 제거\n\t\t4. 카테고리 목록 보기\n\t\t5. 처음화면으로 돌아가기\n\t\t" << endl;
		cout << "==========================================================" << endl;
		cout << "category_command" << endl;
		cout << "숫자 입력: $: ";

		int category_command;
		cin >> category_command;

		if (category_command == 1) {					// 카테고리 생성 함수.
			create_category();
		}
		else if (category_command == 2) {				// 나중에 show_categorys 로 수정
			show_category();
		}
		else if (category_command == 3) {				// 카테고리 제거 함수.
			remove_category();
		}
		else if (category_command == 4) {				// 현재 category들의 이름만 출력.
			show_cate_list();
		}
		else if (category_command == 5) {
			cout << "\t초기 메뉴로 돌아갑니다." << endl << endl;
			cout << "==========================================================" << endl;
			break;
		}
		else {
			cout << "잘못 입력했습니다. 다시 입력해주세요." << endl;
			continue;
		}
	}
}

void todo_menu() {										// 선택한 명령 실행 후 todo_menu화면으로 돌아감.
									
	while (1) {
		cout << "\t\tTo_Do_Menu" << endl;
		cout << "==========================================================" << endl;
		cout << "\t\t To_Do_Menu 명령어 목록: \n\t\t1. 할 일 추가\n\t\t2. 할 일 보기(카테고리로 이동)"
			<< "\n\t\t3. 할 일 제거\n\t\t4. (중요한 할 일 보기)\n\t\t5. 처음화면으로 돌아가기\n\t\t" << endl;
		cout << "==========================================================" << endl;
		cout << "todo_command" << endl;
		cout << "숫자 입력: $: ";

		int todo_command;
		cin >> todo_command;

		if (todo_command == 1) {						// 할 일 생성.
			create_todo();
		}
		else if (todo_command == 2) {					// 할 일 찾기. (찾을 할 일이 있는 카테고리를 선택 -> 카테고리의 할 일들의 목록 보여 줌.)
			search_todo();
		}
		else if (todo_command == 3) {					// 할 일 제거.
			remove_todo();
		}
		else if (todo_command == 4) {					// 중요한 할 일들 출력. (메인 메뉴의 중요함 카테고리 출력과 동일한 기능.)
			show_important();
		}
		else if (todo_command == 5) {					
			cout << "\t초기 메뉴로 돌아갑니다." << endl << endl;
			break;
		}
	}
}