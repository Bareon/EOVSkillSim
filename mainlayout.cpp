#include "mainlayout.h"
#include "linedraw.h"

#include <QtWidgets>
#include <QDebug>

MainLayout::MainLayout(QWidget *parent) : QWidget(parent) {
  setupLayout();
}

//Initializes and creates main layout widgets for simulator
void MainLayout::setupLayout() {
  db = QSqlDatabase::addDatabase("QSQLITE");
  QDir dir(QApplication::applicationDirPath());
  db.setDatabaseName(dir.filePath("EOVSkills.db"));
  db.open();

//Character stats
  QHBoxLayout *charStats = new QHBoxLayout;
  QLabel *raceLabel = new QLabel(tr("Race:"));
  raceLabel->setMaximumWidth(30);

  raceBox = new QComboBox;
  raceBox->setMinimumWidth(70);
  raceBox->setMaximumWidth(70);
  raceBox->setMinimumHeight(25);
  raceBox->setObjectName("Race");
  setRaces();
  connect(raceBox,SIGNAL(currentTextChanged(QString)),this,SLOT(setSkillsR()));


  QLabel *classLabel = new QLabel(tr("Class:"));
  classLabel->setMaximumWidth(30);
  classBox = new QComboBox;
  classBox->setMinimumWidth(90);
  classBox->setMaximumWidth(90);
  classBox->setMinimumHeight(25);
  classBox->setObjectName("Class");
  setClasses();
  connect(classBox,SIGNAL(currentTextChanged(QString)),this,SLOT(classChanged()));

  masterBox = new QComboBox;
  masterBox->setMinimumWidth(100);
  masterBox->setMaximumWidth(100);
  masterBox->setMinimumHeight(25);
  connect(masterBox,SIGNAL(currentTextChanged(QString)),this,SLOT(masteryChanged()));

  level = new QSpinBox;
  level->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
  level->setMaximumWidth(50);
  level->setMinimumHeight(25);
  level->setPrefix(tr("Lv."));
  level->setMinimum(1);
  level->setMaximum(99);
  connect(level,SIGNAL(valueChanged(int)),this,SLOT(updateSkillPts()));

  ret = new QCheckBox;
  ret->setMaximumWidth(60);
  ret->setText("Retired?");
  connect(ret,SIGNAL(toggled(bool)),this,SLOT(updateSkillPts()));

  retLevel = new QSpinBox;
  retLevel->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
  retLevel->setMaximumWidth(50);
  retLevel->setMinimumHeight(25);
  retLevel->setPrefix(tr("Lv."));
  retLevel->setMinimum(30);
  retLevel->setMaximum(99);
  retLevel->setDisabled(true);
  connect(retLevel,SIGNAL(valueChanged(int)),this,SLOT(updateSkillPts()));
  connect(ret,SIGNAL(toggled(bool)),retLevel,SLOT(setEnabled(bool)));


  resetButton = new QPushButton(tr("Reset"));
  resetButton->setMinimumHeight(25);
  connect(resetButton,SIGNAL(clicked(bool)),this,SLOT(resetSkills()));

  charStats->addWidget(raceLabel);
  charStats->addWidget(raceBox);
  charStats->addWidget(classLabel);
  charStats->addWidget(classBox);
  charStats->addWidget(masterBox);
  charStats->addWidget(level);
  charStats->addWidget(ret);
  charStats->addWidget(retLevel);
  charStats->addWidget(resetButton);
  charStats->setAlignment(Qt::AlignLeft);

//Skill Points counter
  QHBoxLayout *skillPtsBox = new QHBoxLayout;
  QLabel *skillPtsLabel = new QLabel(tr("Skill Points: "));
  skillPtsValue = new QLabel(QString::number(skillPts));
  skillPtsBox->addWidget(skillPtsLabel);
  skillPtsBox->addWidget(skillPtsValue);
  skillPtsBox->setAlignment(Qt::AlignLeft);

//Race Skills tab
  raceTab = new QWidget;
  raceSkillsBox = new QGridLayout;
  raceLv1 = new QGroupBox(tr("Lv. 1"));
  raceLv5 = new QGroupBox(tr("Lv. 5"));
  raceLv10 = new QGroupBox(tr("Lv. 10"));
  raceLv15 = new QGroupBox(tr("Lv. 15"));
  raceLv20 = new QGroupBox(tr("Lv. 20"));
  raceLv1->setFlat(true);
  raceLv1->setAlignment(Qt::AlignHCenter);
  raceLv5->setFlat(true);
  raceLv5->setAlignment(Qt::AlignHCenter);
  raceLv10->setFlat(true);
  raceLv10->setAlignment(Qt::AlignHCenter);
  raceLv15->setFlat(true);
  raceLv15->setAlignment(Qt::AlignHCenter);
  raceLv20->setFlat(true);
  raceLv20->setAlignment(Qt::AlignHCenter);

  QGridLayout *raceLv1Grid = new QGridLayout;
  raceLv1Grid->setSizeConstraint(QLayout::SetFixedSize);
  raceLv1Grid->setVerticalSpacing(15);
  QGridLayout *raceLv5Grid = new QGridLayout;
  raceLv5Grid->setSizeConstraint(QLayout::SetFixedSize);
  QGridLayout *raceLv10Grid = new QGridLayout;
  raceLv10Grid->setSizeConstraint(QLayout::SetFixedSize);
  QGridLayout *raceLv15Grid = new QGridLayout;
  raceLv15Grid->setSizeConstraint(QLayout::SetFixedSize);
  QGridLayout *raceLv20Grid = new QGridLayout;
  raceLv20Grid->setSizeConstraint(QLayout::SetFixedSize);
  for (int i = 0; i < numRaceSkills; ++i) {
    raceSet[i] = new QHBoxLayout;
    raceButtons[i] = new QPushButton("Skill");
    raceButtons[i]->setMinimumWidth(80);
    raceButtons[i]->setMinimumHeight(32);
    connect(raceButtons[i],SIGNAL(clicked(bool)),this,SLOT(updateDescRace()));
    raceChecks[i] = new QCheckBox;
    if (i < 4) {
      raceChecks[i]->setChecked(true);
      raceChecks[i]->setEnabled(false);
    }
    connect(raceChecks[i],SIGNAL(toggled(bool)),this,SLOT(updateSkillPts()));
    connect(raceChecks[i],SIGNAL(toggled(bool)),this,SLOT(checkReqsR()));
    connect(raceChecks[i],SIGNAL(toggled(bool)),raceButtons[i],SIGNAL(clicked(bool)));
    raceSet[i]->addWidget(raceButtons[i]);
    raceSet[i]->addWidget(raceChecks[i]);
    raceSet[i]->setSpacing(2);
  }

  //TODO: Logic this
  raceLv1Grid->addLayout(raceSet[0],0,0);
  raceLv1Grid->addLayout(raceSet[1],0,1);
  raceLv1Grid->addLayout(raceSet[2],1,0);
  raceLv1Grid->addLayout(raceSet[3],1,1);
  raceLv1Grid->addLayout(raceSet[4],2,0);
  raceLv1Grid->addLayout(raceSet[5],2,1);
  raceLv1Grid->addLayout(raceSet[6],3,0);
  raceLv1Grid->addLayout(raceSet[7],3,1);
  raceLv5Grid->addLayout(raceSet[8],0,0);
  raceLv5Grid->addLayout(raceSet[9],0,1);
  raceLv5Grid->addLayout(raceSet[10],1,0);
  raceLv5Grid->addLayout(raceSet[11],1,1);
  raceLv10Grid->addLayout(raceSet[12],0,0);
  raceLv10Grid->addLayout(raceSet[13],0,1);
  raceLv10Grid->addLayout(raceSet[14],1,0);
  raceLv10Grid->addLayout(raceSet[15],1,1);
  raceLv15Grid->addLayout(raceSet[16],0,0);
  raceLv15Grid->addLayout(raceSet[17],0,1);
  raceLv15Grid->addLayout(raceSet[18],1,0);
  raceLv15Grid->addLayout(raceSet[19],1,1);
  raceLv20Grid->addLayout(raceSet[20],0,0);
  raceLv20Grid->addLayout(raceSet[21],0,1);
  raceLv20Grid->addLayout(raceSet[22],1,0);
  raceLv20Grid->addLayout(raceSet[23],1,1);
  //

  raceLv1->setLayout(raceLv1Grid);
  raceLv5->setLayout(raceLv5Grid);
  raceLv10->setLayout(raceLv10Grid);
  raceLv15->setLayout(raceLv15Grid);
  raceLv20->setLayout(raceLv20Grid);

  raceSkillsBox->addWidget(raceLv1,0,0,2,1);
  raceSkillsBox->addWidget(raceLv5,2,0);
  raceSkillsBox->addWidget(raceLv10,0,1);
  raceSkillsBox->addWidget(raceLv15,1,1);
  raceSkillsBox->addWidget(raceLv20,2,1);
  raceSkillsBox->setSpacing(5);
  raceTab->setLayout(raceSkillsBox);


//Class Skills tab
  //Initialize Skill Positions
  for (int i = 0; i < numSkillPos;) {
    QPair<int,int> pair;
    for (int y = 0; y <= 1; y++) {
      for (int x = 0; x <= 6; x++) {
        pair.first = x;
        pair.second = y;
        skillPos.insert(i,pair);
        ++i;
      }
    }
  }
  QHBoxLayout *charSkills = new QHBoxLayout;
  QTabWidget *charSkillsTabs = new QTabWidget;
  classTab = new QWidget;
  classSkillsBox = new QHBoxLayout;

  baseSkills = new QGridLayout;
  baseSkills->setHorizontalSpacing(5);
  baseSkills->setVerticalSpacing(10);
  baseSkills->setContentsMargins(0,5,0,0);
  baseSkills->setSizeConstraint(QLayout::SetFixedSize);

  masterSkills = new QGridLayout;
  masterSkills->setHorizontalSpacing(5);
  masterSkills->setVerticalSpacing(10);
  masterSkills->setContentsMargins(0,5,0,0);
  masterSkills->setSizeConstraint(QLayout::SetFixedSize);

  baseSkillsBox = new QGroupBox(tr("Base"));
  baseSkillsBox->setFlat(true);
  baseSkillsBox->setAlignment(Qt::AlignHCenter);

  masterSkillsBox = new QGroupBox(tr("Master"));
  masterSkillsBox->setFlat(true);
  masterSkillsBox->setAlignment(Qt::AlignHCenter);

  for (int i = 0; i < numClassSkills; ++i) {
    classSet[i] = new QHBoxLayout;
    QString skillName("Skill");
    classButtons[i] = new QPushButton(skillName);
    classButtons[i]->setMinimumWidth(90);
    classButtons[i]->setMaximumWidth(90);
    classButtons[i]->setMinimumHeight(32);

    classSkillLv[i] = new QSpinBox;
    classSkillLv[i]->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
    classSkillLv[i]->setParent(classButtons[i]);
    classSkillLv[i]->setMaximumWidth(50);
    classSkillLv[i]->setPrefix("Lv.");
    classSkillLv[i]->setObjectName(classButtons[i]->text());
    classSkillLv[i]->setMinimumHeight(30);

    connect(classButtons[i],SIGNAL(clicked(bool)),this,SLOT(updateDescClass()));
    connect(classSkillLv[i],SIGNAL(valueChanged(int)),this,SLOT(updateSkillPts()));
    connect(classSkillLv[i],SIGNAL(valueChanged(int)),this,SLOT(updateDescClass()));
    connect(classSkillLv[i],SIGNAL(valueChanged(int)),this,SLOT(checkDeps()));
    connect(classSkillLv[i],SIGNAL(valueChanged(int)),this,SLOT(checkReqs()));
    classSet[i]->addWidget(classButtons[i]);
    classSet[i]->addWidget(classSkillLv[i]);

    if (i < 10) {
      baseSkills->addLayout(classSet[i],skillPos[i].first,skillPos[i].second);
    } else {
      masterSkills->addLayout(classSet[i],skillPos[i-10].first,skillPos[i-10].second);
    }
  }

  for (int i = 0; i < 8; ++i) {
    nullSet[i] = new QHBoxLayout;
    QString skillName("Null");
    nullButtons[i] = new QPushButton(skillName);
    nullButtons[i]->setMinimumWidth(90);
    nullButtons[i]->setMaximumWidth(90);
    nullButtons[i]->setMinimumHeight(32);
    nullSkillLv[i] = new QSpinBox;
    nullSkillLv[i]->setMaximumWidth(50);
    nullSkillLv[i]->setPrefix("Lv.");
    nullSkillLv[i]->setMinimumHeight(30);
    nullSet[i]->addWidget(nullButtons[i]);
    nullSet[i]->addWidget(nullSkillLv[i]);
    QSizePolicy sp_retainB = nullButtons[i]->sizePolicy();
    QSizePolicy sp_retainS = nullSkillLv[i]->sizePolicy();
    sp_retainB.setRetainSizeWhenHidden(true);
    sp_retainS.setRetainSizeWhenHidden(true);
    nullButtons[i]->setSizePolicy(sp_retainB);
    nullButtons[i]->setVisible(0);
    nullSkillLv[i]->setSizePolicy(sp_retainS);
    nullSkillLv[i]->setVisible(0);
  }

  baseSkillsBox->setLayout(baseSkills);
  masterSkillsBox->setLayout(masterSkills);

  classSkillsBox->addWidget(baseSkillsBox);
  classSkillsBox->addWidget(masterSkillsBox);

  classTab->setLayout(classSkillsBox);

  charSkillsTabs->addTab(raceTab, "Race");
  charSkillsTabs->addTab(classTab, "Class");
  charSkillsTabs->setCurrentIndex(1);
  skillDesc = new QPlainTextEdit;
  skillDesc->setReadOnly(1);
  charSkills->addWidget(charSkillsTabs);
  charSkills->addWidget(skillDesc);
  //auto* lineDraw = new LineDraw(classButtons[0], classButtons[15]);
  //lineDraw->setLayout(classSkillsBox);
  //LineDraw *draw = new LineDraw;
  //draw->addWidgets(classButtons[0],classButtons[12]);


//Combine layouts and set mainLayout
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addLayout(charStats);
  mainLayout->addLayout(skillPtsBox);
  mainLayout->addLayout(charSkills);
  //mainLayout->addWidget(draw);
  setLayout(mainLayout);
  update();

}

