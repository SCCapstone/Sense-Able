/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionMain_Menu;
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    QStackedWidget *stackedWidget;
    QWidget *Page_StreamData;
    QLabel *objectLabel;
    QLabel *cameraView;
    QPushButton *backButtonGo;
    QPushButton *changeCamera;
    QPushButton *changeOrient;
    QLabel *cameraLabel;
    QLabel *orientLabel;
    QPushButton *Play;
    QWidget *Page_Home;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QLabel *titleLabel;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *streamButton;
    QPushButton *readDataPageButton;
    QSpacerItem *verticalSpacer_2;
    QPushButton *settingsPageButton;
    QPushButton *QuitButton;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QWidget *Page_Settings;
    QLabel *settingsLabel;
    QFrame *line_2;
    QFrame *line_3;
    QLabel *label_25;
    QCheckBox *speechCheckBox;
    QCheckBox *beepCheckBox;
    QFrame *line_4;
    QLabel *label_26;
    QFrame *line_5;
    QPushButton *notificationsButton;
    QLabel *label_9;
    QComboBox *comboBox_2;
    QPushButton *backButtonSettings;
    QSlider *notificationDistanceSlider;
    QLabel *notifDistanceLabel;
    QWidget *Page_Notifications;
    QLabel *notificationsTitle;
    QFrame *line_6;
    QLabel *notificationLabel;
    QLabel *objectTypeLabel;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *obj1_notif_choice;
    QLabel *label_2;
    QComboBox *obj2_notif_choice;
    QComboBox *obj3_notif_choice;
    QComboBox *obj4_notif_choice;
    QComboBox *obj5_notif_choice;
    QComboBox *obj6_notif_choice;
    QComboBox *obj7_notif_choice;
    QComboBox *obj8_notif_choice;
    QPushButton *backButton;
    QWidget *Page_ReplayData;
    QLabel *readingDataLabel;
    QFrame *line_7;
    QLabel *pt1;
    QLabel *pt3;
    QLabel *pt5;
    QLabel *pt6;
    QLabel *pt7;
    QLabel *pt8;
    QLabel *pt9;
    QLabel *pt10;
    QLabel *pt12;
    QLabel *pt11;
    QLabel *pointLabel;
    QLabel *pointLabel_2;
    QLabel *pointLabel_3;
    QLabel *pointLabel_4;
    QLabel *pointLabel_5;
    QLabel *pointLabel_9;
    QLabel *pointLabel_10;
    QLabel *pointLabel_11;
    QLabel *pointLabel_12;
    QLabel *pointLabel_7;
    QLabel *pointLabel_8;
    QPushButton *readDataButton;
    QPushButton *backButtonRead;
    QPushButton *cancelButtonRead;
    QLabel *pointLabel_13;
    QLabel *pointLabel_14;
    QLabel *pointLabel_15;
    QLabel *pointLabel_16;
    QLabel *pt13;
    QLabel *pt14;
    QLabel *pt15;
    QLabel *pt16;
    QLabel *pointLabel_6;
    QLabel *pt2;
    QLabel *pt4;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(892, 726);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(782, 0));
        actionMain_Menu = new QAction(MainWindow);
        actionMain_Menu->setObjectName(QStringLiteral("actionMain_Menu"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        centralWidget->setFont(font);
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setMinimumSize(QSize(866, 624));
        QPalette palette;
        QBrush brush(QColor(239, 246, 238, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        QBrush brush1(QColor(114, 159, 207, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::NoRole, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette.setBrush(QPalette::Inactive, QPalette::NoRole, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette.setBrush(QPalette::Disabled, QPalette::NoRole, brush1);
        stackedWidget->setPalette(palette);
        QFont font1;
        font1.setPointSize(11);
        stackedWidget->setFont(font1);
        Page_StreamData = new QWidget();
        Page_StreamData->setObjectName(QStringLiteral("Page_StreamData"));
        objectLabel = new QLabel(Page_StreamData);
        objectLabel->setObjectName(QStringLiteral("objectLabel"));
        objectLabel->setGeometry(QRect(380, 10, 141, 27));
        QPalette palette1;
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush2);
        QBrush brush3(QColor(190, 190, 190, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush2);
        objectLabel->setPalette(palette1);
        cameraView = new QLabel(Page_StreamData);
        cameraView->setObjectName(QStringLiteral("cameraView"));
        cameraView->setGeometry(QRect(0, 0, 881, 671));
        cameraView->setMinimumSize(QSize(641, 541));
        cameraView->setStyleSheet(QStringLiteral("background-color: rgb(136, 138, 133);"));
        cameraView->setAlignment(Qt::AlignCenter);
        backButtonGo = new QPushButton(Page_StreamData);
        backButtonGo->setObjectName(QStringLiteral("backButtonGo"));
        backButtonGo->setGeometry(QRect(10, 20, 61, 51));
        QPalette palette2;
        QBrush brush4(QColor(245, 36, 54, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush4);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush4);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush4);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        backButtonGo->setPalette(palette2);
        QFont font2;
        font2.setPointSize(12);
        backButtonGo->setFont(font2);
        changeCamera = new QPushButton(Page_StreamData);
        changeCamera->setObjectName(QStringLiteral("changeCamera"));
        changeCamera->setGeometry(QRect(10, 620, 141, 31));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Button, brush4);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush4);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        changeCamera->setPalette(palette3);
        changeCamera->setFont(font2);
        changeOrient = new QPushButton(Page_StreamData);
        changeOrient->setObjectName(QStringLiteral("changeOrient"));
        changeOrient->setGeometry(QRect(160, 620, 201, 31));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Button, brush4);
        palette4.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::Button, brush4);
        palette4.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::Button, brush4);
        palette4.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        changeOrient->setPalette(palette4);
        changeOrient->setFont(font2);
        cameraLabel = new QLabel(Page_StreamData);
        cameraLabel->setObjectName(QStringLiteral("cameraLabel"));
        cameraLabel->setGeometry(QRect(10, 580, 141, 27));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette5.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette5.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette5.setBrush(QPalette::Active, QPalette::ToolTipBase, brush2);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette5.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        palette5.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush2);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette5.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        palette5.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush2);
        cameraLabel->setPalette(palette5);
        orientLabel = new QLabel(Page_StreamData);
        orientLabel->setObjectName(QStringLiteral("orientLabel"));
        orientLabel->setGeometry(QRect(160, 580, 201, 27));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette6.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette6.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette6.setBrush(QPalette::Active, QPalette::ToolTipBase, brush2);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette6.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette6.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        palette6.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush2);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette6.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette6.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        palette6.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush2);
        orientLabel->setPalette(palette6);
        Play = new QPushButton(Page_StreamData);
        Play->setObjectName(QStringLiteral("Play"));
        Play->setGeometry(QRect(720, 620, 141, 31));
        QPalette palette7;
        palette7.setBrush(QPalette::Active, QPalette::Button, brush4);
        palette7.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette7.setBrush(QPalette::Inactive, QPalette::Button, brush4);
        palette7.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette7.setBrush(QPalette::Disabled, QPalette::Button, brush4);
        palette7.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        Play->setPalette(palette7);
        Play->setFont(font2);
        stackedWidget->addWidget(Page_StreamData);
        cameraView->raise();
        objectLabel->raise();
        backButtonGo->raise();
        changeCamera->raise();
        changeOrient->raise();
        cameraLabel->raise();
        orientLabel->raise();
        Play->raise();
        Page_Home = new QWidget();
        Page_Home->setObjectName(QStringLiteral("Page_Home"));
        horizontalLayout_4 = new QHBoxLayout(Page_Home);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(200, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetNoConstraint);
        titleLabel = new QLabel(Page_Home);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(titleLabel->sizePolicy().hasHeightForWidth());
        titleLabel->setSizePolicy(sizePolicy1);
        QPalette palette8;
        QBrush brush5(QColor(185, 88, 107, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette8.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette8.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette8.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette8.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette8.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette8.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        titleLabel->setPalette(palette8);
        QFont font3;
        font3.setPointSize(45);
        titleLabel->setFont(font3);
        titleLabel->setScaledContents(true);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setIndent(0);

        verticalLayout_2->addWidget(titleLabel);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalSpacer_3 = new QSpacerItem(60, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        streamButton = new QPushButton(Page_Home);
        streamButton->setObjectName(QStringLiteral("streamButton"));
        sizePolicy1.setHeightForWidth(streamButton->sizePolicy().hasHeightForWidth());
        streamButton->setSizePolicy(sizePolicy1);
        QPalette palette9;
        palette9.setBrush(QPalette::Active, QPalette::Button, brush4);
        palette9.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette9.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette9.setBrush(QPalette::Inactive, QPalette::Button, brush4);
        palette9.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette9.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette9.setBrush(QPalette::Disabled, QPalette::Button, brush4);
        palette9.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette9.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        streamButton->setPalette(palette9);
        QFont font4;
        font4.setPointSize(17);
        streamButton->setFont(font4);

        verticalLayout->addWidget(streamButton);

        readDataPageButton = new QPushButton(Page_Home);
        readDataPageButton->setObjectName(QStringLiteral("readDataPageButton"));
        sizePolicy1.setHeightForWidth(readDataPageButton->sizePolicy().hasHeightForWidth());
        readDataPageButton->setSizePolicy(sizePolicy1);
        QPalette palette10;
        palette10.setBrush(QPalette::Active, QPalette::Button, brush4);
        palette10.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette10.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette10.setBrush(QPalette::Inactive, QPalette::Button, brush4);
        palette10.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette10.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette10.setBrush(QPalette::Disabled, QPalette::Button, brush4);
        palette10.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette10.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        readDataPageButton->setPalette(palette10);
        readDataPageButton->setFont(font4);

        verticalLayout->addWidget(readDataPageButton);

        verticalSpacer_2 = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        settingsPageButton = new QPushButton(Page_Home);
        settingsPageButton->setObjectName(QStringLiteral("settingsPageButton"));
        sizePolicy1.setHeightForWidth(settingsPageButton->sizePolicy().hasHeightForWidth());
        settingsPageButton->setSizePolicy(sizePolicy1);
        QPalette palette11;
        palette11.setBrush(QPalette::Active, QPalette::Button, brush4);
        palette11.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette11.setBrush(QPalette::Inactive, QPalette::Button, brush4);
        palette11.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette11.setBrush(QPalette::Disabled, QPalette::Button, brush4);
        palette11.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        settingsPageButton->setPalette(palette11);
        settingsPageButton->setFont(font4);

        verticalLayout->addWidget(settingsPageButton);

        QuitButton = new QPushButton(Page_Home);
        QuitButton->setObjectName(QStringLiteral("QuitButton"));
        sizePolicy1.setHeightForWidth(QuitButton->sizePolicy().hasHeightForWidth());
        QuitButton->setSizePolicy(sizePolicy1);
        QPalette palette12;
        palette12.setBrush(QPalette::Active, QPalette::Button, brush4);
        palette12.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette12.setBrush(QPalette::Inactive, QPalette::Button, brush4);
        palette12.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette12.setBrush(QPalette::Disabled, QPalette::Button, brush4);
        palette12.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        QuitButton->setPalette(palette12);
        QuitButton->setFont(font4);

        verticalLayout->addWidget(QuitButton);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer_4 = new QSpacerItem(60, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_2);

        horizontalSpacer_2 = new QSpacerItem(200, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_3);

        verticalSpacer_3 = new QSpacerItem(17, 57, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);


        horizontalLayout_4->addLayout(verticalLayout_3);

        stackedWidget->addWidget(Page_Home);
        Page_Settings = new QWidget();
        Page_Settings->setObjectName(QStringLiteral("Page_Settings"));
        settingsLabel = new QLabel(Page_Settings);
        settingsLabel->setObjectName(QStringLiteral("settingsLabel"));
        settingsLabel->setGeometry(QRect(220, -30, 301, 121));
        QPalette palette13;
        palette13.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette13.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette13.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        settingsLabel->setPalette(palette13);
        QFont font5;
        font5.setPointSize(37);
        settingsLabel->setFont(font5);
        line_2 = new QFrame(Page_Settings);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(200, 50, 441, 30));
        QPalette palette14;
        palette14.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette14.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette14.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        line_2->setPalette(palette14);
        line_2->setFrameShadow(QFrame::Plain);
        line_2->setLineWidth(3);
        line_2->setFrameShape(QFrame::HLine);
        line_3 = new QFrame(Page_Settings);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(200, 180, 441, 30));
        QPalette palette15;
        palette15.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette15.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette15.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        line_3->setPalette(palette15);
        line_3->setFrameShadow(QFrame::Plain);
        line_3->setLineWidth(3);
        line_3->setFrameShape(QFrame::HLine);
        label_25 = new QLabel(Page_Settings);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(220, 210, 231, 41));
        QFont font6;
        font6.setPointSize(20);
        label_25->setFont(font6);
        speechCheckBox = new QCheckBox(Page_Settings);
        speechCheckBox->setObjectName(QStringLiteral("speechCheckBox"));
        speechCheckBox->setGeometry(QRect(170, 260, 301, 41));
        speechCheckBox->setFont(font4);
        speechCheckBox->setLayoutDirection(Qt::RightToLeft);
        speechCheckBox->setTristate(false);
        beepCheckBox = new QCheckBox(Page_Settings);
        beepCheckBox->setObjectName(QStringLiteral("beepCheckBox"));
        beepCheckBox->setGeometry(QRect(170, 300, 301, 41));
        beepCheckBox->setFont(font4);
        beepCheckBox->setLayoutDirection(Qt::RightToLeft);
        line_4 = new QFrame(Page_Settings);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(200, 340, 441, 30));
        QPalette palette16;
        palette16.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette16.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette16.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        line_4->setPalette(palette16);
        line_4->setFrameShadow(QFrame::Plain);
        line_4->setLineWidth(3);
        line_4->setFrameShape(QFrame::HLine);
        label_26 = new QLabel(Page_Settings);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(220, 370, 371, 41));
        label_26->setFont(font6);
        line_5 = new QFrame(Page_Settings);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(200, 480, 441, 30));
        QPalette palette17;
        palette17.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette17.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette17.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        line_5->setPalette(palette17);
        line_5->setFrameShadow(QFrame::Plain);
        line_5->setLineWidth(3);
        line_5->setFrameShape(QFrame::HLine);
        notificationsButton = new QPushButton(Page_Settings);
        notificationsButton->setObjectName(QStringLiteral("notificationsButton"));
        notificationsButton->setGeometry(QRect(220, 530, 181, 51));
        QPalette palette18;
        QBrush brush6(QColor(191, 64, 64, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette18.setBrush(QPalette::Active, QPalette::Button, brush6);
        palette18.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette18.setBrush(QPalette::Inactive, QPalette::Button, brush6);
        palette18.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette18.setBrush(QPalette::Disabled, QPalette::Button, brush6);
        palette18.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        notificationsButton->setPalette(palette18);
        label_9 = new QLabel(Page_Settings);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(220, 80, 291, 41));
        label_9->setFont(font6);
        comboBox_2 = new QComboBox(Page_Settings);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(220, 420, 181, 41));
        backButtonSettings = new QPushButton(Page_Settings);
        backButtonSettings->setObjectName(QStringLiteral("backButtonSettings"));
        backButtonSettings->setGeometry(QRect(10, 10, 61, 51));
        QPalette palette19;
        palette19.setBrush(QPalette::Active, QPalette::Button, brush4);
        palette19.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette19.setBrush(QPalette::Inactive, QPalette::Button, brush4);
        palette19.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette19.setBrush(QPalette::Disabled, QPalette::Button, brush4);
        palette19.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        backButtonSettings->setPalette(palette19);
        backButtonSettings->setFont(font2);
        notificationDistanceSlider = new QSlider(Page_Settings);
        notificationDistanceSlider->setObjectName(QStringLiteral("notificationDistanceSlider"));
        notificationDistanceSlider->setGeometry(QRect(220, 140, 181, 20));
        notificationDistanceSlider->setMinimum(1);
        notificationDistanceSlider->setMaximum(100);
        notificationDistanceSlider->setOrientation(Qt::Horizontal);
        notifDistanceLabel = new QLabel(Page_Settings);
        notifDistanceLabel->setObjectName(QStringLiteral("notifDistanceLabel"));
        notifDistanceLabel->setGeometry(QRect(550, 130, 89, 23));
        stackedWidget->addWidget(Page_Settings);
        Page_Notifications = new QWidget();
        Page_Notifications->setObjectName(QStringLiteral("Page_Notifications"));
        notificationsTitle = new QLabel(Page_Notifications);
        notificationsTitle->setObjectName(QStringLiteral("notificationsTitle"));
        notificationsTitle->setGeometry(QRect(220, -30, 381, 121));
        QPalette palette20;
        palette20.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette20.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette20.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        notificationsTitle->setPalette(palette20);
        notificationsTitle->setFont(font5);
        line_6 = new QFrame(Page_Notifications);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(190, 50, 441, 30));
        QPalette palette21;
        palette21.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette21.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette21.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        line_6->setPalette(palette21);
        line_6->setFrameShadow(QFrame::Plain);
        line_6->setLineWidth(3);
        line_6->setFrameShape(QFrame::HLine);
        notificationLabel = new QLabel(Page_Notifications);
        notificationLabel->setObjectName(QStringLiteral("notificationLabel"));
        notificationLabel->setGeometry(QRect(460, 80, 231, 41));
        QPalette palette22;
        palette22.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette22.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette22.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        notificationLabel->setPalette(palette22);
        QFont font7;
        font7.setPointSize(19);
        notificationLabel->setFont(font7);
        notificationLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        objectTypeLabel = new QLabel(Page_Notifications);
        objectTypeLabel->setObjectName(QStringLiteral("objectTypeLabel"));
        objectTypeLabel->setGeometry(QRect(220, 80, 231, 41));
        QPalette palette23;
        palette23.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        palette23.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette23.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette23.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette23.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette23.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        objectTypeLabel->setPalette(palette23);
        objectTypeLabel->setFont(font7);
        objectTypeLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label = new QLabel(Page_Notifications);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(220, 160, 231, 41));
        QPalette palette24;
        QBrush brush7(QColor(0, 0, 0, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette24.setBrush(QPalette::Active, QPalette::WindowText, brush7);
        palette24.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette24.setBrush(QPalette::Inactive, QPalette::WindowText, brush7);
        palette24.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette24.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette24.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        label->setPalette(palette24);
        label->setFont(font4);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(Page_Notifications);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(220, 280, 231, 41));
        QPalette palette25;
        palette25.setBrush(QPalette::Active, QPalette::WindowText, brush7);
        palette25.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette25.setBrush(QPalette::Inactive, QPalette::WindowText, brush7);
        palette25.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette25.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette25.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        label_3->setPalette(palette25);
        label_3->setFont(font4);
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_4 = new QLabel(Page_Notifications);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(220, 340, 231, 41));
        QPalette palette26;
        palette26.setBrush(QPalette::Active, QPalette::WindowText, brush7);
        palette26.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette26.setBrush(QPalette::Inactive, QPalette::WindowText, brush7);
        palette26.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette26.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette26.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        label_4->setPalette(palette26);
        label_4->setFont(font4);
        label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_7 = new QLabel(Page_Notifications);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(220, 520, 231, 41));
        QPalette palette27;
        palette27.setBrush(QPalette::Active, QPalette::WindowText, brush7);
        palette27.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette27.setBrush(QPalette::Inactive, QPalette::WindowText, brush7);
        palette27.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette27.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette27.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        label_7->setPalette(palette27);
        label_7->setFont(font4);
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_8 = new QLabel(Page_Notifications);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(220, 580, 231, 41));
        QPalette palette28;
        palette28.setBrush(QPalette::Active, QPalette::WindowText, brush7);
        palette28.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette28.setBrush(QPalette::Inactive, QPalette::WindowText, brush7);
        palette28.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette28.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette28.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        label_8->setPalette(palette28);
        label_8->setFont(font4);
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_5 = new QLabel(Page_Notifications);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(220, 400, 231, 41));
        QPalette palette29;
        palette29.setBrush(QPalette::Active, QPalette::WindowText, brush7);
        palette29.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette29.setBrush(QPalette::Inactive, QPalette::WindowText, brush7);
        palette29.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette29.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette29.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        label_5->setPalette(palette29);
        label_5->setFont(font4);
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6 = new QLabel(Page_Notifications);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(220, 460, 231, 41));
        QPalette palette30;
        palette30.setBrush(QPalette::Active, QPalette::WindowText, brush7);
        palette30.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette30.setBrush(QPalette::Inactive, QPalette::WindowText, brush7);
        palette30.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette30.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette30.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        label_6->setPalette(palette30);
        label_6->setFont(font4);
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        obj1_notif_choice = new QComboBox(Page_Notifications);
        obj1_notif_choice->setObjectName(QStringLiteral("obj1_notif_choice"));
        obj1_notif_choice->setGeometry(QRect(450, 160, 181, 41));
        label_2 = new QLabel(Page_Notifications);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(220, 220, 231, 41));
        QPalette palette31;
        palette31.setBrush(QPalette::Active, QPalette::WindowText, brush7);
        palette31.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette31.setBrush(QPalette::Inactive, QPalette::WindowText, brush7);
        palette31.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette31.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        palette31.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        label_2->setPalette(palette31);
        label_2->setFont(font4);
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        obj2_notif_choice = new QComboBox(Page_Notifications);
        obj2_notif_choice->setObjectName(QStringLiteral("obj2_notif_choice"));
        obj2_notif_choice->setGeometry(QRect(450, 220, 181, 41));
        obj3_notif_choice = new QComboBox(Page_Notifications);
        obj3_notif_choice->setObjectName(QStringLiteral("obj3_notif_choice"));
        obj3_notif_choice->setGeometry(QRect(450, 280, 181, 41));
        obj4_notif_choice = new QComboBox(Page_Notifications);
        obj4_notif_choice->setObjectName(QStringLiteral("obj4_notif_choice"));
        obj4_notif_choice->setGeometry(QRect(450, 340, 181, 41));
        obj5_notif_choice = new QComboBox(Page_Notifications);
        obj5_notif_choice->setObjectName(QStringLiteral("obj5_notif_choice"));
        obj5_notif_choice->setGeometry(QRect(450, 400, 181, 41));
        obj6_notif_choice = new QComboBox(Page_Notifications);
        obj6_notif_choice->setObjectName(QStringLiteral("obj6_notif_choice"));
        obj6_notif_choice->setGeometry(QRect(450, 460, 181, 41));
        obj7_notif_choice = new QComboBox(Page_Notifications);
        obj7_notif_choice->setObjectName(QStringLiteral("obj7_notif_choice"));
        obj7_notif_choice->setGeometry(QRect(450, 520, 181, 41));
        obj8_notif_choice = new QComboBox(Page_Notifications);
        obj8_notif_choice->setObjectName(QStringLiteral("obj8_notif_choice"));
        obj8_notif_choice->setGeometry(QRect(450, 580, 181, 41));
        obj8_notif_choice->setEditable(false);
        backButton = new QPushButton(Page_Notifications);
        backButton->setObjectName(QStringLiteral("backButton"));
        backButton->setGeometry(QRect(10, 10, 61, 51));
        QPalette palette32;
        QBrush brush8(QColor(245, 36, 59, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette32.setBrush(QPalette::Active, QPalette::Button, brush8);
        palette32.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette32.setBrush(QPalette::Inactive, QPalette::Button, brush8);
        palette32.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette32.setBrush(QPalette::Disabled, QPalette::Button, brush8);
        palette32.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        backButton->setPalette(palette32);
        stackedWidget->addWidget(Page_Notifications);
        Page_ReplayData = new QWidget();
        Page_ReplayData->setObjectName(QStringLiteral("Page_ReplayData"));
        readingDataLabel = new QLabel(Page_ReplayData);
        readingDataLabel->setObjectName(QStringLiteral("readingDataLabel"));
        readingDataLabel->setGeometry(QRect(220, -30, 431, 121));
        QPalette palette33;
        palette33.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette33.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette33.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        readingDataLabel->setPalette(palette33);
        QFont font8;
        font8.setPointSize(25);
        readingDataLabel->setFont(font8);
        line_7 = new QFrame(Page_ReplayData);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setGeometry(QRect(220, 50, 441, 30));
        QPalette palette34;
        palette34.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette34.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette34.setBrush(QPalette::Disabled, QPalette::WindowText, brush3);
        line_7->setPalette(palette34);
        line_7->setFrameShadow(QFrame::Plain);
        line_7->setLineWidth(3);
        line_7->setFrameShape(QFrame::HLine);
        pt1 = new QLabel(Page_ReplayData);
        pt1->setObjectName(QStringLiteral("pt1"));
        pt1->setGeometry(QRect(20, 350, 41, 51));
        pt3 = new QLabel(Page_ReplayData);
        pt3->setObjectName(QStringLiteral("pt3"));
        pt3->setGeometry(QRect(120, 350, 41, 51));
        pt5 = new QLabel(Page_ReplayData);
        pt5->setObjectName(QStringLiteral("pt5"));
        pt5->setGeometry(QRect(220, 350, 41, 51));
        pt6 = new QLabel(Page_ReplayData);
        pt6->setObjectName(QStringLiteral("pt6"));
        pt6->setGeometry(QRect(270, 350, 41, 51));
        pt7 = new QLabel(Page_ReplayData);
        pt7->setObjectName(QStringLiteral("pt7"));
        pt7->setGeometry(QRect(320, 350, 41, 51));
        pt8 = new QLabel(Page_ReplayData);
        pt8->setObjectName(QStringLiteral("pt8"));
        pt8->setGeometry(QRect(370, 350, 41, 51));
        pt9 = new QLabel(Page_ReplayData);
        pt9->setObjectName(QStringLiteral("pt9"));
        pt9->setGeometry(QRect(420, 350, 41, 51));
        pt10 = new QLabel(Page_ReplayData);
        pt10->setObjectName(QStringLiteral("pt10"));
        pt10->setEnabled(true);
        pt10->setGeometry(QRect(470, 350, 41, 51));
        pt12 = new QLabel(Page_ReplayData);
        pt12->setObjectName(QStringLiteral("pt12"));
        pt12->setGeometry(QRect(570, 350, 41, 51));
        pt11 = new QLabel(Page_ReplayData);
        pt11->setObjectName(QStringLiteral("pt11"));
        pt11->setGeometry(QRect(520, 350, 41, 51));
        pointLabel = new QLabel(Page_ReplayData);
        pointLabel->setObjectName(QStringLiteral("pointLabel"));
        pointLabel->setGeometry(QRect(20, 310, 41, 51));
        pointLabel_2 = new QLabel(Page_ReplayData);
        pointLabel_2->setObjectName(QStringLiteral("pointLabel_2"));
        pointLabel_2->setGeometry(QRect(70, 310, 41, 51));
        pointLabel_3 = new QLabel(Page_ReplayData);
        pointLabel_3->setObjectName(QStringLiteral("pointLabel_3"));
        pointLabel_3->setGeometry(QRect(120, 310, 41, 51));
        pointLabel_4 = new QLabel(Page_ReplayData);
        pointLabel_4->setObjectName(QStringLiteral("pointLabel_4"));
        pointLabel_4->setGeometry(QRect(170, 310, 41, 51));
        pointLabel_5 = new QLabel(Page_ReplayData);
        pointLabel_5->setObjectName(QStringLiteral("pointLabel_5"));
        pointLabel_5->setGeometry(QRect(220, 310, 41, 51));
        pointLabel_9 = new QLabel(Page_ReplayData);
        pointLabel_9->setObjectName(QStringLiteral("pointLabel_9"));
        pointLabel_9->setGeometry(QRect(420, 310, 41, 51));
        pointLabel_10 = new QLabel(Page_ReplayData);
        pointLabel_10->setObjectName(QStringLiteral("pointLabel_10"));
        pointLabel_10->setGeometry(QRect(470, 310, 41, 51));
        pointLabel_11 = new QLabel(Page_ReplayData);
        pointLabel_11->setObjectName(QStringLiteral("pointLabel_11"));
        pointLabel_11->setGeometry(QRect(520, 310, 41, 51));
        pointLabel_12 = new QLabel(Page_ReplayData);
        pointLabel_12->setObjectName(QStringLiteral("pointLabel_12"));
        pointLabel_12->setGeometry(QRect(570, 310, 41, 51));
        pointLabel_7 = new QLabel(Page_ReplayData);
        pointLabel_7->setObjectName(QStringLiteral("pointLabel_7"));
        pointLabel_7->setGeometry(QRect(370, 310, 41, 51));
        pointLabel_8 = new QLabel(Page_ReplayData);
        pointLabel_8->setObjectName(QStringLiteral("pointLabel_8"));
        pointLabel_8->setGeometry(QRect(320, 310, 41, 51));
        readDataButton = new QPushButton(Page_ReplayData);
        readDataButton->setObjectName(QStringLiteral("readDataButton"));
        readDataButton->setGeometry(QRect(330, 460, 181, 61));
        QPalette palette35;
        palette35.setBrush(QPalette::Active, QPalette::Button, brush4);
        palette35.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette35.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette35.setBrush(QPalette::Inactive, QPalette::Button, brush4);
        palette35.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette35.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette35.setBrush(QPalette::Disabled, QPalette::Button, brush4);
        palette35.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        palette35.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        readDataButton->setPalette(palette35);
        readDataButton->setFont(font4);
        backButtonRead = new QPushButton(Page_ReplayData);
        backButtonRead->setObjectName(QStringLiteral("backButtonRead"));
        backButtonRead->setGeometry(QRect(10, 10, 61, 51));
        QPalette palette36;
        palette36.setBrush(QPalette::Active, QPalette::Button, brush4);
        palette36.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette36.setBrush(QPalette::Inactive, QPalette::Button, brush4);
        palette36.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette36.setBrush(QPalette::Disabled, QPalette::Button, brush4);
        palette36.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        backButtonRead->setPalette(palette36);
        backButtonRead->setFont(font2);
        cancelButtonRead = new QPushButton(Page_ReplayData);
        cancelButtonRead->setObjectName(QStringLiteral("cancelButtonRead"));
        cancelButtonRead->setGeometry(QRect(360, 550, 121, 31));
        QPalette palette37;
        palette37.setBrush(QPalette::Active, QPalette::Button, brush4);
        palette37.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette37.setBrush(QPalette::Inactive, QPalette::Button, brush4);
        palette37.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette37.setBrush(QPalette::Disabled, QPalette::Button, brush4);
        palette37.setBrush(QPalette::Disabled, QPalette::ButtonText, brush3);
        cancelButtonRead->setPalette(palette37);
        cancelButtonRead->setFont(font2);
        pointLabel_13 = new QLabel(Page_ReplayData);
        pointLabel_13->setObjectName(QStringLiteral("pointLabel_13"));
        pointLabel_13->setGeometry(QRect(620, 310, 41, 51));
        pointLabel_14 = new QLabel(Page_ReplayData);
        pointLabel_14->setObjectName(QStringLiteral("pointLabel_14"));
        pointLabel_14->setGeometry(QRect(670, 310, 41, 51));
        pointLabel_15 = new QLabel(Page_ReplayData);
        pointLabel_15->setObjectName(QStringLiteral("pointLabel_15"));
        pointLabel_15->setGeometry(QRect(720, 310, 41, 51));
        pointLabel_16 = new QLabel(Page_ReplayData);
        pointLabel_16->setObjectName(QStringLiteral("pointLabel_16"));
        pointLabel_16->setGeometry(QRect(770, 310, 41, 51));
        pt13 = new QLabel(Page_ReplayData);
        pt13->setObjectName(QStringLiteral("pt13"));
        pt13->setGeometry(QRect(620, 350, 41, 51));
        pt14 = new QLabel(Page_ReplayData);
        pt14->setObjectName(QStringLiteral("pt14"));
        pt14->setGeometry(QRect(670, 350, 41, 51));
        pt15 = new QLabel(Page_ReplayData);
        pt15->setObjectName(QStringLiteral("pt15"));
        pt15->setGeometry(QRect(720, 350, 41, 51));
        pt16 = new QLabel(Page_ReplayData);
        pt16->setObjectName(QStringLiteral("pt16"));
        pt16->setGeometry(QRect(770, 350, 41, 51));
        pointLabel_6 = new QLabel(Page_ReplayData);
        pointLabel_6->setObjectName(QStringLiteral("pointLabel_6"));
        pointLabel_6->setGeometry(QRect(270, 310, 41, 51));
        pt2 = new QLabel(Page_ReplayData);
        pt2->setObjectName(QStringLiteral("pt2"));
        pt2->setGeometry(QRect(70, 350, 41, 51));
        pt4 = new QLabel(Page_ReplayData);
        pt4->setObjectName(QStringLiteral("pt4"));
        pt4->setGeometry(QRect(170, 350, 41, 51));
        stackedWidget->addWidget(Page_ReplayData);

        horizontalLayout->addWidget(stackedWidget);


        gridLayout_3->addLayout(horizontalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);
        obj1_notif_choice->setCurrentIndex(0);
        obj2_notif_choice->setCurrentIndex(1);
        obj3_notif_choice->setCurrentIndex(2);
        obj4_notif_choice->setCurrentIndex(3);
        obj5_notif_choice->setCurrentIndex(4);
        obj6_notif_choice->setCurrentIndex(5);
        obj7_notif_choice->setCurrentIndex(6);
        obj8_notif_choice->setCurrentIndex(6);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionMain_Menu->setText(QApplication::translate("MainWindow", "Main Menu", 0));
        objectLabel->setText(QApplication::translate("MainWindow", "Object: NONE", 0));
        cameraView->setText(QString());
        backButtonGo->setText(QApplication::translate("MainWindow", "Back", 0));
        changeCamera->setText(QApplication::translate("MainWindow", "Change Camera", 0));
        changeOrient->setText(QApplication::translate("MainWindow", "Change Orientation", 0));
        cameraLabel->setText(QApplication::translate("MainWindow", "Camera: Built-In", 0));
        orientLabel->setText(QApplication::translate("MainWindow", "Orientation: Horizontal", 0));
        Play->setText(QApplication::translate("MainWindow", "Play", 0));
        titleLabel->setText(QApplication::translate("MainWindow", "Sense-able", 0));
        streamButton->setText(QApplication::translate("MainWindow", "Begin Stream", 0));
        readDataPageButton->setText(QApplication::translate("MainWindow", "Read Data ", 0));
        settingsPageButton->setText(QApplication::translate("MainWindow", "Settings", 0));
        QuitButton->setText(QApplication::translate("MainWindow", "Quit", 0));
        settingsLabel->setText(QApplication::translate("MainWindow", "Settings:", 0));
        label_25->setText(QApplication::translate("MainWindow", "Notification Type:", 0));
        speechCheckBox->setText(QApplication::translate("MainWindow", "Speech                        ", 0));
        beepCheckBox->setText(QApplication::translate("MainWindow", "Beep                            ", 0));
        label_26->setText(QApplication::translate("MainWindow", "Distance measured in:", 0));
        notificationsButton->setText(QApplication::translate("MainWindow", "Notifications", 0));
        label_9->setText(QApplication::translate("MainWindow", "Notification Distance", 0));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Metric ", 0)
         << QApplication::translate("MainWindow", "US customary systems", 0)
        );
        backButtonSettings->setText(QApplication::translate("MainWindow", "Back", 0));
        notifDistanceLabel->setText(QApplication::translate("MainWindow", "0", 0));
        notificationsTitle->setText(QApplication::translate("MainWindow", "Notifications:", 0));
        notificationLabel->setText(QApplication::translate("MainWindow", "Notification", 0));
        objectTypeLabel->setText(QApplication::translate("MainWindow", "Object Type", 0));
        label->setText(QApplication::translate("MainWindow", "1. Wall", 0));
        label_3->setText(QApplication::translate("MainWindow", "3. Pillar/Post ", 0));
        label_4->setText(QApplication::translate("MainWindow", "4. Trip Hazard", 0));
        label_7->setText(QApplication::translate("MainWindow", "7. N/A", 0));
        label_8->setText(QApplication::translate("MainWindow", "8. N/A", 0));
        label_5->setText(QApplication::translate("MainWindow", "5. Other Obstacles", 0));
        label_6->setText(QApplication::translate("MainWindow", "6. N/A", 0));
        obj1_notif_choice->clear();
        obj1_notif_choice->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1 Short Beep", 0)
         << QApplication::translate("MainWindow", "1 Long Beep", 0)
         << QApplication::translate("MainWindow", "1 Short, 1 Long", 0)
         << QApplication::translate("MainWindow", "1 Long, 1 Short", 0)
         << QApplication::translate("MainWindow", "2 Short Beeps", 0)
         << QApplication::translate("MainWindow", "2 Short, 1 Long", 0)
         << QApplication::translate("MainWindow", "1 Long, 2 Short", 0)
        );
        label_2->setText(QApplication::translate("MainWindow", "2. Wall - Corner", 0));
        obj2_notif_choice->clear();
        obj2_notif_choice->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1 Short Beep", 0)
         << QApplication::translate("MainWindow", "1 Long Beep", 0)
         << QApplication::translate("MainWindow", "1 Short, 1 Long", 0)
         << QApplication::translate("MainWindow", "1 Long, 1 Short", 0)
         << QApplication::translate("MainWindow", "2 Short Beeps", 0)
         << QApplication::translate("MainWindow", "2 Short, 1 Long", 0)
         << QApplication::translate("MainWindow", "1 Long, 2 Short", 0)
        );
        obj3_notif_choice->clear();
        obj3_notif_choice->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1 Short Beep", 0)
         << QApplication::translate("MainWindow", "1 Long Beep", 0)
         << QApplication::translate("MainWindow", "1 Short, 1 Long", 0)
         << QApplication::translate("MainWindow", "1 Long, 1 Short", 0)
         << QApplication::translate("MainWindow", "2 Short Beeps", 0)
         << QApplication::translate("MainWindow", "2 Short, 1 Long", 0)
         << QApplication::translate("MainWindow", "1 Long, 2 Short", 0)
        );
        obj4_notif_choice->clear();
        obj4_notif_choice->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1 Short Beep", 0)
         << QApplication::translate("MainWindow", "1 Long Beep", 0)
         << QApplication::translate("MainWindow", "1 Short, 1 Long", 0)
         << QApplication::translate("MainWindow", "1 Long, 1 Short", 0)
         << QApplication::translate("MainWindow", "2 Short Beeps", 0)
         << QApplication::translate("MainWindow", "2 Short, 1 Long", 0)
         << QApplication::translate("MainWindow", "1 Long, 2 Short", 0)
        );
        obj5_notif_choice->clear();
        obj5_notif_choice->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1 Short Beep", 0)
         << QApplication::translate("MainWindow", "1 Long Beep", 0)
         << QApplication::translate("MainWindow", "1 Short, 1 Long", 0)
         << QApplication::translate("MainWindow", "1 Long, 1 Short", 0)
         << QApplication::translate("MainWindow", "2 Short Beeps", 0)
         << QApplication::translate("MainWindow", "2 Short, 1 Long", 0)
         << QApplication::translate("MainWindow", "1 Long, 2 Short", 0)
        );
        obj6_notif_choice->clear();
        obj6_notif_choice->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1 Short Beep", 0)
         << QApplication::translate("MainWindow", "1 Long Beep", 0)
         << QApplication::translate("MainWindow", "1 Short, 1 Long", 0)
         << QApplication::translate("MainWindow", "1 Long, 1 Short", 0)
         << QApplication::translate("MainWindow", "2 Short Beeps", 0)
         << QApplication::translate("MainWindow", "2 Short, 1 Long", 0)
         << QApplication::translate("MainWindow", "1 Long, 2 Short", 0)
        );
        obj7_notif_choice->clear();
        obj7_notif_choice->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1 Short Beep", 0)
         << QApplication::translate("MainWindow", "1 Long Beep", 0)
         << QApplication::translate("MainWindow", "1 Short, 1 Long", 0)
         << QApplication::translate("MainWindow", "1 Long, 1 Short", 0)
         << QApplication::translate("MainWindow", "2 Short Beeps", 0)
         << QApplication::translate("MainWindow", "2 Short, 1 Long", 0)
         << QApplication::translate("MainWindow", "1 Long, 2 Short", 0)
        );
        obj8_notif_choice->clear();
        obj8_notif_choice->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "1 Short Beep", 0)
         << QApplication::translate("MainWindow", "1 Long Beep", 0)
         << QApplication::translate("MainWindow", "1 Short, 1 Long", 0)
         << QApplication::translate("MainWindow", "1 Long, 1 Short", 0)
         << QApplication::translate("MainWindow", "2 Short Beeps", 0)
         << QApplication::translate("MainWindow", "2 Short, 1 Long", 0)
         << QApplication::translate("MainWindow", "1 Long, 2 Short", 0)
        );
        backButton->setText(QApplication::translate("MainWindow", "Back", 0));
        readingDataLabel->setText(QApplication::translate("MainWindow", "Reading Data From a file:", 0));
        pt1->setText(QApplication::translate("MainWindow", "0", 0));
        pt3->setText(QApplication::translate("MainWindow", "0", 0));
        pt5->setText(QApplication::translate("MainWindow", "0", 0));
        pt6->setText(QApplication::translate("MainWindow", "0", 0));
        pt7->setText(QApplication::translate("MainWindow", "0", 0));
        pt8->setText(QApplication::translate("MainWindow", "0", 0));
        pt9->setText(QApplication::translate("MainWindow", "0", 0));
        pt10->setText(QApplication::translate("MainWindow", "0", 0));
        pt12->setText(QApplication::translate("MainWindow", "0", 0));
        pt11->setText(QApplication::translate("MainWindow", "0", 0));
        pointLabel->setText(QApplication::translate("MainWindow", "Pt 1", 0));
        pointLabel_2->setText(QApplication::translate("MainWindow", "Pt 2", 0));
        pointLabel_3->setText(QApplication::translate("MainWindow", "Pt 3", 0));
        pointLabel_4->setText(QApplication::translate("MainWindow", "Pt 4", 0));
        pointLabel_5->setText(QApplication::translate("MainWindow", "Pt 5", 0));
        pointLabel_9->setText(QApplication::translate("MainWindow", "Pt 9", 0));
        pointLabel_10->setText(QApplication::translate("MainWindow", "Pt10", 0));
        pointLabel_11->setText(QApplication::translate("MainWindow", "Pt11", 0));
        pointLabel_12->setText(QApplication::translate("MainWindow", "Pt12", 0));
        pointLabel_7->setText(QApplication::translate("MainWindow", "Pt 8", 0));
        pointLabel_8->setText(QApplication::translate("MainWindow", "Pt 7", 0));
        readDataButton->setText(QApplication::translate("MainWindow", "Read Data ", 0));
        backButtonRead->setText(QApplication::translate("MainWindow", "Back", 0));
        cancelButtonRead->setText(QApplication::translate("MainWindow", "Cancel", 0));
        pointLabel_13->setText(QApplication::translate("MainWindow", "Pt13", 0));
        pointLabel_14->setText(QApplication::translate("MainWindow", "Pt14", 0));
        pointLabel_15->setText(QApplication::translate("MainWindow", "Pt15", 0));
        pointLabel_16->setText(QApplication::translate("MainWindow", "Pt16", 0));
        pt13->setText(QApplication::translate("MainWindow", "0", 0));
        pt14->setText(QApplication::translate("MainWindow", "0", 0));
        pt15->setText(QApplication::translate("MainWindow", "0", 0));
        pt16->setText(QApplication::translate("MainWindow", "0", 0));
        pointLabel_6->setText(QApplication::translate("MainWindow", "Pt 6", 0));
        pt2->setText(QApplication::translate("MainWindow", "0", 0));
        pt4->setText(QApplication::translate("MainWindow", "0", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
