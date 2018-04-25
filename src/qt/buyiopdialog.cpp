// Copyright (c) 2011-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "buyiopdialog.h"

#include "addressbookpage.h"

#include <chrono>
#include <thread>

#include <QDesktopServices>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QNetworkRequest>
#include <QObject>
#include <QSizePolicy>
#include <QUrl>
#include <iostream>

BuyIoPDialog::BuyIoPDialog(const PlatformStyle* _platformStyle, QWidget* parent) : QDialog(parent), model(0), platformStyle(_platformStyle)
{
    slotblock = false;

    QLabel* buyIoPLabel = new QLabel("Buy IoP");
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(buyIoPLabel);

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

    QLabel* adressInfoLabel = new QLabel(tr("exchange service provided by indacoin.com"));
    QLabel* amountInfoLabel = new QLabel(tr("minimum exchange value: "));

    layout->addWidget(adressInfoLabel);
    layout->addSpacing(20);

    // amount selection
    amountIOP = new QLabel();
    amountIOP->setMaximumWidth(350);
    amountIOP->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    amountIOP->setObjectName("buy_amountIOP");

    IOPLabel = new QLabel("IOP");
    IOPLabel->setObjectName("buy_IOPLabel");

    //amountIOP->setReadOnly(true);

    currency = new QComboBox(this);
    currency->addItem("USD");
    currency->addItem("EUR");
    currency->addItem("RUB");
    currency->setObjectName("buy_currency");
    currency->setMaximumWidth(250);
    paySpinBox = new QDoubleSpinBox;
    paySpinBox->setRange(50, 50000);
    paySpinBox->setDecimals(2);
    paySpinBox->setSingleStep(1);
    paySpinBox->setValue(MIN_PRICE[currency->currentIndex()]);
    paySpinBox->setMaximumWidth(350);
    paySpinBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout* fiatLayout = new QHBoxLayout();
    fiatLayout->addWidget(paySpinBox);
    fiatLayout->addWidget(currency);
    fiatLayout->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout* iopLayout = new QHBoxLayout();
    iopLayout->addWidget(amountIOP);
    iopLayout->addWidget(IOPLabel);
    iopLayout->setContentsMargins(0, 0, 0, 0);

    buyButton = new QPushButton("buy");
    buyButton->setObjectName("buyButton");
    buyButton->setEnabled(false);

    QWidget* bottomWidget = new QWidget(this);
    QGridLayout* bottomLayout = new QGridLayout(bottomWidget);

    QWidget* buttonWidget = new QWidget(bottomWidget);
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonWidget);

    buttonLayout->addWidget(buyButton);
    QWidget* payAmount = new QWidget(bottomWidget);
    QVBoxLayout* payLayout = new QVBoxLayout(payAmount);

    payLayout->setContentsMargins(3, 0, 3, 0);
    payLayout->setSpacing(3);


    payLayout->addLayout(fiatLayout);
    payLayout->addWidget(amountInfoLabel);
    payLayout->addSpacing(25);

    payLayout->addLayout(iopLayout);

    bottomLayout->addWidget(payAmount, 0, 0, Qt::AlignLeft);
    bottomLayout->addWidget(buttonWidget, 0, 1, Qt::AlignBottom | Qt::AlignRight);

    layout->addWidget(bottomWidget);


    //network management
    iopPriceNAM = new QNetworkAccessManager();

    //SLOTS
    connect(currency, SIGNAL(currentIndexChanged(int)), this, SLOT(physicalUpdated(int)));
    std::cout << connect(adressLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(adressChanged(const QString&))) << std::endl;
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

void BuyIoPDialog::adressChanged(const QString& txt)
{
    if (adressLineEdit->text().isEmpty() || model->validateAddress(adressLineEdit->text())) {
        buyButton->setEnabled(true);
        adressLineEdit->setStyleSheet("");
        std::cout << "buybutton enabled" << std::endl;
    } else {
        buyButton->setEnabled(false);
        //adressLineEdit->setValid(false);
        adressLineEdit->setStyleSheet("background: rgb(155,0,0);");

        std::cout << "buybutton enabled" << std::endl;
    }
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
    if (i > MIN_PRICE[currency->currentIndex()] && i < MAX_PRICE[currency->currentIndex()])
        updateIoPPrice(i);
    else {
        if (i <= MIN_PRICE[currency->currentIndex()])
            paySpinBox->setValue(MIN_PRICE[currency->currentIndex()]);
        if (i >= MAX_PRICE[currency->currentIndex()])
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

void BuyIoPDialog::sendBuyRequest()
{
    QString adress = QString(BUY_URL).append(PARTNER_NAME).append(CUR_FROM).append(CURRENCY[currency->currentIndex()]).append(CUR_TO).append(IOP_CURRENCY).append(AMOUNT).append(QString::number(paySpinBox->value()).append(ADDRESS).append(adressLineEdit->text()).append(USER_ID));
    std::cout << "buy url: " << adress.toStdString() << std::endl;

    QDesktopServices::openUrl(QUrl(adress, QUrl::TolerantMode));
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
    amountIOP->setText(QString::number(iopPrice));
    responsed = true;
    return;
}


BuyIoPDialog::~BuyIoPDialog()
{
}
