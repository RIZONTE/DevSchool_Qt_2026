#include <QTimer>
#include <QPushButton>
#include <QRandomGenerator>

#include "mainwindow.h"

namespace {
    constexpr int window_width = 300;
    constexpr int window_height = 600;
    constexpr int low_bound_ms = 100;
    constexpr int high_bound_ms = 1000;
    constexpr int layout_up_spawn_px = 100;
    constexpr int btn_size_px = 20;
    constexpr int velocity_low = 2;
    constexpr int velocity_hight = 8;
    constexpr double velocity_multiplier = 1.5;
    constexpr int move_interval = 60;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(window_width, window_height);

    //Таймер на появление кнопок
    auto tm_spawn = new QTimer(this);
    tm_spawn->setInterval(QRandomGenerator::global()->bounded(low_bound_ms, high_bound_ms));
    tm_spawn->start();

    connect(tm_spawn, &QTimer::timeout, this, [tm_spawn, this] {
        QPushButton* btn = new QPushButton("*", this);
        btn->setGeometry( (QRandomGenerator::global()->generateDouble() * (this->width() - btn_size_px)),
                          (QRandomGenerator::global()->generateDouble() * layout_up_spawn_px),
                          btn_size_px,
                          btn_size_px);
        btn->show();

        //Удаление при нажатии
        connect(btn, &QPushButton::clicked, this, [btn] {
            btn->deleteLater();
        });

        //Таймер на движение
        auto tm_anim = new QTimer(btn);
        tm_anim->setInterval(move_interval);
        tm_anim->start();
        //Логика анимации падения
        int velocity = QRandomGenerator::global()->bounded(velocity_low, velocity_hight);
        connect(tm_anim, &QTimer::timeout, btn, [velocity, btn] {
            btn->move(btn->pos() + QPoint(0, btn->underMouse() ? velocity * velocity_multiplier : velocity));
            auto parent = btn->parentWidget();
            //Проигрыш
            if(btn->pos().y() >= parent->height() - btn_size_px / 2) {
                parent->setStyleSheet("QMainWindow  {background-color:red;}");
                parent->setWindowTitle("You LOOSE!");
                btn->deleteLater();
            }
        });

        //Перезапуск таймера с новым интервалом
        tm_spawn->setInterval(QRandomGenerator::global()->bounded(low_bound_ms, high_bound_ms));
    });

}

MainWindow::~MainWindow()
{
}
