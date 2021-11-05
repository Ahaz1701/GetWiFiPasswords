#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 260

int main() {
    char dataWifi[MAX_CHAR];
    FILE* wifiList = popen("netsh wlan show profiles", "r");

    int i = 0;
    while(fgets(dataWifi, MAX_CHAR, wifiList)) {
        if(strstr(dataWifi, "Profil Tous les utilisateurs") != NULL) {
            i++;

            char* wifiName = strtok(dataWifi, ":"); wifiName = strtok(NULL, ":");
            wifiName[strlen(wifiName)-1] = '\0';

            char dataPassword[MAX_CHAR];
            char cmd[] = "netsh wlan show profile \"";
            FILE* passwordList = popen(strcat(strcat(cmd, wifiName+1), "\" key=clear"), "r");

            while(fgets(dataPassword, MAX_CHAR, passwordList)) {
                if(strstr(dataPassword, "Contenu de la")) {
                    char* wifiPassword = wifiPassword = strtok(dataPassword, ":"); wifiPassword = strtok(NULL, ":");
                    wifiPassword[strlen(wifiPassword)-1] = '\0';

                    printf("%s : %s \n", wifiName+1, wifiPassword+1);
                }
            }
            pclose(passwordList);
        }
    }
    pclose(wifiList);

    return EXIT_SUCCESS;
}
