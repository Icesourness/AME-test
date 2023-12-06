#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

#define DOT_HIT (coordinates[i][j].x() <= cursor_pos.x() + 10 && coordinates[i][j].x() >= cursor_pos.x() - 10 && \
                coordinates[i][j].y() <= cursor_pos.y() + 10 && coordinates[i][j].y() >= cursor_pos.y() - 10)

enum mouse_button{NONE, LEFT, RIGHT};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent* ev) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void draw(QPainter &painter);

private slots:
    void on_pushButton_clicked();

private:
    QVector<QVector<QPoint>> coordinates;
    mouse_button mouse_button_flag;
    int object_to_move;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
