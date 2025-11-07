#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Dice.h"


using namespace std;


//주사위 5개를 고정 여부에 따라 굴리는 함수
void Dice_roll(Dice arr[]) {
	cout << endl;
	cout << "결과 : ";
	for (int i = 0; i < 5; i++) {
		if (arr[i].is_held == false) {
			arr[i].roll();
		}
		arr[i].print();
	}
	cout << endl << endl;
}

//주사위 굴리기 기능
void Dice::roll() {
	value = rand() % 6 + 1;
}

//주사위 눈의 값 출력 함수
void Dice::print() {
	//고정된 주사위는 []로 표현
	if (is_held == true) {
		cout << "[" << value << "] ";
	}
	//고정되지 않은 주사위는 ()로 표현
	else {
		cout << "(" << value << ") ";
	}
}

int Dice::count() {
	return value;
}

//모든 주사위의 고정을 해제하는 함수
void Dice_reset(Dice arr[]) {
	for (int i = 0; i < 5; i++) {
		arr[i].is_held = false;
	}
}

//보너스 점수 조건을 확인하고 점수 부여
bool bonus(int list[]) {
	int bonus = 0;
	for (int i = 0; i < 6; i++) {
		bonus += list[i];
	}
	if (bonus >= 63) {
		return true;
	}
	else {
		false;
	}
}

//점수판 그리기
void Dice_list(int list[], bool yn[]) {
	int sum_f = 0;
	int sum_s = 0;
	for (int i = 0; i < 6; i++) {
		sum_f += list[i];
	}

	cout << endl;
	cout << "┌───────── [ 점수판 ]────┬──────┐" << endl;
	cout << "│ 01. one           " << setw(2) << list[0] << "   │   " << yn[0] << "  │" << endl;
	cout << "│ 02. two           " << setw(2) << list[1] << "   │   " << yn[1] << "  │" << endl;
	cout << "│ 03. three         " << setw(2) << list[2] << "   │   " << yn[2] << "  │" << endl;
	cout << "│ 04. four          " << setw(2) << list[3] << "   │   " << yn[3] << "  │" << endl;
	cout << "│ 05. five          " << setw(2) << list[4] << "   │   " << yn[4] << "  │" << endl;
	cout << "│ 06. six           " << setw(2) << list[5] << "   │   " << yn[5] << "  │" << endl;
	cout << "├────────────────────────┼──────┤" << endl;;
	cout << "│ bonus         " << setw(2) << sum_f << " / 63 " << " │   " ;
	if (bonus(list) == true) {
		cout << "+35" << "  │" << endl << endl;
	}
	else {
		cout << "0" << "  │" << endl << "├────────────────────────┼──────┤" << endl;
	}

	cout << "│ 07. choice         " << setw(2) << list[6] << "  │   " << yn[6] << "  │" << endl;
	cout << "│ 08. 4 of kind      " << setw(2) << list[7] << "  │   " << yn[7] << "  │" << endl;
	cout << "│ 09. full house     " << setw(2) << list[8] << "  │   " << yn[8] << "  │" << endl;
	cout << "│ 10. small straight " << setw(2) << list[9] << "  │   " << yn[9] << "  │" << endl;
	cout << "│ 11. Large straight " << setw(2) << list[10] << "  │   " << yn[10] << "  │" << endl;
	cout << "│ 12. yacht          " << setw(2) << list[11] << "  │   " << yn[11] << "  │" << endl;
	cout << "├────────────────────────┼──────┤" << endl;

	for (int j = 0; j < 12; j++) {
		sum_s += list[j];
	}

	cout << "│ total"  << "                  │ " << setw(3) << sum_s << "  │"  << endl;
	cout << "└────────────────────────┴──────┘" << endl;
}

//주사위 눈이 나온 숫자들 세는 함수
void Dice_count(Dice arr[], int count_arr[]){
	for (int i = 0; i < 5; i++) {
		count_arr[arr[i].count() - 1]++;
	}
	cout << endl;
}

//족보 조건 판별 함수
void Dice_judge(int list[], bool yn[], Dice arr[]){
	int order;
	int count_arr[6] = { 0, 0, 0, 0, 0, 0 };
	int score = 0;
	bool complete = false;
	Dice_count(arr, count_arr);
	while (complete == false) {
		cout << "족보 선택 : ";
		cin >> order;
		order--;
		if (yn[order] == false) {
			switch (order) {
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
				yn[order] = true;
				score = count_arr[order] * (order + 1);
				list[order] = score;
				complete = true;
				break;
			case 6:
				yn[order] = true;
				for (int i = 0; i < 6; i++) {
					score += count_arr[i] * (i + 1);
				}
				list[order] = score;
				complete = true;
				break;
			case 7:
				if (judge_4oK(count_arr)) {
					for (int i = 0; i < 5; i++) {
						score += arr[i].count();
					}
					list[order] = score;
				}
				else {
					list[order] = 0;
				}
				yn[order] = true;
				complete = true;
				break;
			case 8:
				if (judge_fullhouse(count_arr)) {
					for (int i = 0; i < 5; i++) {
						score += arr[i].count();
					}
					list[order] = score;
				}
				else {
					list[order] = 0;
				}
				yn[order] = true;
				complete = true;
				break;
			case 9:
				if (judge_S_straight(count_arr)) {
					list[order] = 15;
				}
				else {
					list[order] = 0;
				}
				yn[order] = true;
				complete = true;
				break;
			case 10:
				if (judge_L_straight(count_arr)) {
					list[order] = 30;
				}
				else {
					list[order] = 0;
				}
				yn[order] = true;
				complete = true;
				break;
			case 11:
				if (judge_Yacht(count_arr)) {
					list[order] = 50;
				}
				else {
					list[order] = 0;
				}
				yn[order] = true;
				complete = true;
				break;
			default:
				cout << "잘못된 선택";
			}
		}
		else {
			cout << "이미 선택된 족보입니다. 다시 선택해주세요 ." << endl;
			continue;
		}
	}
}

//안나온 숫자를 세는 함수
int zero_count(int count_arr[]) {
	int num_of_zero = 0;
	for (int i = 0; i < 6; i++) {
		if (count_arr[i] == 0) {
			num_of_zero++;
		}
	}
	return num_of_zero;
}

//족보 4 of kind 판별 함수
bool judge_4oK(int count_arr[]) {
	for (int i = 0; i < 6; i++) {
		if (count_arr[i] >= 4) {
			return true;
		}
	}
	return false;
}

//풀하우스 판별 함수
bool judge_fullhouse(int count_arr[]) {
	if (zero_count(count_arr) >= 4) {
		for (int i = 0; i < 6; i++) {
			if (count_arr[i] == 2 || count_arr[i] == 3 || count_arr[i] == 5) {
				return true;
			}
		}
	}
	return false;
}


//스몰 스트레이트 판별 함수
bool judge_S_straight(int count_arr[]) {
	if (zero_count(count_arr) <= 2) {
		return true;
	}
	else {
		return false;
	}
}

//라지 스트레이트 판별 함수
bool judge_L_straight(int count_arr[]) {
	if (zero_count(count_arr) == 1) {
		return true;
	}
	else {
		return false;
	}
}

//요트 판별 함수
bool judge_Yacht(int count_arr[]) {
	if (zero_count(count_arr) == 5) {
		return true;
	}
	else {
		return false;
	}
}