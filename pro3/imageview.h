#ifndef __IMAGEVIEW_H__
#define __IMAGEVIEW_H__

#include <QMainWindow>
#include <QCommandLineParser>

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
QT_END_NAMESPACE

class ImageView : public QMainWindow
{
    Q_OBJECT;

public:
    ImageView();
    bool loadFile(const QString &);

//private slots:
//    void open();
//    void print();
//    void zoomIn();
//    void zoomOut();
//    void normalSize();
//    void fitToWindow();
//    void about();

private:
    void createActions();
    void createMenus();
    void updateAction();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor;

    QAction *openAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *zoomOutAct;
    QAction *zoomInAct;
    QAction *normalSizeAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
};


#endif

