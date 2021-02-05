# E-Dictionary En c

- *Version 1.0*
- *2018 - 2019*

## Author : SADI Amayas

- Ce projet représent un dictionnaire de mots en anglais, programmé en C.

Description

*Le dictionnaire se base sur deux fonctions de hachages qui permettent d'obtenir une recherche et un ajout en o(1), il y a une pré-selection sur la premiere lettre du mot ensuite la premiere fonction de hachage permet de séparrer les mots (jusqu'à deux collisions - soit 3 mots qui ont la même valeur - ) en résumé la fonction concatene les codes de chaque lettre (et garde le module à chaque iteration) et la deuxieme fonction est une simple fonction qui permet de séparer les 3 mots restants*

## Fonctionnalités :
- Generer un E-dictionnaire depuis un fichier de mots (le fichier fourni contient 86037 mots)
- Permet de rechercher des mots
- Ajouter des mots
- De supprimer de mots

## TO-DO : 
- [ ] Ajout de fonction de suggestion (En-cours)
- [ ] Améliorer la structure
- [ ] Passer sur une interface graphique
