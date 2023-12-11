#include "include/firewall.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <GeoIP2/GeoIP2.h>

Firewall::Firewall() {
    // Initialize your firewall here
}

void Firewall::addBlockedIP(const std::string& ip) {
    blockedIPs.insert(ip);
}

void Firewall::addBlockedPortOutgoing(int port) {
    blockedPortsOutgoing.insert(port);
}

void Firewall::addBlockedProtocol(const std::string& protocol) {
    blockedProtocols.insert(protocol);
}

void Firewall::setBandwidthLimit(const std::string& ip, int limit) {
    bandwidthLimits[ip] = limit;
}

void Firewall::allowTrafficFromCountry(const std::string& country) {
    allowedCountries.insert(country);
}

void Firewall::handleRequest(const std::string& sourceIP) {
    auto now = std::chrono::system_clock::now();
    auto sourceIPCounter = requestCounters.find(sourceIP);
    if (sourceIPCounter == requestCounters.end()) {
        // First request from this IP
        requestCounters[sourceIP] = std::make_pair(1, std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count());
    } else {
        // Increment the request count and check rate limit
        sourceIPCounter->second.first++;
        auto currentTime = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
        auto timeDifference = currentTime - sourceIPCounter->second.second;
        if (timeDifference < 60 && sourceIPCounter->second.first > 100) {
            // Rate limit exceeded, block the request
            blockLog.push_back("Blocked: Rate limit exceeded for " + sourceIP);
            std::cout << "Blocked: Rate limit exceeded for " << sourceIP << "\n";
            // You may want to add actual blocking logic here
        }
    }
}

const std::unordered_set<std::string>& Firewall::getBlockedIPs() const {
    return blockedIPs;
}

const std::unordered_set<int>& Firewall::getBlockedPortsOutgoing() const {
    return blockedPortsOutgoing;
}

const std::unordered_set<std::string>& Firewall::getBlockedProtocols() const {
    return blockedProtocols;
}

int Firewall::getBandwidthLimit(const std::string& ip) const {
    auto limitIt = bandwidthLimits.find(ip);
    return (limitIt != bandwidthLimits.end()) ? limitIt->second : 0;
}

const std::unordered_set<std::string>& Firewall::getAllowedCountries() const {
    return allowedCountries;
}

const std::vector<std::string>& Firewall::getBlockLog() const {
    return blockLog;
}

// Helper function to log blocked traffic
void Firewall::logBlockedTraffic(const std::string& reason, const std::string& sourceIP, const std::string& destinationIP) {
    std::time_t current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string logEntry = std::ctime(&current_time) + reason + " Source: " + sourceIP + " Destination: " + destinationIP;
    blockLog.push_back(logEntry);

    // Implement log rotation and archiving here if needed
    // This is a simplified example; consider using log rotation libraries for production
    if (blockLog.size() > 1000) {
        blockLog.erase(blockLog.begin(), blockLog.begin() + 500);  // Keep the latest 500 entries
    }

    // Optionally, write logs to a file
    std::ofstream logFile("firewall_log.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << logEntry << "\n";
        logFile.close();
    }
}
