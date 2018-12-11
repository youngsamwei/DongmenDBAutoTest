//
// Created by sam on 2018/12/11.
//

#include "monitor_test_cases_execution.h"


void monitor_test_cases_execution(string exe_file_name, int timeout, int &recieving_chars_count) {

    int prev_receiving_chars = -1;
    clock_t prev_time;
    prev_time = clock();
    while (recieving_chars_count >= 0) {
        sleep(1);
        if (prev_receiving_chars == recieving_chars_count) {
            if ((clock() - prev_time) > timeout * 1000) {
                find_process_and_kill(exe_file_name.c_str());
                /*终止进程*/
                cout << endl << exe_file_name << " will be stopped." << endl;
                break;
            }

        } else {
            prev_time = clock();
            prev_receiving_chars = recieving_chars_count;
        }

    }

    /*关闭弹出的appcrash窗口，如果有的话*/
    const char *werfault = "WerFault.exe";
    find_process_and_kill(werfault);
}

void find_process_and_kill(const char *strFilename) {

    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        return;
    }

    PROCESSENTRY32 pe32 = {0};
    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hProcessSnap, &pe32)) {
        do {

            if (strcmp(pe32.szExeFile, strFilename) == 0) {
                HANDLE hprocess = OpenProcess(PROCESS_ALL_ACCESS, false, pe32.th32ProcessID);
                TerminateProcess(hprocess, 0);
                CloseHandle(hprocess);
                break;
            }
        } while (Process32Next(hProcessSnap, &pe32));
    }

    CloseHandle(hProcessSnap);
}
