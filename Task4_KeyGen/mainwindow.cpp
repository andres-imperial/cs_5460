#include "mainwindow.h"

#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QDir>
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(400, 200);

    // size policies
    //QSizePolicy spGrow(QSizePolicy::Minimum, QSizePolicy::Minimum);

    // main page
    QWidget *page = new QWidget(this);
    QGridLayout *layout = new QGridLayout(page);
    layout->setMargin(20);
    layout->setSpacing(10);

    // widgets
    QLabel *privateLabel = new QLabel("Private Key: ", page);   // key labels
    QLabel *publicLabel = new QLabel("Public Key: ", page);
    publicLabel->setAlignment(Qt::AlignTop);
    publicLabel->setMargin(5);
    privateLabel->setAlignment(Qt::AlignTop);
    privateLabel->setMargin(5);

    QTextEdit *privateField = new QTextEdit(page);              // key fields
    QTextEdit *publicField = new QTextEdit(page);
    privateField->setReadOnly(true);
    publicField->setReadOnly(true);

    QCheckBox *chooseDir = new QCheckBox("Choose Directory", page);     // checkbox for manual directory
    chooseDir->setStyleSheet("margin-left:10%");
    QPushButton *generateBtn = new QPushButton("Generate Keys", page);  // button for key generation
    connect(generateBtn, &QPushButton::clicked, [page, chooseDir] {
        if (chooseDir->checkState())                                    // if checkbox checked, open dialog to select path
        {
            QFileDialog dialog(page);
            dialog.setFileMode(QFileDialog::Directory);
            dialog.setOption(QFileDialog::ShowDirsOnly);
            dialog.exec();
        }

        QFile privateFile("private.key");                               // files for keys
        privateFile.open(QIODevice::WriteOnly | QIODevice::Text);
        QFile publicFile("public.key");
        publicFile.open(QIODevice::WriteOnly | QIODevice::Text);

        QString privateKey, publicKey;

        // create keys here

        QTextStream privateStream(&privateFile);                        // output keys to files
        privateStream << privateKey;
        QTextStream publicStream(&publicFile);
        privateStream << publicKey;
    });

    // layout
    layout->addWidget(privateLabel, 0, 0);
    layout->addWidget(privateField, 0, 1, 1, 2);
    layout->addWidget(publicLabel, 1, 0);
    layout->addWidget(publicField, 1, 1, 1, 2);
    layout->addWidget(generateBtn, 2, 1);
    layout->addWidget(chooseDir, 2, 2);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////// credits

    this->setCentralWidget(page);
    this->setWindowTitle("Key Generation");
}

MainWindow::~MainWindow()
{

}
