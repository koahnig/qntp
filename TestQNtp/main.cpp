#include <QCoreApplication>
#include "NtpApp.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    NtpApp ntp;

    return a.exec();
}
