# TL;DR
Tresh est une powerbank à écran OLED qui fait partie du Projet Ayyur mené par les Ei-2i2 de la promotion 2020/2021.

Tresh permet d'alimenter une lampe directement brancher en USB à la Powerbank. L'écran permet de savoir combien de % il reste dans la batterie et combien de temps il reste avant la décharge totale.

Le code possède un mode de test activé par défaut, pour le désactiver il faut changer la variable test en FALSE.

# Tresh
Voici ma participation au projet de fin d'année de la promotion Ei-2i2 de l'année scolaire 2020/2021.

## Origine & besoins
Tresh est un des trois produits nés du besoin de créer une solution efficace au manque d'électricité dans certaines régions un peu plus reculées, ce projet s'appelle le Projet Ayyur.

Tresh est une powerbank (Batterie rechargeable) qui doit être capable d'alimenter une lampe branchée en USB.

Mon but était de concevoir un code à téléverser dans une arduino NANO (connecté à un écran SSD1306 et à un INA219) qui a pour objectif de surveiller l'état de la batterie qui compose la powerbank de notre produit.

Pour ce faire j'avais besoin d'afficher un indicateur de batterie, un pourcentage de charge ainsi que de montrer combien de temps il reste avant la décharge totale de la batterie.

## Liste des matériaux
- Écran OLED SSD1306
- INA219
- Arduino NANO 3.0

## Conception
Afin de concevoir un code complet répondons à tous les besoins j'ai dû me renseigner afin pouvoir utiliser des Libs que je ne connaissais pas :
- https://www.instructables.com/Fun-With-OLED-Display-and-Arduino/ //Tuto de la Lib ADAFRUIT_SSD1306
- https://projetsdiy.fr/capteur-ina219-mesurer-puissance-dun-panneau-solaire-batterie-arduino-esp8266/ //Tuto de la Lib ADAFRUIT_INA219 et Wire.h
- https://learn.adafruit.com/low-power-wifi-datalogging/battery-life-and-current-consumption & https://forum.arduino.cc/t/ina219-measuring-solar-panel-and-battery-please-help/301168/2 //Liens utiles pour la compréhension de prise de mesures et des calcules que l'on peut faire avec l'INA219

## Défis
Une fois après avoir lu les différentes documentations et les liens utiles je me suis mis au travail et j'ai développé les fonctions nécessaires à la réalisation du produit :

- _**Indicateur de batterie**_ : J'ai créé un rectangle de 12 pixels de hauteurs dont deux sont utilisé pour délimiter la batterie, on se retrouve ainsi avec un squelette de batterie qui a 10 pixel de hauteurs à combler. J'ai décidé de diviser notre pourcentage de batterie par 10 pour obtenir une valeur entre 0 et 10, ainsi on rajoute une barre pour chacune de ces valeurs, EXEMPLE : 60% = 6 barres dans l'indicateur. En plus de ça on rajoute 0.5 a notre valeur pour arrondir au supérieur, ainsi si on est à 67% on affichera 6,7+0,5 barres soit 7 barres.
- _**Pourcentage de batterie**_ : Pour afficher le pourcentage de batterie j'ai tout simplement choisi d'afficher le nombre (en nombre à virgule FLOAT) au-dessus de l'indicateur de batterie.
- _**Temps restants**_ : Malheureusement, par manque de temps (ou de travail) le circuit électronique de la powerbank n'a pas pu être fini, par conséquent j'ai dû m'adapter afin de proposer un code fonctionnel dans notre cas (sans circuit) et dans un cas plus idéal (avec un circuit qui marche). J'ai donc calculé combien notre circuit consommé THÉORIQUEMENT (331 milli-Ampére) puis j'ai pris en compte la capacité de la batterie que nous utilisions (1800 milli-Ampére heures), suite à quoi j'ai fait le rapport 1800/331 = 5.44 heures. Ainsi on sait que THÉORIQUEMENT la batterie devrait durer 5.44 heures. J'ai ainsi rajouté un coefficient au rapport en faisant Pourcentage_Batterie/100, ainsi qu'on on est à 100% on aura un coefficient de un et donc THÉORIQUEMENT il nous restera 5.44 heures d'utilisation. Dans la même idée si on est à 50% on aura un coefficient de 0,5 et donc THÉORIQUEMENT il nous restera 2.72 heures d'utilisation et on peut faire cela avec tous les pourcentages de batterie ; EXEMPLE : 25%/100 = 1.36 heure , 10% = 0,54 heure , 60% = 3.26 , etc. Cette méthode est assez ingénieuse et ne requiert pas de scan constant (seulement un rafraîchissement de la valeur) mais malheureusement elle perd toute précision si on n'utilise pas la même capacité de batterie et / ou si on consomme plus d'électricité.

## Inconvéniant et améliorations
Comme dit précédemment, le circuit électronique n'étant pas fini j'ai dû m'adapter. J'ai fini par créer un mode de test qui est activée par défaut dans le code, pour la désactiver il faut mettre le booléen test en FALSE.

Voici les différentes améliorations que j'aurais pu mettre :
- Rajouté le logo que j'ai fait à l'allumage du programme
- Rajouté un mode veille à l'aide d'un bouton et/ou d'un accélérometre (Secouez pour réveiller l'appareil)
- Rajouté des valeurs plus "scientifique" dans un menu alternatif accesible avec un bouton afin d'aider à trouver et déboguer le circuit électronique (Intensité, Courant, Puissance, ect..)
- Rajouté un menu qui permet de changer l'intensité qui sort de la powerbank afin de gerer l'intensité de la lampe.

## Travail bonus
En plus du code que j'ai fait j'ai aider à l'élaboration de différents produits créatif concernant le Projet Ayyur, comme le nom Ayyur, le Logo du Projet et du Produit de mon groupe et le poster du Projet.
