/********************************************************************************
** Form generated from reading UI file 'gtgenerator.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GTGENERATOR_H
#define UI_GTGENERATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <playerwidget.h>

QT_BEGIN_NAMESPACE

class Ui_GTGeneratorClass
{
public:
    QAction *actionNewProject;
    QAction *actionLoadProject;
    QAction *actionSaveProject;
    QAction *actionSettings;
    QAction *actionHelp;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *tagging_layout;
    QHBoxLayout *horizontalLayout_6;
    playerWidget *GTplayerWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *labels_group;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *labels_table;
    QPushButton *createLabel_button;
    QGroupBox *currentROI_group;
    QTableWidget *ROIs_table;
    QGroupBox *ROIenhance_group;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer_5;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GTGeneratorClass)
    {
        if (GTGeneratorClass->objectName().isEmpty())
            GTGeneratorClass->setObjectName(QStringLiteral("GTGeneratorClass"));
        GTGeneratorClass->resize(1151, 594);
        actionNewProject = new QAction(GTGeneratorClass);
        actionNewProject->setObjectName(QStringLiteral("actionNewProject"));
        QIcon icon;
        icon.addFile(QStringLiteral("Resources/New.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNewProject->setIcon(icon);
        actionLoadProject = new QAction(GTGeneratorClass);
        actionLoadProject->setObjectName(QStringLiteral("actionLoadProject"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("Resources/Load.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoadProject->setIcon(icon1);
        actionSaveProject = new QAction(GTGeneratorClass);
        actionSaveProject->setObjectName(QStringLiteral("actionSaveProject"));
        QIcon icon2;
        icon2.addFile(QStringLiteral("Resources/Save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveProject->setIcon(icon2);
        actionSettings = new QAction(GTGeneratorClass);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        QIcon icon3;
        icon3.addFile(QStringLiteral("Resources/Settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSettings->setIcon(icon3);
        actionHelp = new QAction(GTGeneratorClass);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        QIcon icon4;
        icon4.addFile(QStringLiteral("Resources/Help.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHelp->setIcon(icon4);
        centralWidget = new QWidget(GTGeneratorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tagging_layout = new QVBoxLayout();
        tagging_layout->setSpacing(6);
        tagging_layout->setObjectName(QStringLiteral("tagging_layout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        GTplayerWidget = new playerWidget(centralWidget);
        GTplayerWidget->setObjectName(QStringLiteral("GTplayerWidget"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GTplayerWidget->sizePolicy().hasHeightForWidth());
        GTplayerWidget->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(GTplayerWidget);


        tagging_layout->addLayout(horizontalLayout_6);


        horizontalLayout->addLayout(tagging_layout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        labels_group = new QGroupBox(centralWidget);
        labels_group->setObjectName(QStringLiteral("labels_group"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labels_group->sizePolicy().hasHeightForWidth());
        labels_group->setSizePolicy(sizePolicy1);
        labels_group->setMinimumSize(QSize(300, 0));
        labels_group->setMaximumSize(QSize(350, 16777215));
        verticalLayoutWidget_3 = new QWidget(labels_group);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(10, 20, 331, 141));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        labels_table = new QTableWidget(verticalLayoutWidget_3);
        labels_table->setObjectName(QStringLiteral("labels_table"));

        verticalLayout_2->addWidget(labels_table);

        createLabel_button = new QPushButton(verticalLayoutWidget_3);
        createLabel_button->setObjectName(QStringLiteral("createLabel_button"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(createLabel_button->sizePolicy().hasHeightForWidth());
        createLabel_button->setSizePolicy(sizePolicy2);

        verticalLayout_2->addWidget(createLabel_button);


        verticalLayout->addWidget(labels_group);

        currentROI_group = new QGroupBox(centralWidget);
        currentROI_group->setObjectName(QStringLiteral("currentROI_group"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(currentROI_group->sizePolicy().hasHeightForWidth());
        currentROI_group->setSizePolicy(sizePolicy3);
        currentROI_group->setMinimumSize(QSize(300, 0));
        currentROI_group->setMaximumSize(QSize(350, 220));
        ROIs_table = new QTableWidget(currentROI_group);
        ROIs_table->setObjectName(QStringLiteral("ROIs_table"));
        ROIs_table->setGeometry(QRect(10, 20, 331, 191));
        QPalette palette;
        QBrush brush(QColor(170, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        ROIs_table->setPalette(palette);
        ROIs_table->setAutoFillBackground(false);
        ROIs_table->setSelectionBehavior(QAbstractItemView::SelectItems);

        verticalLayout->addWidget(currentROI_group);

        ROIenhance_group = new QGroupBox(centralWidget);
        ROIenhance_group->setObjectName(QStringLiteral("ROIenhance_group"));
        sizePolicy3.setHeightForWidth(ROIenhance_group->sizePolicy().hasHeightForWidth());
        ROIenhance_group->setSizePolicy(sizePolicy3);
        ROIenhance_group->setMinimumSize(QSize(300, 0));
        ROIenhance_group->setMaximumSize(QSize(350, 120));
        verticalLayout_5 = new QVBoxLayout(ROIenhance_group);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(60, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(ROIenhance_group);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        horizontalSpacer_2 = new QSpacerItem(60, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_4 = new QSpacerItem(60, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        pushButton_3 = new QPushButton(ROIenhance_group);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_3->addWidget(pushButton_3);

        horizontalSpacer_3 = new QSpacerItem(60, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_6 = new QSpacerItem(60, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        pushButton_4 = new QPushButton(ROIenhance_group);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_4->addWidget(pushButton_4);

        horizontalSpacer_5 = new QSpacerItem(60, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);


        verticalLayout_4->addLayout(horizontalLayout_4);


        verticalLayout_5->addLayout(verticalLayout_4);


        verticalLayout->addWidget(ROIenhance_group);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout);

        GTGeneratorClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(GTGeneratorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        GTGeneratorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(GTGeneratorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GTGeneratorClass->setStatusBar(statusBar);

        mainToolBar->addAction(actionNewProject);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionLoadProject);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionSaveProject);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionSettings);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionHelp);

        retranslateUi(GTGeneratorClass);

        QMetaObject::connectSlotsByName(GTGeneratorClass);
    } // setupUi

    void retranslateUi(QMainWindow *GTGeneratorClass)
    {
        GTGeneratorClass->setWindowTitle(QApplication::translate("GTGeneratorClass", "GTGenerator", 0));
        actionNewProject->setText(QApplication::translate("GTGeneratorClass", "NewProject", 0));
        actionNewProject->setShortcut(QApplication::translate("GTGeneratorClass", "Ctrl+N", 0));
        actionLoadProject->setText(QApplication::translate("GTGeneratorClass", "LoadProject", 0));
        actionSaveProject->setText(QApplication::translate("GTGeneratorClass", "SaveProject", 0));
        actionSettings->setText(QApplication::translate("GTGeneratorClass", "Settings", 0));
        actionHelp->setText(QApplication::translate("GTGeneratorClass", "Help", 0));
        labels_group->setTitle(QApplication::translate("GTGeneratorClass", "Labels", 0));
        createLabel_button->setText(QApplication::translate("GTGeneratorClass", "+ New Label", 0));
        currentROI_group->setTitle(QApplication::translate("GTGeneratorClass", "Current frame ROIs", 0));
        ROIenhance_group->setTitle(QApplication::translate("GTGeneratorClass", "ROI enhancement and features", 0));
        pushButton_2->setText(QApplication::translate("GTGeneratorClass", "Settings", 0));
        pushButton_3->setText(QApplication::translate("GTGeneratorClass", "Enhance ROIs", 0));
        pushButton_4->setText(QApplication::translate("GTGeneratorClass", "Calculate features", 0));
    } // retranslateUi

};

namespace Ui {
    class GTGeneratorClass: public Ui_GTGeneratorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GTGENERATOR_H
