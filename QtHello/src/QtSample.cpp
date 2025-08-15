// QtSample.cpp: define o ponto de entrada para o aplicativo.
//

#include "QtSample.hpp"

#ifdef SAMPLE_WINDOWED
#include <windows.h>
#include <shellapi.h>
#endif

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <cstdint> // for uint32_t
#include <QObject>

void StartCmdLine(int* out_argc, std::vector<char*>* out_argv);

class ClosableQWidget : public QWidget
{
public:
    ClosableQWidget(bool* runningTrace): m_RunningTrace(runningTrace) {}
protected:
    void closeEvent(QCloseEvent* event) override
    {
        *m_RunningTrace = false;
        QWidget::closeEvent(event); // Call base implementation
    }
private:
	bool* m_RunningTrace;
};

#ifdef SAMPLE_WINDOWED
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
#else
int main(int argc, char* argv[])
#endif
{
#ifdef SAMPLE_WINDOWED
    int argc;
    std::vector<char*> argv;
    StartCmdLine(&argc, &argv);
    QApplication app(argc, argv.data());
#else
    QApplication app(argc, argv);
#endif
    bool running = true;
    ClosableQWidget window(&running);
    window.setWindowTitle("Hello World Clicker");
    window.resize(640, 480);

    QLabel* label = new QLabel("Hello World");
    QPushButton* button = new QPushButton("Click Me");

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(button);
    window.setLayout(layout);

    uint32_t counter = 0;

    // On button click, increment counter and update text
    QObject::connect(button, &QPushButton::clicked, [&]() {
        counter++;
        label->setText(QString("Clicked %1 times").arg(counter));
        });

    window.show();

    // Manual event loop
    while (running) {
        app.processEvents();
        // Could add small sleep here if desired to avoid CPU spinning
    }

    return 0;
}

#ifdef SAMPLE_WINDOWED

void StartCmdLine(int* out_argc, std::vector<char*>* out_argv)
{
    // This function is intentionally left empty.
    // It is used to ensure that the entry point is compatible with the Windows subsystem.
    int argc;
    LPWSTR* argvW = CommandLineToArgvW(GetCommandLineW(), &argc);
    *out_argc = argc;

    std::vector<std::string> utf8Args;
    std::vector<char*> argv;

    for (int i = 0; i < argc; ++i) {
        int len = WideCharToMultiByte(CP_UTF8, 0, argvW[i], -1, nullptr, 0, nullptr, nullptr);
        std::string utf8(len - 1, 0);
        WideCharToMultiByte(CP_UTF8, 0, argvW[i], -1, utf8.data(), len, nullptr, nullptr);
        utf8Args.push_back(utf8);
        argv.push_back(utf8Args.back().data());
    }
    argv.push_back(nullptr);
    *out_argv = argv;
}

#endif
