#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 상수 정의
#define LEN_MIN 15   // 열차의 최소 길이
#define LEN_MAX 50   // 열차의 최대 길이
#define STM_MIN 0    // 마동석 최소 체력
#define STM_MAX 5    // 마동석 최대 체력
#define PROB_MIN 10  // 확률의 최소값
#define PROB_MAX 90  // 확률의 최대값

#define AGGRO_DEFAULT 1  // 기본 어그로 값
#define AGGRO_MAX 5      // 어그로 최대값
#define AGGRO_MIN 0      // 어그로 최소값

// 마동석 이동 방향
#define MOVE_LEFT 1
#define MOVE_STAY 0

// 마동석 행동
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

// 좀비 공격 대상
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

// 스테이지 상태
#define STAGE_CLEAR 1
#define STAGE_FAIL 0

// 전역 변수
int t_l, p_p, d_stamina;
int turn = 0, z_stunned = 0;
int c_aggro = AGGRO_DEFAULT, d_aggro = AGGRO_DEFAULT;
int c_pos, z_pos, d_pos, num_citizens;

// 함수 선언
int getInput(int min, int max, const char* prompt);
void updateAggro(int* aggro, int change, int min, int max);
void printTrain();
void printStatus();
void updateCitizens();
int updateZombie();
void updateDongseok();
void madongseokAction();
int playStage(int stage);

// 메인 함수
int main(void) {
    srand((unsigned int)time(NULL));

    // 사용자 입력 받기
    t_l = getInput(LEN_MIN, LEN_MAX, "train length(15~50)>> ");
    d_stamina = getInput(STM_MIN, STM_MAX, "madongseok stamina(0~5)>> ");
    p_p = getInput(PROB_MIN, PROB_MAX, "percentile probability 'p'(10~90)>> ");

    // 스테이지 시작
    int stage_result = playStage(2);
    if (stage_result == STAGE_CLEAR) {
        printf("스테이지 2를 클리어하여 다음 스테이지로 진행합니다.\n");
        // 다음 스테이지 로직 구현
    }
    else {
        printf("스테이지 2를 클리어하지 못했습니다. 게임 오버.\n");
    }

    return 0;
}

// 사용자 입력 받기
int getInput(int min, int max, const char* prompt) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf_s("%d", &value, sizeof(value)) == 1) {
            if (value >= min && value <= max) {
                break;
            }
            else {
                printf("잘못된 입력입니다. 다시 입력해 주세요.\n");
            }
        }
        else {
            printf("입력 오류입니다. 다시 입력해 주세요.\n");
            while (getchar() != '\n'); // 입력 버퍼를 비웁니다.
        }
    }
    return value;
}

// 어그로 업데이트
void updateAggro(int* aggro, int change, int min, int max) {
    *aggro += change;
    if (*aggro > max) {
        *aggro = max;
    }
    else if (*aggro < min) {
        *aggro = min;
    }
}

// 열차 상태 출력
void printTrain() {
    printf("###############\n");
    for (int i = 0; i < t_l; i++) {
        if (i == c_pos && i == z_pos && i == d_pos) {
            printf("# C Z M #\n");
        }
        else if (i == c_pos && i == z_pos) {
            printf("# C Z #\n");
        }
        else if (i == c_pos && i == d_pos) {
            printf("# C M #\n");
        }
        else if (i == z_pos && i == d_pos) {
            printf("# Z M #\n");
        }
        else if (i == c_pos) {
            printf("# C #\n");
        }
        else if (i == z_pos) {
            printf("# Z #\n");
        }
        else if (i == d_pos) {
            printf("# M #\n");
        }
        else {
            printf("# #\n");
        }
    }
    printf("###############\n");
}

// 상태 출력
void printStatus() {
    printf("citizen: %d (aggro: %d)\n", num_citizens, c_aggro);
    printf("zombie: %d\n", z_pos);
    printf("madongseok: %d (aggro: %d, stamina: %d)\n", d_pos, d_aggro, d_stamina);
}

// 시민 이동 업데이트
void updateCitizens() {
    int move_prob = rand() % 100;
    if (move_prob < (100 - p_p)) {
        c_pos--;
        updateAggro(&c_aggro, 1, AGGRO_MIN, AGGRO_MAX);
    }
    else {
        updateAggro(&c_aggro, -1, AGGRO_MIN, AGGRO_MAX);
    }
}

// 좀비 업데이트
int updateZombie() {
    if (z_stunned) {
        z_stunned = 0;
        return z_pos;
    }

    if (turn % 2 == 1) {
        if (z_pos == d_pos) {
            return ATK_DONGSEOK;
        }
        else if (z_pos == c_pos) {
            return ATK_CITIZEN;
        }
        else if (d_aggro > c_aggro) {
            return z_pos + (z_pos < d_pos ? 1 : -1);
        }
        else {
            return z_pos + (z_pos < c_pos ? 1 : -1);
        }
    }
    return z_pos;
}

// 마동석 이동 업데이트
void updateDongseok() {
    int move;
    printf("madongseok move(0:stay, 1:left)>> ");
    if (scanf_s("%d", &move, sizeof(move)) == 1) {
        if (move == MOVE_LEFT) {
            d_pos--;
            if (d_pos < 0) d_pos = 0;
            updateAggro(&d_aggro, 1, AGGRO_MIN, AGGRO_MAX);
        }
        else {
            updateAggro(&d_aggro, -1, AGGRO_MIN, AGGRO_MAX);
        }
    }
    else {
        printf("입력 오류입니다. 다시 입력해 주세요.\n");
        while (getchar() != '\n'); // 입력 버퍼를 비웁니다.
        updateDongseok(); // 재귀적으로 호출하지 않고, 단순히 함수를 종료합니다.
    }
}

// 마동석 행동 업데이트
void madongseokAction() {
}

// 스테이지 실행
int playStage(int stage) {
}
