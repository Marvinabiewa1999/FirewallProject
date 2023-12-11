#include "include/firewall.h"
#include "include/dashboard.h"
#include <chrono>
#include <thread>

int main() {
    // Initialize and run your firewall and dashboard components
    Firewall firewall;

    // Block all incoming traffic from a specific IP address
    firewall.addBlockedIP("192.168.1.100");

    // Block all outgoing traffic on port 80
    firewall.addBlockedPortOutgoing(80);

    // Block all HTTPS traffic
    firewall.addBlockedProtocol("HTTPS");

    // Limit the total bandwidth used by a particular IP
    firewall.setBandwidthLimit("192.168.1.101", 1000000);  // 1 Mbps

    // Geo-blocking - Allow traffic only from specific countries
    firewall.allowTrafficFromCountry("US");
    firewall.allowTrafficFromCountry("CA");

    // Rate limiting - Limit requests from a particular IP
    for (int i = 0; i < 150; ++i) {
        firewall.handleRequest("192.168.1.102");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Simulate requests over time
    }

    Dashboard dashboard(firewall);

    // Add application logic here
    dashboard.run();

    return 0;
}
