# Animation 3D Project
## Mini-golf
>Authors:
>* Mathéo DUCROT 
>* Nicolas MULLER

### Description
This project is a mini-golf game. The player can move the ball with the mouse and the keyboard. The goal is to put the ball in the hole with the fewer strokes possible.

### How to play
* **Select the direction**: Use the mouse to move the camera. The ball will move in the direction of the camera.
* **Shoot the ball**: Use the `Shift` button to shoot the ball.

### How to build
```bash
cd scenes/scene1
mkdir build
cd build
cmake ..
make
./scene1
```
# Les solutions mises en place
Nous nous sommes basé sur l'exercice 3 de la série de TP pour commencer notre projet. Nous avons donc repris la structure de base du projet et nous avons ajouté les fonctionnalités nécessaires à la réalisation de notre mini-golf.

## Gestion des objets
Nous avons d'abord créé tous les objets nécessaires pour faire nortre scènes. Nous avons donc créé les objets suivants:
* **Le sol et les murs**: Ce sont des quadrialtères qui sont placés à des positions précises dans la scène.
* **La balle**: C'est une sphère qui est placée sur la position de départ.
* **Les obstacles mobiles**: Ce sont des sphères qui sont placées à des positions précises dans la scène. Elles sont mobiles et bougent en fonction du temps. Elles ne peuvent pas être bougées par le joueur.
* **Les cylindres**: Ce sont des cylindres qui sont placés à des positions précises dans la scène. Ils ne peuvent pas être bougés par le joueur.

## Création de la scène
Nous avons ensuite créé la scène. Nous avons donc placé les objets dans la scène et nous avons ajouté des couleurs pour un rendu visuel plus agréable.
La scène est composée des élements suivants:
* Une zone d'apparition de la balle partiellement emmurée
* Une legere pente pour que la balle puisse rouler
* Plusieurs virages à 90° avec des murs en diagonale pour pouvoir rebondir dessus et arriver à la cible en moins de coups
* Un creux qui necessite une certaine puissance pour pouvoir en sortir
* Plusieurs obstacles mobiles qui demandent de tirer au bon moment, ajoutant de la difficulté au jeu
* Une cible qui termine le niveau

## Gestion des mouvements
### Mouvement de la balle
Pour le mouvement de la balle, nous avons repris le principe de l'exercice 3 du TP. Nous actualisons la position grâce à la vitesse et la gravité. Nous multiplions cette vitesse par le temps entre deux frames pour un rendu plus fluide. De plus, nous avons ajouté un moyen de donner une impulsion à la balle pour pouvoir la relancer à chaque coups.

### Mouvement des obstacles
Pour le mouvement des obstacles, nous avons utilisé le même principe que pour la balle, mais avons utilisé des fonctions trigonométriques pour faire des mouvements périodiques. Nos obstacles ne sont pas attirés par la gravité

## Gestion des collisions
### Collision avec les murs
Nos murs étant des quadrilatères définis uniquement par les coordonnées de leurs sommets, nous avons dû créer une fonction qui permet de savoir si un point est dans un quadrilatère. Pour cela, nous avons utilisé la méthode suivante:
* Nous avons calculé la normale au quadrilatère en utilisant le prodiut vectoriel
* Grâce à un projeté orthogonal, nous avons calculé la distance entre le point et le plan sur lequel se trouve le quadrilatère
* Pour savoir si la collision à lieu avec le quadrilatere, nous calculons la vecteur entre le point et un des sommets du quadrilatère. Nous exprimons ensuite ce vecteur comme une combinaison linéaire des vecteurs des côtés du quadrilatère. Si les coefficients de cette combinaison linéaire sont tous entre 0 et 1, alors le point est dans le quadrilatère.

### Collision avec les spheres
Tout comme dans le TP, les collisions entre spheres ont été gérées en comparant la distance entre les centres des deux spheres avec la somme de leurs rayons. Si la distance est inférieure à la somme des rayons, alors les deux spheres sont en collision.

### Collision avec les cylindres
Pour les cylindres, nous avons utilisé le même principe que pour les murs. Nous avons calculé la distance entre le centre de la balle et l'axe sur lequel se trouve le cylindre grâce à un projeté orthogonal. Si cette distance est inférieure à la somme du rayon de la balle et du rayon du cylindre, alors il y a collision. De plus, nous avons ajouté une condition pour savoir si la balle est dans la hauteur du cylindre. Pour cela, nous utlisons le projeté othogonal calculé précedemment et le comparons avec l'axe du cylindre. Si le produit scalaire est compris entre 0 et la hauteur du cylindre, alors la balle est dans la hauteur du cylindre. 


Dans le cas d'une collisions, nous changons la vitesse par son symmetrique par rapport à la normale à la surface rencontrée. Cela permet de simuler un rebond.

## Gestion de la camera
Nous avons repris la camera de l'exercice 3 du TP. Nous avons ajouté un déplacement de la caméra lorsque l'on frappe dans la balle et que celle-ci s'immobilise. Cela permet de voir la balle s'éloigner et de pouvoir la suivre pour le tir suivant.

## Gestion des inputs
