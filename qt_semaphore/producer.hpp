 
#pragma once
 
#include <QThread>
#include <QTime>
#include <QSemaphore>
 
class Producer : public QThread {
public:
    Producer(const int DataSize, const int BufferSize, char buffer[8192], QSemaphore* freeBytes, QSemaphore* usedBytes) {
        ds=DataSize;
        bs = BufferSize;
        buf=buffer;
        fb = freeBytes;
        ub = usedBytes;
    }
    void run()  {
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        for (int i = 0; i < ds; ++i) {
            fb->acquire(); // aquire free
            buf[i % bs] = "ACGT"[(int)qrand() % 4];
            ub->release(); // release used 
        }
    }
private:
    int ds;
    int bs;
    char* buf;
    QSemaphore* fb;
    QSemaphore* ub;
};

