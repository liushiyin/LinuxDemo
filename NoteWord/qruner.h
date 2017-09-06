#ifndef QRUNER_H
#define QRUNER_H

#include <QDialog>
#include<QProcess>

namespace Ui {
class QRuner;
}

class QRuner : public QDialog
{
    Q_OBJECT

public:
    explicit QRuner(QWidget *parent = 0);
    ~QRuner();

private slots:
    void on_okBtn_clicked();

    void on_cancelBtn_clicked();

    void on_RunEdit_returnPressed();

private:
    Ui::QRuner *ui;
};

#endif // QRUNER_H
