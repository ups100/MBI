#ifndef SEQINPUTVIEW_H
#define SEQINPUTVIEW_H

#include <QWidget>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QByteArray>
#include <QVector>
#include <QMessageBox>

namespace Ui {
class SeqInputView;
}

typedef QByteArray SequenceType;

class SeqInputView : public QWidget
{
    Q_OBJECT

public:
    explicit SeqInputView(QWidget *parent = 0);
    ~SeqInputView();

    QVector<SequenceType> getSequence() const;

signals:
    void done_signal();

private slots:
    void on_m_pushButt_Add_clicked();

    void on_m_lineInsert_returnPressed();

    void on_m_pushButt_Delete_clicked();

    void on_m_pushButt_Cancel_clicked();

    void on_m_pushButt_Export_clicked();

    void on_m_pushButt_Import_clicked();

    void on_m_pushButt_Done_clicked();

private:
    Ui::SeqInputView *ui;
};

#endif // SEQINPUTVIEW_H
