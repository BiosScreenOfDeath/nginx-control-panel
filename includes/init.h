int init(int argc, char** argv){

    string terminationCheck = (string)argv[1];
    if(terminationCheck == "-k" || terminationCheck == "--kill"){
        cout << "Terminating processes (if available) ...\n";
        terminateServices();
        return 0;
    }

    int port;
    string ip;
    vector<string> commandLineData = commandLineArgumentsExist(argc, argv); 

    if(commandLineData[0] == "1"){   
        cout << "Please enter an IP and a valid port.\n>";
        cin >> ip;
        cout << ">";
        cin >> port;
        if(runTests(ip, port)){
            cout << "Note: Class 'F' denotes a special IP range.\n";
            cout << "IP is valid!\n" << "Class: " << (char)('@' + isValidIP(ip)) << '\n';
            cout << "Valid port: " << port << "\n";
            runPHP_CGI(ip, to_string(port));
            runNginx();
        } else { cout << "Invalid IP or port.\nGoodbye.\n"; }
    } else if (commandLineData[0] == "0") {
        cout << "Invalid IP or port.\nGoodbye.\n";
    } else if (commandLineData.size() == 2) {
        cout << "Note: Class 'F' denotes a special IP range.\n";
        cout << "IP is valid!\n" << "Class: " << (char)('@' + isValidIP(commandLineData[0])) << '\n';
        cout << "IP:port - " << commandLineData[0] << ":" << commandLineData[1] << '\n';
        cout << "Actual work done.\n";
        runPHP_CGI(commandLineData[0], commandLineData[1]);
        runNginx();
    }

    return 0;
}