### Vintra Rootkit
![Vintra](https://github.com/user-attachments/assets/5de78acf-6951-4199-ba73-f2935e0fd397)
### Fonctionnalités du Rootkit Vritra

Vritra peut être chargé avec kdmapper pour contourner l'Enforcement de Signature de Pilote (DSE), fonctionnant ainsi sans nécessiter l'activation du mode test. Bien que le chargeur Vritra soit encore en cours d'amélioration, j'ai intégré driver-hijack pour garantir une fonctionnalité complète du pilote, y compris la prise en charge des callbacks.

    Contournement de la DSE : Pas besoin d'activer la signature de test.
    Bypass de la KPP : Pas encore
    Masquage des Processus : Cache les processus pour une invisibilité totale.
    Masquage des Ports (TCP/UDP) : Discrétion assurée pour les communications réseau.
    Élévation des Permissions des Processus : Augmente discrètement les privilèges des processus.
    Protection des Processus : Empêche la terminaison des processus critiques.
    Injection Persistante de Shellcode : Le shellcode continue de fonctionner même après la fermeture du processus hôte.
