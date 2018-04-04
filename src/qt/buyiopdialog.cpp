// Copyright (c) 2011-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "buyiopdialog.h"

#include "addressbookpage.h"


#include <QGridLayout>
#include <QObject>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QHBoxLayout>
#include <iostream>

BuyIoPDialog::BuyIoPDialog(const PlatformStyle* _platformStyle, QWidget* parent ) : QDialog(parent),  model(0),platformStyle(_platformStyle)
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
    QComboBox* currency = new QComboBox(this);
    currency->addItem("Dollar");
    currency->addItem("Euro");
    currency->addItem("Rubel");
    QWidget *payAmount = new QWidget(this);

    QHBoxLayout *payLayout = new QHBoxLayout(payAmount);
    payLayout->setContentsMargins(3,0,3,0);
    payLayout->setSpacing(3);
    payLayout->addWidget(paySpinBox);
    payLayout->addWidget(currency);
    layout->addWidget(payAmount);


    adressLineEdit = new QLineEdit("choose adress or paste your own",this);
    selectAdress = new QPushButton("choose");

    QWidget *addressWidget = new QWidget(this);
    QHBoxLayout *adressLayout = new QHBoxLayout(addressWidget);
    adressLayout->setContentsMargins(3,0,3,0);
    adressLayout->setSpacing(3);
    adressLayout->addWidget(adressLineEdit);
    adressLayout->addWidget(selectAdress);
    layout->addWidget(addressWidget);
    
    connect(selectAdress,SIGNAL(clicked()),this,SLOT(chooseAdress()));
    std::cout << connect(amountIoP, SIGNAL(valueChanged()), this, SLOT(updatePhysical())) << std::endl;
    std::cout << connect(paySpinBox, SIGNAL(valueChanged(double)), this, SLOT(updateIoP(double))) << std::endl;
    //setStyleSheet(" background: rgb(255,0,0)");
}

void BuyIoPDialog::setModel(WalletModel *_model)
{
    this->model = _model;
}

void BuyIoPDialog::chooseAdress() {
    if(model){
    AddressBookPage dlg(platformStyle, AddressBookPage::ForSelection, AddressBookPage::ReceivingTab, this);
        dlg.setModel(model->getAddressTableModel());
        if (dlg.exec())
        {
            adressLineEdit->setText(dlg.getReturnValue());
        }
    }
}

void BuyIoPDialog::updatePhysical() {
    if(!slotblock){
        slotblock = true;
        paySpinBox->setValue(amountIoP->value());
        slotblock = false;
    }
}

void BuyIoPDialog::updateIoP(double i) {
    if(!slotblock){
        slotblock = true;
        amountIoP->setValue(i*0.5);
        slotblock = false;
    }
}

BuyIoPDialog::~BuyIoPDialog()
{
}
