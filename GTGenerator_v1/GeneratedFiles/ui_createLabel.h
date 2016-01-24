/********************************************************************************
** Form generated from reading UI file 'createLabel.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATELABEL_H
#define UI_CREATELABEL_H

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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_createLabel_Dialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *labelName_input;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_2;
    QPushButton *labelColor_button;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *acceptLabel;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *cancelLabel;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *createLabel_Dialog)
    {
        if (createLabel_Dialog->objectName().isEmpty())
            createLabel_Dialog->setObjectName(QStringLiteral("createLabel_Dialog"));
        createLabel_Dialog->resize(449, 96);
        verticalLayout_2 = new QVBoxLayout(createLabel_Dialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(createLabel_Dialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        labelName_input = new QLineEdit(createLabel_Dialog);
        labelName_input->setObjectName(QStringLiteral("labelName_input"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelName_input->sizePolicy().hasHeightForWidth());
        labelName_input->setSizePolicy(sizePolicy);
        labelName_input->setMinimumSize(QSize(200, 0));
        labelName_input->setMaximumSize(QSize(150, 16777215));

        horizontalLayout->addWidget(labelName_input);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        label_2 = new QLabel(createLabel_Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        labelColor_button = new QPushButton(createLabel_Dialog);
        labelColor_button->setObjectName(QStringLiteral("labelColor_button"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelColor_button->sizePolicy().hasHeightForWidth());
        labelColor_button->setSizePolicy(sizePolicy1);
        labelColor_button->setMinimumSize(QSize(30, 0));

        horizontalLayout->addWidget(labelColor_button);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        acceptLabel = new QPushButton(createLabel_Dialog);
        acceptLabel->setObjectName(QStringLiteral("acceptLabel"));

        horizontalLayout_2->addWidget(acceptLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        cancelLabel = new QPushButton(createLabel_Dialog);
        cancelLabel->setObjectName(QStringLiteral("cancelLabel"));

        horizontalLayout_2->addWidget(cancelLabel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(createLabel_Dialog);

        QMetaObject::connectSlotsByName(createLabel_Dialog);
    } // setupUi

    void retranslateUi(QDialog *createLabel_Dialog)
    {
        createLabel_Dialog->setWindowTitle(QApplication::translate("createLabel_Dialog", "Dialog", 0));
        label->setText(QApplication::translate("createLabel_Dialog", "Label name:", 0));
        label_2->setText(QApplication::translate("createLabel_Dialog", "Label color:", 0));
        labelColor_button->setText(QString());
        acceptLabel->setText(QApplication::translate("createLabel_Dialog", "Accept", 0));
        cancelLabel->setText(QApplication::translate("createLabel_Dialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class createLabel_Dialog: public Ui_createLabel_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATELABEL_H
