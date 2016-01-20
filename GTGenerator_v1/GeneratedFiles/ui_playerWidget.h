/********************************************************************************
** Form generated from reading UI file 'playerWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERWIDGET_H
#define UI_PLAYERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_playerWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *image_label;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *play_button;
    QSlider *progres_slider;

    void setupUi(QWidget *playerWidget)
    {
        if (playerWidget->objectName().isEmpty())
            playerWidget->setObjectName(QStringLiteral("playerWidget"));
        playerWidget->resize(603, 462);
        verticalLayout_2 = new QVBoxLayout(playerWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        image_label = new QLabel(playerWidget);
        image_label->setObjectName(QStringLiteral("image_label"));

        horizontalLayout->addWidget(image_label);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        play_button = new QPushButton(playerWidget);
        play_button->setObjectName(QStringLiteral("play_button"));
        QIcon icon;
        icon.addFile(QStringLiteral("Resources/play128.png"), QSize(), QIcon::Normal, QIcon::Off);
        play_button->setIcon(icon);
        play_button->setIconSize(QSize(24, 20));

        horizontalLayout_2->addWidget(play_button);

        progres_slider = new QSlider(playerWidget);
        progres_slider->setObjectName(QStringLiteral("progres_slider"));
        progres_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(progres_slider);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(playerWidget);

        QMetaObject::connectSlotsByName(playerWidget);
    } // setupUi

    void retranslateUi(QWidget *playerWidget)
    {
        playerWidget->setWindowTitle(QApplication::translate("playerWidget", "Form", 0));
        image_label->setText(QString());
        play_button->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class playerWidget: public Ui_playerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERWIDGET_H
