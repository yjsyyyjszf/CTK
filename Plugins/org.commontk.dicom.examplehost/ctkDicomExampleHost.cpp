#include "ctkDicomExampleHost.h"
#include "ctkDicomWG23TypesHelper.h"

#include <QProcess>
#include <QtDebug>
#include <QRect>

#include <iostream>

ctkDicomExampleHost::ctkDicomExampleHost(ctkHostedAppPlaceholderWidget* placeholderWidget, int hostPort, int appPort) :
    ctkDicomAbstractHost(hostPort, appPort),
    placeholderWidget(placeholderWidget),
    applicationState(ctkDicomWG23::IDLE)
{
  connect(&this->appProcess,SIGNAL(readyReadStandardOutput()),SLOT(forwardConsoleOutput()));
}

void ctkDicomExampleHost::StartApplication(QString AppPath){

    QStringList l;
    l.append("--hostURL");
    l.append(QString("http://localhost:") + QString::number(this->getHostPort()) + "/HostInterface" );
    l.append("--applicationURL");
    l.append(QString("http://localhost:") + QString::number(this->getAppPort()) + "/ApplicationInterface" );
    l.append("dicomapp"); // the app plugin to use - has to be changed later
    //if (!QProcess::startDetached (
    //{
    //    qCritical() << "application failed to start!";
    //}
    //qDebug() << "starting application: " << AppPath << " " << l;
    qDebug() << "starting application: " << AppPath << " " << l;
    this->appProcess.setProcessChannelMode(QProcess::MergedChannels);
    this->appProcess.start(AppPath,l);
}

QRect ctkDicomExampleHost::getAvailableScreen(const QRect& preferredScreen){
    qDebug()<< "Application asked for this area:"<< preferredScreen;

    QRect rect (this->placeholderWidget->getAbsolutePosition());

    emit giveAvailableScreen(rect);
    return rect;
}


void ctkDicomExampleHost::notifyStateChanged(ctkDicomWG23::State state){
    qDebug()<< "new state received:"<< static_cast<int>(state);
    qDebug()<< "new state received:"<< ctkDicomSoapState::toStringValue(state);
    emit stateChangedReceived(state);
}

void ctkDicomExampleHost::notifyStatus(const ctkDicomWG23::Status& status){
    qDebug()<< "new status received:"<<status.codeMeaning;
    emit statusReceived(status);;
}

ctkDicomExampleHost::~ctkDicomExampleHost()
{
  qDebug() << "Exiting host: trying to terminate app";
  this->appProcess.terminate();
  qDebug() << "Exiting host: trying to kill app";
  this->appProcess.kill();
}

void ctkDicomExampleHost::forwardConsoleOutput()
{
  while( this->appProcess.bytesAvailable() )
  {
    QString line( this->appProcess.readLine() );
    line.prepend(">>>> ");
    std::cout << line.toStdString();
  }
}

bool ctkDicomExampleHost::notifyDataAvailable(ctkDicomWG23::AvailableData data, bool lastData)
{
  return false;
}

QList<ctkDicomWG23::ObjectLocator>* ctkDicomExampleHost::getData(
  QList<QUuid> objectUUIDs, 
  QList<QString> acceptableTransferSyntaxUIDs, 
  bool includeBulkData)
{
  return NULL;
}
void ctkDicomExampleHost::releaseData(QList<QUuid> objectUUIDs)
{
}
