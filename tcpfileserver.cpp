#include "tcpfileserver.h"

TcpFileServer::TcpFileServer(QWidget *parent)
    : QDialog(parent)
{
    totalBytes   = 0;
    byteReceived = 0;
    fileNameSize = 0;

    serverProgressBar = new QProgressBar;
    serverStatusLabel = new QLabel(tr("伺服器端就緒"));
    startButton = new QPushButton(tr("接收"));
    quitButton  = new QPushButton(tr("退出"));
    buttonBox = new QDialogButtonBox;
    buttonBox -> addButton(startButton, QDialogButtonBox::ActionRole);
    buttonBox -> addButton(quitButton,  QDialogButtonBox::RejectRole);

    // layout配置
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout -> addWidget(serverProgressBar);
    mainLayout -> addWidget(serverStatusLabel);
    mainLayout -> addStretch();
    mainLayout -> addWidget(buttonBox);
    setLayout(mainLayout);
    setWindowTitle(tr("接收檔案"));

    // 連接訊號與槽函數
    connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
    connect(quitButton,  SIGNAL(clicked()), this, SLOT(close()));
    connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    connect(&tcpServer, SIGNAL(acceptError(QAbstractSocket:: SocketError)), this,
            SLOT(displayError(QAbstractSocket:: SocketError)));
}

TcpFileServer::~TcpFileServer() = default;

// 按下「接收」讓伺服器進入監聽狀態
void TcpFileServer::start()
{
    startButton->setEnabled(false);
    byteReceived = 0;
    fileNameSize = 0;
    while (!tcpServer.isListening() &&
           !tcpServer.listen(QHostAddress::AnyIPv4, 16689))
    {
        QMessageBox::StandardButton ret = QMessageBox::critical(this,
                tr("迴圈"),
                tr("無法啟動伺服器: %1.").arg(tcpServer.errorString()),
                QMessageBox::Retry | QMessageBox::Cancel);
        if (ret == QMessageBox::Cancel) {
            startButton->setEnabled(true);
            return;
        }
    }
    serverStatusLabel->setText(tr("監聽中..."));
}

// 下次上課再繼續實作
void TcpFileServer::acceptConnection()
{
}

void TcpFileServer::updateServerProgress()
{
}

void TcpFileServer::displayError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
}
