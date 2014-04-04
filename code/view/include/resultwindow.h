#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include "tableabstract.h"
#include <QMainWindow>

namespace Ui {
class ResultWindow;
}

/**
 * @brief The ResultWindow class
 * This class provide interface to display results of BLOSUM algorithm calculations.
 * @details It creates new main window with results.
 */
class ResultWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief ResultWindow Constructor
     * @param dim Result matrix dimmension. I suppose that matrix is square.
     * @param parent Pointer to parent widget. By default NULL.
     */
    explicit ResultWindow(int dim, QWidget *parent = 0);
    ~ResultWindow();

    /**
     * @brief showBlosumMat insert data into Blosum matrix result Tab.
     * @param m Pointer to data. Type of this pointer is prepared espacially
     * for algorithm implementation.
     * This data will be coverted into class internal type (integer value convert into double)
     */
    void showBlosumMat(const IntMatrix *m);

    /**
     * @brief showSubstMat insert data into substitution matrix result Tab.
     * @param m is pointer to substitution matrix.
     * This data will be coverted into class internal type (integer value convert into double)
     */
    void showSubstMat(const IntMatrix *m);

    /**
     * @brief showProbMat displays probability matrix.
     * @param m is pointer to probability matrix data
     */
    void showProbMat(TMatrix *m);

    /**
     * @brief showLogsMat displays logarithm of probabilities matrix
     * @param m is pointer to logarithms matrix
     */
    void showLogsMat(TMatrix *m);

public slots:
    /**
     * @brief changeViewToTable calls changeView() function with Table parameter
     * @see ResultWindow::changeView() and ViewStyle::Table
     */
    void changeViewToTable();
    /**
     * @brief changeViewToText calls changeView() function with PlainText parameter
     * @see ResultWindow::changeView() and ViewStyle::PlainText
     */
    void changeViewToText();
    /**
     * @brief saveToCSV calls saveAs() routine with separator set to coma character with space after coma
     * @see ResultWindow::saveAs()
     */
    void saveToCSV();
    /**
     * @brief saveToCSVsemicolon calls saveAs() routine with semicolon with space as separator sign
     * @see ResultWindow::saveAs()
     */
    void saveToCSVsemicolon();
    /**
     * @brief saveToText calls saveAs() routine with single space as separator sign
     * @see ResultWindow::saveAs()
     */
    void saveToText();

private:
    /**
     * @brief makeTabs Prepare all Tab widgets with all their contents.
     * @param vs is a flag to tell which view style will be used to display matrix in each tab
     * @details This routine may be call only when ResultWindow::ui->m_tabWidget is empty,
     * which is signalised by ResultWindow::m_vs set to None.
     * This function is used by constructor and changeView after clean all tabs.
     * @see ViewStyle, ResultWindow::changeViewToTable(), ResultWindow::changeViewToText()
     */
    void makeTabs(ViewStyle vs);

    /**
     * @brief changeView change style of matrix visualise in each tab. There is table style and plain text style.
     * @param vs is the selector to choose style.
     * @details If current style is the same as proposed new style, then this function do nothing.
     * @see ViewStyle
     */
    void changeView(ViewStyle vs);

    /**
     * @brief saveAs saves matrix to a file using sep as separator between values.
     * @details Only this matrix whose Tab is active will be saved.
     * @param sep are characters which will be put between each two value of matrix.
     * No separator will be put on the end of line (on the end of matrix row).
     * @see ViewStyle, ResultWindow::saveToCSV(), ResultWindow::saveToCSVsemicolon(), ResultWindow::saveToText()
     */
    void saveAs(QString sep);

    /**
     * @brief showAllMat Calls all show*Mat functions.
     * @details This function is used after changing of View Style
     * This means that in m_*Data variables there is prepared data to display.
     */
    void showAllMat();

private:
    // User Interface
    Ui::ResultWindow *ui;

    // Dimmension of each result matrix
    const int m_dim;

    // Raw data - each matrix values.
    TMatrix *m_blosumData;
    TMatrix *m_substData;
    TMatrix *m_probData;
    TMatrix *m_logsData;

    // Pointer to widget which presents matrix (table or plain text)
    TableAbstract *m_matBlosum;
    TableAbstract *m_matSubst;
    TableAbstract *m_matProb;
    TableAbstract *m_matLogs;

    // Current view style (table or plain text)
    ViewStyle m_vs;

    //Tab widgets:
    QWidget *m_tab_1;
    QWidget *m_tab_2;
    QWidget *m_tab_3;
    QWidget *m_tab_4;
};

#endif // RESULTWINDOW_H
