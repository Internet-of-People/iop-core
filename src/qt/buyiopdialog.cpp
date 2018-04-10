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
#include <QDesktopServices>
#include <QObject>
#include <QUrl>
#include <iostream>

BuyIoPDialog::BuyIoPDialog(const PlatformStyle* _platformStyle, QWidget* parent) : QDialog(parent), model(0), platformStyle(_platformStyle)
{   

    slotblock = false;

    QLabel* buyIoPLabel = new QLabel("Buy IoP");
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(buyIoPLabel);

    // amount selection
    amountIoP = new IoPAmountField();
    amountIoP->setReadOnly(true);
    
    
    currency = new QComboBox(this);
    currency->addItem("Dollar");
    currency->addItem("Euro");
    currency->addItem("Rubel");

    paySpinBox = new QDoubleSpinBox;
    paySpinBox->setRange(50, 50000);
    paySpinBox->setDecimals(2);
    paySpinBox->setSingleStep(1);
    paySpinBox->setValue(MIN_PRICE[currency->currentIndex()]);

    QWidget* payAmount = new QWidget(this);
    QHBoxLayout* payLayout = new QHBoxLayout(payAmount);

    payLayout->setContentsMargins(3, 0, 3, 0);
    payLayout->setSpacing(3);
    payLayout->addWidget(paySpinBox);
    payLayout->addWidget(currency);
    payLayout->addWidget(amountIoP);

    layout->addWidget(payAmount);

    //adress selection
    adressLineEdit = new QLineEdit(this);
    adressLineEdit->setPlaceholderText("choose adress or paste your own");
    selectAdress = new QPushButton("choose");

    QWidget* addressWidget = new QWidget(this);
    QHBoxLayout* adressLayout = new QHBoxLayout(addressWidget);

    adressLayout->setContentsMargins(3, 0, 3, 0);
    adressLayout->setSpacing(3);
    adressLayout->addWidget(adressLineEdit);
    adressLayout->addWidget(selectAdress);

    layout->addWidget(addressWidget);

    buyButton = new QPushButton("buy");
    buyButton->setEnabled(false);
    layout->addWidget(buyButton);

    //network management
    iopPriceNAM = new QNetworkAccessManager();

    //SLOTS
    connect(currency, SIGNAL(currentIndexChanged(int)), this, SLOT(physicalUpdated(int)));
    std::cout << connect(adressLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(adressChanged(const QString &)))<< std::endl;
    connect(selectAdress, SIGNAL(clicked()), this, SLOT(chooseAdress()));
    connect(paySpinBox, SIGNAL(valueChanged(double)), this, SLOT(physicalUpdated(double)));
    connect(iopPriceNAM, SIGNAL(finished(QNetworkReply*)), this, SLOT(gotIoPPrice(QNetworkReply*)));
    connect(buyButton, SIGNAL(clicked()), this, SLOT(sendBuyRequest()));


    updateIoPPrice(paySpinBox->value());
}


void BuyIoPDialog::setModel(WalletModel* _model)
{
    this->model = _model;
}

void BuyIoPDialog::adressChanged(const QString &txt){
    //if(valid(adressLineEdit->getText())
    buyButton->setEnabled(true);
    std::cout<<"buybutton enabled"<<std::endl;
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

void BuyIoPDialog::physicalUpdated(int i)
{
    BuyIoPDialog::physicalUpdated(paySpinBox->value());
}

void BuyIoPDialog::physicalUpdated(double i)
{
    std::cout << i << "$\n";
    if(i > MIN_PRICE[currency->currentIndex()] && i < MAX_PRICE[currency->currentIndex()])
        updateIoPPrice(i);
    else{
        if(i <= MIN_PRICE[currency->currentIndex()])
            paySpinBox->setValue(MIN_PRICE[currency->currentIndex()]);
        if(i >= MAX_PRICE[currency->currentIndex()])
            paySpinBox->setValue(MAX_PRICE[currency->currentIndex()]);
    }
}

void BuyIoPDialog::updateIoPPrice(double amount)
{
    responsed = false;
    QNetworkRequest request(QUrl(QString(GET_PRICE).append(CURRENCY[currency->currentIndex()]).append(SEPERATOR).append(IOP_CURRENCY).append(SEPERATOR).append(QString::number(amount).append(SEPERATOR))));
    std::cout << "iop price: " << request.url().toString().toStdString() << std::endl;
    iopPriceNAM->get(request);
}

void BuyIoPDialog::sendBuyRequest(){
    QString adress = QString(BUY_URL).append(PARTNER_NAME).append(WITH_CARD).append(CURRENCY[currency->currentIndex()]).append(AMOUNT_PAY).append(QString::number(paySpinBox->value()).append(WALLET).append(adressLineEdit->text()).append(DISCOUNT));
    std::cout << "buy url: " << adress.toStdString() << std::endl;

    QDesktopServices::openUrl(QUrl(adress,QUrl::TolerantMode));
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
    amountIoP->setValue(iopPrice* 100000000);
    responsed = true;
    return;
}


BuyIoPDialog::~BuyIoPDialog()
{
}
