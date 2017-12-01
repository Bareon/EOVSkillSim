#include "formuladialog.h"

FormulaDialog::FormulaDialog(QWidget *parent) : QDialog(parent) {
  formulae = new QPlainTextEdit;
  formulae->setReadOnly(1);
  formulae->setPlainText(loadFormText());
  closeButton = new QPushButton(tr("Close"));
  connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

  QVBoxLayout *formulaBox = new QVBoxLayout;
  formulaBox->addWidget(formulae);
  formulaBox->addWidget(closeButton);
  setLayout(formulaBox);

  setWindowTitle("Formulae");
}

QString FormulaDialog::loadFormText() {
  QFile file("EOVFormulae.txt");
  file.open(QFile::ReadOnly | QFile::Text);
  QTextStream in(&file);
  QString formulae;
  while (!in.atEnd()) {
    formulae.append(in.readLine());
    formulae.append("\n");
  }
  file.close();
  return formulae;
}
