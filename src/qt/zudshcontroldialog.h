// Copyright (c) 2017-2018 The PIVX developers
// Copyright (c) 2019 The Ultradash developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZUDSHCONTROLDIALOG_H
#define ZUDSHCONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "zudsh/zerocoin.h"
#include "privacydialog.h"

class CZerocoinMint;
class WalletModel;

namespace Ui {
class ZUdshControlDialog;
}

class CZUdshControlWidgetItem : public QTreeWidgetItem
{
public:
    explicit CZUdshControlWidgetItem(QTreeWidget *parent, int type = Type) : QTreeWidgetItem(parent, type) {}
    explicit CZUdshControlWidgetItem(int type = Type) : QTreeWidgetItem(type) {}
    explicit CZUdshControlWidgetItem(QTreeWidgetItem *parent, int type = Type) : QTreeWidgetItem(parent, type) {}

    bool operator<(const QTreeWidgetItem &other) const;
};

class ZUdshControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZUdshControlDialog(QWidget *parent);
    ~ZUdshControlDialog();

    void setModel(WalletModel* model);

    static std::set<std::string> setSelectedMints;
    static std::set<CMintMeta> setMints;
    static std::vector<CMintMeta> GetSelectedMints();

private:
    Ui::ZUdshControlDialog *ui;
    WalletModel* model;
    PrivacyDialog* privacyDialog;

    void updateList();
    void updateLabels();

    enum {
        COLUMN_CHECKBOX,
        COLUMN_DENOMINATION,
        COLUMN_PUBCOIN,
        COLUMN_VERSION,
        COLUMN_PRECOMPUTE,
        COLUMN_CONFIRMATIONS,
        COLUMN_ISSPENDABLE
    };
    friend class CZUdshControlWidgetItem;

private slots:
    void updateSelection(QTreeWidgetItem* item, int column);
    void ButtonAllClicked();
};

#endif // ZUDSHCONTROLDIALOG_H
