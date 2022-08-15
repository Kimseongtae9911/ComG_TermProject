#pragma once


enum class OBJ_ID { OBJ_PLAYER1, OBJ_PLAYER2, OBJ_BOSS, OBJ_MONSTER1, OBJ_MONSTER2, OBJ_MAP, OBJ_BOX, OBJ_BULLET, OBJ_PORTAL, OBJ_KEY, OBJ_SPIKE, OBJ_UI, OBJ_END};

enum class SCENE_ID {	SCENE_LOGO,SCENE_LOAD, SCENE_STAGE1, SCENE_STAGE2, SCENE_STAGE3, SCENE_STAGE4, SCENE_END, SCENE_GAMEOVER};

enum class RENDER_ID { REDER_BACK, REDER_NONAL, RENDER_BOSS, REDER_BULLET, REDER_ALPHA, REDER_UI, RENDER_END };

enum class DIR {LEFT = 1, RIGHT, UP, DOWN = 4};