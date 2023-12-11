#include "include/dashboard.h"
#include <iostream>

Dashboard::Dashboard(const Firewall& firewall) : firewall(firewall) {
    // Initialize your dashboard here
}

void Dashboard::run() {
    // Add code to display dashboard information
    std::cout << "Firewall Dashboard\n";

    // Example: Display the list of blocked IPs
    std::cout << "Blocked IPs:\n";
    for (const auto& ip : firewall.getBlockedIPs()) {
        std::cout << ip << "\n";
    }

    // Example: Display the list of blocked outgoing ports
    std::cout << "Blocked Outgoing Ports:\n";
    for (const auto& port : firewall.getBlockedPortsOutgoing()) {
        std::cout << port << "\n";
    }

    // Example: Display the list of blocked protocols
    std::cout << "Blocked Protocols:\n";
    for (const auto& protocol : firewall.getBlockedProtocols()) {
        std::cout << protocol << "\n";
    }

    // Example: Display bandwidth limits
    std::cout << "Bandwidth Limits:\n";
    for (const auto& entry : firewall.getBandwidthLimits()) {
        std::cout << "IP: " << entry.first << ", Limit: " << entry.second << " bps\n";
    }

    // Example: Display allowed countries
    std::cout << "Allowed Countries:\n";
    for (const auto& country : firewall.getAllowedCountries()) {
        std::cout << country << "\n";
    }

    // Example: Display blocked traffic log
    std::cout << "Blocked Traffic Log:\n";
    for (const auto& entry : firewall.getBlockLog()) {
        std::cout << entry << "\n";
    }
}
