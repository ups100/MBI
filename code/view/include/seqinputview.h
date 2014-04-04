#ifndef SEQINPUTVIEW_H
#define SEQINPUTVIEW_H

#include <QWidget>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QByteArray>
#include <QVector>
#include <QMessageBox>
#include <QShortcut>

namespace Ui {
class SeqInputView;
}

// Type inherited from Blosum algorithm implementation
typedef QByteArray SequenceType;

/**
 * @brief The SeqInputView class
 * Creates window which allows to bring in some sequence.
 * @details This window provide manual sequence insert or load from file.
 * All sequence can be edited any time.
 * It also allows to export prepared data to new file.
 */
class SeqInputView : public QWidget
{
    Q_OBJECT

public:
    explicit SeqInputView(QWidget *parent = 0);
    ~SeqInputView();

    /**
     * @brief getSequence return all collected sequences
     * @return all sequences
     */
    QVector<SequenceType> getSequence() const;

signals:
    /**
     * @brief done_signal is emitted when Done button was clicked.
     * @details "DONE" button is element of this window
     * which should be clicked after accomplished all sequences.
     */
    void done_signal();

private slots:
    /**
     * @brief on_m_pushButt_Add_clicked is routine which will be called after click on Add button
     * After that action, sequence which is inside m_lineInsert field will be put into sequence list.
     * @notice When this action is performed but no character is put into line edit field,
     * this routine display new window with appropriate information.
     */
    void on_m_pushButt_Add_clicked();

    /**
     * @brief on_m_lineInsert_returnPressed
     * routine is called after Return Key (enter) press when lineInsert is active
     * After that action, sequence which is inside m_lineInsert field will be put into sequence list.
     * @notice When this action is performed but no character is put into line edit field,
     * this routine display new window with appropriate information.
     */
    void on_m_lineInsert_returnPressed();

    /**
     * @brief on_m_pushButt_Delete_clicked routine is called after click on Delete button.
     * It causes that all selected items in sequence list will be deleted.
     */
    void on_m_pushButt_Delete_clicked();

    /**
     * @brief on_m_pushButt_Cancel_clicked routine called after click on Cancel button
     * Then entire window will be closed (not destroy). All data will not be lost.
     * Re-open window should look the same as that which was closed.
     */
    void on_m_pushButt_Cancel_clicked();

    /**
     * @brief on_m_pushButt_Export_clicked is called after click on Export button
     * Display new window - file save window - which allows choose directory and file name.
     * After confirmation of selected file, this routine open it and save all sequence
     * which are inside sequence list.
     */
    void on_m_pushButt_Export_clicked();

    /**
     * @brief on_m_pushButt_Import_clicked is called after click on Import button
     * Display new window - file open window - which choose one file to open and import data.
     * All line is treated as sequence and load into sequence list.
     */
    void on_m_pushButt_Import_clicked();

    /**
     * @brief on_m_pushButt_Done_clicked is called after click on Done button
     * Performing this action user wants to show that all sequences are correct.
     * Window is closed but not distroy - it will be used to get all sequences to move it into algorithm.
     */
    void on_m_pushButt_Done_clicked();

    /**
     * @brief on_m_pushButt_Edit_clicked is called after click on Edit button
     * After this action the selected item could be edited.
     */
    void on_m_pushButt_Edit_clicked();
private:

    /**
     * @brief checkGivenSeq check if all given sequences has the same length
     * @details This method takes length of first sequence as reference length and check if all next has the same.
     * If a sequence don't have the same size, then this sequence is selected (highlighted)
     * @return true if sequences are correct; false when some of them have different lenght
     */
    bool checkGivenSeq() const;

	/**
	 * @brief readMbiFiles function is used when somebody imports file with extension .mbi
	 * The .mbi file intentionally is used to testing this project.
	 * The file contains some sequences which are separated by semicolon 
	 * and after that there is some strings with structure string=number; (also separated by semicolon)
	 * This second part is not interesting for SeqInputView so it is ignored.
	 * To sum up, this function read first part of the .mbi file which contains sequences separated by semicolons.
	 */
	void readMbiFiles(QFile &file);

    Ui::SeqInputView *ui;

    // shortcut to close window
    QShortcut m_esc;
};

#endif // SEQINPUTVIEW_H