//Recalculates available Skill Points, connected to inputs with
//any sort of allocation or change in Class, Mastery, or Race
void MainLayout::updateSkillPts() {
  retPts = 0;
  ptsTotal = 0;
  if (ret->checkState() == 2) {
    retLv = retLevel->value();
    if ( 30 <= retLv && retLv < 40) {
      retPts = 4;
    } else if ( 40 <= retLv && retLv < 50) {
      retPts = 5;
    } else if ( 50 <= retLv && retLv < 60) {
      retPts = 6;
    } else if ( 60 <= retLv && retLv < 70) {
      retPts = 7;
    } else if ( 70 <= retLv && retLv < 98) {
      retPts = 8;
    } else if ( retLv == 99) {
      retPts = 10;
    }
    if (level->value() < 15) {
      level->setValue(15);
    }
  }

  ptsAlloc = 0;
  for (int i=4; i<24; ++i) {
    if(raceChecks[i]->isChecked()) {
          ptsAlloc++;
      }
  }
  for(int i=0; i < numClassSkills; ++i) {
    ptsAlloc += classSkillLv[i]->value();
    while (i >= 10 && classSkillLv[i]->value() > 0 && level->value() < 20) {
        level->setValue(20);
    }
  }

  if (level->value() >= 20) {
    ptsTotal = 7 + level->value() + retPts;
    skillPts = ptsTotal - ptsAlloc;
  } else {
    ptsTotal = 2 + level->value() + retPts;
    skillPts = ptsTotal - ptsAlloc;
  }
  while (skillPts < 0 && level->value() < 99) {
    level->setValue(level->value() - skillPts);
    skillPts = 0;
  }
  skillPtsValue->setNum(skillPts);
}

