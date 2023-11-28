bool runTests(string IP, int port){
    bool IPCheck = isValidIP(IP);
    bool portCheck = isValidPort(port);
    return IPCheck == portCheck;
}

int isValidIPClassA(vector<string> ip){
    if( !( stoi(ip[0]) >= 1 && stoi(ip[0]) <= 127)){ return false; }
    if( !( stoi(ip[1]) >= 0 && ( ( stoi(ip[0]) == 127 && stoi(ip[1]) == 0 ) || (stoi(ip[0]) < 127 && stoi(ip[1]) <= 255) ))){ return false; }
    if( !( stoi(ip[2]) >= 0 && ( ( stoi(ip[0]) == 127 && stoi(ip[2]) == 0 ) || (stoi(ip[0]) < 127 && stoi(ip[2]) <= 255) ))){ return false; }
    if( !( stoi(ip[3]) >= 0 && ( ( stoi(ip[0]) == 127 && stoi(ip[3]) == 0 ) || (stoi(ip[0]) < 127 && stoi(ip[3]) <= 255) ))){ return false; }

    return 1;
}

int isValidIPClassB(vector<string> ip){
    if( !( stoi(ip[0]) >= 128 && stoi(ip[0]) <= 191) ){ return false; }
    if( !( stoi(ip[1]) >= 0 && stoi(ip[1]) <= 255)){ return false; }
    if( !( stoi(ip[2]) >= 0 && ( ( stoi(ip[0]) == 191 && stoi(ip[2]) == 0 ) || ( stoi(ip[0]) < 191 && stoi(ip[2]) <= 255) ))) { return false; }
    if( !( stoi(ip[3]) >= 0 && ( ( stoi(ip[0]) == 191 && stoi(ip[3]) == 0 ) || ( stoi(ip[0]) < 191 && stoi(ip[3]) <= 255) ))){ return false; }

    return 2;
}

int isValidIPClassC(vector<string> ip){
    if( !( stoi(ip[0]) >= 192 && stoi(ip[0]) <= 223)){ return false; }
    if( !( stoi(ip[1]) >= 0 && stoi(ip[1]) <= 255)){ return false; }
    if( !( stoi(ip[2]) >= 0 && stoi(ip[2]) <= 255)){ return false; }
    if( !( stoi(ip[3]) >= 0 && ( ( stoi(ip[0]) == 223 && stoi(ip[3]) == 0 ) || ( stoi(ip[0]) < 223 && stoi(ip[3]) <= 255) ))){ return false; }

    return 3;
}

int isValidIPClassD(vector<string> ip){
    if( !( stoi(ip[0]) >= 224 && stoi(ip[0]) <= 239) ){ return false; }
    if( !( stoi(ip[1]) >= 0 && stoi(ip[1]) <= 255)){ return false; }
    if( !( stoi(ip[2]) >= 0 && stoi(ip[2]) <= 255)){ return false; }
    if( !( stoi(ip[3]) >= 0 && stoi(ip[3]) <= 255)){ return false; }

    return 4;
}

int isValidIPClassE(vector<string> ip){
    if( stoi(ip[0]) != 192 ){ return false; }
    if( !( stoi(ip[1]) >= 168 && stoi(ip[1]) <= 255)){ return false; }
    if( !( stoi(ip[2]) >= 0 && stoi(ip[2]) <= 255)){ return false; }
    if( !( stoi(ip[3]) >= 0 && stoi(ip[3]) <= 255)){ return false; }

    return 5;
}

int isCustom(vector<string> ip){
    if( stoi(ip[0]) == 0
    && stoi(ip[1]) == 0
    && stoi(ip[2]) == 0
    && stoi(ip[3]) == 0 ){
        return false;
    }

    if( stoi(ip[0]) == 255
    && stoi(ip[1]) == 255
    && stoi(ip[2]) == 255
    && stoi(ip[3]) == 255 ){
        return false;
    }

    if( isValidIPClassA(ip)
    || isValidIPClassB(ip)
    || isValidIPClassC(ip)
    || isValidIPClassD(ip)
    || isValidIPClassE(ip)
    ){ return false; }

    return 6;
}

int isValidIP(string ip){
    vector<string> IPAdress;
    string delimiter = ".";
    int iterate = 1;
    size_t pos = 0;
    // cout << "Current string: " << ip << '\n';
    while( ( pos = ip.find(delimiter) ) != string::npos){
        string IPbyte = ip.substr(0, pos);
        IPAdress.push_back(IPbyte);
        // cout << "Byte " << iterate << ": " << IPbyte << '\n';
        // iterate++;
        ip.erase(0, pos+1); // +1 for the "."
    }
    string IPbyte = ip.substr(0, pos);
    IPAdress.push_back(IPbyte);
    
    return isValidIPClassA(IPAdress)
     + isValidIPClassB(IPAdress)
     + isValidIPClassC(IPAdress)
     + isValidIPClassD(IPAdress)
     + isValidIPClassE(IPAdress)
     + isCustom(IPAdress);
}

bool isValidPort(int port){
    return port >= 1 && port <= 9999;
}

vector<string> commandLineArgumentsExist(int argc, char** argv){
    // set this stuff to tests.h later
    if(argc > 1 && !runTests((string)argv[1], atoi(argv[2])) ) {
        cout << "Improper IP or port.\n>";
        cout << "Usage: [executable] [IP] [Port]\n";
        cout << "e.g. nginx_control_panel 127.0.0.1:9999\n";
        return {"0"}; // erroneous case
    } else if (argc == 1) {
        return {"1"}; // no command line arguments
    }
    
    return {(string)argv[1], (string)argv[2]};
}