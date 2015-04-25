#ifndef CMMD_H
#define CMMD_H


#include <QProcess>
#include <QObject>
#include <QTimer>
#include <QThread>

#include <iostream>
#include <stdio.h>

class cmmd : public QObject {
    Q_OBJECT

public:
    QProcess ps;

    cmmd();

public slots:
    void cmmdOutput(){
        std::cout << "cmmdOutput\n";
        std::cout << ps.readAllStandardOutput().toStdString();
    }

    void cmmdError(){
        std::cout << "cmmdError\n";
        QThread::sleep(1);
        std::cout << ps.readAllStandardError().toStdString();
    }
};

#endif // CMMD_H
