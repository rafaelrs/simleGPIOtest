#include <QCoreApplication>
#include <QTextStream>
#include <QFile>
#include <QDebug>

QString readFromFile(const QString &filename);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString currValue = "";
    QString prevValue = "";

    forever {
        currValue = readFromFile("/sys/class/gpio/gpio128/value");
        if (currValue != prevValue) {
            qDebug() << "Monitored value is: " << currValue;
            prevValue = currValue;
        }
    }

    return a.exec();
}

QString readFromFile(const QString &filename)
{
    QFile gpioFile(filename);
    if (gpioFile.open(QIODevice::ReadOnly)) {
        QTextStream gpioStream(&gpioFile);
        QString fileContent = gpioStream.read(1);
        gpioFile.close();
        return fileContent;
    } else {
//        qDebug() << "Can't to open file " << filename;
//        stopped = true;
//        sendSignal("fatalAbort");
        return "open error";
    }

}
