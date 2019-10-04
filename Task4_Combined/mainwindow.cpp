#include "mainwindow.h"

#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QDir>
#include <QFileDialog>
#include <QTextStream>

#include "rsa_codec.hpp"

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
    QLabel *privateLabel = new QLabel("Private Key: ", keyPage);    // key labels
    QLabel *publicLabel = new QLabel("Public Key: ", keyPage);
    publicLabel->setAlignment(Qt::AlignTop);
    publicLabel->setMargin(5);
    privateLabel->setAlignment(Qt::AlignTop);
    privateLabel->setMargin(5);

    QTextEdit *privateField = new QTextEdit(keyPage);               // key fields
    QTextEdit *publicField = new QTextEdit(keyPage);
    privateField->setReadOnly(true);
    publicField->setReadOnly(true);

    QCheckBox *chooseDir = new QCheckBox("Choose Directory", keyPage);      // checkbox for manual directory
    chooseDir->setStyleSheet("margin-left:10%");
    QPushButton *generateBtn = new QPushButton("Generate Keys", keyPage);   // button for key generation
    connect(generateBtn, &QPushButton::clicked, [keyPage, chooseDir] {
        if (chooseDir->checkState())                                        // if checkbox checked, open dialog to select path
        {
            QFileDialog dialog(keyPage);
            dialog.setFileMode(QFileDialog::Directory);
            dialog.setOption(QFileDialog::ShowDirsOnly);
            dialog.exec();
        }

        QString directory = QDir::currentPath();
        auto keys = rsa::genKeys(directory.toStdString());                                     // generate keys
        /*
        QFile privateFile("private.key");                               // file for private key
        privateFile.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream privateStream(&privateFile);                        // output key to file
        privateStream << keys.first.exponent;

        QFile publicFile("public.key");                                 // repeat for public key
        publicFile.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream publicStream(&publicFile);
        privateStream << keys.second.exponent;
        */
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

    QTextEdit *keyEdit = new QTextEdit(encryptPage);
    QTextEdit *keyMod = new QTextEdit(encryptPage);
    QPushButton *keyBtn = new QPushButton("Open Key", encryptPage);         // button for getting key
    keyBtn->setSizePolicy(spGrow);
    connect(keyBtn, &QPushButton::clicked, [encryptPage, keyBtn, keyEdit, keyMod] {
        QString filename = QFileDialog::getOpenFileName(encryptPage);       // dialog for key file
        QFile keyFile(filename);
        if (keyFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream qts(&keyFile);
            QString temp;
            qts >> temp;
            keyEdit->setText(temp);
            qts >> temp;
            keyMod->setText(temp);
            keyBtn->setText("Key Opened");
        }
    });

    QPushButton *encryptBtn = new QPushButton("Encrypt", encryptPage);      // button to encrypt plaintext
    encryptBtn->setSizePolicy(spGrow);
    connect(encryptBtn, &QPushButton::clicked, [plaintextField, keyEdit, keyMod, ciphertextField] {
        mp::mpz_int numMessage = rsa::stringToMpz_int(plaintextField->toPlainText().toStdString());
        rsa::Key tempKey{rsa::stringToMpz_int(keyEdit->toPlainText().toStdString()), rsa::stringToMpz_int(keyMod->toPlainText().toStdString())};
        auto decodedNumMessage = rsa::encryptOrDecrypt(numMessage, tempKey);
        ciphertextField->setText(QString::fromStdString(decodedNumMessage.convert_to<std::string>()));
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

    QTextEdit *keyEdit2 = new QTextEdit(decryptPage);
    QTextEdit *keyMod2 = new QTextEdit(decryptPage);
    QPushButton *keyBtn2 = new QPushButton("Open Key", decryptPage);        // button for getting key
    keyBtn2->setSizePolicy(spGrow);
    connect(keyBtn2, &QPushButton::clicked, [decryptPage, keyBtn2, keyEdit2, keyMod2] {
        QString filename = QFileDialog::getOpenFileName(decryptPage);       // dialog for key file
        QFile keyFile(filename);
        if (keyFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString temp;
            QTextStream qts(&keyFile);
            qts >> temp;
            keyEdit2->setText(temp);
            qts >> temp;
            keyMod2->setText(temp);
            keyBtn2->setText("Key Opened");
        }
    });

    QPushButton *decryptBtn = new QPushButton("Decrypt", decryptPage);     // button to decrypt ciphertext
    decryptBtn->setSizePolicy(spGrow);
    connect(decryptBtn, &QPushButton::clicked, [ciphertextField2, keyEdit2, keyMod2, plaintextField2] {
        mp::mpz_int numMessage = rsa::stringToMpz_int(ciphertextField2->toPlainText().toStdString());
        rsa::Key tempKey{rsa::stringToMpz_int(keyEdit2->toPlainText().toStdString()), rsa::stringToMpz_int(keyMod2->toPlainText().toStdString())};
        auto encodedNumMessage = rsa::encryptOrDecrypt(numMessage, tempKey);
        plaintextField2->setText(QString::fromStdString(encodedNumMessage.convert_to<std::string>()));
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
