#pragma once

#include "../../../Utils/Utils.h"

class Client;

class Notification {
public:
    ImVec2 pad = ImVec2(6.f, 2.f);
    
    float alpha = 1.f;
    float animXOff = 0.f;
    bool doneAnim = false;
    std::string title, contents;

    std::chrono::steady_clock::time_point timepoint;

    Notification(std::string nTitle, std::string nContent, int msDelay) : title(nTitle), contents(nContent) {
        this->timepoint = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(msDelay);
    };

    auto getBounds(float fontSize) -> ImVec2 {

        auto currSize = Renderer::getTextSize(this->title, fontSize);
        currSize.x += pad.x; currSize.y += pad.y;

        auto contentsSize = Renderer::getTextSize(this->contents, fontSize);
        contentsSize.x += pad.x; contentsSize.y += pad.y;

        if(contentsSize.x > currSize.x)
            currSize.x = contentsSize.x;
        
        currSize.y += contentsSize.y;
        return currSize;
    };
};

class NotificationManager {
public:
    NotificationManager(Client*);
    ~NotificationManager(void);

    auto render(void) -> void;

    auto addNotif(std::string title, std::string contents, int msDelay = 3000) {
        this->notifications.push_back(std::make_unique<Notification>(title, contents, msDelay));
    };

    auto setFontSize(float font_size) -> void {
        this->fontSize = font_size;
    };

    auto setSpace(float new_space) -> void {
        this->space = new_space;
    };
private:
    Client* client = nullptr;
    float fontSize = 18.f, space = 100.f;
    std::vector<std::unique_ptr<Notification>> notifications;
};