//Fills Skill description textbox with Race Skill details
//Connected to Skill buttons and levels
void MainLayout::updateDescRace() {
  QString skill = QObject::sender()->property("text").toString();
  QSqlQuery query;
  QString race = raceBox->currentText();
  query.prepare("SELECT desc, descUse, reqLv"
                " FROM RaceSkills WHERE race = :race and name= :skill");
  query.bindValue(":race",race);
  query.bindValue(":skill",skill);
  query.exec();
  query.next();
  QString desc = skill + " - " + query.value(1).toString()
    +"\n*****\nRequirement:\nLv. " + query.value(2).toString() + "\n\n"
    + query.value(0).toString();

  skillDesc->setPlainText(desc);
}

//Fills Skill description textbox with Class Skill details
//Connected to Skill buttons and levels
void MainLayout::updateDescClass() {
  QString skill = QObject::sender()->objectName();
  QSqlQuery query;
  QString job = classBox->currentText();
  query.prepare("SELECT desc, descUse, descLv, req1, req1Lv, req2, req2Lv, req3, req3Lv"
    " FROM ClassSkills WHERE class = :job and name= :skill");
  query.bindValue(":job",job);
  query.bindValue(":skill",skill);
  query.exec();
  query.next();
  QString desc = skill + " - " + query.value(1).toString() + "\n*****\nRequirement:\n";
  if (query.value(3) != "") {
      for (int i = 3; query.value(i) != "" && i < 8; i+=2) {
        desc+= query.value(i).toString() + " Lv. " + query.value(i+1).toString() + "\n";
      }
      desc+= "\n";
  } else {
    desc+= "None\n\n";
  }
  desc+= query.value(0).toString() + "\n\n";
  desc+= query.value(2).toString();

  skillDesc->setPlainText(desc);
}

