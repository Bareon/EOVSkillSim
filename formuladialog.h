#ifndef FORMULADIALOG_H
#define FORMULADIALOG_H

#include <QDialog>
#include <QtWidgets>
#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
class QPushButton;
QT_END_NAMESPACE

class FormulaDialog : public QDialog {
  Q_OBJECT

  public:
    FormulaDialog(QWidget *parent);
    QString loadFormText();

  private:
    QPlainTextEdit *formulae;
    QPushButton *closeButton;


};

#endif // FORMULADIALOG_H
