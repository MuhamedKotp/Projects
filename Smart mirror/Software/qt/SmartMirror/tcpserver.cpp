/**
    tcpserver.cpp
    Purpose: instantiate  a server that can accept messages from different clients then
             send a signal to the main window to modify its parameters based on the received message.

*/
#include "tcpserver.h"
#include<QTcpServer>
#include<QTcpSocket>
#include<QMessageBox>
#include<QDebug>
const int PORT_NUMBER = 10000; // valiable hold the server port number
TcpServer::TcpServer(QObject *parent) : QObject(parent),m_server(new QTcpServer(this)) , m_soket(nullptr) ,  m_is_connected(false)
{
    connect(m_server,&QTcpServer::newConnection , this,&TcpServer::newConnection);
}
/**
    enable the server to listen to the incoming messages on the PORT_NUMBER
*/
bool TcpServer::StartServer()
{
    m_is_connected = m_server->listen(QHostAddress::Any , PORT_NUMBER);
    if(!m_is_connected)
    {
        QMessageBox::critical(
                    nullptr,
                    tr("server start error"),
                    tr("unable to start the server %1").arg(m_server->errorString())
                    );
    }
    return m_is_connected;
}

void TcpServer::StopServer()
{
    /**
        it closes the server and an opened connections
    */
    m_server->close();
    if(m_soket != nullptr && m_soket->isOpen())
    {
        m_soket->close();
    }
}

void TcpServer::newConnection()
{
    /**
        handle the new connections
    */
    m_soket = m_server->nextPendingConnection();
    if(m_soket->isOpen())
    {
        connect(m_soket , &QTcpSocket::readyRead , this , &TcpServer::dataIsReady);
    }
}

void TcpServer::dataIsReady()
{
    /*
     * receives data from the socket connections
     * */
    QString message;
    while (!m_soket->atEnd()) {
        message.append(m_soket->readAll());
        m_soket->waitForReadyRead(10); //10ms delay ensuring that  the whole message has been received
    }
    emit new_command(message);
}

void TcpServer::sendEcho(const QString &tcp_message)
{
    /*
     * send the response to the client from the main window
     * */
    if(m_soket != nullptr && m_soket->isOpen())
    {
        m_soket->write(qPrintable(tcp_message));
    }
}
