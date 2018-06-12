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

    QVBoxLayout* layout = new QVBoxLayout(this);

    // ADRESS SELECTION
    adressLineEdit = new QLineEdit(this);
    adressLineEdit->setPlaceholderText(tr("choose adress or paste your own"));
    selectAdress = new QPushButton(tr("choose"));

    mailEdit = new QLineEdit(this);
    mailEdit->setPlaceholderText(tr("your email adress"));

    QLabel* adressInfoLabel = new QLabel(tr("exchange service provided by indacoin.com"));
    adressInfoLabel->setObjectName("buy_adressInfo");

    QWidget* addressWidget = new QWidget(this);
    QVBoxLayout* topLayout = new QVBoxLayout(addressWidget);
    QHBoxLayout* adressLayout = new QHBoxLayout();
    QHBoxLayout* mailLayout = new QHBoxLayout();

    adressLayout->setContentsMargins(3, 0, 3, 0);
    adressLayout->setSpacing(3);
    adressLayout->addWidget(adressLineEdit);
    adressLayout->addWidget(selectAdress);
    mailLayout->addWidget(mailEdit);

    topLayout->addLayout(adressLayout);
    topLayout->addSpacing(20);
    topLayout->addLayout(mailLayout);
    topLayout->addSpacing(5);
    topLayout->addWidget(adressInfoLabel);

    layout->addWidget(addressWidget);

    layout->addSpacing(30);

    // AMOUNT SELECTION
    QLabel* amountInfoLabel = new QLabel(tr("minimum exchange value"));
    QLabel* amountVaryInfoLabel = new QLabel(tr("the amount may vary"));
    amountInfoLabel->setObjectName("buy_amountInfo");
    amountVaryInfoLabel->setObjectName("buy_amountVaryInfo");


    amountIOP = new QLabel();
    amountIOP->setMaximumWidth(350);
    amountIOP->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
    amountIOP->setObjectName("buy_amountIOP");

    IOPLabel = new QLabel("IOP");
    IOPLabel->setObjectName("buy_IOPLabel");
    //IOPLabel->setMaximumWidth(500);

    currency = new QComboBox(this);
    currency->addItem("USD");
    currency->addItem("EUR");
    currency->addItem("RUB");
    currency->setObjectName("buy_currency");
    //currency->setMaximumWidth(500);

    paySpinBox = new QDoubleSpinBox();
    paySpinBox->setObjectName("pay_spinbox");
    paySpinBox->setRange(50, 50000);
    paySpinBox->setDecimals(2);
    paySpinBox->setSingleStep(1);
    paySpinBox->setValue(MIN_PRICE[currency->currentIndex()]);
    //paySpinBox->setMaximumWidth(350);
    paySpinBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);

    buyButton = new QPushButton(tr("buy"));
    buyButton->setObjectName("buyButton");
    buyButton->setEnabled(false);

    QWidget* bottomWidget = new QWidget(this);
    QGridLayout* bottomLayout = new QGridLayout(bottomWidget);

    QWidget* buttonWidget = new QWidget(bottomWidget);
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonWidget);

    buttonLayout->addWidget(buyButton);

    QWidget* payAmount = new QWidget(bottomWidget);
    QGridLayout* payLayout = new QGridLayout(payAmount);
    payLayout->setHorizontalSpacing(10);
    payLayout->setVerticalSpacing(5);
    payLayout->setRowMinimumHeight(2,10);
    payLayout->setColumnMinimumWidth(0,100);

    payLayout->addWidget(paySpinBox,0,0);
    payLayout->addWidget(currency,0,1);
    payLayout->addWidget(amountInfoLabel,1,0,1,2);

    payLayout->addWidget(amountIOP,3,0);
    payLayout->addWidget(IOPLabel,3,1);
    payLayout->addWidget(amountVaryInfoLabel,4,0,2,1);

    bottomLayout->addWidget(payAmount, 0, 0, Qt::AlignLeft);
    bottomLayout->addWidget(buttonWidget, 0, 1, Qt::AlignBottom | Qt::AlignRight);

    layout->addWidget(bottomWidget);
    
    
    
    QFrame* lineb1 = new QFrame(this);
    lineb1->setObjectName(QStringLiteral("lineb1"));
    lineb1->setFrameShape(QFrame::HLine);
    lineb1->setFrameShadow(QFrame::Sunken);
    layout->addWidget(lineb1);

    layout->addSpacing(20);

    //network management
    iopPriceNAM = new QNetworkAccessManager();

    //SLOTS
    connect(currency, SIGNAL(currentIndexChanged(int)), this, SLOT(physicalUpdated(int)));
    connect(adressLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(adressChanged(const QString&)));
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
        //std::cout << "buybutton enabled" << std::endl;
    } else {
        buyButton->setEnabled(false);
        //adressLineEdit->setValid(false);
        adressLineEdit->setStyleSheet("background: rgb(155,0,0);");

        //std::cout << "buybutton enabled" << std::endl;
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
    //std::cout << "iop price: " << request.url().toString().toStdString() << std::endl;
    iopPriceNAM->get(request);
}

void BuyIoPDialog::sendBuyRequest()
{
    QString adress = QString(BUY_URL).append(PARTNER_NAME).append(CUR_FROM).append(CURRENCY[currency->currentIndex()]).append(CUR_TO).append(IOP_CURRENCY).append(AMOUNT).append(QString::number(paySpinBox->value()).append(ADDRESS).append(adressLineEdit->text()).append(USER_ID).append(mailEdit->text().replace('@',"%40",Qt::CaseInsensitive)));
    //std::cout << "buy url: " << adress.toStdString() << std::endl;

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
    //std::cout << "GOT PRICE: " << answer.toStdString() << std::endl;
    amountIOP->setText(QString::number(iopPrice));
    responsed = true;
    return;
}

BuyIoPDialog::~BuyIoPDialog()
{
}
