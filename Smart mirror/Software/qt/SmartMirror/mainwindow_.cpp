#include "mainwindow.h"
#include"tcpserver.h"
#include<QDebug>

MainWindow::MainWindow()
{
    // Widgets
    label = new QLabel;
    lineEdit = new QLineEdit;
    checkbox = new QCheckBox;
    //textLine = new QTextLine;
    mainWidget = new QWidget;
    m_server_connector = new TcpServer; //server handler
    connect(m_server_connector , SIGNAL(new_command(const QString&)) , this , SLOT(message_analyser(const QString& )));
    m_server_connector->StartServer();
    label->setText("My Name");
    checkbox->setText("Toggle");

    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    layout->addWidget(checkbox);
    //layout->addWidget(textLine);

    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);

    createActions();

    setWindowTitle(tr("Scripting Example"));
    resize(300, 100);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
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
    if(msg_list.size() == 1){
        if(msg_list[0] == "getQLine")
        {
            responce_message = lineEdit->text();
        }else if(msg_list[0] == "getQCheckBox")
        {
            bool state = checkbox->isChecked();
            if(state)
                responce_message = "true";
            else
                responce_message = "false";
        }
        else{
            responce_message = "unknown command";
        }
    }else if(msg_list.size() == 2)
    {
        if(msg_list[0] == "setQLine")
        {
            lineEdit->setText(msg_list[1]);
            responce_message = "ok";

        }
        else if(msg_list[0] == "timeLabel")
        {
            timeLabel->setText(msg_list[1]);
            responce_message = "ok";

        }
        else if(msg_list[0] == "dateLabel")
        {
            dateLabel->setText(msg_list[1]);
            responce_message = "ok";

        }
        else if(msg_list[0] == "tempLabel")
        {
            tempLabel->setText(msg_list[1]);
            responce_message = "ok";

        }
        else if(msg_list[0] == "setQCheckBox")
        {
            if(msg_list[1] == "true")
            {
                responce_message = "ok";
                checkbox->setChecked(true);
            }
            else if(msg_list[1] == "false")
            {
                responce_message = "ok";
                checkbox->setChecked(false);
            }else
            {
                responce_message = "unknown command";
            }
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
