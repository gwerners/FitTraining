#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QMainWindow>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QFileInfo>
#include <QList>

const int NewBlood = 1;
const int GoodBehavior = 2;
const int Veteran = 3;

const int Sunday = 1;
const int Monday = 2;
const int Tuesday = 3;
const int Wednesday = 4;
const int Thursday = 5;
const int Friday = 6;
const int Saturday = 7;

const int Pushups = 1;
const int Squats = 2;
const int Pullups = 3;
const int LegRaises = 4;
const int Bridges = 5;
const int HandstandPushups = 6;

class DbManager
{
  public:
    DbManager(const QString& path);
    QSqlDatabase db();
    void setUser(int user);
    void setDay(int day);
    void setRoutine1(int routine1);
    void setRoutine2(int routine2);
    int user() const;
    int day() const;
    int routine1() const;
    int routine2() const;

    int routine() const;
    void setRoutine(int routine);
    void updateRoutine(int routine);
    void updatePushups(int value);
    void updateSquats(int value);
    void updatePullups(int value);
    void updateLegRaises(int value);
    void updateBridges(int value);
    void updateHandstandPushups(int value);
    QStringList getUsers();
    QStringList getWeeDays();
    QString getMovementName(int movement);
    QStringList getMovementNames(int movement);
    void refreshStatus();
    void refreshRoutines();
    void getStatus(int user,
                   int* Routine,
                   int* Pushups,
                   int* Squats,
                   int* Pullups,
                   int* LegRaises,
                   int* Bridges,
                   int* HandstandPushups);
    int getProgressionIndex(int movement);
    QList<int> getProgress(int day);
    int getMovementProgress(int movement);

    int getRoutine() const;

    int getRoutine1() const;

    int getRoutine2() const;

  private:
    QSqlDatabase m_db;
    int m_user;
    int m_day;
    int m_routine1;
    int m_routine2;
    int m_routine;
    int m_movement;
    int m_Pushups;
    int m_Squats;
    int m_Pullups;
    int m_LegRaises;
    int m_Bridges;
    int m_HandstandPushups;
};
int
getWeekDay();
#endif // DBMANAGER_H
