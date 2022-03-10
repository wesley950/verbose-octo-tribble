#pragma once

class Application {
public:
    Application() = default;
    virtual ~Application() = default;

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
};

Application* create_application();
