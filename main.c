#include <stdio.h>
#include <windows.h>

void ReadAllValues(HKEY hKey) {
    DWORD i, retCode;
    DWORD valueCount, maxValueNameLen, maxValueLen;
    char *valueName, *dataBuffer;
    DWORD valueNameSize, dataSize, valueType;

    // Get information about the key
    retCode = RegQueryInfoKey(hKey, NULL, NULL, NULL, NULL, NULL, NULL, &valueCount, &maxValueNameLen, &maxValueLen, NULL, NULL);
    if (retCode != ERROR_SUCCESS) {
        printf("Error querying key info: %ld\n", retCode);
        return;
    }

    valueName = (char*)malloc(maxValueNameLen + 1);
    dataBuffer = (char*)malloc(maxValueLen);

    // Enumerate and print all values
    for (i = 0; i < valueCount; i++) {
        valueNameSize = maxValueNameLen + 1;
        dataSize = maxValueLen;
        retCode = RegEnumValue(hKey, i, valueName, &valueNameSize, NULL, &valueType, (LPBYTE)dataBuffer, &dataSize);

        if (retCode == ERROR_SUCCESS) {
            printf("Value Name: %s\n", valueName);
            switch (valueType) {
                case REG_SZ:
                    printf("Value Type: String\n");
                    printf("Value Data: %s\n", (char*)dataBuffer);
                    break;
                case REG_DWORD:
                    printf("Value Type: DWORD\n");
                    printf("Value Data: %lu\n", *(DWORD*)dataBuffer);
                    break;
                default:
                    printf("Value Type: Other\n");
                    break;
            }
            printf("\n");
        } else {
            printf("Error enumerating value: %ld\n", retCode);
        }
    }

    free(valueName);
    free(dataBuffer);
}

void EnumerateRegistryKeys(HKEY hKey) {
    DWORD i, retCode;
    DWORD subKeyCount, maxSubKeyLen;
    char *subKeyName;
    DWORD subKeyNameSize;
    HKEY hSubKey;

    // Get information about the key
    retCode = RegQueryInfoKey(hKey, NULL, NULL, NULL, &subKeyCount, &maxSubKeyLen, NULL, NULL, NULL, NULL, NULL, NULL);
    if (retCode != ERROR_SUCCESS) {
        printf("Error querying key info: %ld\n", retCode);
        return;
    }

    subKeyName = (char*)malloc(maxSubKeyLen + 1);

    // Enumerate and print all subkeys
    for (i = 0; i < subKeyCount; i++) {
        subKeyNameSize = maxSubKeyLen + 1;
        retCode = RegEnumKeyEx(hKey, i, subKeyName, &subKeyNameSize, NULL, NULL, NULL, NULL);

        if (retCode == ERROR_SUCCESS) {
            printf("SubKey Name: %s\n", subKeyName);

            // Open the subkey and read its values
            retCode = RegOpenKeyEx(hKey, subKeyName, 0, KEY_READ, &hSubKey);
            if (retCode == ERROR_SUCCESS) {
                ReadAllValues(hSubKey);
                RegCloseKey(hSubKey);
            } else {
                printf("Error opening subkey: %ld\n", retCode);
            }

            printf("\n");
        } else {
            printf("Error enumerating subkey: %ld\n", retCode);
        }
    }

    free(subKeyName);
}

int main() {
    HKEY hKey;
    LONG result;

    // Open the registry key
    result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_READ, &hKey);
    if (result != ERROR_SUCCESS) {
        printf("Error opening key: %ld\n", result);
        return 1;
    }

    // Enumerate and read all subkeys and values
    EnumerateRegistryKeys(hKey);
    ReadAllValues(hKey);

    // Close the registry key
    RegCloseKey(hKey);

    return 0;
}
