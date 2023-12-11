#pragma once
#include "firewall.h"

class Dashboard {
public:
    // Constructor
    Dashboard(const Firewall& firewall);

    // Run the dashboard
    void run();

private:
    const Firewall& firewall;

    // Add private members or helper functions if needed
};
