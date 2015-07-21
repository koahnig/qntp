#ifndef NTPAPP_H
#define NTPAPP_H

#include <QObject>
#include "NtpClient.h"
#include "NtpReply.h"
#include <QTimer>
#include <QHostInfo>

class NtpApp : public QObject
{
    Q_OBJECT

    NtpClient *Ntp;

    QHostInfo HostInfo;

    QTimer    *Timer;
public:
    explicit NtpApp(QObject *parent = 0);

signals:

public slots:
    void sltReplyReceived ( const QHostAddress& addr, quint16 port, const NtpReply &reply );
    void sltTrigger ();

    void sltLookupReceived (QHostInfo hinfo );
};

#endif // NTPAPP_H
