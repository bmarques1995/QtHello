#pragma once

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class Dialog : public QDialog {
public:
    enum Result { OptionA, OptionB, OptionC, None };
    explicit Dialog(QWidget* parent = nullptr);

    Result getResult() const;

private:
    Result result = None;

    void setupUi();
    void connectSignals();
};