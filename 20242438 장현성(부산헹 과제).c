#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN_MIN 15   // 열차의 최소 길이
#define LEN_MAX 20   // 열차의 최대 길이
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
#define ACTION_PROVO 1
#define ACTION_PULL 2

// 스테이지 상태
#define STAGE_CLEAR 1
#define STAGE_FAIL 0

// 시민 수
#define NUM_CITIZENS_MIN 2
#define NUM_CITIZENS_MAX 5

int t_l, p_p, d_stamina, z_move, d_move;
int turn = 0, dont_move = 0, z_stunned = 0;
int c_aggro = AGGRO_DEFAULT, d_aggro = AGGRO_DEFAULT;

// 입력 함수 수정
int getInput(int min, int max, const char* prompt) {
    int value;
    while (1) {
        printf("%s", prompt);
        scanf_s("%d", &value);
        // 입력 범위를 벗어나면 다시 입력 요청
        if (value >= min && value <= max) {
            break;
        }
        else {
            printf("잘못된 입력입니다. 다시 입력해 주세요.\n");
        }
    }
    return value;
}

// 어그로와 체력 갱신 함수 수정
void updateAggro(int* aggro, int change, int min, int max) {
    *aggro += change;
    // 최솟값과 최댓값 범위 내에서 유지
    if (*aggro > max) {
        *aggro = max;
    }
    else if (*aggro < min) {
        *aggro = min;
    }
}

void printTrain(int num_citizens) {
    // 코드 생략
}

void printStatus(int num_citizens) {
    // 코드 생략
}

void generateCitizens(int* num_citizens, int train_length) {
    // 시민 수를 열차길이/4에서 열차길이/2 사이의 랜덤값으로 설정
    *num_citizens = rand() % (train_length / 2 - train_length / 4 + 1) + train_length / 4;
}

void updateCitizens() {
    // 코드 생략
}

int updateZombie() {
    // 코드 생략
}

int updateDongseok() {
    // 코드 생략
}

int playStage(int stage) {
    // 시민 수를 생성
    int num_citizens;
    generateCitizens(&num_citizens, t_l);

    printf("시민 수: %d\n", num_citizens);

    // 스테이지별 게임 진행
    while (1) {
        turn++; // 턴 증가
        printf("\n스테이지 %d - %d 번째 턴\n", stage, turn);

        // 시민 이동 페이즈
        updateCitizens();

        // 좀비 행동 및 공격 처리
        int attack = updateZombie();
        printf("좀비 행동 완료: 위치 %d\n", z_move);
        if (attack) {
            printf("좀비가 공격했습니다. 스테이지 실패.\n");
            return STAGE_FAIL;
        }

        // 마동석 행동
        int pull_success = updateDongseok();
        printf("마동석 행동 완료: 위치 %d (어그로 %d, 스태미나 %d)\n", d_move, d_aggro, d_stamina);

        // 열차 상태 출력
        printTrain(num_citizens);

        // 상태 출력
        printStatus(num_citizens);
    }
}

int main(void) {
    srand((unsigned int)time(NULL)); // 난수 생성기를 초기화

    // 공통적인 파라미터 입력
    t_l = getInput(LEN_MIN, LEN_MAX, "train length(15~20)>> ");
    p_p = getInput(PROB_MIN, PROB_MAX, "percentile probability 'p'(10~90)>> ");
    d_stamina = getInput(STM_MIN, STM_MAX, "마동석의 체력(0~5)>> ");

    // 스테이지 플레이
    int stage_result = playStage(2);
    if (stage_result == STAGE_CLEAR) {
        printf("스테이지 2를 클리어하여 다음 스테이지로 진행합니다.\n");
        // 다음 스테이지 구현
    }
    else {
        printf("스테이지 2를 클리어하지 못했습니다. 게임 오버.\n");
    }

    return 0;
}