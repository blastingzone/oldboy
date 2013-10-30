#pragma once

enum SceneType
{
	SCENE_TITLE,
	SCENE_PLAY,
	SCENE_RESULT,
	NO_SCENE
};

enum LayerType
{
	LAYER_BACKGROUND,
	LAYER_NOTE1,
	LAYER_NOTE2,
	LAYER_NOTE_HIT,
	LAYER_EFFECT,
	LAYER_SHUTTER,
	LAYER_LABEL,
	LAYER_MEMORY_POOL,
	NO_LAYER
};

enum ObjectType
{
	OBJECT_BG_IMAGE_TITLE,
	OBJECT_BG_IMAGE_PLAY,
	OBJECT_NOTE_NORMAL_1,
	OBJECT_NOTE_NORMAL_2,
	OBJECT_EFFECT,
	OBJECT_NOTE_HIT,
	OBJECT_SHUTTER,
	NO_OBJECT
};

enum KeyTable
{
	ESCAPE,

	P1_TARGET1,
	P1_TARGET2,
	P1_ATTACK,

	P2_TARGET1,
	P2_TARGET2,
	P2_ATTACK,

	NO_INPUT
};

enum PlayerNumber
{
	PLAYER_ONE,
	PLAYER_TWO,

	NO_PLAYER
};

enum CountType
{
	PERFECT_COUNT,
	GOOD_COUNT,
	MISS_COUNT,
	COMBO_COUNT,
	SCORE_COUNT,

	NO_COUNT
};