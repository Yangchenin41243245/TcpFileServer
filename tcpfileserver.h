#ifndef TCPFILESERVER_H
#define TCPFILESERVER_H

#include <QDialog>
#include <QtWidgets>
#include <QtNetwork>

class TcpFileServer : public QDialog
{
    Q_OBJECT

public:
    explicit TcpFileServer(QWidget *parent = nullptr);
    ~TcpFileServer() override;

public slots:
    void start();
    void acceptConnection();
    void updateServerProgress();
    void displayError(QAbstractSocket::SocketError socketError);

private:
    QProgressBar     *serverProgressBar;
    QLabel           *serverStatusLabel;
    QPushButton      *startButton;
    QPushButton      *quitButton;
    QDialogButtonBox *buttonBox;

    QTcpServer       tcpServer;
    QTcpSocket       *tcpServerConnection = nullptr;
    qint64           totalBytes;
    qint64           byteReceived;
    qint64           fileNameSize;
    QString          fileName;
    QFile            *localFile = nullptr;
    QByteArray       inBlock;
};
#endif // TCPFILESERVER_H
