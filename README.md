![pipex](https://github.com/user-attachments/assets/e8536226-6141-4131-ba23-b4b690ef08cc)

# Sujet :
pipex est un projet qui consiste à reproduire le fonctionnement du pipe (|) en shell. L’objectif est de comprendre comment rediriger l’entrée et la sortie standard entre plusieurs commandes.

# Fonctionnement :
La commande doit reproduire l’équivalent du comportement shell : `< infile cmd1 | cmd2 > outfile` <br>
Autrement dit :
- Lire depuis un fichier (infile)
- Exécuter cmd1, dont la sortie est redirigée vers l’entrée de cmd2
- Écrire la sortie finale dans outfile

# Explications :
Le projet repose sur plusieurs appels système clés : <br>
- `pipe()` : Crée un canal de communication entre deux processus (cmd1 → cmd2)
- `fork()` : Duplique le processus pour exécuter chaque commande séparément
- `dup2()` : Redirige les entrées/sorties (stdin/stdout) vers les fichiers/pipes
- `execve()` : Exécute les commandes données en argument

# Structure du programme :
- Ouvre les fichiers (infile, outfile)
- Crée un pipe avec pipe()
- Fork un processus pour chaque commande
- Redirige les entrées/sorties avec dup2()
- Exécute les commandes avec execve()
- Ferme les descripteurs, attend la fin des processus
