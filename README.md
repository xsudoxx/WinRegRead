
# Registry Key Reader and Anomaly Detection Tool
## Overview
This document provides information on how to read Windows registry entries using a C program and highlights common types of anomalous registry keys that might indicate malicious activity. It includes a sample C program to enumerate and read registry entries, focusing on startup keys to detect potential anomalies.

## Types of Anomalous Registry Keys
Anomalous registry keys are entries that exhibit unusual or suspicious behavior, often indicating the presence of malware or unauthorized changes. Below are some common types:

### Startup Keys
Malware often adds itself to startup keys to ensure it runs on system boot.

#### Common Keys:

HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Run
HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run
HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\RunOnce
HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\RunOnce
### Shell Keys
Modify default behavior of Windows Explorer shell.

#### Key to Check:

HKEY_LOCAL_MACHINE\Software\Microsoft\Windows NT\CurrentVersion\Winlogon\Shell
### Service Keys
Malware might create or modify service entries.

#### Keys to Check:

HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services
HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Uninstall
### AppInit_DLLs
Used to load malicious DLLs into every process that loads User32.dll.

#### Key to Check:

HKEY_LOCAL_MACHINE\Software\Microsoft\Windows NT\CurrentVersion\Windows\AppInit_DLLs
### Image File Execution Options (IFEO)
Intercept process execution.

#### Key to Check:

HKEY_LOCAL_MACHINE\Software\Microsoft\Windows NT\CurrentVersion\Image File Execution Options
### Autorun.inf
Execute files automatically when external drives are connected.

#### Key to Check:

HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Explorer\AutoplayHandlers
Indicators of Anomalous Registry Keys
Unexpected Entries: New or unknown entries in common keys.
Suspicious Values: Values pointing to non-standard directories or executables with unusual names.
Unusual Data: Entries with obfuscated or encoded data.
Permissions Changes: Keys with altered permissions preventing administrator access.
Frequent Modifications: Keys frequently modified, especially startup keys.