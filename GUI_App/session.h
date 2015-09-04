#ifndef SESSION_H
#define SESSION_H

#include <QFile>
#include <QString>
#include <QScopedPointer>

#include "qcustomplot.h"

class Session {
public:
    Session(QCustomPlot* plotter) : status_(Closed), plotter_(plotter) {
    }
    bool create(QString name, QString datafile_location, QString& err);
    bool open(QString session_file_name, QString& err);
    void start();
    void stop();
    void close();
    bool remove(bool erase_data, QString& err);

    inline QString getSessionName() const {
        return name_;
    }

    inline QString getDataFileName() const {
        return datafile_name_;
    }

private:
    enum Status {
        Active,
        Stopped,
        Closed
    };
    inline bool isActive() const {
        return status_ == Active;
    }
    inline bool isClosed() const {
        return status_ == Closed;
    }
    void setupPlotter() const;

private:
    QString name_;
    QString datafile_name_;
    Status status_;

    QScopedPointer<QFile> session_file;
    QScopedPointer<QFile> data_file;

    QCustomPlot* plotter_;
};

#endif // SESSION_H
