#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets>
#include <QMainWindow>

class QAction;
class TcpServer;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void message_analyser(const QString& message);
    void runScript();

private:
    QLabel *label;
    QLineEdit *lineEdit;
    QCheckBox *checkbox;
    QWidget *mainWidget;
    //QTextLine *textLine;
    TcpServer *m_server_connector;
    void createActions();
};

#endif // MAINWINDOW_H
