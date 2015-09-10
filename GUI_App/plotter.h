#ifndef PLOTTER_H
#define PLOTTER_H

#include <stdint.h>
#include <deque>
#include <QFile>
#include <QObject>
#include <QScopedPointer>

#include "qcustomplot.h"

class Plotter : public QObject {
    Q_OBJECT
public:
    Plotter(const QScopedPointer<QFile>& data_file_, QCustomPlot* plotter);
    void setupPlotter() const;

public slots:
    void start();
    void stop();

signals:
    void finished();

private:
    enum Status {
        Active,
        Stopped
    };
    void draw();
    inline bool isActive() {
        return status_ == Active;
    }
    void readFromFile();

private:
    const QScopedPointer<QFile>& data_file;
    QCustomPlot* plotter_;
    Status status_;

    std::deque<uint16_t> draw_queue_;
};

#endif // PLOTTER_H