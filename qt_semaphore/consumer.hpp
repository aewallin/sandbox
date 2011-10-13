
#pragma once

#include <QThread>
#include <QSemaphore>

#include <stdio.h>
 
class Consumer : public QThread {
public:
    Consumer(const int DataSize, const int BufferSize, char buffer[8192], QSemaphore* freeBytes, QSemaphore* usedBytes) {
        ds=DataSize;
        bs = BufferSize;
        buf=buffer;
        fb = freeBytes;
        ub = usedBytes;
    }
    
    void run(){
        for (int i = 0; i < ds; ++i) {
            ub->acquire(); // acquire used
            fprintf(stderr, "%c", buf[i % bs]);
            fb->release(); // release free
        }
        fprintf(stderr, "\n");
    }
private:
    int ds;
    int bs;
    char* buf;
    QSemaphore* fb;
    QSemaphore* ub;
};

