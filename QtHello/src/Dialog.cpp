#include "Dialog.hpp"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCoreApplication>

Dialog::Dialog(QWidget* parent)
    : QDialog(parent)
{
    setupUi();
    connectSignals();
}

void Dialog::setupUi()
{
    setWindowTitle(QCoreApplication::translate("Messages", "Action"));

    auto* label = new QLabel("Você está prestes a encerrar o programa, o que deseja?", this);
    auto* buttonA = new QPushButton("Salvar e Sair", this);
    auto* buttonB = new QPushButton("Sair sem salvar", this);
    auto* buttonC = new QPushButton("Cancelar", this);
    buttonA->setStyleSheet("padding: 8px 8px;");
    buttonB->setStyleSheet("padding: 8px 8px;");
    buttonC->setStyleSheet("padding: 8px 8px;");

    auto* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(buttonA);
    buttonLayout->addWidget(buttonB);
    buttonLayout->addWidget(buttonC);

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(label);
    mainLayout->addLayout(buttonLayout);

    // Store signals locally so they connect to this
    connect(buttonA, &QPushButton::clicked, this, [this]() {
        result = OptionA;
        accept();
        });
    connect(buttonB, &QPushButton::clicked, this, [this]() {
        result = OptionB;
        accept();
        });
    connect(buttonC, &QPushButton::clicked, this, [this]() {
        result = OptionC;
        accept();
        });
}

void Dialog::connectSignals()
{
}

Dialog::Result Dialog::getResult() const
{
    return result;
}