/********************************************************************************
** Form generated from reading UI file 'newProject.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPROJECT_H
#define UI_NEWPROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_newProject_dialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *projectName_edit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *sourceImage_button;
    QHBoxLayout *horizontalLayout_6;
    QRadioButton *sourceVideo_button;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *sourcePath_edit;
    QPushButton *browsePath_button;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *acceptNew_button;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *cancelNew_button;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *newProject_dialog)
    {
        if (newProject_dialog->objectName().isEmpty())
            newProject_dialog->setObjectName(QStringLiteral("newProject_dialog"));
        newProject_dialog->resize(443, 237);
        verticalLayout_3 = new QVBoxLayout(newProject_dialog);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_3 = new QLabel(newProject_dialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font;
        font.setFamily(QStringLiteral("Optima"));
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        label_3->setFont(font);

        verticalLayout->addWidget(label_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(newProject_dialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        projectName_edit = new QLineEdit(newProject_dialog);
        projectName_edit->setObjectName(QStringLiteral("projectName_edit"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(projectName_edit->sizePolicy().hasHeightForWidth());
        projectName_edit->setSizePolicy(sizePolicy);
        projectName_edit->setMinimumSize(QSize(100, 0));
        projectName_edit->setMaximumSize(QSize(250, 16777215));

        horizontalLayout->addWidget(projectName_edit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_2 = new QLabel(newProject_dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setMinimumSize(QSize(100, 0));
        label_2->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_5->addWidget(label_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        sourceImage_button = new QRadioButton(newProject_dialog);
        sourceImage_button->setObjectName(QStringLiteral("sourceImage_button"));

        horizontalLayout_2->addWidget(sourceImage_button);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        sourceVideo_button = new QRadioButton(newProject_dialog);
        sourceVideo_button->setObjectName(QStringLiteral("sourceVideo_button"));

        horizontalLayout_6->addWidget(sourceVideo_button);


        verticalLayout_2->addLayout(horizontalLayout_6);


        horizontalLayout_5->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(newProject_dialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        sourcePath_edit = new QLineEdit(newProject_dialog);
        sourcePath_edit->setObjectName(QStringLiteral("sourcePath_edit"));

        horizontalLayout_4->addWidget(sourcePath_edit);

        browsePath_button = new QPushButton(newProject_dialog);
        browsePath_button->setObjectName(QStringLiteral("browsePath_button"));

        horizontalLayout_4->addWidget(browsePath_button);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        acceptNew_button = new QPushButton(newProject_dialog);
        acceptNew_button->setObjectName(QStringLiteral("acceptNew_button"));

        horizontalLayout_3->addWidget(acceptNew_button);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        cancelNew_button = new QPushButton(newProject_dialog);
        cancelNew_button->setObjectName(QStringLiteral("cancelNew_button"));

        horizontalLayout_3->addWidget(cancelNew_button);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_3->addLayout(verticalLayout);


        retranslateUi(newProject_dialog);

        QMetaObject::connectSlotsByName(newProject_dialog);
    } // setupUi

    void retranslateUi(QDialog *newProject_dialog)
    {
        newProject_dialog->setWindowTitle(QApplication::translate("newProject_dialog", "Dialog", 0));
        label_3->setText(QApplication::translate("newProject_dialog", "Create New GTGenerator Project:", 0));
        label->setText(QApplication::translate("newProject_dialog", "Project name:", 0));
        label_2->setText(QApplication::translate("newProject_dialog", "Select input source:", 0));
        sourceImage_button->setText(QApplication::translate("newProject_dialog", "Image sequence", 0));
        sourceVideo_button->setText(QApplication::translate("newProject_dialog", "Video", 0));
        label_4->setText(QApplication::translate("newProject_dialog", "Path", 0));
        browsePath_button->setText(QApplication::translate("newProject_dialog", "Browse", 0));
        acceptNew_button->setText(QApplication::translate("newProject_dialog", "Accept", 0));
        cancelNew_button->setText(QApplication::translate("newProject_dialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class newProject_dialog: public Ui_newProject_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPROJECT_H
