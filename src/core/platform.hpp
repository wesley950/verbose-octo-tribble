#pragma once

class Platform {
public:
    Platform() = default;
    virtual ~Platform() = default;

    virtual int run() = 0;

    void quit(int exitCode = 0);

protected:
    int m_ExitCode = 0;
    bool m_Running = false;
};

Platform* create_platform();
