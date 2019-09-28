#include "mainwindow.h"

#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QDir>
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////// intro..? premise?

    this->resize(400, 200);

    // size policies
    QSizePolicy spGrow(QSizePolicy::Minimum, QSizePolicy::Minimum);

    // stack and main menu
    QStackedWidget *stack = new QStackedWidget(this);
    QWidget *mainPage = new QWidget(stack);
    QVBoxLayout *mainLayout = new QVBoxLayout(mainPage);

    // menu buttons
    QPushButton *navKey = new QPushButton("Generate Keys", mainPage);
    connect(navKey, &QPushButton::clicked, [stack] { stack->setCurrentIndex(1); });
    navKey->setSizePolicy(spGrow);
    QPushButton *navEncrypt = new QPushButton("Encrypt", mainPage);
    connect(navEncrypt, &QPushButton::clicked, [stack] { stack->setCurrentIndex(2); });
    navEncrypt->setSizePolicy(spGrow);
    QPushButton *navDecrypt = new QPushButton("Decrypt", mainPage);
    connect(navDecrypt, &QPushButton::clicked, [stack] { stack->setCurrentIndex(3); });
    navDecrypt->setSizePolicy(spGrow);

    // menu layout
    mainLayout->addWidget(navKey);
    mainLayout->addWidget(navEncrypt);
    mainLayout->addWidget(navDecrypt);


    // pages
    QWidget *keyPage = new QWidget(stack);
    QWidget *encryptPage = new QWidget(stack);
    QWidget *decryptPage = new QWidget(stack);

    stack->addWidget(mainPage);
    stack->addWidget(keyPage);
    stack->addWidget(encryptPage);
    stack->addWidget(decryptPage);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////// key page

    // main keyPage
    QGridLayout *keyLayout = new QGridLayout(keyPage);
    keyLayout->setMargin(20);
    keyLayout->setSpacing(10);

    // widgets
    QLabel *privateLabel = new QLabel("Private Key: ", keyPage);   // key labels
    QLabel *publicLabel = new QLabel("Public Key: ", keyPage);
    publicLabel->setAlignment(Qt::AlignTop);
    publicLabel->setMargin(5);
    privateLabel->setAlignment(Qt::AlignTop);
    privateLabel->setMargin(5);

    QTextEdit *privateField = new QTextEdit(keyPage);              // key fields
    QTextEdit *publicField = new QTextEdit(keyPage);
    privateField->setReadOnly(true);
    publicField->setReadOnly(true);

    QCheckBox *chooseDir = new QCheckBox("Choose Directory", keyPage);     // checkbox for manual directory
    chooseDir->setStyleSheet("margin-left:10%");
    QPushButton *generateBtn = new QPushButton("Generate Keys", keyPage);  // button for key generation
    connect(generateBtn, &QPushButton::clicked, [keyPage, chooseDir] {
        if (chooseDir->checkState())                                    // if checkbox checked, open dialog to select path
        {
            QFileDialog dialog(keyPage);
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

    QPushButton *back1 = new QPushButton("Back", keyPage);
    connect(back1, &QPushButton::clicked, [stack] { stack->setCurrentIndex(0); });

    // layout
    keyLayout->addWidget(privateLabel, 0, 0);
    keyLayout->addWidget(privateField, 0, 1, 1, 2);
    keyLayout->addWidget(publicLabel, 1, 0);
    keyLayout->addWidget(publicField, 1, 1, 1, 2);
    keyLayout->addWidget(generateBtn, 2, 1);
    keyLayout->addWidget(chooseDir, 2, 2);
    keyLayout->addWidget(back1, 3, 0, 1, 3);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////// encrypt page

    // main page
    QGridLayout *encryptLayout = new QGridLayout(encryptPage);
    encryptLayout->setMargin(20);
    encryptLayout->setSpacing(10);

    // widgets
    QTextEdit *plaintextField = new QTextEdit(encryptPage);    // field for plaintext input
    QTextEdit *ciphertextField = new QTextEdit(encryptPage);   // field for ciphertext output
    ciphertextField->setReadOnly(true);

    QString *key;
    QPushButton *keyBtn = new QPushButton("Open Key", encryptPage);        // button for getting key
    connect(keyBtn, &QPushButton::clicked, [encryptPage, keyBtn, &key] {
        QString filename = QFileDialog::getOpenFileName(encryptPage);      // dialog for key file
        QFile keyFile(filename);
        if (keyFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream qts(&keyFile);
            //qts >> *key;                                          // this breaks everything lol
            keyBtn->setText("Key Opened");
        }
    });
    QPushButton *encryptBtn = new QPushButton("Encrypt", encryptPage);     // button to encrypt plaintext
    connect(encryptBtn, &QPushButton::clicked, [] {
        // encryption algorithm
    });

    QPushButton *back2 = new QPushButton("Back", keyPage);
    connect(back2, &QPushButton::clicked, [stack] { stack->setCurrentIndex(0); });

    // layout
    encryptLayout->addWidget(keyBtn, 0, 0);
    encryptLayout->addWidget(plaintextField, 0, 1);
    encryptLayout->addWidget(encryptBtn, 1, 0);
    encryptLayout->addWidget(ciphertextField, 1, 1);
    encryptLayout->addWidget(back2, 2, 0, 1, 2);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////// decrypt page

    // main page
    QGridLayout *decryptLayout = new QGridLayout(decryptPage);
    decryptLayout->setMargin(20);
    decryptLayout->setSpacing(10);

    // widgets
    QTextEdit *ciphertextField2 = new QTextEdit(decryptPage);   // field for ciphertext input
    QTextEdit *plaintextField2 = new QTextEdit(decryptPage);    // field for plaintext output
    plaintextField2->setReadOnly(true);

    QString *key2;
    QPushButton *keyBtn2 = new QPushButton("Open Key", decryptPage);        // button for getting key
    connect(keyBtn2, &QPushButton::clicked, [decryptPage, keyBtn2, &key2] {
        QString filename = QFileDialog::getOpenFileName(decryptPage);      // dialog for key file
        QFile keyFile(filename);
        if (keyFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream qts(&keyFile);
            //qts >> *key2;                                          // this breaks everything lol
            keyBtn2->setText("Key Opened");
        }
    });
    QPushButton *decryptBtn = new QPushButton("Decrypt", decryptPage);     // button to decrypt ciphertext
    connect(decryptBtn, &QPushButton::clicked, [] {
        // decryption algorithm
    });

    QPushButton *back3 = new QPushButton("Back", keyPage);
    connect(back3, &QPushButton::clicked, [stack] { stack->setCurrentIndex(0); });

    // layout
    decryptLayout->addWidget(keyBtn2, 0, 0);
    decryptLayout->addWidget(plaintextField2, 0, 1);
    decryptLayout->addWidget(decryptBtn, 1, 0);
    decryptLayout->addWidget(ciphertextField2, 1, 1);
    decryptLayout->addWidget(back3, 2, 0, 1, 2);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////// credits

    stack->setCurrentIndex(0);
    this->setCentralWidget(stack);
    this->setWindowTitle("RSA Calculator");
}

MainWindow::~MainWindow()
{

}
