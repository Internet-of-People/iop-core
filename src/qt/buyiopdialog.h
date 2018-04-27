// Copyright (c) 2011-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef IOP_QT_BUYIOPDIALOG_H
#define IOP_QT_BUYIOPDIALOG_H

#include "iopamountfield.h"
#include "walletmodel.h"

#include <QComboBox>
#include <QDialog>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPushButton>
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
    void adressChanged(const QString& txt);
    void chooseAdress();
    void physicalUpdated(int i);
    void physicalUpdated(double i);
    void gotIoPPrice(QNetworkReply* r);
    void sendBuyRequest();

public:
    const PlatformStyle* platformStyle;
    WalletModel* model;
    QPushButton* selectAdress;
    QPushButton* buyButton;
    QLineEdit* adressLineEdit;
    QLineEdit* mailEdit;
    QDoubleSpinBox* paySpinBox;
    QComboBox* currency;
    QLabel* amountIOP;
    QLabel* IOPLabel;
    QNetworkAccessManager* iopPriceNAM;


private:
    bool slotblock;
    bool responsed;

    const int DOLLAR = 0;
    const int EURO = 1;
    const int RUBEL = 2;


    const int MAX_PRICE[3] = {1000, 1000, 50000};
    const int MIN_PRICE[3] = {50, 50, 2000};

    const int FACTOR_IOP = 100000000;

    const QString CURRENCY[3] = {QString("USD"), QString("EUR"), QString("RUB")};

    const QString PARTNER_NAME = QString("iopglobal");

    const QString IOP_CURRENCY = QString("IOP");

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
    const QString CREATE_TRANSACTION = QString("https://indacoin.com/gw/payment_form?partner=");


    const QString BUY_URL = QString("https://indacoin.com/gw/payment_form?partner=");

    const QString CUR_FROM = QString("&cur_from=");

    const QString CUR_TO = QString("&cur_to=");

    const QString AMOUNT = QString("&amount=");

    const QString ADDRESS = QString("&address=");

    const QString DISCOUNT = QString("&discount=82446");

    const QString USER_ID = QString("&user_id=test@web.de");


    double iopPrice;

    void updateIoPPrice(double amount);
};

#endif // IOP_QT_BUYIOPDIALOG_H
