// QtSample.cpp: define o ponto de entrada para o aplicativo.
//

#include "QtSample.hpp"

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <cstdint> // for uint32_t
#include <QObject>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Hello World Clicker");

    QLabel* label = new QLabel("Hello World");
    QPushButton* button = new QPushButton("Click Me");

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(button);
    window.setLayout(layout);

    uint32_t counter = 0;
    bool running = true;

    // On button click, increment counter and update text
    QObject::connect(button, &QPushButton::clicked, [&]() {
        counter++;
        label->setText(QString("Clicked %1 times").arg(counter));
        });

    // On window close, stop the loop
    QObject::connect(&app, &QApplication::aboutToQuit, [&]() {
        running = false;
        });

    window.show();

    // Manual event loop
    while (running) {
        app.processEvents();
        // Could add small sleep here if desired to avoid CPU spinning
    }

    return 0;
}
