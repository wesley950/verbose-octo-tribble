#include "platform.hpp"

void Platform::quit(int exitCode) {
    m_ExitCode = exitCode;
    m_Running = false;
}