//Resets Skill Point allocation, for Reset button
void MainLayout::resetSkills() {
  for (int i=0; i < numClassSkills; ++i) {
    classSkillLv[i]->blockSignals(true);
    classSkillLv[i]->setValue(0);
    raceChecks[i+4]->setChecked(false);
    classSkillLv[i]->blockSignals(false);
  }
  skillDesc->clear();
  updateSkillPts();
}

//Sets Class masteries to dropdown box
void MainLayout::setMasteries() {
  masterBox->clear();
  QSqlQuery query;
  QString job = classBox->currentText();
  query.prepare("SELECT DISTINCT rank FROM ClassSkills WHERE class = :job and rank != :base");
  query.bindValue(":job",job);
  query.bindValue(":base", "Base");
  query.exec();
  while (query.next()) {
    masterBox->addItem(query.value(0).toString());
  }
}

//Updates Race Skill buttons with active Race, resets allocation
void MainLayout::setSkillsR() {
  skillMapR.clear();
  QSqlQuery query;
  QString race = raceBox->currentText();
  query.prepare("SELECT name, reqLv FROM RaceSkills WHERE race = :race");
  query.bindValue(":race",race);
  query.exec();
  for (int i = 0; i < numRaceSkills; ++i) {
    query.next();
    QString skillName = query.value(0).toString();
    raceButtons[i]->setText(skillName);
      if (i > 3) {
        raceChecks[i]->setChecked(false);
      }
    skillMapR.insert(i,query.value(1).toInt());
  }
}

