#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "seqinputview.h"
#include "infoview.h"
#include "tableabstract.h"
#include <QMainWindow>

#include "BLOSUMAlgorithm.h"

namespace Ui {
class MainWindow;
}

using namespace MBI_project::Algorithm;

/**
 * @brief The MainWindow class
 * This class provide main window widget. Here is the main application control.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

	/**
	 * @brief setAlgorithm sets pointer to algorithm object into this class
	 * @details This class doesn't take responsibility for this object life
	 */
	void setAlgorithm(BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType> *alg);

private slots:
    /**
     * @brief on_m_pushButt_Quit_clicked is called after click on Quit button
     * After that application will be closed.
     */
    void on_m_pushButt_Quit_clicked();

    /**
     * @brief on_m_pushButt_SeqInput_clicked is called after click on Sequence input button
     * This open new window which helps with input new sequences.
     */
    void on_m_pushButt_SeqInput_clicked();

    /**
     * @brief on_sequenceProvided is called after accomplished all sequences in Sequence input
     * window and choose DONE button.
     */
    void on_sequenceProvided();

    /**
     * @brief on_m_pushButt_Run_clicked is called after click on RUN button
     * This run blosum algorithm routine, and display results
     * Makes Clear button enabled, but RUN button disabled
     *  (only one algorithm start without clear is permissible)
     */
    void on_m_pushButt_Run_clicked();

    /**
     * @brief on_m_pushButt_Clear_clicked is called after click on Clear button
     * This clear algorithm data (any matrix) from implementation - not from view.
     */
    void on_m_pushButt_Clear_clicked();

    /**
     * @brief on_m_pushButt_Info_clicked
     * Displays additional information about application. Help and authors.
     */
    void on_m_pushButt_Info_clicked();

private:
    Ui::MainWindow *ui;
    // This widget is still the same, because it helps with input sequences.
    SeqInputView seqInView;
    // Window with helpfull information
    InfoView m_infoWidget;

	// Pointer to algorithm object:
	BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType> *m_alg;
};

#endif // MAINWINDOW_H
