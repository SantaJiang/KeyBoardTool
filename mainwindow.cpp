﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QObject>
#include <QDebug>
#include <QSettings>
#include <windows.h>
#include <stdint.h>

HHOOK keyHook= nullptr;

//keyboard hook
LRESULT CALLBACK keyProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *pkbhs = (KBDLLHOOKSTRUCT *) lParam;

    if(nCode == HC_ACTION)
    {
        if(pkbhs->vkCode == VK_ESCAPE && GetAsyncKeyState(VK_CONTROL)& 0x8000 && GetAsyncKeyState(VK_SHIFT)&0x8000) //"Ctrl+Shift+Esc"
        {
            return 1;
        }
        else if(pkbhs->vkCode == VK_ESCAPE && GetAsyncKeyState(VK_CONTROL) & 0x8000)                                //"Ctrl+Esc"
        {
            return 1;
        }
        else if(pkbhs->vkCode == VK_TAB && pkbhs->flags & LLKHF_ALTDOWN )                                           //"Alt+Tab"
        {
            return 1;
        }
        else if(pkbhs->vkCode == VK_ESCAPE && pkbhs->flags &LLKHF_ALTDOWN )                                         //"Alt+Esc"
        {
            return 1;
        }
        else if(pkbhs->vkCode == VK_F4 && pkbhs->flags & LLKHF_ALTDOWN)                                             //"Alt+F4"
        {
            return 1;
        }
        else if(wParam == WM_KEYDOWN && pkbhs->vkCode == VK_SNAPSHOT)                                               //"Prtic"
        {
            MainWindow::getInstance()->keyPressedDisplay(MainWindow::getInstance()->ui->label_prtsc);
            return 1;
        }
        else if(wParam == WM_KEYUP && pkbhs->vkCode == VK_SNAPSHOT)
        {
            MainWindow::getInstance()->keyReleasedDisplay(MainWindow::getInstance()->ui->label_prtsc);
            return 1;
        }
        else if(wParam == WM_KEYDOWN && pkbhs->vkCode == VK_LWIN)                                                   // "LeftWin"
        {
            MainWindow::getInstance()->keyPressedDisplay(MainWindow::getInstance()->ui->label_winl);
            return 1;
        }
        else if(wParam == WM_KEYUP && pkbhs->vkCode == VK_LWIN)
        {
            MainWindow::getInstance()->keyReleasedDisplay(MainWindow::getInstance()->ui->label_winl);
            return 1;
        }
        else if(wParam == WM_KEYDOWN && pkbhs->vkCode == VK_RWIN)                                                   //"RightWin"
        {
            MainWindow::getInstance()->keyPressedDisplay(MainWindow::getInstance()->ui->label_winr);
            return 1;
        }
        else if(wParam == WM_KEYUP && pkbhs->vkCode == VK_RWIN)
        {
            MainWindow::getInstance()->keyReleasedDisplay(MainWindow::getInstance()->ui->label_winr);
            return 1;
        }
        else if(wParam == WM_KEYDOWN && pkbhs->vkCode == VK_TAB)                                                    //"TAB"
        {
            MainWindow::getInstance()->keyPressedDisplay(MainWindow::getInstance()->ui->label_tab);
            return 1;
        }
        else if(wParam == WM_KEYUP && pkbhs->vkCode == VK_TAB)
        {
            MainWindow::getInstance()->keyReleasedDisplay(MainWindow::getInstance()->ui->label_tab);
            return 1;
        }
    }
    return CallNextHookEx(keyHook, nCode, wParam, lParam);
}

void hook(bool flag)
{
    if(flag)
    {
        //registered hooks
        keyHook = SetWindowsHookEx(WH_KEYBOARD_LL,keyProc,GetModuleHandle(nullptr),0);
    }
    else
    {
        UnhookWindowsHookEx(keyHook);
        keyHook= nullptr;
    }
}


MainWindow* instance;
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    instance = this;
    initWidget();
    hook(true);
}

MainWindow::~MainWindow()
{
    hook(false);
    delete ui;
}

MainWindow *MainWindow::getInstance()
{
    return instance;
}

