### Filmothèque SquidFlix
Dans le cadre de notre projet de fin d'année en CIR1 à l'ISEN, nous devions réaliser une filmothèque permettant de naviguer parmi une grande liste de film. SquidFlix propose ainsi une base de donnée allant jusqu'à 1 million de film vous permettant de rechercher par genre, titre et même de bénéificer d'un compte abonné.

Initialisation
- Ouvrir le dossier c: /src/c dans un IDE type CLion afin de créer le dossier cmake-build-debug (cmake-build-debug doit être dans le dossier /c)
- Déposer la base de donnée souhaitée "BD_X.txt" dans le dossier cmake-build-debug 
- Dans le fichier "dataBaseInit.h", vous pouvez changer la variable DB afin de séléctionner la base de donnée à initaliser
- Executer le fichier "main.c", des fichiers textes devraient se créer dans le dossier cmake-build-debug
- Ouvrer le fichier index.html dans un navigateur. 
- ATTENTION!: Pour que les requêtes soient lues par le serveur, vous devez changer le répertoire cible de vos téléchargements à: /src/c/cmake-build-debug

Conseils:
- La base de donnée peut prendre du temps à charger, attention à ne pas appuyer trop vite sur les champs de recherches, les requêtes risquent de se stack. Le cas échéant, vous pourrez supprimer les doublons "request(X).txt" dans le dossier /src/c/cmake-build-debug
- Si vous souhaitez retarder le temps de lecture/suppression pour lire le fichier sortant "results.txt", localiser la fonction "clearInput()" dans le fichier "dataBaseInit.c" et changer la valeur de de "usleep(X)" (en micro secondes)
