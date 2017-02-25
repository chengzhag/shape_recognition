/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBoxShapeRecognising;
    QLabel *labelPreProcessingMethod;
    QPushButton *pushButtonCameraIn;
    QSlider *horizontalSliderAreaThreshold;
    QLabel *labelAreaThreshold;
    QSpinBox *spinBoxCameraID;
    QLabel *labelCameraID;
    QPushButton *pushButtonImSelect;
    QComboBox *comboBoxPreProcessingMethod;
    QGroupBox *groupBoxResetSampleNet;
    QPushButton *pushButtonResetSampleNet;
    QSpinBox *spinBoxNumLayers;
    QLabel *labelNumLayers;
    QLabel *labelHiddenLayerSize;
    QSpinBox *spinBoxHiddenLayerSize;
    QGroupBox *groupBoxRenameShape;
    QComboBox *comboBoxCategory;
    QLabel *labelClassify;
    QLineEdit *lineEditAddCategory;
    QLabel *labelAddCategory;
    QPushButton *pushButtonAddClassify;
    QLabel *labelWeight;
    QLabel *labelNoiseStrength;
    QSpinBox *spinBoxWeight;
    QSpinBox *spinBoxNoiseStrength;
    QPushButton *pushButtonStartFineTuning;
    QLabel *labelNoiseUnit;
    QTextBrowser *textBrowserLog;
    QGroupBox *groupBoxAfterChange;
    QPushButton *pushButtonSaveNetAndSample;
    QPushButton *pushButtonLoadNetAndSample;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(570, 535);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBoxShapeRecognising = new QGroupBox(centralWidget);
        groupBoxShapeRecognising->setObjectName(QStringLiteral("groupBoxShapeRecognising"));
        groupBoxShapeRecognising->setGeometry(QRect(30, 10, 251, 141));
        labelPreProcessingMethod = new QLabel(groupBoxShapeRecognising);
        labelPreProcessingMethod->setObjectName(QStringLiteral("labelPreProcessingMethod"));
        labelPreProcessingMethod->setGeometry(QRect(10, 50, 71, 21));
        pushButtonCameraIn = new QPushButton(groupBoxShapeRecognising);
        pushButtonCameraIn->setObjectName(QStringLiteral("pushButtonCameraIn"));
        pushButtonCameraIn->setGeometry(QRect(130, 20, 111, 21));
        horizontalSliderAreaThreshold = new QSlider(groupBoxShapeRecognising);
        horizontalSliderAreaThreshold->setObjectName(QStringLiteral("horizontalSliderAreaThreshold"));
        horizontalSliderAreaThreshold->setGeometry(QRect(100, 110, 141, 22));
        horizontalSliderAreaThreshold->setMinimum(5);
        horizontalSliderAreaThreshold->setMaximum(100);
        horizontalSliderAreaThreshold->setOrientation(Qt::Horizontal);
        labelAreaThreshold = new QLabel(groupBoxShapeRecognising);
        labelAreaThreshold->setObjectName(QStringLiteral("labelAreaThreshold"));
        labelAreaThreshold->setGeometry(QRect(10, 110, 71, 21));
        spinBoxCameraID = new QSpinBox(groupBoxShapeRecognising);
        spinBoxCameraID->setObjectName(QStringLiteral("spinBoxCameraID"));
        spinBoxCameraID->setGeometry(QRect(100, 80, 141, 22));
        labelCameraID = new QLabel(groupBoxShapeRecognising);
        labelCameraID->setObjectName(QStringLiteral("labelCameraID"));
        labelCameraID->setGeometry(QRect(10, 80, 71, 21));
        pushButtonImSelect = new QPushButton(groupBoxShapeRecognising);
        pushButtonImSelect->setObjectName(QStringLiteral("pushButtonImSelect"));
        pushButtonImSelect->setGeometry(QRect(10, 20, 111, 21));
        comboBoxPreProcessingMethod = new QComboBox(groupBoxShapeRecognising);
        comboBoxPreProcessingMethod->setObjectName(QStringLiteral("comboBoxPreProcessingMethod"));
        comboBoxPreProcessingMethod->setGeometry(QRect(80, 50, 161, 22));
        labelPreProcessingMethod->raise();
        pushButtonCameraIn->raise();
        horizontalSliderAreaThreshold->raise();
        labelAreaThreshold->raise();
        labelCameraID->raise();
        pushButtonImSelect->raise();
        spinBoxCameraID->raise();
        comboBoxPreProcessingMethod->raise();
        groupBoxResetSampleNet = new QGroupBox(centralWidget);
        groupBoxResetSampleNet->setObjectName(QStringLiteral("groupBoxResetSampleNet"));
        groupBoxResetSampleNet->setGeometry(QRect(30, 160, 251, 111));
        pushButtonResetSampleNet = new QPushButton(groupBoxResetSampleNet);
        pushButtonResetSampleNet->setObjectName(QStringLiteral("pushButtonResetSampleNet"));
        pushButtonResetSampleNet->setEnabled(true);
        pushButtonResetSampleNet->setGeometry(QRect(10, 80, 231, 21));
        pushButtonResetSampleNet->setCheckable(false);
        pushButtonResetSampleNet->setChecked(false);
        spinBoxNumLayers = new QSpinBox(groupBoxResetSampleNet);
        spinBoxNumLayers->setObjectName(QStringLiteral("spinBoxNumLayers"));
        spinBoxNumLayers->setGeometry(QRect(100, 20, 141, 22));
        spinBoxNumLayers->setMinimum(1);
        labelNumLayers = new QLabel(groupBoxResetSampleNet);
        labelNumLayers->setObjectName(QStringLiteral("labelNumLayers"));
        labelNumLayers->setGeometry(QRect(10, 20, 71, 21));
        labelHiddenLayerSize = new QLabel(groupBoxResetSampleNet);
        labelHiddenLayerSize->setObjectName(QStringLiteral("labelHiddenLayerSize"));
        labelHiddenLayerSize->setGeometry(QRect(10, 50, 61, 21));
        spinBoxHiddenLayerSize = new QSpinBox(groupBoxResetSampleNet);
        spinBoxHiddenLayerSize->setObjectName(QStringLiteral("spinBoxHiddenLayerSize"));
        spinBoxHiddenLayerSize->setGeometry(QRect(100, 50, 141, 21));
        spinBoxHiddenLayerSize->setMinimum(1);
        spinBoxHiddenLayerSize->setValue(9);
        groupBoxRenameShape = new QGroupBox(centralWidget);
        groupBoxRenameShape->setObjectName(QStringLiteral("groupBoxRenameShape"));
        groupBoxRenameShape->setEnabled(true);
        groupBoxRenameShape->setGeometry(QRect(30, 280, 251, 171));
        comboBoxCategory = new QComboBox(groupBoxRenameShape);
        comboBoxCategory->setObjectName(QStringLiteral("comboBoxCategory"));
        comboBoxCategory->setGeometry(QRect(100, 20, 141, 21));
        comboBoxCategory->setMaxVisibleItems(10);
        labelClassify = new QLabel(groupBoxRenameShape);
        labelClassify->setObjectName(QStringLiteral("labelClassify"));
        labelClassify->setGeometry(QRect(10, 20, 81, 21));
        lineEditAddCategory = new QLineEdit(groupBoxRenameShape);
        lineEditAddCategory->setObjectName(QStringLiteral("lineEditAddCategory"));
        lineEditAddCategory->setGeometry(QRect(100, 50, 91, 21));
        labelAddCategory = new QLabel(groupBoxRenameShape);
        labelAddCategory->setObjectName(QStringLiteral("labelAddCategory"));
        labelAddCategory->setGeometry(QRect(10, 50, 81, 21));
        pushButtonAddClassify = new QPushButton(groupBoxRenameShape);
        pushButtonAddClassify->setObjectName(QStringLiteral("pushButtonAddClassify"));
        pushButtonAddClassify->setGeometry(QRect(200, 50, 41, 23));
        labelWeight = new QLabel(groupBoxRenameShape);
        labelWeight->setObjectName(QStringLiteral("labelWeight"));
        labelWeight->setGeometry(QRect(10, 80, 81, 21));
        labelNoiseStrength = new QLabel(groupBoxRenameShape);
        labelNoiseStrength->setObjectName(QStringLiteral("labelNoiseStrength"));
        labelNoiseStrength->setGeometry(QRect(10, 110, 81, 21));
        spinBoxWeight = new QSpinBox(groupBoxRenameShape);
        spinBoxWeight->setObjectName(QStringLiteral("spinBoxWeight"));
        spinBoxWeight->setGeometry(QRect(100, 80, 141, 22));
        spinBoxWeight->setMinimum(0);
        spinBoxWeight->setMaximum(30000);
        spinBoxWeight->setValue(30);
        spinBoxNoiseStrength = new QSpinBox(groupBoxRenameShape);
        spinBoxNoiseStrength->setObjectName(QStringLiteral("spinBoxNoiseStrength"));
        spinBoxNoiseStrength->setGeometry(QRect(100, 110, 91, 22));
        spinBoxNoiseStrength->setMaximum(20);
        spinBoxNoiseStrength->setSingleStep(0);
        spinBoxNoiseStrength->setValue(5);
        pushButtonStartFineTuning = new QPushButton(groupBoxRenameShape);
        pushButtonStartFineTuning->setObjectName(QStringLiteral("pushButtonStartFineTuning"));
        pushButtonStartFineTuning->setGeometry(QRect(10, 140, 231, 21));
        labelNoiseUnit = new QLabel(groupBoxRenameShape);
        labelNoiseUnit->setObjectName(QStringLiteral("labelNoiseUnit"));
        labelNoiseUnit->setGeometry(QRect(200, 110, 41, 21));
        labelNoiseUnit->setAlignment(Qt::AlignCenter);
        textBrowserLog = new QTextBrowser(centralWidget);
        textBrowserLog->setObjectName(QStringLiteral("textBrowserLog"));
        textBrowserLog->setGeometry(QRect(290, 20, 251, 491));
        groupBoxAfterChange = new QGroupBox(centralWidget);
        groupBoxAfterChange->setObjectName(QStringLiteral("groupBoxAfterChange"));
        groupBoxAfterChange->setEnabled(true);
        groupBoxAfterChange->setGeometry(QRect(30, 460, 251, 51));
        pushButtonSaveNetAndSample = new QPushButton(groupBoxAfterChange);
        pushButtonSaveNetAndSample->setObjectName(QStringLiteral("pushButtonSaveNetAndSample"));
        pushButtonSaveNetAndSample->setGeometry(QRect(10, 20, 111, 21));
        pushButtonLoadNetAndSample = new QPushButton(groupBoxAfterChange);
        pushButtonLoadNetAndSample->setObjectName(QStringLiteral("pushButtonLoadNetAndSample"));
        pushButtonLoadNetAndSample->setGeometry(QRect(130, 20, 111, 21));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        comboBoxCategory->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        groupBoxShapeRecognising->setTitle(QApplication::translate("MainWindow", "\345\275\242\347\212\266\350\257\206\345\210\253", Q_NULLPTR));
        labelPreProcessingMethod->setText(QApplication::translate("MainWindow", "\351\242\204\345\244\204\347\220\206\346\226\271\346\263\225\357\274\232", Q_NULLPTR));
        pushButtonCameraIn->setText(QApplication::translate("MainWindow", "\346\221\204\345\203\217\345\244\264\350\276\223\345\205\245", Q_NULLPTR));
        labelAreaThreshold->setText(QApplication::translate("MainWindow", "\351\235\242\347\247\257\351\230\210\345\200\274\357\274\232", Q_NULLPTR));
        labelCameraID->setText(QApplication::translate("MainWindow", "\346\221\204\345\203\217\345\244\264ID\357\274\232", Q_NULLPTR));
        pushButtonImSelect->setText(QApplication::translate("MainWindow", "\351\200\211\345\217\226\345\233\276\347\211\207", Q_NULLPTR));
        comboBoxPreProcessingMethod->clear();
        comboBoxPreProcessingMethod->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "OTSU\357\274\210\351\273\230\350\256\244\357\274\211", Q_NULLPTR)
         << QApplication::translate("MainWindow", "\350\207\252\351\200\202\345\272\224\344\272\214\345\200\274\345\214\226", Q_NULLPTR)
         << QApplication::translate("MainWindow", "CANNY\350\276\271\347\274\230\346\243\200\346\265\213", Q_NULLPTR)
        );
        groupBoxResetSampleNet->setTitle(QApplication::translate("MainWindow", "\351\207\215\347\275\256\347\245\236\347\273\217\347\275\221\347\273\234\345\222\214\346\240\267\346\234\254", Q_NULLPTR));
        pushButtonResetSampleNet->setText(QApplication::translate("MainWindow", "\351\207\215\347\275\256", Q_NULLPTR));
        labelNumLayers->setText(QApplication::translate("MainWindow", "\351\232\220\345\220\253\345\261\202\345\261\202\346\225\260\357\274\232", Q_NULLPTR));
        labelHiddenLayerSize->setText(QApplication::translate("MainWindow", "\345\261\202\350\212\202\347\202\271\346\225\260\357\274\232", Q_NULLPTR));
        groupBoxRenameShape->setTitle(QApplication::translate("MainWindow", "\347\202\271\345\207\273\345\233\276\345\275\242\347\272\240\351\224\231", Q_NULLPTR));
        labelClassify->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\347\261\273\345\210\253\357\274\232", Q_NULLPTR));
        labelAddCategory->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\347\261\273\345\210\253\357\274\232", Q_NULLPTR));
        pushButtonAddClassify->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240", Q_NULLPTR));
        labelWeight->setText(QApplication::translate("MainWindow", "\345\242\236\345\212\240\346\255\245\351\225\277\357\274\232", Q_NULLPTR));
        labelNoiseStrength->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\345\231\252\345\243\260\357\274\232", Q_NULLPTR));
        pushButtonStartFineTuning->setText(QApplication::translate("MainWindow", "\345\276\256\350\260\203\347\245\236\347\273\217\347\275\221\347\273\234", Q_NULLPTR));
        labelNoiseUnit->setText(QApplication::translate("MainWindow", "\345\203\217\347\264\240", Q_NULLPTR));
        textBrowserLog->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        groupBoxAfterChange->setTitle(QApplication::translate("MainWindow", "\344\277\235\345\255\230\346\210\226\350\277\230\345\216\237\347\245\236\347\273\217\347\275\221\347\273\234\345\222\214\346\240\267\346\234\254", Q_NULLPTR));
        pushButtonSaveNetAndSample->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", Q_NULLPTR));
        pushButtonLoadNetAndSample->setText(QApplication::translate("MainWindow", "\350\277\230\345\216\237", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
