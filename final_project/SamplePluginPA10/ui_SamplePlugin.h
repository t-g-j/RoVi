/********************************************************************************
** Form generated from reading UI file 'SamplePlugin.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAMPLEPLUGIN_H
#define UI_SAMPLEPLUGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SamplePlugin
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *_btn0;
    QPushButton *_btn1;
    QPushButton *_btn2;
    QPushButton *_btn3;
    QPushButton *_btn4;
    QCheckBox *_checkBox;
    QSpinBox *_spinBox;
    QSlider *_slider;
    QLabel *_label;
    QLabel *_label_marker;

    void setupUi(QDockWidget *SamplePlugin)
    {
        if (SamplePlugin->objectName().isEmpty())
            SamplePlugin->setObjectName(QStringLiteral("SamplePlugin"));
        SamplePlugin->resize(603, 627);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        _btn0 = new QPushButton(dockWidgetContents);
        _btn0->setObjectName(QStringLiteral("_btn0"));

        verticalLayout->addWidget(_btn0);

        _btn1 = new QPushButton(dockWidgetContents);
        _btn1->setObjectName(QStringLiteral("_btn1"));

        verticalLayout->addWidget(_btn1);

        _btn2 = new QPushButton(dockWidgetContents);
        _btn2->setObjectName(QStringLiteral("_btn2"));

        verticalLayout->addWidget(_btn2);

        _btn3 = new QPushButton(dockWidgetContents);
        _btn3->setObjectName(QStringLiteral("_btn3"));

        verticalLayout->addWidget(_btn3);

        _btn4 = new QPushButton(dockWidgetContents);
        _btn4->setObjectName(QStringLiteral("_btn4"));

        verticalLayout->addWidget(_btn4);

        _checkBox = new QCheckBox(dockWidgetContents);
        _checkBox->setObjectName(QStringLiteral("_checkBox"));

        verticalLayout->addWidget(_checkBox);

        _spinBox = new QSpinBox(dockWidgetContents);
        _spinBox->setObjectName(QStringLiteral("_spinBox"));

        verticalLayout->addWidget(_spinBox);

        _slider = new QSlider(dockWidgetContents);
        _slider->setObjectName(QStringLiteral("_slider"));
        _slider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(_slider);

        _label = new QLabel(dockWidgetContents);
        _label->setObjectName(QStringLiteral("_label"));

        verticalLayout->addWidget(_label);

        _label_marker = new QLabel(dockWidgetContents);
        _label_marker->setObjectName(QStringLiteral("_label_marker"));

        verticalLayout->addWidget(_label_marker);


        verticalLayout_2->addLayout(verticalLayout);

        SamplePlugin->setWidget(dockWidgetContents);

        retranslateUi(SamplePlugin);

        QMetaObject::connectSlotsByName(SamplePlugin);
    } // setupUi

    void retranslateUi(QDockWidget *SamplePlugin)
    {
        SamplePlugin->setWindowTitle(QApplication::translate("SamplePlugin", "DockWidget", 0));
        _btn0->setText(QApplication::translate("SamplePlugin", "Load background", 0));
        _btn1->setText(QApplication::translate("SamplePlugin", "StartTimer", 0));
        _btn2->setText(QApplication::translate("SamplePlugin", "Open saving files", 0));
        _btn3->setText(QApplication::translate("SamplePlugin", "Read data", 0));
        _btn4->setText(QApplication::translate("SamplePlugin", "Initialize", 0));
        _checkBox->setText(QApplication::translate("SamplePlugin", "CheckBox", 0));
        _label->setText(QApplication::translate("SamplePlugin", "Label", 0));
        _label_marker->setText(QApplication::translate("SamplePlugin", "Label_containing_marker", 0));
    } // retranslateUi

};

namespace Ui {
    class SamplePlugin: public Ui_SamplePlugin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAMPLEPLUGIN_H
