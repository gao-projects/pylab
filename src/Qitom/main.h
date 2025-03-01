

#ifndef MAIN_H
#define MAIN_H

#include <qapplication.h>
#include <qdebug.h>
#include <QMetaEnum>
#include <iostream>
#include "opencv2/opencv.hpp"

class QItomApplication : public QApplication
{
    Q_OBJECT
public:

    QItomApplication ( int & argc, char ** argv ) : QApplication(argc,argv) {}

    bool notify ( QObject * receiver, QEvent * event )
    {
        try
        {
            /*int type = event ? event->type() : -1;

            if (type == 68 || type == 74 || type == 69)
            {
                QString className =  receiver->metaObject()->className();
                if (className == "ito::ScriptDockWidget")
                {
                    int j = 1;
                }
            }*/
            return QApplication::notify(receiver,event);
        }
        catch (cv::Exception &exc)
        {
            QString name = QString("%1 (%2)").arg(receiver->objectName()).arg(receiver->metaObject()->className());
            qWarning("Itom-Application has caught a cv::exception");
            qWarning() << (exc.err).c_str() << " from" << name;
            //qDebug() << "Itom-Application caught an exception from" <<  receiver->objectName() << "from event type" << event->type();
#ifdef _DEBUG
            qFatal("Exiting due to exception caught. OpenCV-Exception: %s", (exc.err).c_str());
#endif
            std::cerr << "Itom-Application has caught a cv::exception: " << (exc.err).c_str() << " from: " << name.toLatin1().constData() << "\n" << std::endl;
        }
        catch(std::exception &exc)
        {
            QString name = QString("%1 (%2)").arg(receiver->objectName()).arg(receiver->metaObject()->className());
            qWarning("Itom-Application has caught a std::exception");
            qWarning() << "Message:" << exc.what() << " from" << name;
#ifdef _DEBUG
            qFatal("Exiting due to std::exception caught. Exception: %s", exc.what());
#endif
            std::cerr << "Itom-Application has caught a std::exception: " << exc.what() << " from: " << name.toLatin1().constData() << "\n" << std::endl;
        }
        catch (...)
        {
            int enumIdx = QEvent::staticMetaObject.indexOfEnumerator("Type");
            QMetaEnum me = QEvent::staticMetaObject.enumerator(enumIdx);
            QByteArray key = event ? me.valueToKeys(event->type()) : QByteArray("");
            int type = event ? event->type() : -1;
            QString name = QString("%1 (%2)").arg(receiver->objectName()).arg(receiver->metaObject()->className());
            qWarning("Itom-Application has caught an unknown exception");
            qWarning() << "Itom-Application caught an unknown exception from" <<  name << "from event type" << type << " (" << key.constData() << ")";
#ifdef _DEBUG
            qFatal("Exiting due to exception caught");
#endif
            std::cerr << "Itom-Application caught an unknown exception from: " << name.toLatin1().constData() << " from event type " << type << " (" << key.constData() << ")" << "\n" << std::endl;
        }
        return false;
    }
};

#endif
