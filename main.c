#include <stdio.h>
#include <windows.h>

void CheckStartupKeys(HKEY rootKey, LPCSTR subKey) {
    HKEY hKey;
    LONG result;
    DWORD i, valueCount, maxValueNameLen, maxValueLen;
    char *valueName, *dataBuffer;
    DWORD valueNameSize, dataSize, valueType;

    result = RegOpenKeyEx(rootKey, subKey, 0, KEY_READ, &hKey);
    if (result != ERROR_SUCCESS) {
        printf("Error opening key %s: %ld\n", subKey, result);
        return;
    }

    result = RegQueryInfoKey(hKey, NULL, NULL, NULL, NULL, NULL, NULL, &valueCount, &maxValueNameLen, &maxValueLen, NULL, NULL);
    if (result != ERROR_SUCCESS) {
        printf("Error querying key info for %s: %ld\n", subKey, result);
        RegCloseKey(hKey);
        return;
    }

    valueName = (char*)malloc(maxValueNameLen + 1);
    dataBuffer = (char*)malloc(maxValueLen);

    for (i = 0; i < valueCount; i++) {
        valueNameSize = maxValueNameLen + 1;
        dataSize = maxValueLen;
        result = RegEnumValue(hKey, i, valueName, &valueNameSize, NULL, &valueType, (LPBYTE)dataBuffer, &dataSize);

        if (result == ERROR_SUCCESS) {
            printf("Startup Key: %s\n", valueName);
            if (valueType == REG_SZ) {
                printf("Value Type: String\n");
                printf("Value Data: %s\n", (char*)dataBuffer);
            } else if (valueType == REG_DWORD) {
                printf("Value Type: DWORD\n");
                printf("Value Data: %lu\n", *(DWORD*)dataBuffer);
            } else {
                printf("Value Type: Other\n");
            }
            printf("\n");
        } else {
            printf("Error enumerating value for %s: %ld\n", subKey, result);
        }
    }

    free(valueName);
    free(dataBuffer);
    RegCloseKey(hKey);
}

int main() {
    printf("Checking HKLM Run keys...\n");
    CheckStartupKeys(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");

    printf("Checking HKCU Run keys...\n");
    CheckStartupKeys(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");

    printf("Checking HKLM RunOnce keys...\n");
    CheckStartupKeys(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce");

    printf("Checking HKCU RunOnce keys...\n");
    CheckStartupKeys(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce");

    printf("Checking HKLM Policies Explorer Run keys...\n");
    CheckStartupKeys(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\Run");

    printf("Checking HKCU Policies Explorer Run keys...\n");
    CheckStartupKeys(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer\\Run");

    printf("Checking HKLM Wow6432Node Run keys...\n");
    CheckStartupKeys(HKEY_LOCAL_MACHINE, "SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Run");

    printf("Checking HKLM Wow6432Node RunOnce keys...\n");
    CheckStartupKeys(HKEY_LOCAL_MACHINE, "SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\RunOnce");

    printf("Checking HKLM Shell Folders keys...\n");
    CheckStartupKeys(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");

    printf("Checking HKCU Shell Folders keys...\n");
    CheckStartupKeys(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders");

    return 0;
}
