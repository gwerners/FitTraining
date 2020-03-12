#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

//#define DEBUG
#define DATABASE "/convict.db"
#define ALARM "/alarm.mp3"
void
MainWindow::changeSerie(QString tblName, QTableView* tbl, int index)
{

    QSqlTableModel* model = new QSqlTableModel(this, m_db.db());
    model->setTable(tblName);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, "Id");
    model->setHeaderData(1, Qt::Horizontal, "Rest");
    model->setHeaderData(2, Qt::Horizontal, "Set1");
    model->setHeaderData(3, Qt::Horizontal, "Set2");
    model->setHeaderData(4, Qt::Horizontal, "Set3");
    model->setHeaderData(5, Qt::Horizontal, "Set4");
    model->setHeaderData(6, Qt::Horizontal, "Set5");
    model->setHeaderData(7, Qt::Horizontal, "Set6");
    model->setHeaderData(8, Qt::Horizontal, "Set7");
    model->setHeaderData(9, Qt::Horizontal, "Set8");

    QTableView* view = tbl;
    view->setModel(model);
    for (int c = 0; c < model->rowCount(); ++c) {

        view->hideRow(c);
    }
    view->showRow(index - 1);
    for (int c = 0; c < model->columnCount(); ++c) {
        view->horizontalHeader()->setSectionResizeMode(
          c, QHeaderView::ResizeToContents);
    }
    view->show();
}

