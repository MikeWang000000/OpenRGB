#include "OpenRGBSettingsManagerEntry.h"
#include "ui_OpenRGBSettingsManagerEntry.h"
#include <QLabel>
#include <QVBoxLayout>

using namespace Ui;

OpenRGBSettingsManagerEntry::OpenRGBSettingsManagerEntry(std::string settings_key, json settings_data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpenRGBSettingsManagerEntryUi)
{
    key = settings_key;
    data = settings_data;

    ui->setupUi(this);

    ui->SettingsGroupBox->setTitle(QString::fromStdString(key));

    QVBoxLayout layout;
    ui->SettingsGroupBox->setLayout(&layout);

    QLabel new_label;

    new_label.setText("test 123");

    layout.addWidget(&new_label);
}

OpenRGBSettingsManagerEntry::~OpenRGBSettingsManagerEntry()
{
    delete ui;
}

void OpenRGBSettingsManagerEntry::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}
