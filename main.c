#include <stdio.h>
#include <windows.h>

int main(){
    HKEY hkey;
    LONG result;
    DWORD buffersize = 255;
    char buffer[255];
    DWORD dwType = 0;

    // Open the registry key

    result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\MICROSOFT\\Windows NT\\CurrentVersion", 0, KEY_READ, &hkey);

    if (result != ERROR_SUCCESS) {
        printf("Error opening key: %ld\n", result);
        return 1;
    }

    result = RegQueryValueEx(hkey, "ProductName", NULL, &dwType, (LPBYTE)buffer, &buffersize);

    if (result == ERROR_SUCCESS){
        printf("ProductName: %s\n", buffer);
    } else {
        printf("Error reading value %ld\n", result);
    }

    //Close the registry key
    RegCloseKey(hkey);

    return 0;
}