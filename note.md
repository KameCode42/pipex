Projet pipex :
- Projet qui consiste a reproduire un pip
  exemple de commande : < infile grep a1 | wc -w > outfile

Definition symboles :
- '<' : redirige le contenu de infile vers la sortie standard
		grep va lire le contenu de infile et trouver toutes les lignes contenant le mot a1

- '|' : symbole pipe qui redirige la sortie standard de la commande precedente(grep a1) vers
		l'entree stantard de la commande suivant(wc -w)

- 'wc -w' : commande qui sert a compter les elements, avec -w, elle compte le nombre de mot
			dans l'exemple ici, elle compte le nombre de mots dans la sortie générée par grep a1, c'est-à-dire dans les lignes contenant a1

- '> outfile' : > redirige la sortie standard de la commande finale(resultat de wc -w) vers un
				fichier outfile, si le fichier outfile n'existe pas, il est cree
				si le fichier existe, son contenu est ecrase par la nouvelle sortie

Exemple :
apple banana
alpha a1 beta
gamma delta a1 epsilon
zeta

exemple de commande :
./pipex file.txt "grep a1" "wc -w" output.txt
- la commande grep cherche les ligne contenant le mot a1, dans ce cas la ligne 2 et 3
- la commande wc -w compte le nombre de mot que contient les lignes 2 et 3
- la sortie standard de la commande finale sera 7 (ligne 2 = 3 mots, ligne 3 = 4 mots)

./pipex file.txt "grep apple" "wc -w" output.txt

access : int access(char *pathfile, int mode)
		 utilisée pour vérifier les permissions d'accès d'un fichier ou d'un répertoire. Elle permet de tester si un fichier ou répertoire existe,
		 et si l'utilisateur a les droits nécessaires pour effectuer certaines opérations sur ce fichier (comme la lecture, l'écriture ou l'exécution)

pipe : pipe(pipe_fd)
	   Le pipe agit comme un canal :
	   Écriture : Un processus peut envoyer des données dans le pipe
	   Lecture : Un autre processus peut récupérer ces données depuis le pipe
	   int pipe_fd[2] = pipe_fd[0] = lecture et pipe_fd[1] = ecriture
	   retourne 0 si tous se passe bien
	   retourne -1 en cas d'erreur

fork : pid_t fork(void)
	   Créer un nouveau processus, appelé le processus fils, qui est une copie exacte du processus parent
Retour de fork :
	   pid < 0 ou pid == 0
	   Dans le processus parent : fork() retourne le PID du processus fils (un nombre positif).
	   Dans le processus fils : fork() retourne 0.
	   Si une erreur se produit : fork() retourne -1 (par exemple, en cas de manque de ressources).

dup2 : permet de rediriger la sortie sur un fichier et non sur le terminal

execve : permet de faire executer la commande rechercher

waitpid : dans la fonction parents, attend la fin du processus enfant

-------------------------------------------------------------------------------------------------------------

pipex.h :

#include <sys/wait.h> : controle si le programme se termine correcement avec la bonne sortie
#include <sys/types.h> : dans un programme C sert à inclure un fichier qui définit des types spécifiques au système d'exploitation comme 'pid'

-------------------------------------------------------------------------------------------------------------

FIND_PATH.C :

ft_path :
- la fonction permet de parcourir l'environnement dans le terminal afin de rechercher la ligne contenant "PATH=", une fois dessus on copie toute la chaine qui se trouve apres "PATH=", on split le repertoir apres les : afin que la chaine ne contienne plus que "/usr/local/bin", on retourne la chaine

exemple :
Répertoire 1: /usr/local/bin
Répertoire 2: /usr/bin
Répertoire 3: /usr/local/sbin

f_path[0] = "/usr/local/bin";
f_path[1] = "/usr/bin";
f_path[2] = "/bin";
f_path[3] = "/usr/sbin";
f_path[4] = "/sbin";
f_path[5] = NULL; // Fin du tableau

avec ft_path on obtient la ligne de l env : /usr/local/bin:/usr/bin:/usr/local/sbin:
avec execute_command on obtient /usr/local/bin/ls -l

execute_command :
- la fonction permet d'executer la commande souhaite, on split la commande ou se trouve les espace "ls -l", on joint "/usr/local/bin" avec un "/" cela devient "/usr/local/bin/", on joint ensuite la commande "/usr/local/bin/ls -l", avec access on verfie si la commande existe et peut etre executer, si oui execve trouve la commande et l execute

exemple extract :
cmd_extract[0] = "ls"
cmd_extract[1] = "-l"
cmd_extract[2] = NULL

cmd_extract = ft_split(pipex->cmd1, ' ') = commande ls -l

cmd_path = ft_strjoin(path[i], "/") = cmd_path devient /usr/local/bin/
cmd_path = ft_strjoin(cmd_path, cmd_extract[0]) = cmd_path devient /usr/local/bin/ls -l

-------------------------------------------------------------------------------------------------------------

CHECK_ERROR :

check_args :
-check si tous les arguments sont presents pour lancer le programme

check_files :
-fonction qui permet de verifier si les fichiers ont les droits necessaire et si ils existent

- si le input_file n'existe pas ou que le input_file n'est pas accessible en lecture, retourne une erreur
- si on a pas la permission au fichier input_file en mode lecture seul ou 
  que la permission n est pas autorise pour le output_file pour le mode ecriture, creer, remplacer le contenu, retourne une erreur

R_OK : verifie si le fichier est accessible en lecture (utiliser pour input_file)
F_OK : verifie l existence du fichier (utiliser pour le output_file)
W_OK : verifie si le output_file est en mode ecriture
X_OK : verifie si c'est executable

permission pour le fichier entree en mode lecture seul
O_RDONLY : fichier en mode lecture seul

Si le fichier de sortie n'existe pas, on essaie de le créer en utilisant open(). Les flags utilisés sont :
- O_WRONLY : nous ouvrons le fichier en mode écriture
- O_CREAT : si le fichier n'existe pas, il sera créé
- O_TRUNC : si le fichier existe déjà, son contenu sera supprimé (le fichier sera tronqué à zéro) chmod 0644

handle_command_error :
- fonction qui permet de verfier si la commande demande en argument existe

-------------------------------------------------------------------------------------------------------------

PIPEX.C :

execute_child :

- création d'un pipe : pipex->pipe_fd est créé, avec un côté lecture et un côté écriture.
- création du processus enfant : Le fork() crée un nouveau processus.
- ouverture du fichier d'entrée
- redirection de l'entrée standard vers le fichier d'entrée (exemple makefile)
- redirection de la sortie standard vers le pipe (écriture)
- fermeture du descripteur de fichier d'entrée enfant
- fermeture du descripteur de lecture du pipe dans l'enfant
- exécution de la commande dans l'enfant et envoi de sa sortie dans le pipe.

Processus enfant : Exécute la première commande (ls -l) et redirige la sortie vers le pipe

execute_parents :

- creer le processus parent avec fork
- recupere le processus enfant
- ouverture ecriture seul, creation ou suppression du fichier de sortie
- le process parent recoit les donnee du process enfant
- redirige la sortie vers le fichier output creer
- ferme lecture du pipe
- ferme l ecriture du pipe
- execution de la commande parent
- ferme les descripteur
- attend le processus

Processus parent : Récupère la sortie de ls -l à partir du pipe, et l'utilise comme entrée pour exécuter la deuxième commande (wc -l).

-------------------------------------------------------------------------------------------------------------