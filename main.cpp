//
//  main.cpp
//  URLCheck
//
//  Created by Tim Liu on 1/31/20.
//  Copyright © 2020 Tim Liu. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string>
#include <cstdlib>

using namespace std;

void checkURL(string );
void displayVersion(double );

// comment added here
static double version = 1.2;

int main(int argc, char** argv) {
    string inputURL = argv[1];
//    string inputURL = "https://cs.utdallas.edu:80/directory/faculty/people.html?name=Robert";
//    checkURL(inputURL);
//    inputURL = "httpz://cs.utdallas.edu:80000/people.html?name=Robert";
//    checkURL(inputURL);
//    inputURL = "https://cs.utdallas.adu:80/people.html?name=Robert";
//    checkURL(inputURL);
//    inputURL = "https://cs.utdallas.edu/directory/people.htm";
    
    checkURL(inputURL);
    displayVersion(version);    

    return 0;
}

// hello this is tim
void checkURL(string inputURL) {
    string protocol = "";
    string domain = "";
    string port = "";
    string filePath = "";
    string parameters = "";
    
    string::size_type n0 = inputURL.find("://");
    if (n0 != string::npos) {
        protocol = inputURL.substr(0, n0);
    }
    
    string::size_type n1 = inputURL.find(":", n0+1);
    string::size_type n2;
    if (n1 != string::npos) {
        domain = inputURL.substr(n0+3, n1-n0-3);
        n2 = inputURL.find("/", n1+1);
        if (n2 != string::npos) {
            port = inputURL.substr(n1+1, n2-n1-1);
        }
    }
    else {
        n1 = inputURL.find("/", n0+3);
        if (n1 == string::npos)
        {
            n1 = inputURL.length();
        }
        domain = inputURL.substr(n0+3, n1-n0-3);
        n2 = n1;
    }
    
    string::size_type n3 = inputURL.find("?");
    if (n3 != string::npos) {
        filePath = inputURL.substr(n2, n3-n2);
        parameters = inputURL.substr(n3+1);
    }
    else {
        filePath = inputURL.substr(n2);
    }
    
    bool isValidProtocol = protocol == "http" || protocol == "https" || protocol == "ftp" || protocol == "ftps";
    
    bool isValidDomain = false;
    string domainName = "";
    string::size_type m0 = domain.find(".");
    if (m0 != string::npos && m0 > 0) {
        string::size_type m1 = domain.find(".", m0+2);
        if (m1 != string::npos) {
            domainName = domain.substr(m1+1);
            isValidDomain = domainName == "com" || domainName == "net" || domainName == "biz" || domainName == "edu" || domainName == "gov";
        }
    }
    
    int p = 1;
    if (port != "") {
        p = stoi(port);
//        sscanf(port, "%d", &p);
//        p = stoi(port);
    }
    bool isValidPort = p >= 1 && p <= 65535;
    
    bool isValidFilePath = filePath.substr(0, 1) == "/" && (filePath.substr(filePath.length()-4) == "html" || filePath.substr(filePath.length()-3) == "htm");
    
    if (!isValidProtocol || !isValidDomain || !isValidPort || !isValidFilePath) {
        cout << "Invalid URL with following erroneous components: " << endl;
        if (!isValidProtocol)
            cout << "Protocol:     " << protocol << " is not a valid protocol." << endl;
        if (!isValidDomain)
            cout << "Domain:       " << domainName << " is an invalid domain name." << endl;
        if (!isValidPort)
            cout << "Port:         port number must be between 1 and 65535" << endl;
        if (!isValidFilePath)
            cout << "File path:    " << filePath << " is not a valid file path." << endl;
    }
    else {
        cout << "Protocol:     " << protocol << endl;
        cout << "Domain:       " << domain << endl;
        if (port != "")
            cout << "Port:         " << port << endl;
        cout << "File path:    " << filePath << endl;
        if (parameters != "")
            cout << "Parameters:   " << parameters << endl;
    }
    cout << endl;
}
