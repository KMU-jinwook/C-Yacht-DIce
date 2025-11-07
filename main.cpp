#include <iostream>
#include <windows.h>
#include "Dice.h"

using namespace std;

//주사위 객체 5개 생성
Dice first;
Dice second;
Dice third;
Dice fourth;
Dice fifth;

//주사위 5개를 효율적으로 관리하기 위한 배열 생성
Dice arr[5] = { first, second, third, fourth, fifth };

int main() {
	srand((unsigned)time(NULL));

	int choose = 0;
	int hold_num = 0;
	int hold_dice = 0;
	int time = 0;
	int turn = 0;
	int dice_list[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	bool list[12] = { false, false , false , false , false , false , false , false , false , false , false , false };


	while (true) {
		Dice_reset(arr);
		time = 0;
		while (time < 3) {
			cout << "1. 주사위를 굴리기 / 2. 주사위 보관 / 3. 족보 선택 (남은 기회 : " << 3 - time << ")\n" << "입력 : ";
			cin >> choose;
			if (choose == 1) {
				system("cls");
				Dice_list(dice_list, list);
				Dice_roll(arr);
				time++;
			}
			else if (choose == 2) {
				cout << "보관할 주사위의 개수 : ";
				cin >> hold_num;
				for (int j = 0; j < hold_num; j++) {
					cout << "보관할 주사위 : ";
					cin >> hold_dice;
					hold_dice--;
					arr[hold_dice].is_held = !arr[hold_dice].is_held;
				}
			}
			else if (choose == 3) {
				Dice_judge(dice_list, list, arr);
				turn++;
				break;
			}

			if (time == 3) {
				Dice_judge(dice_list, list, arr);
				turn++;
			}
		}
		if (turn == 12) {
			int final_score = 0;
			for (int i = 0; i < 12; i++) {
				final_score += dice_list[i];
			}
			if (bonus(dice_list) == true) {
				final_score += 35;
			}
			cout << "게임 종료!" << endl << "최종 점수 : " << final_score;
			break;
		}
	}
}