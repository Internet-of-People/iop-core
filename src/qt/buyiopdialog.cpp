// Copyright (c) 2011-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "buyiopdialog.h"

#include "addressbookpage.h"

#include <chrono>
#include <thread>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QNetworkRequest>
#include <QObject>
#include <QUrl>
#include <iostream>

BuyIoPDialog::BuyIoPDialog(const PlatformStyle* _platformStyle, QWidget* parent) : QDialog(parent), model(0), platformStyle(_platformStyle)
{
    QLabel* buyIoPLabel = new QLabel("Buy IoP");
    amountIoP = new IoPAmountField();
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(buyIoPLabel);
    layout->addWidget(amountIoP);
    paySpinBox = new QDoubleSpinBox;
    paySpinBox->setRange(50, 50000);
    paySpinBox->setDecimals(2);
    paySpinBox->setSingleStep(.01);
    paySpinBox->setValue(50);
    currency = new QComboBox(this);
    currency->addItem("Dollar");
    currency->addItem("Euro");
    currency->addItem("Rubel");
    QWidget* payAmount = new QWidget(this);

    QHBoxLayout* payLayout = new QHBoxLayout(payAmount);
    payLayout->setContentsMargins(3, 0, 3, 0);
    payLayout->setSpacing(3);
    payLayout->addWidget(paySpinBox);
    payLayout->addWidget(currency);
    layout->addWidget(payAmount);
    slotblock = false;

    adressLineEdit = new QLineEdit("choose adress or paste your own", this);
    selectAdress = new QPushButton("choose");

    QWidget* addressWidget = new QWidget(this);
    QHBoxLayout* adressLayout = new QHBoxLayout(addressWidget);
    adressLayout->setContentsMargins(3, 0, 3, 0);
    adressLayout->setSpacing(3);
    adressLayout->addWidget(adressLineEdit);
    adressLayout->addWidget(selectAdress);
    layout->addWidget(addressWidget);
    iopPriceNAM = new QNetworkAccessManager();

    connect(selectAdress, SIGNAL(clicked()), this, SLOT(chooseAdress()));
    connect(amountIoP, SIGNAL(valueChanged()), this, SLOT(iopUpdated()));
    connect(paySpinBox, SIGNAL(valueChanged(double)), this, SLOT(physicalUpdated(double)));

    std::cout << "pricecheck: " << connect(iopPriceNAM, SIGNAL(finished(QNetworkReply*)), this, SLOT(gotIoPPrice(QNetworkReply*))) << std::endl;

    //setStyleSheet(" background: rgb(255,0,0)");
}


void BuyIoPDialog::setModel(WalletModel* _model)
{
    this->model = _model;
}

void BuyIoPDialog::chooseAdress()
{
    if (model) {
        AddressBookPage dlg(platformStyle, AddressBookPage::ForSelection, AddressBookPage::ReceivingTab, this);
        dlg.setModel(model->getAddressTableModel());
        if (dlg.exec()) {
            adressLineEdit->setText(dlg.getReturnValue());
        }
    }
}

void BuyIoPDialog::iopUpdated()
{
    if (!slotblock) {
        slotblock = true;
        std::cout << amountIoP->value() << "IoP\n";
        paySpinBox->setValue(getPhysicalPrice(amountIoP->value() * 0.00000001));
        slotblock = false;
    }
}

void BuyIoPDialog::physicalUpdated(double i)
{
    if (!slotblock) {
        slotblock = true;

        std::cout << i << "$\n";
        amountIoP->setValue(getIoPPrice(i) * 100000000);
        slotblock = false;
    }
}

double BuyIoPDialog::getIoPPrice(double amount)
{
    responsed = false;
    QNetworkRequest request(QUrl(QString(GET_PRICE).append(CURRENCY[currency->currentIndex()]).append(SEPERATOR).append(PARTNER_NAME).append(SEPERATOR).append(QString::number(amount).append(SEPERATOR).append(PARTNER_NAME))));
    std::cout << "iop price: " << request.url().toString().toStdString() << std::endl;
    iopPriceNAM->get(request);
    waitForResponse();
    return iopPrice;
}

double BuyIoPDialog::getPhysicalPrice(double amount)
{
    responsed = false;
    int maxbuy = MAX_PRICE[currency->currentIndex()];
    QNetworkRequest request(QUrl(QString(GET_PRICE).append(CURRENCY[currency->currentIndex()]).append(SEPERATOR).append(PARTNER_NAME).append(SEPERATOR).append(QString::number(maxbuy).append(SEPERATOR).append(PARTNER_NAME))));
    std::cout << "phys maxbuy price: " << request.url().toString().toStdString() << std::endl;
    
    iopPriceNAM->get(request);
    waitForResponse();

    iopPrice = maxbuy/iopPrice *amount;
    std::cout << amount << "iop cost" << iopPrice << "( " << amount << " )" << std::endl; 
    return iopPrice;
}

void BuyIoPDialog::waitForResponse()
{
    //while (!responsed) {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    //}
}

void BuyIoPDialog::gotIoPPrice(QNetworkReply* reply)
{   
    if (reply->error()) {
        std::cout << "ERROR! " << reply->errorString().toStdString() << std::endl; //Error handling
        responsed = true;
        return;
    }
    QString answer = reply->readAll();
    bool successfullParsed;
    iopPrice = answer.toDouble(&successfullParsed);
    std::cout << "GOT PRICE: " << answer.toStdString() << std::endl;

    responsed = true;
    return;
}


BuyIoPDialog::~BuyIoPDialog()
{
}