void
MainWindow::setSerie(int day)
{
    int count = 0;
    if (ui->tblSerie1->model()) {
        delete ui->tblSerie1->model();
        QSqlTableModel* model = new QSqlTableModel(this, m_db.db());
        ui->tblSerie1->setModel(model);
    }
    if (ui->tblSerie2->model()) {
        delete ui->tblSerie2->model();
        QSqlTableModel* model = new QSqlTableModel(this, m_db.db());
        ui->tblSerie2->setModel(model);
    }
    if (ui->tblSerie3->model()) {
        delete ui->tblSerie3->model();
        QSqlTableModel* model = new QSqlTableModel(this, m_db.db());
        ui->tblSerie3->setModel(model);
    }

    if (ui->tblSerie4->model()) {
        delete ui->tblSerie4->model();
        QSqlTableModel* model = new QSqlTableModel(this, m_db.db());
        ui->tblSerie4->setModel(model);
    }
    if (ui->tblSerie5->model()) {
        delete ui->tblSerie5->model();
        QSqlTableModel* model = new QSqlTableModel(this, m_db.db());
        ui->tblSerie5->setModel(model);
    }
    if (ui->tblSerie6->model()) {
        delete ui->tblSerie6->model();
        QSqlTableModel* model = new QSqlTableModel(this, m_db.db());
        ui->tblSerie6->setModel(model);
    }

    qDebug() << "setSerie<<<<<<<<<<<<<<<";
    for (const auto& i : m_db.getProgress(day)) {
        qDebug() << i;
        if (count == 0) {
            ui->cmbRoutine1->addItems(m_db.getMovementNames(i));
            ui->cmbRoutine1->setCurrentIndex(m_db.getProgressionIndex(i));
            changeSerie("Set1", ui->tblSerie1, m_db.getMovementProgress(i));
            changeSerie("Set2", ui->tblSerie2, m_db.getMovementProgress(i));
            changeSerie("Set3", ui->tblSerie3, m_db.getMovementProgress(i));
            ui->tblSerie1->selectColumn(2);
            ui->tblSerie2->selectColumn(2);
            ui->tblSerie3->selectColumn(2);
            m_db.setRoutine1(i);
            showImage1(m_db.getMovementName(i), m_db.getProgressionIndex(i));
            ++count;
        } else {
            ui->cmbRoutine2->addItems(m_db.getMovementNames(i));
            ui->cmbRoutine2->setCurrentIndex(m_db.getProgressionIndex(i));
            changeSerie("Set1", ui->tblSerie4, m_db.getMovementProgress(i));
            changeSerie("Set2", ui->tblSerie5, m_db.getMovementProgress(i));
            changeSerie("Set3", ui->tblSerie6, m_db.getMovementProgress(i));
            ui->tblSerie4->selectColumn(2);
            ui->tblSerie5->selectColumn(2);
            ui->tblSerie6->selectColumn(2);
            m_db.setRoutine2(i);
            showImage2(m_db.getMovementName(i), m_db.getProgressionIndex(i));
        }
    }
}
void
MainWindow::getRoutine(int user, int day)
{
    int Routine;
    int Pushups = 0;
    int Squats = 0;
    int Pullups = 0;
    int LegRaises = 0;
    int Bridges = 0;
    int HandstandPushups = 0;
    qDebug() << "getRoutine: " << user;
    m_db.getStatus(user,
                   &Routine,
                   &Pushups,
                   &Squats,
                   &Pullups,
                   &LegRaises,
                   &Bridges,
                   &HandstandPushups);

    ui->spnPushups->setValue(Pushups);
    ui->spnSquats->setValue(Squats);
    ui->spnPullups->setValue(Pullups);
    ui->spnLegRaises->setValue(LegRaises);
    ui->spnBridges->setValue(Bridges);
    ui->spnHandstandPushups->setValue(HandstandPushups);

    qDebug() << "   Progress " << Routine;
    ui->rbtnNewBlood->setChecked(false);
    ui->rbtnGoodBhavior->setChecked(false);
    ui->rbtnVeteran->setChecked(false);
    switch (Routine) {
        case NewBlood:
            ui->rbtnNewBlood->toggle();
            break;
        case GoodBehavior:
            ui->rbtnGoodBhavior->toggle();
            break;
        case Veteran:
            ui->rbtnVeteran->toggle();
            break;
    }
    setSerie(day);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void
MainWindow::on_cmbDayOfWeek_currentIndexChanged(int index)
{
    pos = 2;
    m_db.setDay(index + 1);
    fillRoutines(index);
}

void
MainWindow::on_rbtnNewBlood_clicked()
{
    pos = 2;
    m_db.updateRoutine(NewBlood);
    fillRoutines(ui->cmbDayOfWeek->currentIndex());
}

void
MainWindow::on_rbtnGoodBhavior_clicked()
{
    pos = 2;
    m_db.updateRoutine(GoodBehavior);
    fillRoutines(ui->cmbDayOfWeek->currentIndex());
}

void
MainWindow::on_rbtnVeteran_clicked()
{
    pos = 2;
    m_db.updateRoutine(Veteran);
    fillRoutines(ui->cmbDayOfWeek->currentIndex());
}
DbManager&
MainWindow::db()
{
    return m_db;
}

void
MainWindow::on_spnPushups_valueChanged(int arg1)
{
    pos = 2;
    m_db.updatePushups(arg1);
    fillRoutines(ui->cmbDayOfWeek->currentIndex());
}

void
MainWindow::on_spnSquats_valueChanged(int arg1)
{
    pos = 2;
    m_db.updateSquats(arg1);
    fillRoutines(ui->cmbDayOfWeek->currentIndex());
}

void
MainWindow::on_spnPullups_valueChanged(int arg1)
{
    pos = 2;
    m_db.updatePullups(arg1);
    fillRoutines(ui->cmbDayOfWeek->currentIndex());
}

void
MainWindow::on_spnLegRaises_valueChanged(int arg1)
{
    pos = 2;
    m_db.updateLegRaises(arg1);
    fillRoutines(ui->cmbDayOfWeek->currentIndex());
}

void
MainWindow::on_spnBridges_valueChanged(int arg1)
{
    pos = 2;
    m_db.updateBridges(arg1);
    fillRoutines(ui->cmbDayOfWeek->currentIndex());
}

void
MainWindow::on_spnHandstandPushups_valueChanged(int arg1)
{
    pos = 2;
    m_db.updateHandstandPushups(arg1);
    fillRoutines(ui->cmbDayOfWeek->currentIndex());
}
void
MainWindow::showImage1(QString name, int index)
{
    if (index <= 0)
        index = 1;
    qDebug() << "load image 1" << name << " " << index;
    qDebug() << qgetenv("APPDIR")  + "/images/" + name +
                  "/" + QString::number(index + 1) + ".jpg";
    QPixmap pm(qgetenv("APPDIR")  + "/images/" + name +
               "/" + QString::number(index + 1) + ".jpg");
    ui->lblImage1->setPixmap(pm);
    ui->lblImage1->resize(pm.width(), pm.height());
    // ui->lblImage1->setScaledContents(true);

    ui->vfImage1->resize(pm.width(), pm.height());
    // remove the widget in area;
    ui->scrollArea1->takeWidget();
    // set this property
    ui->scrollArea1->setWidgetResizable(false);
    // reset widget
    ui->scrollArea1->setWidget(ui->vfImage1);
}

void
MainWindow::showImage2(QString name, int index)
{
    if (index <= 0)
        index = 1;
    qDebug() << "load image 2" << name << " " << index;
    qDebug() << qgetenv("APPDIR")  + "/images/" + name +
                  "/" + QString::number(index + 1) + ".jpg";
    QPixmap pm(qgetenv("APPDIR")  + "/images/" + name +
               "/" + QString::number(index + 1) + ".jpg");

    ui->lblImage2->setPixmap(pm);
    ui->lblImage2->resize(pm.width(), pm.height());
    // ui->lblImage2->setScaledContents(true);

    ui->vfImage2->resize(pm.width(), pm.height());
    // remove the widget in area;
    ui->scrollArea2->takeWidget();
    // set this property
    ui->scrollArea2->setWidgetResizable(false);
    // reset widget
    ui->scrollArea2->setWidget(ui->vfImage2);
}
void
MainWindow::on_cmbRoutine1_currentIndexChanged(int arg1)
{
    pos = 2;
    if (canUpdateRoutine1) {
        QSqlQuery query;
        query.prepare(
          QString("UPDATE ProgressionIndex SET %1 = '%2' WHERE Id = %3")
            .arg(m_db.getMovementName(m_db.getRoutine1()))
            .arg(arg1)
            .arg(ui->cmbUser->currentIndex() + 1));
        if (!query.exec()) {

            qDebug() << "on_cmbRoutine1_currentIndexChanged error: "
                     << query.lastError();
        } else {
            qDebug() << query.lastQuery();
        }
        showImage1(m_db.getMovementName(m_db.getRoutine1()), arg1);
        canUpdateRoutine1 = false;
    }
}

void
MainWindow::on_cmbUser_currentIndexChanged(int index)
{
    pos = 2;
    m_db.setUser(index + 1);
}

void
MainWindow::on_cmbRoutine1_highlighted(int index)
{
    pos = 2;
    canUpdateRoutine1 = true;
}

void
MainWindow::on_cmbRoutine2_currentIndexChanged(int arg1)
{
    pos = 2;
    if (canUpdateRoutine2) {
        QSqlQuery query;
        query.prepare(
          QString("UPDATE ProgressionIndex SET %1 = '%2' WHERE Id = %3")
            .arg(m_db.getMovementName(m_db.getRoutine2()))
            .arg(arg1)
            .arg(ui->cmbUser->currentIndex() + 1));
        if (!query.exec()) {

            qDebug() << "on_cmbRoutine2_currentIndexChanged error: "
                     << query.lastError();
        } else {
            qDebug() << query.lastQuery();
        }
        showImage2(m_db.getMovementName(m_db.getRoutine2()), arg1);
        canUpdateRoutine2 = false;
    }
}

void
MainWindow::on_cmbRoutine2_highlighted(int index)
{
    pos = 2;
    canUpdateRoutine2 = true;
}
void
MainWindow::showTime()
{
    ui->lcdRest->display(QString("%1").arg(rest));
    if (!rest) {
        ui->btnStart->setEnabled(true);
        timer->stop();
        QMediaPlayer* player = new QMediaPlayer;
        player->setMedia(QUrl::fromLocalFile(qgetenv("APPDIR") + ALARM));
        player->setVolume(100);
        player->play();
        ++pos;
        ui->tblSerie1->selectColumn(pos);
        ui->tblSerie2->selectColumn(pos);
        ui->tblSerie3->selectColumn(pos);

        ui->tblSerie4->selectColumn(pos);
        ui->tblSerie5->selectColumn(pos);
        ui->tblSerie6->selectColumn(pos);

        if (pos == 10) {
            pos = 2;
            ui->btnStart->setText("Start Routine");
        }

    } else {
        --rest;
    }
}

void
MainWindow::on_btnStart_released()
{
    if (player) {
        delete player;
        player = nullptr;
    }
    rest = 60;
    timer->start(1000);
    ui->btnStart->setText("Next");
    ui->btnStart->setEnabled(false);
    ui->tblSerie1->selectColumn(pos);
    ui->tblSerie2->selectColumn(pos);
    ui->tblSerie3->selectColumn(pos);

    ui->tblSerie4->selectColumn(pos);
    ui->tblSerie5->selectColumn(pos);
    ui->tblSerie6->selectColumn(pos);
}
void
MainWindow::fillRoutines(int day)
{
    int user = ui->cmbUser->currentIndex();
    ui->cmbRoutine1->clear();
    ui->cmbRoutine2->clear();
    ui->vfImage1->resize(0, 0);
    ui->vfImage2->resize(0, 0);

    ui->lblImage1->clear();
    ui->lblImage2->clear();

    getRoutine(user + 1, day + 1);
}
MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , m_db(qgetenv("HOME") + DATABASE)
  , canUpdateRoutine1(false)
  , canUpdateRoutine2(false)
  , timer(nullptr)
  , rest(0)
  , pos(2)
  , player(nullptr)

{
    ui->setupUi(this);
    m_db.setUser(1);
    fillRoutines(getWeekDay());
    ui->cmbDayOfWeek->clear();
    ui->cmbDayOfWeek->addItems(m_db.getWeeDays());

    ui->cmbUser->clear();
    ui->cmbUser->addItems(m_db.getUsers());
    ui->cmbDayOfWeek->setCurrentIndex(getWeekDay());

    timer = new QTimer(this);

    // setup signal and slot
    connect(timer, &QTimer::timeout, this, &MainWindow::showTime);
}
