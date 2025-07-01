![pipex](https://github.com/user-attachments/assets/e8536226-6141-4131-ba23-b4b690ef08cc)

# Sujet :
pipex est un projet qui consiste à reproduire le fonctionnement du pipe (|) en shell. L’objectif est de comprendre comment rediriger l’entrée et la sortie standard entre plusieurs commandes.

# Fonctionnement :
La commande doit reproduire l’équivalent du comportement shell : `< infile cmd1 | cmd2 > outfile` <br>
La commande dans le terminal est la suivante : `./pipex infile "cmd1" "cmd2" outfile` <br>
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
- Fork un processus pour chaque commande, avec chacun son propre PID
- Redirige les entrées/sorties avec dup2()
- Exécute les commandes avec execve()
- Ferme les descripteurs, attend la fin des processus

# Process
C'est un programme en cours d’exécution, identifié par un PID.

execute_child : `Le child traite la première commande et alimente le pipe.`
- Création d'un pipe
- Création du processus enfant : Le fork() crée un nouveau processus
- Ouverture du fichier d'entrée
- Redirection de l'entrée standard vers le fichier d'entrée (exemple makefile)
- Redirection de la sortie standard vers le pipe (écriture)
- Fermeture du descripteur de fichier d'entrée enfant
- Fermeture du descripteur de lecture du pipe dans l'enfant
- Exécution de la commande dans l'enfant et envoie de sa sortie dans le pipe

execute_parents : `Le parent, après le fork, prend le relais en consommant le pipe pour exécuter la deuxième commande.`
- Créer le processus parent avec fork
- Recupère le processus enfant
- Ouverture écriture seul, creation ou suppression du fichier de sortie
- Le process parent recoit les données du process enfant
- Redirige la sortie vers le fichier output créer
- Ferme lecture du pipe
- Ferme l'écriture du pipe
- Execution de la commande parent
- Ferme les descripteur
- Attend la fin du process enfant
