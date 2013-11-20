#pragma once

enum SceneType
{
	SCENE_NONE,

	SCENE_OPENING,
	SCENE_TITLE,
	SCENE_SELECT_MUSIC,
	SCENE_PLAY,
	SCENE_RESULT,

	SCENE_MAX
};

enum LayerType
{
	LAYER_NONE,

	LAYER_BACKGROUND,
	LAYER_JUDGERING,  //item 구현용
	LAYER_GAUGE,	  //item 구현용
	LAYER_ITEM,		  //item 구현용
	LAYER_NOTE1,
	LAYER_NOTE2,
	LAYER_NOTE_HIT,
	LAYER_EFFECT,
	LAYER_SHUTTER,
	LAYER_LABEL,
	LAYER_MEMORY_POOL,

	LAYER_MAX
};

enum ObjectType
{
	OBJECT_NONE,

	OBJECT_BG_IMAGE_TITLE,
	OBJECT_BG_IMAGE_SELECT,
	OBJECT_BG_IMAGE_PLAY,
	OBJECT_BG_IMAGE_RESULT,
	OBJECT_JUDGERING, //item 구현용
	OBJECT_GAUGE_1P,  //item 구현용
	OBJECT_GAUGE_2P,  //item 구현용
	OBJECT_NOTE_NORMAL_1,
	OBJECT_NOTE_NORMAL_2,
	OBJECT_EFFECT,
	OBJECT_NOTE_HIT,
	OBJECT_SHUTTER,
	OBJECT_ALBUM_IMAGE,

	OBJECT_MAX
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
	SOUND_SHUTTER,

	SOUND_MAX
};

enum PlayerNumber
{
	PLAYER_NONE,

	PLAYER_ONE,
	PLAYER_TWO,

	PLAYER_MAX
};

enum CountType
{
	COUNT_NONE,

	COUNT_PERFECT,
	COUNT_GOOD,
	COUNT_MISS,
	COUNT_COMBO,
	COUNT_MAX_COMBO,
	COUNT_SCORE,

	COUNT_MAX
};

enum JudgeType
{
	JUDGE_NONE,

	JUDGE_PERFECT,
	JUDGE_GOOD,
	JUDGE_MISS,

	JUDGE_MAX
};

enum KeyStatus
{
	KEY_STATUS_NONE,

	KEY_STATUS_DOWN,
	KEY_STATUS_PRESSED,
	KEY_STATUS_UP,
	KEY_STATUS_NOT_PRESSED,

	KEY_MAX
};

enum ItemT1Type
{
	ITEM_T1_NONE,

	ITEM_T1_1,
	ITEM_T1_2,
	ITEM_T1_3,
	ITEM_T1_4,

	ITEM_T1_MAX
}; // 추후 아이템 구현에 맞게 수정합시다.

enum ItemT2Type
{
	ITEM_T2_NONE,

	ITEM_T2_1,
	ITEM_T2_2,
	ITEM_T2_3,
	ITEM_T2_4,

	ITEM_T2_MAX
}; // 추후 아이템 구현에 맞게 수정합시다.

enum ItemT3Type
{
	ITEM_T3_NONE,

	ITEM_T3_1,
	ITEM_T3_2,
	ITEM_T3_3,
	ITEM_T3_4,

	ITEM_T3_MAX
}; // 추후 아이템 구현에 맞게 수정합시다.

enum ItemTierType
{
	TIER_NONE,

	TIER_ONE,
	TIER_TWO,
	TIER_THREE,

	TIER_MAX
};