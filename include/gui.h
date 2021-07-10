#ifndef GUI_INCLUDED
#define GUI_INCLUDED

#include <QApplication>
#include <QPushButton>
#include <QSpinBox>
#include <elevations.h>
#include <Windows.h>


void DisplayError(uint8_t err);
void ShowStuff(int argc, char **argv);
void RunMainLoop(HANDLE hRotn, void *rotnMoneyObjectAdress);
INT32 GetRotnMoney(HANDLE hRotn, void *rotnMoneyObjectAdress);

#endif