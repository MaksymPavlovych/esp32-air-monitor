#pragma once

namespace wifi_manager {
    void begin();       // підключення при старті
    void loop();        // викликати в loop(): перепідключення, якщо зв'язок пропав
    bool connected();
}
