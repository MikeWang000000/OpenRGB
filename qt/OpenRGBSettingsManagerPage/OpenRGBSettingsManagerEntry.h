#ifndef OPENRGBSETTINGSMANAGERENTRY_H
#define OPENRGBSETTINGSMANAGERENTRY_H

#include "ui_OpenRGBSettingsManagerEntry.h"
#include <QWidget>
#include "ResourceManager.h"

namespace Ui {
class OpenRGBSettingsManagerEntry;
}

class Ui::OpenRGBSettingsManagerEntry : public QWidget
{
    Q_OBJECT

public:
    explicit OpenRGBSettingsManagerEntry(std::string settings_key, json settings_data, QWidget *parent = nullptr);
    ~OpenRGBSettingsManagerEntry();
    Ui::OpenRGBSettingsManagerEntryUi *ui;

private slots:
    void changeEvent(QEvent *event);

private:
    std::string key;
    json        data;
};

#endif // OPENRGBSETTINGSMANAGERENTRY_H
