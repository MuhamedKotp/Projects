#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
class QTcpServer;
class QTcpSocket;
class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);
    bool StartServer();
    void StopServer();

signals:
    void new_command(const QString& tcp_message);

public slots:
    void newConnection();
    void dataIsReady();
    void sendEcho(const QString& tcp_message);
private:
    QTcpServer *m_server;
    QTcpSocket *m_soket;
    bool m_is_connected;

};

#endif // TCPSERVER_H
