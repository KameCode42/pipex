![pipex](https://github.com/user-attachments/assets/e8536226-6141-4131-ba23-b4b690ef08cc)

# Sujet :
pipex est un projet qui consiste à reproduire le fonctionnement du pipe (|) en shell. L’objectif est de comprendre comment rediriger l’entrée et la sortie standard entre plusieurs commandes, à l’aide de pipe(), fork(), dup2() et execve().

# Fonctionnement :
La commande doit reproduire l’équivalent du comportement shell : `< infile cmd1 | cmd2 > outfile`
Autrement dit :
- Lire depuis un fichier (infile)
- Exécuter cmd1, dont la sortie est redirigée vers l’entrée de cmd2
- Écrire la sortie finale dans outfile