void MainWindow::initWidget()
{   
    m_mapKeysPartA.insert(2,ui->label_1l);              //L1
    m_mapKeysPartA.insert(3,ui->label_2l);              //L2
    m_mapKeysPartA.insert(4,ui->label_3l);              //L3
    m_mapKeysPartA.insert(5,ui->label_4l);              //L4
    m_mapKeysPartA.insert(6,ui->label_5l);              //L5
    m_mapKeysPartA.insert(7,ui->label_6l);              //L6
    m_mapKeysPartA.insert(8,ui->label_7l);              //L7
    m_mapKeysPartA.insert(9,ui->label_8l);              //L8
    m_mapKeysPartA.insert(10,ui->label_9l);             //L9
    m_mapKeysPartA.insert(11,ui->label_0l);             //L0
    m_mapKeysPartA.insert(12,ui->label_minusl);         //-
    m_mapKeysPartA.insert(13,ui->label_plusl);          //=
    m_mapKeysPartA.insert(16,ui->label_Q);              //Q
    m_mapKeysPartA.insert(17,ui->label_W);              //W
    m_mapKeysPartA.insert(18,ui->label_E);              //E
    m_mapKeysPartA.insert(19,ui->label_R);              //R
    m_mapKeysPartA.insert(20,ui->label_T);              //T
    m_mapKeysPartA.insert(21,ui->label_Y);              //Y
    m_mapKeysPartA.insert(22,ui->label_U);              //U
    m_mapKeysPartA.insert(23,ui->label_I);              //I
    m_mapKeysPartA.insert(24,ui->label_O);              //O
    m_mapKeysPartA.insert(25,ui->label_P);              //P
    m_mapKeysPartA.insert(26,ui->label_parenthesisl);   //{
    m_mapKeysPartA.insert(27,ui->label_parenthesisr);   //}
    m_mapKeysPartA.insert(30,ui->label_A);              //A
    m_mapKeysPartA.insert(31,ui->label_S);              //S
    m_mapKeysPartA.insert(32,ui->label_D);              //D
    m_mapKeysPartA.insert(33,ui->label_F);              //F
    m_mapKeysPartA.insert(34,ui->label_G);              //G
    m_mapKeysPartA.insert(35,ui->label_H);              //H
    m_mapKeysPartA.insert(36,ui->label_J);              //J
    m_mapKeysPartA.insert(37,ui->label_K);              //K
    m_mapKeysPartA.insert(38,ui->label_L);              //L
    m_mapKeysPartA.insert(39,ui->label_semicolon);      //:
    m_mapKeysPartA.insert(40,ui->label_colon);          //"
    m_mapKeysPartA.insert(41,ui->label_tilde);          //~
    m_mapKeysPartA.insert(43,ui->label_backslash);      //|
    m_mapKeysPartA.insert(44,ui->label_Z);              //Z
    m_mapKeysPartA.insert(45,ui->label_X);              //X
    m_mapKeysPartA.insert(46,ui->label_C);              //C
    m_mapKeysPartA.insert(47,ui->label_V);              //V
    m_mapKeysPartA.insert(48,ui->label_B);              //B
    m_mapKeysPartA.insert(49,ui->label_N);              //N
    m_mapKeysPartA.insert(50,ui->label_M);              //M
    m_mapKeysPartA.insert(51,ui->label_comma);          //,
    m_mapKeysPartA.insert(52,ui->label_period);         //.
    m_mapKeysPartA.insert(53,ui->label_question);       //？
    m_mapKeysPartA.insert(57,ui->label_space);          //Space
    m_mapKeysPartA.insert(59,ui->label_f1);             //F1
    m_mapKeysPartA.insert(60,ui->label_f2);             //F2
    m_mapKeysPartA.insert(61,ui->label_f3);             //F3
    m_mapKeysPartA.insert(62,ui->label_f4);             //F4
    m_mapKeysPartA.insert(67,ui->label_f9);             //F9
    m_mapKeysPartA.insert(68,ui->label_f10);            //F10
    m_mapKeysPartA.insert(71,ui->label_7r);             //R7
    m_mapKeysPartA.insert(72,ui->label_8r);             //R8
    m_mapKeysPartA.insert(73,ui->label_9r);             //R9
    m_mapKeysPartA.insert(75,ui->label_4r);             //R4
    m_mapKeysPartA.insert(76,ui->label_5r);             //R5
    m_mapKeysPartA.insert(77,ui->label_6r);             //R6
    m_mapKeysPartA.insert(79,ui->label_1r);             //R1
    m_mapKeysPartA.insert(80,ui->label_2r);             //R2
    m_mapKeysPartA.insert(81,ui->label_3r);             //R3
    m_mapKeysPartA.insert(82,ui->label_0r);             //R0
    m_mapKeysPartA.insert(83,ui->label_dot);            // dotr
    m_mapKeysPartA.insert(87,ui->label_f11);            //F11
    m_mapKeysPartA.insert(88,ui->label_f12);            //F12

    //666, 777, 888, 999 are invalid codes for filling vacancies
    m_mapKeysPartB.insert(1,ui->label_esc);             //Esc
    m_mapKeysPartB.insert(14,ui->label_backspace);      //Backspace
    m_mapKeysPartB.insert(28,ui->label_enterl);         //enterl
    m_mapKeysPartB.insert(29,ui->label_ctll);           //ctll
    m_mapKeysPartB.insert(42,ui->label_shiftl);         //LeftShift
    m_mapKeysPartB.insert(54,ui->label_shiftr);         //RShift
    m_mapKeysPartB.insert(55,ui->label_multiply);       // *
    m_mapKeysPartB.insert(56,ui->label_altr);           //altr
    m_mapKeysPartB.insert(58,ui->label_caps);           //CapsLock
    m_mapKeysPartB.insert(63,ui->label_f5);             //F5
    m_mapKeysPartB.insert(64,ui->label_f6);             //F6
    m_mapKeysPartB.insert(65,ui->label_f7);             //F7
    m_mapKeysPartB.insert(66,ui->label_f8);             //F8
    m_mapKeysPartB.insert(69,ui->label_pausebreak);     //Pause
    m_mapKeysPartB.insert(70,ui->label_scrolllock);     //ScrollLock
    m_mapKeysPartB.insert(74,ui->label_minusr);         // -
    m_mapKeysPartB.insert(78,ui->label_plusr);          // +
    m_mapKeysPartB.insert(284,ui->label_enterr);        // enterr
    m_mapKeysPartB.insert(285,ui->label_ctlr);          //ctlr
    m_mapKeysPartB.insert(336,ui->label_down);          //Down
    m_mapKeysPartB.insert(328,ui->label_up);            //Up
    m_mapKeysPartB.insert(309,ui->label_divide);        // /
    m_mapKeysPartB.insert(312,ui->label_altl);          //Altl
    m_mapKeysPartB.insert(325,ui->label_num);           //Num
    m_mapKeysPartB.insert(327,ui->label_home);          //Home
    m_mapKeysPartB.insert(329,ui->label_pageup);        //PageUp
    m_mapKeysPartB.insert(331,ui->label_left);          //Left
    m_mapKeysPartB.insert(333,ui->label_right);         //Right
    m_mapKeysPartB.insert(335,ui->label_end);           //End
    m_mapKeysPartB.insert(337,ui->label_pagedown);      //PageDown
    m_mapKeysPartB.insert(338,ui->label_ins);           //Insert
    m_mapKeysPartB.insert(339,ui->label_del);           //Delete
    m_mapKeysPartB.insert(349,ui->label_menu);          //Menu
    m_mapKeysPartB.insert(666,ui->label_tab);           //Tab
    m_mapKeysPartB.insert(777,ui->label_winl);          //Winl
    m_mapKeysPartB.insert(888,ui->label_winr);          //Winr
    m_mapKeysPartB.insert(999,ui->label_prtsc);         //Prtsc

    defaultColor();
}

