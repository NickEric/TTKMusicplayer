#include "musicemojilabelwidget.h"
#include "musictinyuiobject.h"
#include "musicclickedlabel.h"
#include "musicwidgetheaders.h"
#include "musicstringutils.h"
#include "musicclickedgroup.h"

#include <QFile>
#include <QButtonGroup>

MusicEMOJILabelWidget::MusicEMOJILabelWidget(QWidget *parent)
    : QLabel(parent)
{
    setFixedSize(260, 175);
    setAttribute(Qt::WA_DeleteOnClose);
    setStyleSheet("background:white");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    QToolButton *closeButton = new QToolButton(this);
    closeButton->setFixedSize(16, 16);
    closeButton->setStyleSheet(MusicUIObject::MQSSTinyBtnClose);
    closeButton->setCursor(QCursor(Qt::PointingHandCursor));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QWidget *labelWidget = new QWidget(this);
    labelWidget->setFixedHeight(110);
    //
    QGridLayout *labelIconLayout = new QGridLayout(labelWidget);
    labelIconLayout->setContentsMargins(0, 0, 0, 0);
    labelIconLayout->setSpacing(3);

    MusicClickedGroup *clickedGroup = new MusicClickedGroup(this);
    connect(clickedGroup, SIGNAL(clicked(int)), SLOT(labelClicked(int)));

    for(int i=0; i<3; ++i)
    {
        for(int j=0; j<7; ++j)
        {
            MusicClickedLabel *l = new MusicClickedLabel(labelWidget);
            l->setAlignment(Qt::AlignCenter);
            l->setStyleSheet(QString("QLabel{%1}QLabel:hover{%2}").arg(MusicUIObject::MQSSBorderStyle04, MusicUIObject::MQSSBorderStyle05));
            l->setFixedSize(32, 32);
            labelIconLayout->addWidget(l, i, j);

            m_labelItems << l;
            clickedGroup->mapped(l);
        }
    }
    labelWidget->setLayout(labelIconLayout);
    //
    QWidget *buttonWidget = new QWidget(this);
    QHBoxLayout *buttonWidgetLayout = new QHBoxLayout(buttonWidget);\
    buttonWidgetLayout->setContentsMargins(0, 0, 5, 0);
    buttonWidgetLayout->addStretch(1);

    QButtonGroup *buttonGroup = new QButtonGroup(buttonWidget);
#if TTK_QT_VERSION_CHECK(5,15,0)
    connect(buttonGroup, SIGNAL(idClicked(int)), SLOT(buttonClicked(int)));
#else
    connect(buttonGroup, SIGNAL(buttonClicked(int)), SLOT(buttonClicked(int)));
#endif
    for(int i=0; i<5; ++i)
    {
        QToolButton *button = new QToolButton(buttonWidget);
        button->setCursor(Qt::PointingHandCursor);
        button->setText(QString::number(i + 1));
        button->setFixedSize(15, 15);
        buttonWidgetLayout->addWidget(button, 0 , Qt::AlignRight);
        buttonWidget->setLayout(buttonWidgetLayout);
        buttonGroup->addButton(button, i);
        m_buttonItems << button;
    }
    buttonClicked(0);
    //
    layout->addWidget(closeButton, 0, Qt::AlignRight | Qt::AlignVCenter);
    layout->addWidget(labelWidget);
    layout->addWidget(buttonWidget);
    setLayout(layout);

    QFile file(":/emoji/db");
    if(file.open(QFile::ReadOnly))
    {
       m_datas = QString(file.readAll()).split(MusicUtils::String::newlines());
    }
    file.close();
}

MusicEMOJILabelWidget::~MusicEMOJILabelWidget()
{
    qDeleteAll(m_labelItems);
    qDeleteAll(m_buttonItems);
}

void MusicEMOJILabelWidget::buttonClicked(int index)
{
    m_currentPage = index;
    for(QToolButton *button : qAsConst(m_buttonItems))
    {
        button->setStyleSheet(MusicUIObject::MQSSBackgroundStyle01 + MusicUIObject::MQSSBorderStyle01);
    }
    m_buttonItems[index]->setStyleSheet(m_buttonItems[index]->styleSheet() + MusicUIObject::MQSSBorderStyle04);

    for(int i=0; i<3; ++i)
    {
        for(int j=0; j<7; ++j)
        {
            const int in = i * 7 + j;
            m_labelItems[in]->setPixmap(QPixmap(QString(":/emoji/%1").arg(21 * index + in + 1)));
        }
    }
}

void MusicEMOJILabelWidget::labelClicked(int index)
{
    const int offset = index + m_currentPage * 21;
    if(offset < 0 || offset >= m_datas.count())
    {
        return;
    }

    Q_EMIT dataChanged(m_datas[offset]);
}

void MusicEMOJILabelWidget::leaveEvent(QEvent *event)
{
    QLabel::leaveEvent(event);
    close();
}
