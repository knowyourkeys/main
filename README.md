Synopsis Projet Transverse


I)	Analyse du sujet

Actuellement, chaque individu possède environ 14 mots de passe et se retrouve assez souvent dans la situation où ils les oublient. Dans ce cadre-là, notre groupe a décidé de créer un gestionnaire de mots de passe pour éviter ce genre de problème. Nous allons donc proposer un logiciel qui permet de stocker de manière sécurisée des mots de passe ainsi que la génération de mots de passe sécurisés, la comparaison de dictionnaire parmi une liste complète. Pour cela, nous allons utiliser le langage C++ ainsi que QT pour établir une interface graphique. En ce qui concerne le chiffrement des mots de passe, nous allons rechercher parmi les algorithmes les plus utilisés et nous utiliserons celui qui sera le plus efficace.

II)	Travail de conception 

Concernant le chiffrement des mots de passe, après avoir réalisé des recherches concernant les algorithmes utilisés dans les autres gestionnaires de mots de passe, nous avons décidé d’utiliser le AES 256. Nous allons implémenter cet algorithme avec la librairie 
Crypto++. 


III)	Feuille de route projet
Pour réaliser ce projet de manière efficace, nous l’avons séparé en plusieurs parties : une partie où l’on réaliserai l’interface graphique qui permettrait de rendre un projet plus propre et non un projet seulement en console ; une autre partie qui concernerait la génération de clés aléatoires, contenant chiffres, lettres, caractères spéciaux ; de même qu’il serait nécessaire de faire en sorte que le dictionnaire ne devienne pas un problème dû à sa taille ; pour finir une dernière partie concernant le chiffrement des clés pour faire en sorte que tout soit bien sécurisé.
Si le temps nous le permet, nous pourrions aussi intégrer d’autres fonctions à notre projet telle qu’une fonction permettant le remplissage automatique du mot de passe lors d’une connexion à un compte en particulier.
Pour cela, chacun d’entre nous aura pour tâche, une partie précédemment évoquée :
Diogo BRANCO GABRIEL -> QT, interface graphique 
Charles ROBICHON -> générateur de clés aléatoires 	
Louis POTRON -> dictionnaire 	
Radu CERNAIANU -> chiffrement  


IV)	Objectifs du prototype initial
Ce qui est important d’évoqué est que l’interface graphique va jouer un rôle important dans le fait qu’elle doit être intuitive et très performante pour permettre à l’utilisateur de l’utiliser facilement. Il faudrait aussi pouvoir avoir déjà jusque là avoir réussi à trouver une méthode de chiffrement et savoir l’appliquer.

V) Résultats
	Nous avons donc réalisé la majorité des fonctionnalités que nous avons décidé de faire, malheureusement nous n’avons pas pu faire l’extension chrome. Nous avons rencontré quelques difficultés durant la réalisation de ce projet, notamment dû à l’utilisation des différentes librairies. Nous avons rencontré des problèmes de compatibilité entre Qt, le logiciel que nous avons utilisé pour l’interface, et la librairie Crypto++ que nous avons utilisé pour le chiffrement. Nous avons trouvé une solution à ce problème en utilisant un fichier temporaire pour communiquer entre les deux programmes. En ce qui concerne l’extension, un problème majeur est apparu. L’utilisation de l’extension aurait forcé l’information chiffrée. Or notre projet se reliant majoritairement sur le chiffrement de données, nous aurions dû recréer le système de chiffrage et déchiffrage sur l’application donc en JavaScript/HTML5. Du coup cela revenait à refaire notre projet en Js sans l’interface. L’idée a donc été abandonnée après une vive introduction aux extensions (manifest.json, background scripts,etc…).


