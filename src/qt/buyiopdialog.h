// Copyright (c) 2011-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef IOP_QT_BUYIOPDIALOG_H
#define IOP_QT_BUYIOPDIALOG_H

#include "iopamountfield.h"
#include "walletmodel.h"

#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>


class PlatformStyle;

/** Dialog for sending iops */
class BuyIoPDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BuyIoPDialog(const PlatformStyle* platformStyle, QWidget* parent = 0);

    ~BuyIoPDialog();
    void setModel(WalletModel* model);

public Q_SLOTS:
    //void managerFinished();
    void chooseAdress();
    void iopUpdated();
    void physicalUpdated(double i);
    void gotIoPPrice(QNetworkReply* r);


public:
    const PlatformStyle* platformStyle;
    WalletModel* model;
    QPushButton* selectAdress;
    QLineEdit* adressLineEdit;
    QDoubleSpinBox* paySpinBox;
    QComboBox* currency;
    IoPAmountField* amountIoP;

    QNetworkAccessManager* iopPriceNAM;


private:
    bool slotblock;
    bool responsed;

    const int DOLLAR = 0;
    const int EURO = 1;
    const int RUBEL = 2;


    const int MAX_PRICE[3] = {1000,1000,50000};
    const int MIN_PRICE[3] = {50,50,2000};

    const int FACTOR_IOP = 100000000;

    const QString CURRENCY[3] = {QString("USD"), QString("EUR"), QString("RUB")};

    const QString PARTNER_NAME = QString("iop");

    const QString SEPERATOR = QString("/");

    //GET https://indacoin.com/api/GetCoinConvertAmount/{currencyFrom}/{currencyTo}/{amount:decimal}/{partner?}/{userId?}
    const QString GET_PRICE = QString("https://indacoin.com/api/GetCoinConvertAmount/");

    //POST https://indacoin.com/api/exgw_getUserlimits
    const QString USER_LIMITS = QString("https://indacoin.com/api/exgw_getUserlimits");

    //POST https://indacoin.com/api/exgw_getTransactions
    const QString TRANSACTIONS = QString("https://indacoin.com/api/exgw_getTransactions");

    //POST https://indacoin.com/api/exgw_gettransactioninfo
    const QString TRANSACTION_INFO = QString("https://indacoin.com/api/exgw_gettransactioninfo");

    //POST https://indacoin.com/api/exgw_createTransaction
    const QString CREATE_TRANSACTION = QString("https://indacoin.com/api/exgw_createTransaction");

    double iopPrice;

    double getIoPPrice(double amount);
    double getPhysicalPrice(double amount);
    void waitForResponse();
};

#endif // IOP_QT_BUYIOPDIALOG_H
