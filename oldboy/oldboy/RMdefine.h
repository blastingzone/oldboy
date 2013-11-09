#pragma once

//�̹��� ��ť��Ʈ ��� ���� ���� ���� ����
#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

//define for memroy leak check
#ifdef _DEBUG
#define	new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif


#define SCREEN_SIZE_X 1040 // 1024 + 16
#define SCREEN_SIZE_Y 700  // 668 + 32

#define NOTE_SIZE 100

#define DEFAULT_POSITION_X 5504
#define DEFAULT_POSITION_Y 5504

// judge Manager ���� ����ϴ� ������ ��Ʈ�� ���� ��ġ�� ���
#define NOTE_ONE_START_POSITION_X 395
#define NOTE_TWO_START_POSITION_X 910
#define NOTE_START_POSITION_Y -100

#define NOTE_JUDGE_PERFECT_START_LINE 534
#define NOTE_JUDGE_PERFECT_END_LINE 556
#define NOTE_JUDGE_GOOD_START_LINE 514
#define NOTE_JUDGE_GOOD_END_LINE 576
#define NOTE_JUDGE_FAST_MISS_LINE 504
#define NOTE_JUDGE_LATE_MISS_LINE 555


// Label ���� define
#define LABEL_JUDGE_PERFECT L"PERFECT!!"
#define LABEL_JUDGE_GOOD L"  GOOD!  "
#define LABEL_JUDGE_MISS L"  MISS..."

#define LABEL_PLAY_SCORE L"SCORE"
#define LABEL_PLAY_COMBO L"COMBO"

#define LABEL_NAME_P1_SCORE L"�÷��̾�1����"
#define LABEL_NAME_P1_COMBO L"�÷��̾�1�޺�"
#define LABEL_NAME_P2_SCORE L"�÷��̾�2����"
#define LABEL_NAME_P2_COMBO L"�÷��̾�2�޺�"

#define LABEL_FONT_NORMAL L"���� ���"


#define MAX_INPUT_KEY	20

#define MAX_COUNT	6

