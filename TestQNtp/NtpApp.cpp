#include "NtpApp.h"

#include <QHostAddress>
#include <QHostInfo>
#include <cassert>
#include <iostream>

NtpApp::NtpApp(QObject *parent) :
    QObject(parent)
{
    QHostInfo::lookupHost( "time-a.nist.gov", this, SLOT ( sltLookupReceived( QHostInfo ) ) );
    Ntp = new NtpClient;
    bool boo = connect ( Ntp, SIGNAL (replyReceived(const QHostAddress &, quint16, const NtpReply &)),
                         this, SLOT ( sltReplyReceived ( const QHostAddress&, quint16, const NtpReply &) ) );
    assert ( boo );
    Timer = new QTimer;

    boo = connect ( Timer, SIGNAL ( timeout() ), this, SLOT ( sltTrigger () ) );
    Timer->start( 5000 );

    assert ( boo );

}

void NtpApp::sltReplyReceived(const QHostAddress &addr, quint16 port, const NtpReply &reply)
{
    qDebug() << "reply received " << addr << " " << port;
    qDebug() << reply.localClockOffset() * 0.001;
    qDebug() << reply.roundTripDelay() * 0.001;
    qDebug() << reply.destinationTime().time() << " " << reply.receiveTime().time() << " " << reply.referenceTime().time();
}

void NtpApp::sltTrigger()
{
//    HostInfo.setHostName( "time-a.nist.gov" );
    QList < QHostAddress > lst = HostInfo.addresses();
    qDebug() << "List size " << lst.size();
    if ( lst.size () )
    {
        qDebug() << "Trying " << lst[0];
        bool boo = Ntp->sendRequest( lst[0], 123 );
        qDebug() << "request sent " << boo;
    }
}

void NtpApp::sltLookupReceived(QHostInfo host)
{
    if (host.error() != QHostInfo::NoError) {
        qDebug() << "Lookup failed:" << host.errorString();
        return;
    }

    foreach (const QHostAddress &address, host.addresses())
        qDebug() << "Found address:" << address.toString();

    HostInfo = host;
}
