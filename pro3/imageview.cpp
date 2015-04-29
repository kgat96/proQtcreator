
#include <QtWidgets>

#include "imageview.h"

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

//    createActions();
//    createMenus();

    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);

}
