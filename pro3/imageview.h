#ifndef __IMAGEVIEW_H__
#define __IMAGEVIEW_H__

#include <QMainWindow>
#include <QCommandLineParser>

#include <QCoreApplication>
#include <QApplication>

#include <QtCore>

#include <QWidget>


QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
QT_END_NAMESPACE

class ImageView;

typedef void (ImageView::*fun_t)(int);

class ImageThread : public QThread
{
public:
    ImageThread() : mImageView(NULL), func(NULL) {}
    ImageThread(ImageView &image, fun_t p)
    {
        if (p != NULL) {
            func = p;
            mImageView = &image;
        }
    }

private:
    ImageView *mImageView;
    fun_t func;

    void run()
    {
        qDebug()<<"From worker thread: "<< currentThreadId();
        if (func) (mImageView->*func)(1000);
    }
};

class ImageView : public QMainWindow
{
    Q_OBJECT;

public:
    ImageView();
    bool loadFile(const QString &);
    void xloadFile(int);

private slots:
    void open();
//    void print();
//    void zoomIn();
//    void zoomOut();
//    void normalSize();
//    void fitToWindow();
//    void about();

private:
    void createActions();
    void createMenus();
    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    ImageThread *mImageThread;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor;

    QAction *openAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *zoomOutAct;
    QAction *zoomInAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
};

#endif

