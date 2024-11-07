# Cheat Sheet : Terminal (Mac & Linux)

## Navigation dans le terminal
| Action                          | Raccourci                    |
|---------------------------------|------------------------------|
| Accéder au début de la ligne    | `Ctrl + A`                   |
| Accéder à la fin de la ligne    | `Ctrl + E`                   |
| Effacer la ligne entière        | `Ctrl + U`                   |
| Effacer de la position au début | `Ctrl + W`                   |
| Effacer du curseur à la fin     | `Ctrl + K`                   |
| Passer au mot précédent         | `Option + B` ou `Alt + B`    |
| Passer au mot suivant           | `Option + F` ou `Alt + F`    |
| Ouvrir un nouveau terminal      | `Cmd + N` (Mac) / `Ctrl + Shift + N` (Linux) |

## Gestion de commandes
| Action                          | Raccourci                    |
|---------------------------------|------------------------------|
| Annuler la commande             | `Ctrl + C`                   |
| Suspendre le processus          | `Ctrl + Z`                   |
| Reprendre un processus          | `fg`                         |
| Répéter la dernière commande    | `!!`                         |
| Parcourir l'historique          | `history` ou `↑ / ↓`         |

### Commandes associées
| Action                          | Commande                     |
|---------------------------------|------------------------------|
| Afficher l'historique complet   | `history`                    |
| Exécuter une commande de l'historique | `!<numéro>`             |
| Tuer un processus par son ID    | `kill <PID>`                 |
| Lancer un processus en arrière-plan | `command &`             |

## Édition de commandes
| Action                          | Raccourci                    |
|---------------------------------|------------------------------|
| Supprimer le caractère précédent| `Ctrl + H` ou `Backspace`    |
| Supprimer le mot précédent      | `Ctrl + W`                   |
| Supprimer le caractère suivant  | `Ctrl + D`                   |
| Supprimer le mot suivant        | `Alt + D`                    |
| Transposer deux caractères      | `Ctrl + T`                   |
| Changer en majuscules           | `Alt + U`                    |
| Changer en minuscules           | `Alt + L`                    |

## Manipulation des fenêtres du terminal
| Action                          | Raccourci                    |
|---------------------------------|------------------------------|
| Ouvrir un nouvel onglet terminal | `Cmd + T` (Mac) / `Ctrl + Shift + T` (Linux) |
| Diviser la fenêtre (Tilix)      | `Ctrl + Shift + O` (horizontal) / `Ctrl + Shift + E` (vertical) |
| Passer d'un onglet à l'autre    | `Cmd + Shift + ]` ou `Cmd + Shift + [` (Mac) / `Ctrl + PageUp/PageDown` (Linux) |
| Fermer un onglet                | `Cmd + W` (Mac) / `Ctrl + Shift + W` (Linux) |

## Commandes pour consulter le système
| Action                          | Commande                     |
|---------------------------------|------------------------------|
| Afficher les processus actifs   | `ps aux`                     |
| Afficher l'utilisation des ressources | `top` ou `htop`         |
| Afficher l'espace disque        | `df -h`                      |
| Afficher la mémoire disponible  | `free -h`                    |
| Afficher l'adresse IP           | `ifconfig` ou `ip a`         |

