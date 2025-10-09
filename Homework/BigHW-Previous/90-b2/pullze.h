// 2451317 冯久恒 计算机

#pragma once

/* 提示：空文件，仅为了提醒你不要忘记首行 && 不要把文件名弄错 */
int menu();
int size();
void wait(int op);

void puzzle_base(int s, int op);
bool game_check(int s, char bl[16][16], char ip[16][16]);

void draw_1(int s, char bl[16][16]);
void draw_11(int s, char bl[16][16], int op);

void draw_21(int s, char bl[16][16], int op);
void draw_2(int s, char bl[16][16]);