//Updates Base Skill buttons with active Class, resets allocation
void MainLayout::setSkillsB() {
  QSqlQuery query;
  QString job = classBox->currentText();
  query.prepare("SELECT name, max FROM ClassSkills WHERE class = :job AND rank = 'Base'");
  query.bindValue(":job",job);
  query.exec();
  for (int i = 0; i < 10; ++i) {
    query.next();
    QString skillName = query.value(0).toString();
    int skillMax = query.value(1).toInt();
    classButtons[i]->setText(skillName);
    classButtons[i]->setObjectName(skillName);
    classSkillLv[i]->setMaximum(skillMax);
    classSkillLv[i]->setValue(0);
    classSkillLv[i]->setObjectName(skillName);
    skillMap.insert(skillName,i);
    baseSkills->removeItem(classSet[i]);
    if (i < 4) {
      baseSkills->removeItem(nullSet[i]);
    }
  }


  query.prepare("SELECT slot FROM ClassSkills WHERE class = :job AND rank = 'Base'");
  query.bindValue(":job",job);
  query.exec();
  for (int i = 0; i < 10; ++i) {
    query.next();
    int slot = query.value(0).toInt();
    baseSkills->addLayout(classSet[i]
     , skillPos[slot].first
     , skillPos[slot].second);
  }
  int i=0;
  for (int y = 0; y <= 1; ++y) {
    for (int x = 0; x <= 6; ++x) {
      if (baseSkills->itemAtPosition(x,y) == 0) {
        baseSkills->addLayout(nullSet[i],x,y);
        ++i;
      }
    }
  }
}

