#include "musicopenfilewidget.h"
#include "musicclickedlabel.h"
#include "musicwidgetutils.h"
#include "musicwidgetheaders.h"

MusicOpenFileWidget::MusicOpenFileWidget(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    QLabel *uploadFileIcon = new QLabel(this);
    uploadFileIcon->setPixmap(QPixmap(":/tiny/btn_open_file"));
    MusicClickedLabel *uploadFile = new MusicClickedLabel(this);
    uploadFile->setText(tr("Open File"));
    MusicUtils::Widget::setLabelFontStyle(uploadFile, MusicObject::Underline);
    connect(uploadFile, SIGNAL(clicked()), SIGNAL(uploadFileClicked()));

    QLabel *uploadDirIcon = new QLabel(this);
    uploadDirIcon->setPixmap(QPixmap(":/tiny/btn_open_files"));
    MusicClickedLabel *uploadDir = new MusicClickedLabel(this);
    uploadDir->setText(tr("Open Dir"));
    MusicUtils::Widget::setLabelFontStyle(uploadDir, MusicObject::Underline);
    connect(uploadDir, SIGNAL(clicked()), SIGNAL(uploadDirClicked()));

    layout->addWidget(uploadFileIcon, 0, 0, Qt::AlignRight);
    layout->addWidget(uploadFile, 0, 1, Qt::AlignLeft);
    layout->addWidget(uploadDirIcon, 1, 0, Qt::AlignRight);
    layout->addWidget(uploadDir, 1, 1, Qt::AlignLeft);
    setLayout(layout);

    resize(150, 50);
}

void MusicOpenFileWidget::adjustWidgetRect(int w, int h)
{
    const int x = (w - width() - 60) / 2;
    const int y = (h - height()) / 2;
    move(x, y);
}
