#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "seqinputview.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_m_pushButt_Quit_clicked();

    void on_m_pushButt_SeqInput_clicked();

    void on_sequenceProvided();

private:
    Ui::MainWindow *ui;
    SeqInputView seqInView;
};

#endif // MAINWINDOW_H
