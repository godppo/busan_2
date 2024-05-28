#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN_MIN 15   // ������ �ּ� ����
#define LEN_MAX 20   // ������ �ִ� ����
#define STM_MIN 0    // ������ �ּ� ü��
#define STM_MAX 5    // ������ �ִ� ü��
#define PROB_MIN 10  // Ȯ���� �ּҰ�
#define PROB_MAX 90  // Ȯ���� �ִ밪

#define AGGRO_DEFAULT 1  // �⺻ ��׷� ��
#define AGGRO_MAX 5      // ��׷� �ִ밪
#define AGGRO_MIN 0      // ��׷� �ּҰ�

// ������ �̵� ����
#define MOVE_LEFT 1
#define MOVE_STAY 0

// ������ �ൿ
#define ACTION_REST 0
#define ACTION_PROVO 1
#define ACTION_PULL 2

// �������� ����
#define STAGE_CLEAR 1
#define STAGE_FAIL 0

// �ù� ��
#define NUM_CITIZENS_MIN 2
#define NUM_CITIZENS_MAX 5

int t_l, p_p, d_stamina, z_move, d_move;
int turn = 0, dont_move = 0, z_stunned = 0;
int c_aggro = AGGRO_DEFAULT, d_aggro = AGGRO_DEFAULT;

// �Է� �Լ� ����
int getInput(int min, int max, const char* prompt) {
    int value;
    while (1) {
        printf("%s", prompt);
        scanf_s("%d", &value);
        // �Է� ������ ����� �ٽ� �Է� ��û
        if (value >= min && value <= max) {
            break;
        }
        else {
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���.\n");
        }
    }
    return value;
}

// ��׷ο� ü�� ���� �Լ� ����
void updateAggro(int* aggro, int change, int min, int max) {
    *aggro += change;
    // �ּڰ��� �ִ� ���� ������ ����
    if (*aggro > max) {
        *aggro = max;
    }
    else if (*aggro < min) {
        *aggro = min;
    }
}

void printTrain(int num_citizens) {
    // �ڵ� ����
}

void printStatus(int num_citizens) {
    // �ڵ� ����
}

void generateCitizens(int* num_citizens, int train_length) {
    // �ù� ���� ��������/4���� ��������/2 ������ ���������� ����
    *num_citizens = rand() % (train_length / 2 - train_length / 4 + 1) + train_length / 4;
}

void updateCitizens() {
    // �ڵ� ����
}

int updateZombie() {
    // �ڵ� ����
}

int updateDongseok() {
    // �ڵ� ����
}

int playStage(int stage) {
    // �ù� ���� ����
    int num_citizens;
    generateCitizens(&num_citizens, t_l);

    printf("�ù� ��: %d\n", num_citizens);

    // ���������� ���� ����
    while (1) {
        turn++; // �� ����
        printf("\n�������� %d - %d ��° ��\n", stage, turn);

        // �ù� �̵� ������
        updateCitizens();

        // ���� �ൿ �� ���� ó��
        int attack = updateZombie();
        printf("���� �ൿ �Ϸ�: ��ġ %d\n", z_move);
        if (attack) {
            printf("���� �����߽��ϴ�. �������� ����.\n");
            return STAGE_FAIL;
        }

        // ������ �ൿ
        int pull_success = updateDongseok();
        printf("������ �ൿ �Ϸ�: ��ġ %d (��׷� %d, ���¹̳� %d)\n", d_move, d_aggro, d_stamina);

        // ���� ���� ���
        printTrain(num_citizens);

        // ���� ���
        printStatus(num_citizens);
    }
}

int main(void) {
    srand((unsigned int)time(NULL)); // ���� �����⸦ �ʱ�ȭ

    // �������� �Ķ���� �Է�
    t_l = getInput(LEN_MIN, LEN_MAX, "train length(15~20)>> ");
    p_p = getInput(PROB_MIN, PROB_MAX, "percentile probability 'p'(10~90)>> ");
    d_stamina = getInput(STM_MIN, STM_MAX, "�������� ü��(0~5)>> ");

    // �������� �÷���
    int stage_result = playStage(2);
    if (stage_result == STAGE_CLEAR) {
        printf("�������� 2�� Ŭ�����Ͽ� ���� ���������� �����մϴ�.\n");
        // ���� �������� ����
    }
    else {
        printf("�������� 2�� Ŭ�������� ���߽��ϴ�. ���� ����.\n");
    }

    return 0;
}