
#include <QCoreApplication>
#include <QSemaphore>

#include "producer.hpp"
#include "consumer.hpp"


    

int main(int argc, char *argv[]) {
    
    const int DataSize = 100000;
    const int BufferSize = 8192;
    char buffer[BufferSize];

    QSemaphore freeBytes(BufferSize);
    QSemaphore usedBytes;

    QCoreApplication app(argc, argv);
    Producer producer(DataSize, BufferSize, buffer, &freeBytes, &usedBytes);
    Consumer consumer(DataSize, BufferSize, buffer, &freeBytes, &usedBytes);
    producer.start();
    consumer.start();
    producer.wait();
    consumer.wait();
    return 0;
}
