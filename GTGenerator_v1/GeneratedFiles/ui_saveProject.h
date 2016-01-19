/********************************************************************************
** Form generated from reading UI file 'saveProject.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVEPROJECT_H
#define UI_SAVEPROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_saveProject_Dialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QTableWidget *labelsOverview_table;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *groupBox;
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QPushButton *viewROI_button;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *saveROI_chbox;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox_2;
    QWidget *horizontalLayoutWidget_7;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_9;
    QCheckBox *enhance_chbox;
    QSpacerItem *horizontalSpacer_10;
    QCheckBox *feat_chbox;
    QSpacerItem *horizontalSpacer_11;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *acceptSave_button;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *cancelSave_button;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QDialog *saveProject_Dialog)
    {
        if (saveProject_Dialog->objectName().isEmpty())
            saveProject_Dialog->setObjectName(QStringLiteral("saveProject_Dialog"));
        saveProject_Dialog->resize(365, 360);
        verticalLayoutWidget = new QWidget(saveProject_Dialog);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(9, 9, 351, 341));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(0, 20));

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelsOverview_table = new QTableWidget(verticalLayoutWidget);
        labelsOverview_table->setObjectName(QStringLiteral("labelsOverview_table"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelsOverview_table->sizePolicy().hasHeightForWidth());
        labelsOverview_table->setSizePolicy(sizePolicy1);
        labelsOverview_table->setMinimumSize(QSize(0, 100));
        labelsOverview_table->setMaximumSize(QSize(16777215, 150));

        horizontalLayout->addWidget(labelsOverview_table);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        groupBox = new QGroupBox(verticalLayoutWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayoutWidget_6 = new QWidget(groupBox);
        horizontalLayoutWidget_6->setObjectName(QStringLiteral("horizontalLayoutWidget_6"));
        horizontalLayoutWidget_6->setGeometry(QRect(9, 19, 331, 25));
        horizontalLayout_6 = new QHBoxLayout(horizontalLayoutWidget_6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        viewROI_button = new QPushButton(horizontalLayoutWidget_6);
        viewROI_button->setObjectName(QStringLiteral("viewROI_button"));

        horizontalLayout_6->addWidget(viewROI_button);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);

        saveROI_chbox = new QCheckBox(horizontalLayoutWidget_6);
        saveROI_chbox->setObjectName(QStringLiteral("saveROI_chbox"));

        horizontalLayout_6->addWidget(saveROI_chbox);

        horizontalSpacer_3 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);


        horizontalLayout_5->addWidget(groupBox);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        groupBox_2 = new QGroupBox(verticalLayoutWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayoutWidget_7 = new QWidget(groupBox_2);
        horizontalLayoutWidget_7->setObjectName(QStringLiteral("horizontalLayoutWidget_7"));
        horizontalLayoutWidget_7->setGeometry(QRect(9, 20, 331, 22));
        horizontalLayout_7 = new QHBoxLayout(horizontalLayoutWidget_7);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_9 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_9);

        enhance_chbox = new QCheckBox(horizontalLayoutWidget_7);
        enhance_chbox->setObjectName(QStringLiteral("enhance_chbox"));

        horizontalLayout_7->addWidget(enhance_chbox);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_10);

        feat_chbox = new QCheckBox(horizontalLayoutWidget_7);
        feat_chbox->setObjectName(QStringLiteral("feat_chbox"));

        horizontalLayout_7->addWidget(feat_chbox);

        horizontalSpacer_11 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_11);


        horizontalLayout_2->addWidget(groupBox_2);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        acceptSave_button = new QPushButton(verticalLayoutWidget);
        acceptSave_button->setObjectName(QStringLiteral("acceptSave_button"));

        horizontalLayout_4->addWidget(acceptSave_button);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        cancelSave_button = new QPushButton(verticalLayoutWidget);
        cancelSave_button->setObjectName(QStringLiteral("cancelSave_button"));

        horizontalLayout_4->addWidget(cancelSave_button);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(saveProject_Dialog);

        QMetaObject::connectSlotsByName(saveProject_Dialog);
    } // setupUi

    void retranslateUi(QDialog *saveProject_Dialog)
    {
        saveProject_Dialog->setWindowTitle(QApplication::translate("saveProject_Dialog", "Dialog", 0));
        label->setText(QApplication::translate("saveProject_Dialog", "Project overview:", 0));
        groupBox->setTitle(QApplication::translate("saveProject_Dialog", "ROI options", 0));
        viewROI_button->setText(QApplication::translate("saveProject_Dialog", "View ROI images", 0));
        saveROI_chbox->setText(QApplication::translate("saveProject_Dialog", "Save image ROIs to disk?", 0));
        groupBox_2->setTitle(QApplication::translate("saveProject_Dialog", "ROI enhancing and feature computation", 0));
        enhance_chbox->setText(QApplication::translate("saveProject_Dialog", "ROIs enhanced?", 0));
        feat_chbox->setText(QApplication::translate("saveProject_Dialog", "Features computed?", 0));
        acceptSave_button->setText(QApplication::translate("saveProject_Dialog", "Accept", 0));
        cancelSave_button->setText(QApplication::translate("saveProject_Dialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class saveProject_Dialog: public Ui_saveProject_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEPROJECT_H
