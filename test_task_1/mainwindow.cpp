#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mouse_button_flag(NONE)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(1325, 750);
    setWindowTitle("TEST TASK 1");
    coordinates = {{}};
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    if (path.size())
    {
        QPixmap bkgnd(path);
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton)
        mouse_button_flag = RIGHT;
    else if (e->button() == Qt::LeftButton)
        mouse_button_flag = LEFT;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    if (mouse_button_flag == LEFT && !ui->checkBox->isChecked())
        coordinates.back().push_back(e->pos());

    this->update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    QPoint cursor_pos = e->pos();

    for (int i = 0; i < coordinates.size(); ++i)
        for (int j = 0; j < coordinates[i].size(); ++j)
            if (DOT_HIT)
            {
                if (ui->checkBox->isChecked())
                {
                    object_to_move = i;
                    int x = coordinates[i][j].x(), y = coordinates[i][j].y();
                    int dx = cursor_pos.x() - x, dy = cursor_pos.y() - y;
                    for (int k = 0; k < coordinates[object_to_move].size(); ++k)
                    {
                        x = coordinates[object_to_move][k].x();
                        y = coordinates[object_to_move][k].y();
                        coordinates[object_to_move][k] = {x + dx, y + dy};
                    }
                }
                else
                    coordinates[i][j] = cursor_pos;

                this->update();
            }
}

void MainWindow::draw(QPainter &painter)
{
    for (int i = 0; i < coordinates.size(); ++i)
    {
        for (int j = 0; j < coordinates[i].size(); ++j)
            painter.drawEllipse(coordinates[i][j], 5, 5);

        int j = 0;
        for ( ; j < coordinates[i].size() - 1; ++j)
            painter.drawLine(coordinates[i][j], coordinates[i][j + 1]);

        if (coordinates[i].size())
            painter.drawLine(coordinates[i][j], coordinates[i][0]);
    }
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::blue, 2));

    draw(painter);

    if (mouse_button_flag == RIGHT && (coordinates.back().size()))
            coordinates.push_back({});

    mouse_button_flag = NONE;
    painter.end();
}
