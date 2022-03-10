#pragma once

#include "platform.hpp"

int main(int argc, char** argv) {
    Platform* platform = create_platform();
    int result = platform->run();
    delete platform;
    return result;
}
