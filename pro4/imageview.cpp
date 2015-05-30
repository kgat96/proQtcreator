
#include <QtWidgets>

#include "imageview.h"

struct headformat {
    int hight;
    int width;
    int format;
};

void imageinfo(struct headformat *h)
{
    qDebug() << "hight: " << h->hight;
    qDebug() << "width: " << h->width;
    qDebug() << "format: " << h->format;
}

void ImageView::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "mouseMoveEvent " << event->x();
    event->accept();
}

void ImageView::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "mousePressEvent " << event->button();
    event->accept();
}

void ImageView::mouseReleaseEvent(QMouseEvent *event)
{
//  Qt::LeftButton; // define -- LeftButton 0001
    qDebug() << "mouseReleaseEvent " << event->button();
    event->accept();
}

ImageView::ImageView()
{
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);

    createActions();
    createMenus();

    resize(QGuiApplication::primaryScreen()->availableSize() * 2 / 5);

//  loadFile(1);
}

void ImageView::updateActions()
{
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}

bool ImageView::loadFile(const QString &fileName)
{
//    QImage image(fileName);
//    if (image.isNull()) {
//        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
//                tr("Cannot load %1").arg(QDir::toNativeSeparators(fileName)));
//        setWindowFilePath(QString());
//        imageLabel->setPixmap(QString());
//        imageLabel->adjustSize();
//        return false;
//    }

    struct headformat *ihead;

    QFile rawfile("./image/image.raw");
    if (!rawfile.open(QFile::ReadOnly)) return false;

    QByteArray array = rawfile.readAll();

    ihead = (struct headformat *)array.data();

    imageinfo(ihead);

    QImage image((uchar *)array.data() + sizeof(struct headformat),
                 320, 320, QImage::Format_RGBX8888);

    imageLabel->setPixmap(QPixmap::fromImage(image));
    scaleFactor = 1.0;

    printAct->setEnabled(true);
    fitToWindowAct->setEnabled(true);
    updateActions();

    if(!fitToWindowAct->isChecked())
        imageLabel->adjustSize();

    setWindowFilePath(fileName);
    return true;
}

void ImageView::xloadFile(int count)
{
    QString fileName;

    fileName = "./1.png";
    // this delay test async fun
    QThread::msleep(count);
    loadFile(fileName);
}

void ImageView::open()
{
    QStringList mimeTypeFileters;
    foreach(const QByteArray &mimeTypeName, QImageReader::supportedMimeTypes())
        mimeTypeFileters.append(mimeTypeName);

    mimeTypeFileters.sort();
    const QStringList picturesLocations =
            QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);

    for (int i = 0; i < picturesLocations.size(); ++i)
         qDebug() << picturesLocations.at(i);

    QFileDialog dialog(this, tr("Open File"),
         picturesLocations.isEmpty() ? QDir::currentPath():picturesLocations.first());

    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setMimeTypeFilters(mimeTypeFileters);
    dialog.selectMimeTypeFilter("image/jpeg");

//    while(dialog.exec() == QDialog::Accepted &&
//          !loadFile(dialog.selectedFiles().first()));
    while(dialog.exec() != QDialog::Accepted);
    loadFile(dialog.selectedFiles().first());
}

void ImageView::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+0"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    printAct = new QAction(tr("&Print..."), this);
    printAct->setShortcut(tr("Ctrl+P"));
    printAct->setEnabled(false);
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    zoomInAct = new QAction(tr("Zoom &In (25%)"), this);
    zoomInAct->setShortcut(tr("Ctrl++"));
    zoomInAct->setEnabled(false);
    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

    zoomOutAct = new QAction(tr("Zoom &Out (25%)"), this);
    zoomOutAct->setShortcut(tr("Ctrl+-"));
    zoomOutAct->setEnabled(false);
    connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

    normalSizeAct = new QAction(tr("&Normal Size"), this);
    normalSizeAct->setShortcut(tr("Ctrl+S"));
    normalSizeAct->setEnabled(false);
    connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));

    fitToWindowAct = new QAction(tr("&Fit to Window"), this);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setCheckable(true);
    connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void ImageView::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    viewMenu = new QMenu(tr("&view"), this);
    viewMenu->addAction(zoomInAct);
    viewMenu->addAction(zoomOutAct);
    viewMenu->addAction(normalSizeAct);
    viewMenu->addSeparator();
    viewMenu->addAction(fitToWindowAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(helpMenu);
}

