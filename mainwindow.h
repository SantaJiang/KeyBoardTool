#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QDebug>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow* getInstance();
    Ui::MainWindow *ui;
    void keyPressedDisplay(QLabel* label);
    void keyReleasedDisplay(QLabel* label);
private:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void initWidget();
    void defaultColor();

    QMap<int,QLabel *> m_mapKeysPartA;
    QMap<int,QLabel *> m_mapKeysPartB;
};

#endif // MAINWINDOW_H
