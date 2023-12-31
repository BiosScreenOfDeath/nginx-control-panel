void startServices(string, string); // TODO: implement in checks.h for to avoid DRY-ness
void runCommand(string, string);
bool isValidPort(int);
int isValidIP(string);

void runPHP_CGI(string ip, string port){   
    cout << "Running PHP-CGI...\n";
    string cmd = "php-cgi.exe -b " + ip + ":" + port;
    
    runCommand("PHP-CGI", cmd);
}

void runNginx(){
    cout << "Running Nginx...\n";
    string cmd = "cmd /c start \"\" \"C:\\Program Files\\nginx-1.25.2\\nginx.exe\" ";
    SetCurrentDirectory("\"C:\\Program Files\\nginx-1.25.2\\");

    runCommand("NGINX", cmd);
}

void runCommand(string title, string cmd){
    
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    if( !CreateProcess( NULL,   // No module name (use command line)
        cmd.data(),        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        CREATE_NO_WINDOW,              // No window flag
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
    ) 
    {
        printf( "CreateProcess failed (%d).\n", GetLastError() );
        return;
    } else { cout << title << " successfully running!\n"; }
}

void terminateServices(){
    DWORD aProcesses[1024], cbNeeded, cProcesses;

    if( !EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded) ){
        return;
    }
    cProcesses = cbNeeded / sizeof(DWORD);

    for(int iterate = 0; iterate < cProcesses; iterate++){
        if( aProcesses[iterate] != 0 ){
            bool successCheck = 0;
            HANDLE hProcess = OpenProcess( 
                PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_TERMINATE,
                FALSE,
                aProcesses[iterate] );
            if ( NULL != hProcess ) {
                HMODULE hMod = 0;
                LPSTR lpExeName = new char[MAX_PATH];
                DWORD dwFlags=0x00000000, charsCarried = MAX_PATH;

                successCheck = QueryFullProcessImageName( 
                    hProcess,
                    dwFlags, 
                    lpExeName, 
                    &charsCarried );                

                string procName = (string)lpExeName;
                int pos;
                while( ( pos = procName.find('\\') ) != string::npos){
                    procName.erase(0, pos+1); // +1 for the "."
                }
                // cout << "Process: " << procName <<": PID " << aProcesses[iterate] << '\n';

                if( procName == "php-cgi.exe" 
                 || procName == "nginx.exe"){
                    unsigned int lpExitCode = 123;
                    int getexitcode = GetExitCodeProcess(hProcess,&lpExitCode);
                    int terminateprocess = TerminateProcess(hProcess,lpExitCode) << '\n';
                    cout << "Terminated (PID: " << aProcesses[iterate] << "): " << procName << '\n';
                }
            }
            CloseHandle( hProcess );
        }
    }
    return;
}