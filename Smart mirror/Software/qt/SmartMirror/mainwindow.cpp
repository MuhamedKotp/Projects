#include"tcpserver.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_server_connector = new TcpServer; //server handler
    connect(m_server_connector , SIGNAL(new_command(const QString&)) , this , SLOT(message_analyser(const QString& )));
    m_server_connector->StartServer();

    process = new QProcess();
    process->start("python", QStringList() << "../../Python/main.py");

    ui->setupUi(this);
    this->setStyleSheet("background-color: black;");
    setWindowTitle("Smart Mirror");
    QMainWindow::showFullScreen();

    createActions();

}

MainWindow::~MainWindow()
{
    delete ui;
    process->kill();
}

void MainWindow::message_analyser(const QString &message)
{
    /*
     *validate the incomming messages
     * the setting command <widget><\2><text>
     * the get command  <widget>
 */
    QString responce_message;
    QList<QString> msg_list = message.split("\2"); // split the widget and command
    if(msg_list.size() == 2)
    {
        if(msg_list[0] == "timeLabel")
        {
            ui->timeLabel->setText(msg_list[1]);
            responce_message = "ok";

        }
        else if(msg_list[0] == "dateLabel")
        {
            ui->dateLabel->setText(msg_list[1]);
            responce_message = "ok";

        }
        else if(msg_list[0] == "tempLabel")
        {
            ui->tempLabel->setText(msg_list[1]);
            responce_message = "ok";

        }else
        {
            responce_message = "unknown command";
        }
    }else
    {
        responce_message = "unknown command";
    }
    m_server_connector->sendEcho(responce_message);
}

void MainWindow::runScript()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        // run python script
        statusBar()->showMessage(tr("Run Script: %1"));
        //statusBar()->showMessage(tr("Run Script: %1".arg(fileName)));
}

void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    // Run Script File Action
    QAction *runFileAct = new QAction(tr("&Run Script"), this);
    runFileAct->setShortcuts(QKeySequence::Open);
    runFileAct->setStatusTip(tr("Run a python script"));
    connect(runFileAct, &QAction::triggered, this, &MainWindow::runScript);
    fileMenu->addAction(runFileAct);
}
