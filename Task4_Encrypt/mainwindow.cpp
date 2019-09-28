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
    QTextEdit *plaintextField = new QTextEdit(page);    // field for plaintext input
    QTextEdit *ciphertextField = new QTextEdit(page);   // field for ciphertext output
    ciphertextField->setReadOnly(true);

    QString *key;
    QPushButton *keyBtn = new QPushButton("Open Key", page);        // button for getting key
    connect(keyBtn, &QPushButton::clicked, [page, keyBtn, &key] {
        QString filename = QFileDialog::getOpenFileName(page);      // dialog for key file
        QFile keyFile(filename);
        if (keyFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream qts(&keyFile);
            //qts >> *key;                                          // this breaks everything lol
            keyBtn->setText("Key Opened");
        }
    });
    QPushButton *encryptBtn = new QPushButton("Encrypt", page);     // button to encrypt plaintext
    connect(encryptBtn, &QPushButton::clicked, [] {
        // encryption algorithm
    });

    // layout
    layout->addWidget(keyBtn, 0, 0);
    layout->addWidget(plaintextField, 0, 1);
    layout->addWidget(encryptBtn, 1, 0);
    layout->addWidget(ciphertextField, 1, 1);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////// credits

    this->setCentralWidget(page);
    this->setWindowTitle("Key Generation");
}

MainWindow::~MainWindow()
{

}
