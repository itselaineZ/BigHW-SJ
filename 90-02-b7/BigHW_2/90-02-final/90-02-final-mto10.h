/*1952339 ��08 ��ܰ��*/
#pragma once

#include "../include/class_gmw.h"

const int Maxn = 8 + 2;
const int INF = 0x3f3f3f3f;
const int slp = 0;
const int dd[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
const int data_interval[3][2] = { {5, 8}, {5, 8}, {5, 20} };//���������������
const int Color[21] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 1, 2, 3, 4, 5 };
const int cols = 80;
const int rows = 25;

bool check_in_mp(int posc, int posr, int row, int column);/*����Ƿ���ͼ��*/

void memst(int(*a)[Maxn]);/*��������*/
void mempy(int(*a)[Maxn], const int b[Maxn][Maxn]);/*���鸴��b��a*/

void game_find_same_BFS(int posr, int posc, int row, int column, const int table[Maxn][Maxn], int(*fnd)[Maxn]);/*Bfs������Χ��ͬ����*/

void change_neighbor(CONSOLE_GRAPHICS_INFO mto, bool id, int row, int column, const int table[Maxn][Maxn], const int fnd[Maxn][Maxn], const BLOCK_DISPLAY_INFO *cb, const int (*opt)[2]);/*�ı�������ɫ״̬, 0:δѡ��->ѡ��*/
void puzzle_clr(CONSOLE_GRAPHICS_INFO mto, int posr, int posc, int row, int column, int(*table)[Maxn], int(*fnd)[Maxn], const BLOCK_DISPLAY_INFO *cb, bool id = 1, int* maxv = 0);/*�ϲ������ѡ�п�*/
void table_move(CONSOLE_GRAPHICS_INFO mto, int id, int row, int column, int(*table)[Maxn], int(*fnd)[Maxn], const BLOCK_DISPLAY_INFO* cb);/*���ֵ��� id��0��ʾ��αͼ�ν���*/