//键盘配色显示方案
void MainWindow::defaultColor()
{
    //GMK Metropolis
    ui->centralWidget->setStyleSheet("background-color: rgb(35, 35, 35);");                                 //background color
    ui->widget_Keyboard->setStyleSheet("QWidget#widget_Keyboard{ border:none; border-radius:8px; background-color: rgb(0,0,0);}"
                                       "QLabel{ border:none; border-radius:5px; font-size:9px;}");          //keyboard shell color

    QMapIterator<int, QLabel *> itA(m_mapKeysPartA);
    QMapIterator<int, QLabel *> itB(m_mapKeysPartB);
    while (itA.hasNext())
    {
        itA.next();
        itA.value()->setStyleSheet("background-color: rgb(14, 31, 44); color: rgb(85, 195, 183);");         //area A color
    }
    while (itB.hasNext())
    {
        itB.next();
        itB.value()->setStyleSheet("background-color: rgb(14, 31, 44); color: rgb(85, 195, 183);");         //area B color
    }

    //个性化按键配色
    QString styleA = QString("background-color: rgb(14, 31, 44); color: rgb(244, 188, 71);");
    QString styleB = QString("background-color: rgb(14, 31, 44); color: rgb(211, 71, 40);");

    ui->label_esc->setStyleSheet("background-color: rgb(244, 188, 71); color: rgb(14, 31, 44);");           //Esc
    ui->label_altr->setStyleSheet("background-color: rgb(211, 71, 40); color: rgb(14, 31, 44);");
    ui->label_enterl->setStyleSheet("background-color: rgb(85, 195, 183); color: rgb(14, 31, 44);");        //Enterl
    ui->label_enterr->setStyleSheet("background-color: rgb(85, 195, 183); color: rgb(14, 31, 44);");        //Enterr
    ui->label_prtsc->setStyleSheet(styleA);
    ui->label_scrolllock->setStyleSheet(styleA);
    ui->label_pausebreak->setStyleSheet(styleA);
    ui->label_ins->setStyleSheet(styleA);
    ui->label_home->setStyleSheet(styleA);
    ui->label_pageup->setStyleSheet(styleA);
    ui->label_pagedown->setStyleSheet(styleA);
    ui->label_end->setStyleSheet(styleA);
    ui->label_del->setStyleSheet(styleA);
    ui->label_backspace->setStyleSheet(styleA);
    ui->label_num->setStyleSheet(styleA);
    ui->label_divide->setStyleSheet(styleA);
    ui->label_multiply->setStyleSheet(styleA);
    ui->label_minusr->setStyleSheet(styleA);
    ui->label_plusr->setStyleSheet(styleA);
    ui->label_tab->setStyleSheet(styleA);
    ui->label_caps->setStyleSheet(styleA);
    ui->label_shiftl->setStyleSheet(styleB);
    ui->label_ctll->setStyleSheet(styleB);
    ui->label_winl->setStyleSheet(styleB);
    ui->label_altl->setStyleSheet(styleB);
    ui->label_winr->setStyleSheet(styleB);
    ui->label_menu->setStyleSheet(styleB);
    ui->label_ctlr->setStyleSheet(styleB);
    ui->label_shiftr->setStyleSheet(styleB);
    ui->label_up->setStyleSheet(styleB);
    ui->label_down->setStyleSheet(styleB);
    ui->label_left->setStyleSheet(styleB);
    ui->label_right->setStyleSheet(styleB);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->nativeScanCode();  //nativescancode is unique

    if(m_mapKeysPartA.contains(key))
    {
        keyPressedDisplay(m_mapKeysPartA[key]);
    }
    else
    {
        keyPressedDisplay(m_mapKeysPartB[key]);
    }
}

void MainWindow::keyPressedDisplay(QLabel* label)
{
    label->setStyleSheet("background-color: rgb(255, 153, 0);");
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    int key = event->nativeScanCode();

    if(m_mapKeysPartA.contains(key))
    {
        keyReleasedDisplay(m_mapKeysPartA[key]);
    }
    else
    {
        keyReleasedDisplay(m_mapKeysPartB[key]);
    }
}

void MainWindow::keyReleasedDisplay(QLabel *label)
{
    label->setStyleSheet("background-color: rgb(200, 215, 227);");
}

