# projetCIR1_groupe_7
Projet de fin d'année ISEN Nantes CIR1
Filmothèque SquidFlix

Initialisation
- Ouvrir le dossier c: /src/c dans un compilateur type CLion afin de créer le dossier cmake-build-debug (cmake-build-debug doit être dans le dossier /c)
- Déposer la base de donnée souhaitée "BD_X.txt" dans le dossier cmake-build-debug 
- Dans le fichier "dataBaseInit.h", vous pouvez changer la variable DB afin de séléctionner la base de donnée à initaliser
- Executer le fichier "main.c", des fichiers textes devraient se créer dans le dossier cmake-build-debug
- Ouvrer le fichier index.html dans un navigateur. 
- ATTENTION!: Pour que les requêtes soient lues par le serveur, vous devez changer le répertoire cible de vos téléchargements à: /src/c/cmake-build-debug

Conseils:
- La base de donnée peut prendre du temps à charger, attention à ne pas appuyer trop vite sur les champs de recherches, les requêtes risquent de se stack. Le cas échéant, vous pourrez supprimer les doublons "request(X).txt" dans le dossier /src/c/cmake-build-debug
- Si vous souhaitez retarder le temps de lecture/suppression pour lire le fichier sortant "results.txt", localiser la fonction "clearInput()" dans le fichier "dataBaseInit.c" et changer la valeur de de "usleep(X)" (en micro secondes)
