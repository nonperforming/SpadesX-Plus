// Copyright DarkNeutrino 2021
#include "Server.h"
#include "Structs.h"

#include <Types.h>
#include <json-c/json.h>
#include <json-c/json_object.h>
#include <stdio.h>

int main(void)
{
    struct json_object* parsed_json;
    struct json_object* portInConfig;
    struct json_object* masterInConfig;
    struct json_object* mapInConfig;
    struct json_object* managerPasswdInConfig;
    struct json_object* adminPasswdInConfig;
    struct json_object* modPasswdInConfig;
    struct json_object* guardPasswdInConfig;
    struct json_object* trustedPasswdInConfig;
    struct json_object* serverNameInConfig;
    struct json_object* team1NameInConfig;
    struct json_object* team2NameInConfig;
    struct json_object* team1ColorInConfig;
    struct json_object* team2ColorInConfig;
    struct json_object* team1ColorTemp;
    struct json_object* team2ColorTemp;

    uint16 port   = DEFAULT_SERVER_PORT;
    uint8  master = 1;

    parsed_json = json_object_from_file("config.json");
    if (json_object_object_get_ex(parsed_json, "port", &portInConfig) == 0) {
        printf("Failed to find port number in config\n");
        return -1;
    }
    if (json_object_object_get_ex(parsed_json, "master", &masterInConfig) == 0) {
        printf("Failed to find master variable in config\n");
        return -1;
    }
    if (json_object_object_get_ex(parsed_json, "map", &mapInConfig) == 0) {
        printf("Failed to find map name in config\n");
        return -1;
    }
    if (json_object_object_get_ex(parsed_json, "manager_password", &managerPasswdInConfig) == 0) {
        printf("Failed to find manager password in config\n");
        return -1;
    }
    if (json_object_object_get_ex(parsed_json, "admin_password", &adminPasswdInConfig) == 0) {
        printf("Failed to find admin password in config\n");
        return -1;
    }
    if (json_object_object_get_ex(parsed_json, "moderator_password", &modPasswdInConfig) == 0) {
        printf("Failed to find moderator password in config\n");
        return -1;
    }
    if (json_object_object_get_ex(parsed_json, "guard_password", &guardPasswdInConfig) == 0) {
        printf("Failed to find guard password in config\n");
        return -1;
    }
    if (json_object_object_get_ex(parsed_json, "trusted_password", &trustedPasswdInConfig) == 0) {
        printf("Failed to find trusted password in config\n");
        return -1;
    }
    if (json_object_object_get_ex(parsed_json, "server_name", &serverNameInConfig) == 0) {
        printf("Failed to find server name in config\n");
        return -1;
    }
    if (json_object_object_get_ex(parsed_json, "team1_name", &team1NameInConfig) == 0) {
        printf("Failed to find team1 name in config\n");
        return -1;
    }
    if (json_object_object_get_ex(parsed_json, "team2_name", &team2NameInConfig) == 0) {
        printf("Failed to find team2 name in config\n");
        return -1;
    }
    if (json_object_object_get_ex(parsed_json, "team1_color", &team1ColorInConfig) == 0) {
        printf("Failed to find team1 color in config\n");
        return -1;
    }
    if (json_object_object_get_ex(parsed_json, "team2_color", &team2ColorInConfig) == 0) {
        printf("Failed to find team2 color in config\n");
        return -1;
    }
    const char* map           = json_object_get_string(mapInConfig);
    port                      = json_object_get_int(portInConfig);
    master                    = json_object_get_int(masterInConfig);
    const char* managerPasswd = json_object_get_string(managerPasswdInConfig);
    const char* adminPasswd   = json_object_get_string(adminPasswdInConfig);
    const char* modPasswd     = json_object_get_string(modPasswdInConfig);
    const char* guardPasswd   = json_object_get_string(guardPasswdInConfig);
    const char* trustedPasswd = json_object_get_string(trustedPasswdInConfig);
    char*       serverName    = (char*) json_object_get_string(serverNameInConfig);
    char*       team1Name     = (char*) json_object_get_string(team1NameInConfig);
    char*       team2Name     = (char*) json_object_get_string(team2NameInConfig);
    uint8       team1Color[3];
    uint8       team2Color[3];
    for (int i = 0; i < 3; ++i) {
        team1ColorTemp = json_object_array_get_idx(team1ColorInConfig, i);
        team2ColorTemp = json_object_array_get_idx(team2ColorInConfig, i);
        team1Color[i]  = json_object_get_int(team1ColorTemp);
        team2Color[i]  = json_object_get_int(team2ColorTemp);
    }

    StartServer(port,
                64,
                2,
                0,
                0,
                master,
                map,
                managerPasswd,
                adminPasswd,
                modPasswd,
                guardPasswd,
                trustedPasswd,
                serverName,
                team1Name,
                team2Name,
                team1Color,
                team2Color);
    return 0;
}