//Updates Master Skill buttons with active Class, resets Master Skill allocation
void MainLayout::setSkillsM() {
  QSqlQuery query;
  QString job = classBox->currentText();
  QString mastery = masterBox->currentText();
  query.prepare("SELECT name, max FROM ClassSkills WHERE class = :job AND rank = :mastery");
  query.bindValue(":job",job);
  query.bindValue(":mastery",mastery);
  query.exec();
  for (int i = 10; i < numClassSkills; ++i) {
      query.next();
      QString skillName = query.value(0).toString();
      int skillMax = query.value(1).toInt();
      classButtons[i]->setText(skillName);
      classButtons[i]->setObjectName(skillName);
      classSkillLv[i]->setMaximum(skillMax);
      classSkillLv[i]->setValue(0);
      classSkillLv[i]->setObjectName(skillName);
      skillMap.insert(skillName,i);
      masterSkills->removeItem(classSet[i]);
      //if (i < 4) {
      //  masterSkills->removeItem(nullSet[i+4]);
     // }
    }
  query.prepare("SELECT slot FROM ClassSkills WHERE class = :job AND rank = :mastery");
  query.bindValue(":job",job);
  query.bindValue(":mastery",mastery);
  query.exec();
  for (int i = 10; i < numClassSkills; ++i) {
    query.next();
    int slot = query.value(0).toInt();
    masterSkills->addLayout(classSet[i]
     , skillPos[slot].first
     , skillPos[slot].second);
  }
  int i=4;
  for (int y = 0; y <= 1; ++y) {
    for (int x = 0; x <= 6; ++x) {
      if (masterSkills->itemAtPosition(x,y) == 0) {
        masterSkills->addLayout(nullSet[i],x,y);
        ++i;
      }
    }
  }
}

void MainLayout::checkReqsR() {
  for (int i = 8; i < numRaceSkills; ++i) {
    if (raceChecks[i]->isChecked() && skillMapR.value(i) > level->value()) {
      level->setValue(skillMapR.value(i));
    }
  }
}

//Checks for valid Skill requirements, allocates if not
void MainLayout::checkReqs() {
  QString skill = QObject::sender()->objectName();
  QString job = classBox->currentText();
  QSqlQuery query;

  query.prepare("SELECT req1, req1Lv, req2, req2Lv, req3, req3Lv"
    " FROM ClassSkills WHERE class = :job and name= :skill and req1 != :null");
  query.bindValue(":job",job);
  query.bindValue(":skill",skill);
  query.bindValue(":null","NULL");
  query.exec();
  query.next();
  if (!query.isNull(0)) {
    int req1Ind = skillMap.value(query.value(0).toString());
    int req1Lv = query.value(1).toInt();
    int req1LvCu = classSkillLv[req1Ind]->value();
    if (req1LvCu < req1Lv) {
      classSkillLv[req1Ind]->blockSignals(true);
      classSkillLv[req1Ind]->setValue(req1Lv);
      classSkillLv[req1Ind]->blockSignals(false);
    }
  }

  if (!query.isNull(2)) {
    int req2Ind = skillMap.value(query.value(2).toString());
    int req2Lv = query.value(3).toInt();
    int req2LvCu = classSkillLv[req2Ind]->value();
    if (req2LvCu < req2Lv) {
      classSkillLv[req2Ind]->blockSignals(true);
      classSkillLv[req2Ind]->setValue(req2Lv);
      classSkillLv[req2Ind]->blockSignals(false);
    }
  }

  if (!query.isNull(4)) {
    int req3Ind = skillMap.value(query.value(4).toString());
    int req3Lv = query.value(5).toInt();
    int req3LvCu = classSkillLv[req3Ind]->value();
    if (req3LvCu < req3Lv) {
      classSkillLv[req3Ind]->blockSignals(true);
      classSkillLv[req3Ind]->setValue(req3Lv);
      classSkillLv[req3Ind]->blockSignals(false);
    }
  }
}

//Checks if updated Skill has dependencies, clears dep if below threshold
void MainLayout::checkDeps() {
  QString skill = QObject::sender()->objectName();
  int skillId = skillMap.value(skill);
  QString job = classBox->currentText();
  QString rank = masterBox->currentText();
  QSqlQuery query;
  int skillRevId;

  query.prepare("SELECT name, rank, req1, req1Lv, req2, req2Lv, req3, req3Lv"
    " FROM ClassSkills WHERE class = :job and req1 != :null"
    " and (rank = :base or rank = :master)");
  query.bindValue(":job",job);
  query.bindValue(":base","Base");
  query.bindValue(":master",rank);
  query.bindValue(":null","NULL");

  query.exec();
  while (query.next()) {
    skillRevId = skillMap.value(query.value(0).toString());
    if (skill == query.value(2).toString()
      && classSkillLv[skillId]->value() < query.value(3).toInt()
      && classSkillLv[skillRevId]->value() > 0) {
          classSkillLv[skillRevId]->setValue(0);
          classSkillLv[skillId]->setValue(classSkillLv[skillId]->value()-1);
    }
    if (skill == query.value(4).toString()
      && classSkillLv[skillId]->value() < query.value(5).toInt()
      && classSkillLv[skillRevId]->value() > 0) {
          classSkillLv[skillRevId]->setValue(0);
          classSkillLv[skillId]->setValue(classSkillLv[skillId]->value()-1);
    }
    if (skill == query.value(6).toString()
      && classSkillLv[skillId]->value() < query.value(7).toInt()
      && classSkillLv[skillRevId]->value() > 0) {
          classSkillLv[skillRevId]->setValue(0);
          classSkillLv[skillId]->setValue(classSkillLv[skillId]->value()-1);
    }
  }
}

