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

#define GAME_NAME	L"Rhythm Match v0.125"
#define CLASS_NAME	L"RhythmMatch"

#define SCREEN_SIZE_X 1024 // 1024 + 16
#define SCREEN_SIZE_Y 662  // 668 + 32

#define NOTE_SIZE 100

#define MAX_NOTE_IN_POOL	200
#define MAX_EFFECT			20

#define DEFAULT_POSITION_X -5504
#define DEFAULT_POSITION_Y -5504

// judge Manager ���� ����ϴ� ������ ��Ʈ�� ���� ��ġ�� ���
#define NOTE_ONE_START_POSITION_X	395
#define NOTE_TWO_START_POSITION_X	910
#define NOTE_START_POSITION_Y		-100

// ������ ���� �߻� �� ���� �� ��
#define ERROR_POSITION -9504

#define NOTE_JUDGE_PERFECT_START_LINE	534
#define NOTE_JUDGE_PERFECT_END_LINE		556
#define NOTE_JUDGE_GOOD_START_LINE		514
#define NOTE_JUDGE_GOOD_END_LINE		576
#define NOTE_JUDGE_FAST_MISS_LINE		504
#define NOTE_JUDGE_LATE_MISS_LINE		555

// shutter ���� ����ϴ� ������ ��Ʈ�� ���� ��ġ�� ���
#define SHUTTER_P1_START_POSITION_X 0
#define SHUTTER_P2_START_POSITION_X 515
#define SHUTTER_START_POSITION_Y -668

// shutter ���� �÷��̾� HP ����
#define PLAYER_HP_MAX		10

// Label ���� define
#define LABEL_JUDGE_PERFECT	L"PERFECT!!"
#define LABEL_JUDGE_GOOD	L"  GOOD!  "
#define LABEL_JUDGE_MISS	L"  MISS..."

#define LABEL_PLAY_SCORE	L"SCORE"
#define LABEL_PLAY_COMBO	L"COMBO"

#define LABEL_RESULT_SCORE		"SCORE   : "
#define LABEL_RESULT_PERFECT	"PERFECT : "
#define LABEL_RESULT_GOOD		"GOOD    : "
#define LABEL_RESULT_MISS		"MISS    : "
#define LABEL_RESULT_COMBO		"COMBO   : "

#define LABEL_NAME_P1_SCORE	L"�÷��̾�1����"
#define LABEL_NAME_P1_COMBO	L"�÷��̾�1�޺�"
#define LABEL_NAME_P2_SCORE	L"�÷��̾�2����"
#define LABEL_NAME_P2_COMBO	L"�÷��̾�2�޺�"

#define LABEL_NAME_SELECT_LIST1	L"����Ʈ����Ʈ1"
#define LABEL_NAME_SELECT_LIST2	L"����Ʈ����Ʈ2"
#define LABEL_NAME_SELECT_LIST3	L"����Ʈ����Ʈ3"
#define LABEL_NAME_SELECT_LIST4	L"����Ʈ����Ʈ4"
#define LABEL_NAME_SELECT_LIST5	L"����Ʈ����Ʈ5"

#define LABEL_FONT_NORMAL	L"���� ���"

#define LABEL_FPS			L"FPS"

#define MAX_INPUT_KEY		256

#define MAX_COUNT			7

// Resource ����

#define FOLDER_SLASH		"/"
#define MUSIC_FOLDER_SEARCH	"./Music/.\\*" // ���� ���� ���� ��� ���� �ǹ�
#define MUSIC_FOLDER		"./Music/"
#define BGM_TITLE			"./Resource/bgm_title_00_01.mp3"

#define BG_IMAGE_TITLE	L"./Resource/image_bg_00_01.png"
#define BG_IMAGE_SELECT	L"./Resource/image_bg_select_01.png"
#define BG_IMAGE_RESULT	L"./Resource/image_bg_result_01.png"

#define PLAY_IMAGE_JUDGE_RING	L"./Resource/judgeRing.png"
#define PLAY_IMAGE_BLUE_GAUGE	L"./Resource/blueBar.png"
#define PLAY_IMAGE_RED_GAUGE	L"./Resource/redBar.png"

// Error ���� 
// ���� ������ �ܼ� â���� ǥ���Ǵ� ��

// �޽��� �ڽ� Ÿ��Ʋ ERROR_TITLE_~~~
#define ERROR_TITLE_NORMAL			L"ERROR!"
#define ERROR_TITLE_LOAD			L"LOAD ERROR!"

// �޽��� �ڽ� ����  ERROR_MESSAGE_~~~

// xmlLoader ���� 
#define ERROR_MESSAGE_LOAD_XML_TITLE				L"Missing title Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_ARTIST				L"Missing artist Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_LEVEL				L"Missing level Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_IMAGE_ALBUM			L"Missing imageAlbum Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_IMAGE_BACKGROUND		L"Missing imageBackground Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_IMAGE_SHUTTER		L"Missing imageShutter Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_IMAGE_NOTE1			L"Missing imageNote1 Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_IMAGE_NOTE2			L"Missing imageNote2 Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_IMAGE_NOTE_EFFECT	L"Missing imageNoteEffect Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_SOUND_BACKGROUND		L"Missing soundBackground Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_SOUND_NOTE_EFFECT1	L"Missing soundNoteEffect1 Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_SOUND_NOTE_EFFECT2	L"Missing soundNoteEffect2 Data in index.xml"
#define ERROR_MESSAGE_LOAD_XML_NOTE_DATA			L"Missing note Data in index.xml"

#define ERROR_CHANGE_SCENE	L"Error to Change Scene"

#define ERROR_SOUND_INIT	L"Error Sound Initialize...."
#define ERROR_SOUND_LOADING	L"Error Loading Sound Files...."

#define ERROR_CREATE_RESOURCE		L"Error to Create Object Resources"
#define ERROR_CREATE_RENDER			L"Error to Create Renderer"
#define ERROR_CREATE_RENDER_TARGET	L"Error to Create Render Target"
#define ERROR_CREATE_WIC_FACTORY	L"Error to Create WIC Factory"

#define ERROR_CREATE_BG_IMAGE		L"Error to Create BackGround Texture"
#define ERROR_LOAD_MUSIC_XML	L"Error Loading Music Index File...."
#define ERROR_LOAD_IMAGE	L"Error Loading Image Files...."
#define ERROR_LOAD_SOUND	L"Error Loading Sound Files...."

#define ERROR_LOAD_IMAGE_CONSOLE	"Image Loading Error! (%d) \n"
#define ERROR_FMOD_CONSOLE			"FMOD error! (%d) %s\n"