#pragma once
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

class Firewall {
public:
    // Constructor
    Firewall();

    // Add your firewall-specific functions and members here

    // Add IP to the blocked list
    void addBlockedIP(const std::string& ip);

    // Add port to the blocked outgoing ports list
    void addBlockedPortOutgoing(int port);

    // Add protocol to the blocked protocol list
    void addBlockedProtocol(const std::string& protocol);

    // Set bandwidth limit for a specific IP
    void setBandwidthLimit(const std::string& ip, int limit);

    // Allow traffic only from specific countries
    void allowTrafficFromCountry(const std::string& country);

    // Handle a request and apply rate limiting
    void handleRequest(const std::string& sourceIP);

    // Get the set of blocked IPs (for logging or UI)
    const std::unordered_set<std::string>& getBlockedIPs() const;

    // Get the set of blocked outgoing ports (for logging or UI)
    const std::unordered_set<int>& getBlockedPortsOutgoing() const;

    // Get the set of blocked protocols (for logging or UI)
    const std::unordered_set<std::string>& getBlockedProtocols() const;

    // Get bandwidth limit for a specific IP (for logging or UI)
    int getBandwidthLimit(const std::string& ip) const;

    // Get the set of allowed countries (for logging or UI)
    const std::unordered_set<std::string>& getAllowedCountries() const;

    // Get the log of blocked traffic (for logging or UI)
    const std::vector<std::string>& getBlockLog() const;

private:
    std::unordered_set<std::string> blockedIPs;
    std::unordered_set<int> blockedPortsOutgoing;
    std::unordered_set<std::string> blockedProtocols;
    std::unordered_map<std::string, int> bandwidthLimits;
    std::unordered_set<std::string> allowedCountries;
    std::unordered_map<std::string, std::pair<int, int>> requestCounters;  // For rate limiting
    std::vector<std::string> blockLog;

    // Helper function to log blocked traffic
    void logBlockedTraffic(const std::string& reason, const std::string& sourceIP, const std::string& destinationIP);
    
};

