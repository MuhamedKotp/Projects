#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>


class QAction;
class TcpServer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QProcess *process;

private slots:
    void message_analyser(const QString& message);
    void runScript();

private:
    Ui::MainWindow *ui;
    TcpServer *m_server_connector;
    void createActions();
};

#endif // MAINWINDOW_H
