#ifndef PRIM_H
#define PRIM_H

#include <QThread>
#include <QMutex>
#include <functional>

class Prim : public QObject{
    Q_OBJECT
    QMutex* mut;    

public:
   
    Prim(QMutex* m) : mut(m){
    }
    void DoWork(uint32_t* inc, bool mutexOn, int numIterat);

signals:

    void sig_Finish( void );

};



class Controller : public QObject
{
    Q_OBJECT
    QThread workerThread; 
    QMutex* mut;

public:
    Controller(QMutex* m) : mut(m) {

        Prim*race = new Prim(mut); //экземпляр нашего класса
        race->moveToThread(&workerThread); //Помещаем в поток
        connect(&workerThread, &QThread::finished, race, &QObject::deleteLater); //По завершению потока удаляем экземпляр класса
        connect(this, &Controller::operate, race, &Prim::DoWork); //Запускаем "тяжелый" метод
        connect(race, &Prim::sig_Finish, this, &Controller::sig_WorkFinish); //Пробрасываем сигнал для отображения в GUI
        workerThread.start(); //Запускаем работу потока
    }
    ~Controller(){

        //Завершаем работу потока
        workerThread.quit();
        workerThread.wait();

    }

signals:
    void operate( uint32_t *num, bool mutexOn, int numIterat );
    void sig_WorkFinish( void );

};


#endif // PRIM_H
