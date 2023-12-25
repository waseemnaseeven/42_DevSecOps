# WRITE FREE, MALLOC AND REALLOC FUNCTIONS IN C

======

## COMPREHENSION DU SUJET :

les fonctions
le cadre/plan
les tests unitaires

### mmap/munmap

- Les fonctions `mmap` et `munmap` sont utilisées pour créer et supprimer des mappings mémoire, respectivement. Ces fonctions sont souvent utilisées pour la gestion avancée de la mémoire dans les programmes C, notamment lors de l'allocation et de la libération de mémoire de manière personnalisée.

```c
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);

void *ptr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
```

- `mmap` crée un nouveau mapping dans l'espace d'adressage virtuel du processus appelant.
addr spécifie l'adresse de départ du nouveau mapping. Si addr est NULL, le noyau choisit l'adresse (alignée sur une page) où créer le mapping.
- `addr` spécifie l'adresse de départ du nouveau mapping. Si addr est NULL, le noyau choisit l'adresse (alignée sur une page) où créer le mapping.
- `length` spécifie la longueur du mapping.
- `prot` décrit la protection mémoire désirée pour le mapping.
- `flags` détermine si les mises à jour du mapping sont visibles pour d'autres processus et si elles sont reportées dans le fichier sous-jacent.
- `fd` est le descripteur de fichier du fichier (ou autre objet) à mapper.
- `offset` est le décalage dans le fichier où commence le mapping.

Attributs de Protection (prot)
PROT_EXEC: Autorise l'exécution de code dans la zone mémoire.
PROT_READ: Autorise la lecture de la zone mémoire.
PROT_WRITE: Autorise l'écriture dans la zone mémoire.
PROT_NONE: Zone mémoire inaccessible.

```c
int munmap(void *addr, size_t length);

munmap(ptr, 4096);
```

- `munmap` supprime les mappings pour la plage d'adresses spécifiée.
- `addr` est l'adresse de départ du mapping à supprimer.
- `length` est la longueur de la plage à désallouer.