//Sets Races from DB to raceBox
void MainLayout::setRaces() {
  QSqlQuery query;
  query.prepare("SELECT DISTINCT race FROM RaceSkills");
  query.exec();
  while (query.next()) {
    raceBox->addItem(query.value(0).toString());
  }
}

//Sets Classes from DB to classBox
void MainLayout::setClasses() {
  QSqlQuery query;
  query.prepare("SELECT DISTINCT class FROM ClassSkills");
  query.exec();
  while (query.next()) {
    classBox->addItem(query.value(0).toString());
  }
}

//Updates all Class Skill buttons when Class is changed, resets Class Skill allocation
void MainLayout::classChanged() {
  skillMap.clear();
  //for (int i=0; i < numClassSkills; ++i) {
  //  classSkillLv[i]->blockSignals(true);
  //}
  skillDesc->clear();
  classBox->blockSignals(true);
  masterBox->blockSignals(true);
  for (int i=0; i < numClassSkills; ++i) {
    classButtons[i]->blockSignals(true);
    classSkillLv[i]->blockSignals(true);
  }
  setSkillsB();
  setMasteries();
  setSkillsM();
  for (int i=0; i < numClassSkills; ++i) {
    classButtons[i]->blockSignals(false);
    classSkillLv[i]->blockSignals(false);
  }
  classBox->blockSignals(false);
  masterBox->blockSignals(false);
}

//Updates Master Skill buttons to selected mastery, resets Master Skill allocation
void MainLayout::masteryChanged() {
  for (int i=10; i < numClassSkills; ++i) {
    classButtons[i]->blockSignals(true);
    classSkillLv[i]->blockSignals(true);
    skillMap.remove(classButtons[i]->text());
  }
  setSkillsM();
  for (int i=10; i < numClassSkills; ++i) {
    classButtons[i]->blockSignals(false);
    classSkillLv[i]->blockSignals(false);
  }
}

//Not implemented yet, should change to Race or Class tab when either value is changed
void MainLayout::setActiveTab() {
  charSkillsTabs->setCurrentIndex(1);
}

//Format for exporting build to text file
QString MainLayout::writeBuild() {
  QString build;
  QString race = raceBox->currentText();
  QString job = classBox->currentText();
  QString mastery = masterBox->currentText();
  QString lv = QString::number(level->value());
  QString rLv = QString::number(retLv);
  QString sp = skillPtsValue->text();
  QString spTot = QString::number(ptsTotal);
  if (ret->isChecked()) {
    build += "Lv. " + lv + "(" + rLv + ") "
      + race + " " + job + " - " + mastery + "\n";
  } else {
    build += "Lv. " + lv + " " + race + " " + job + " - " + mastery + "\n";
  }
  build += "\nSkill Points Remaining: " + sp + "/" + spTot + "\n\nBase:\n";
  for (int i=0; i < 10; ++i) {
    if (classSkillLv[i]->value() > 0) {
      build += " " + classButtons[i]->text() + " - "
        + QString::number(classSkillLv[i]->value()) + "\n";
    }
  }
  build += "\n" + mastery + ":\n";
  for (int i=10; i < numClassSkills; ++i) {
    if (classSkillLv[i]->value() > 0) {
      build += " " + classButtons[i]->text() + " - "
        + QString::number(classSkillLv[i]->value()) + "\n";
    }
  }
  build += "\n" + race + ":\n";
  for (int i=4; i < numRaceSkills; ++i) {
    if (raceChecks[i]->isChecked()) {
      build += " " + raceButtons[i]->text() + "\n";
    }
  }

  return build;
}

/*
void MainLayout::paintEvent(QPaintEvent *e) {
  QPainter painter(this);
  QPoint start = classButtons[0]->rect().center();
  QPoint end = classButtons[5]->rect().center();
  painter.drawLine(500,500,100,100);
  painter.drawLine(start,end);
}*/
