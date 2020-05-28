#pragma once

unsigned constexpr FRAME_RATE = 100;

float constexpr USER_WINDOW_HEIGHT = 600;
float constexpr USER_WINDOW_WIDTH = 500;
float constexpr OFFSET_HEIGHT = USER_WINDOW_HEIGHT / 10;

float constexpr FIELD_WINDOW_HEIGHT = 2 * USER_WINDOW_HEIGHT / 5;
float constexpr FIELD_WINDOW_WIDTH = USER_WINDOW_WIDTH;
unsigned constexpr NUMBER_BRICKS_IN_ROW = 6;
unsigned constexpr NUMBER_BRICKS_IN_COLUMN = 3;

float constexpr BALL_RADIUS = USER_WINDOW_WIDTH / 40;
float constexpr BALL_X = USER_WINDOW_WIDTH / 2 - BALL_RADIUS;
float constexpr BALL_Y = 17 * USER_WINDOW_HEIGHT / 20;

float constexpr BAR_HEIGHT = USER_WINDOW_HEIGHT / 40;
float constexpr BAR_WIDTH = USER_WINDOW_WIDTH / 4;
float constexpr BAR_X = BALL_X - BAR_WIDTH / 2 + BALL_RADIUS;
float constexpr BAR_Y = BALL_Y + 2 * BALL_RADIUS;

float constexpr TEXT_SIZE = USER_WINDOW_HEIGHT / 20;
float constexpr TEXT_X = USER_WINDOW_WIDTH / 50;
float constexpr TEXT_Y = USER_WINDOW_HEIGHT / 30;

float constexpr INCREASE_SPEED = 1.5;
unsigned constexpr BONUS_NUMBER = 6;