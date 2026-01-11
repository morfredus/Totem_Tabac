#ifndef SECRETS_EXAMPLE_H
#define SECRETS_EXAMPLE_H

// =========================================================
// FICHIER D'EXEMPLE POUR LES SECRETS WIFI
// =========================================================
// 
// INSTRUCTIONS:
// 1. Renommez ce fichier en "secrets.h" ou créez "secrets.h" manuellement
// 2. Remplacez SSID1, PASSWORD1, etc. par vos vrais réseaux WiFi
// 3. Ajoutez autant de réseaux que vous le souhaitez
// 4. IMPORTANT: N'ajoutez JAMAIS secrets.h à votre dépôt Git (voir .gitignore)
// 5. Conservez ce fichier (secrets_example.h) dans le dépôt pour la documentation
//

// Liste des réseaux WiFi connus (SSID, mot de passe)
// Format: {"SSID", "MOT_DE_PASSE"}
// L'appareil tentera de se connecter au premier réseau disponible dans l'ordre
static const char* WIFI_NETWORKS[][2] = {
    {"SSID1", "MOT_DE_PASSE1"},
    {"SSID2", "MOT_DE_PASSE2"},
    {"SSID3", "MOT_DE_PASSE3"},
};

#endif // SECRETS_EXAMPLE_H
