class Dice {
private:
        int value;
public:
        bool is_held;
        Dice() {
                roll();
        }
        void roll();
        void print();
        int count();
};

bool bonus(int list[]);

void Dice_reset(Dice arr[]);

void Dice_roll(Dice arr[]);

void Dice_list(int list[], bool yn[]);

void Dice_count(Dice arr[], int count_arr[]);

void Dice_judge(int list[], bool yn[], Dice arr[]);

int zero_count(int count_arr[]);
bool judge_4oK(int count_arr[]);
bool judge_fullhouse(int count_arr[]);
bool judge_S_straight(int count_arr[]);
bool judge_L_straight(int count_arr[]);
bool judge_Yacht(int count_arr[]);