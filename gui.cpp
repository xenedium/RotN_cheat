#include <gui.h>


void DisplayError(uint8_t err)
{
    char msg[][70] = 
    {
        "Could not get game PID.\nMake sure the game is fully opened !",
        "Could not get game's handle.\nMake sure you open this cheat as admin.",
        "Could not get module base adress.\n",
        "Could not get object adress.\n",
        "Could not set game's money.\n"
    };
    MessageBoxA(NULL, msg[err], "Error", MB_ICONERROR);
    exit(err + 1);
}

void RunMainLoop(HANDLE hRotn, void *rotnMoneyObjectAdress)
{
    int fakeargc = 1;
    char *fakeargv = GetCommandLineA();     //im not proud of doing this workaround xD
    QApplication mainApp(fakeargc, &fakeargv);

    QWidget mainWindow;
    mainWindow.setFixedSize(400, 200);

    QPushButton mainButton(&mainWindow);
    mainButton.setGeometry(280, 50, 91, 31);
    mainButton.setText("Set Money");
    
    QSpinBox mainBox(&mainWindow);
    mainBox.setGeometry(80, 50, 131, 31);
    mainBox.setMinimum(0);
    mainBox.setMaximum(MAXINT32);
    mainBox.setSingleStep(1000);
    mainBox.setValue(GetRotnMoney(hRotn, rotnMoneyObjectAdress));

    QObject::connect(&mainButton, &QPushButton::clicked, [hRotn, rotnMoneyObjectAdress, &mainBox]{SetRotnMoney(hRotn, rotnMoneyObjectAdress, mainBox.value());});

    mainWindow.show();

    mainApp.exec();
}