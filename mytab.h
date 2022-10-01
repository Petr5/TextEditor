#ifndef MYTAB_H
#define MYTAB_H
#include <QWidget>
#include <QTabWidget>
class MyTab : public QTabWidget
{
    Q_OBJECT
public:
    explicit MyTab(QTabWidget* parent = 0);
//    explicit GeneralTab(const QFileInfo &fileInfo, QWidget *parent = nullptr);
};

#endif // MYTAB_H
