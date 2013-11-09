#pragma once

enum SceneType
{
	SCENE_NONE,

	SCENE_OPENING,
	SCENE_TITLE,
	SCENE_SELECT_MUSIC,
	SCENE_PLAY,
	SCENE_RESULT
};

enum LayerType
{
	LAYER_NONE,

	LAYER_BACKGROUND,
	LAYER_NOTE1,
	LAYER_NOTE2,
	LAYER_NOTE_HIT,
	LAYER_EFFECT,
	LAYER_SHUTTER,
	LAYER_LABEL,
	LAYER_MEMORY_POOL
};

enum ObjectType
{
	OBJECT_NONE,

	OBJECT_BG_IMAGE_TITLE,
	OBJECT_BG_IMAGE_PLAY,
	OBJECT_NOTE_NORMAL_1,
	OBJECT_NOTE_NORMAL_2,
	OBJECT_EFFECT,
	OBJECT_NOTE_HIT,
	OBJECT_SHUTTER
};

enum SoundType
{
	SOUND_NONE,

	SOUND_BG_TITLE,
	SOUND_BG_PLAY,
	SOUND_BG_RESULT,
	SOUND_NOTE_1,
	SOUND_NOTE_2,
	SOUND_NOTE_EFFECT,
	SOUND_SHUTTER
};

enum KeyTable
{
	KEY_TABLE_NONE,

	KEY_TABLE_ESCAPE,
	KEY_TABLE_RETURN,

	KEY_TABLE_P1_TARGET1,
	KEY_TABLE_P1_TARGET2,
	KEY_TABLE_P1_ATTACK,

	KEY_TABLE_P2_TARGET1,
	KEY_TABLE_P2_TARGET2,
	KEY_TABLE_P2_ATTACK
};

enum PlayerNumber
{
	PLAYER_NONE,

	PLAYER_ONE,
	PLAYER_TWO
};

enum CountType
{
	COUNT_NONE,

	COUNT_PERFECT,
	COUNT_GOOD,
	COUNT_MISS,
	COUNT_COMBO,
	COUNT_SCORE
};

enum JudgeType
{
	JUDGE_NONE,

	JUDGE_PERFECT,
	JUDGE_GOOD,
	JUDGE_MISS
};

enum KeyStatus
{
	KEY_STATUS_NONE,

	KEY_STATUS_DOWN,
	KEY_STATUS_PRESSED,
	KEY_STATUS_UP,
	KEY_STATUS_NOT_PRESSED,
};