#pragma once

#include <iostream>
#include <map>

class Dashboard {
public:
    Dashboard();

    // Statistics and Monitoring
    void displayTotalTraffic();
    void displayTrafficBreakdown();
    void displayBlockedRequestsByRule();
    void displayBandwidthUsageOverTime();

private:
   std::vector<std::string> rules;
};

