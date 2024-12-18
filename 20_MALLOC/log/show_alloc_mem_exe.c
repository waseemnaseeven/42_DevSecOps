#include "../includes/malloc.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>



void ft_putchar_fd(char c, int fd) {
    write(fd, &c, 1);
}

void ft_putnbr_fd(int n, int fd)
{
    char buf[32];
    int len = 0;
    if (n == -2147483648) {
        write(fd, "-2147483648", 11);
        return;
    }
    if (n < 0) {
        write(fd, "-", 1);
        n = -n;
    }
    if (n == 0) {
        write(fd, "0", 1);
        return;
    }
    while (n > 0 && len < 31) {
        buf[len++] = (n % 10) + '0';
        n /= 10;
    }
    for (int i = len - 1; i >= 0; i--) {
        write(fd, &buf[i], 1);
    }
}

/// Print an address in hexadecimal format (ex: 0x7ffee3c0a9b0)
static void print_address_hex(size_t value) {
    char hex[16] = "0123456789abcdef";
    char buffer[32]; 
    int i = 0;

    if (value == 0) {
        write(1, "0x0", 3);
        return;
    }

    while (value > 0 && i < 32) {
        buffer[i++] = hex[value % 16];
        value /= 16;
    }
    write(1, "0x", 2);
    while (i > 0) {
        write(1, &buffer[--i], 1);
    }
}

/// Print a memory block in hexadecimal format, 16 bytes per line
static void print_block_hex(void *block_start, size_t size) {
    unsigned char *ptr = (unsigned char *)block_start;
    size_t i = 0;
    char buf[256];

    while (i < size) {
        if (i % 16 == 0) {
            if (i > 0) {
                write(1, "\n", 1);
            }
            // Print address
            print_address_hex((size_t)(ptr + i));
            write(1, ": ", 2);
        }

        snprintf(buf, sizeof(buf), " %02x", ptr[i]);
        write(1, buf, strlen(buf));
        i++;
    }
    write(1, "\n", 1);
}

/// Retourne le nom du groupe en fonction de t_heap_group
static const char *get_group_name(t_heap_group group) {
    if (group == TINY)
        return "TINY";
    else if (group == SMALL)
        return "SMALL";
    else
        return "LARGE";
}

/// Affiche toutes les heaps et blocs d'un type donné (TINY, SMALL ou LARGE)
/// Le paramètre 'dump' indique s'il faut afficher l'hexdump des blocs alloués.
static void print_zone(const char *zone_name, size_t *total, char dump)
{
    t_heap *heap = g_heap;
    int zone_printed = 0;
    char buf[256];

    while (heap) {
        const char *heap_name = get_group_name(heap->group);
        if (strlen(heap_name) == strlen(zone_name) && strncmp(heap_name, zone_name, strlen(zone_name)) == 0) {
            // Afficher la heap
            int len = snprintf(buf, sizeof(buf), "%s : ", zone_name);
            write(1, buf, len);
            print_address_hex((size_t)heap);
            write(1, "\n", 1);

            t_block *block = heap->blocks;
            int i = 0;
            while (block) {
                void *block_start = (void *)BLOCK_SHIFT(block);
                void *block_end = (void *)((char *)block_start + block->size);

                // i - numéro de bloc
                // Si freed -> vert, sinon rouge
                i++;
                snprintf(buf, sizeof(buf), "%d - ", i);
                write(1, buf, strlen(buf));
                if (block->freed) {
                    write(1, "\033[0;32m", 7);
                } else {
                    *total += block->size;
                    write(1, "\033[0;31m", 7);
                }

                // Adresse début - fin + taille
                write(1, "", 0);
                print_address_hex((size_t)block_start);
                write(1, " - ", 3);
                print_address_hex((size_t)block_end);
                snprintf(buf, sizeof(buf), " : %zu bytes\n", block->size);
                write(1, buf, strlen(buf));

                write(1, "\033[0m", 4); // Reset color

                if (dump && !block->freed) {
                    print_block_hex(block_start, block->size);
                }
                block = block->next;
            }
            zone_printed = 1;
        }
        heap = heap->next;
    }

    // Même si aucune heap de ce type n'a été trouvée, on affiche le titre
    // avec une ligne vide.
    if (!zone_printed) {
        snprintf(buf, sizeof(buf), "%s : \n", zone_name);
        write(1, buf, strlen(buf));
    }
}

/// Affiche l'intro et appelle print_zone pour chaque zone (TINY, SMALL, LARGE)
static void intro_print_zone(char dump)
{
    char buf[256];
    write(1, "--------------------------------\n", 33);
    if (dump) {
        write(1, "🔋 Memory hexdump \n", 22);
    } else {
        write(1, "🔋 Memory allocations \n", 26);
    }

    size_t total_memory = 0;

    print_zone("TINY", &total_memory, dump);
    print_zone("SMALL", &total_memory, dump);
    print_zone("LARGE", &total_memory, dump);

    snprintf(buf, sizeof(buf), "Total : %zu bytes\n", total_memory);
    write(1, buf, strlen(buf));

    write(1, "--------------------------------\n", 33);
}

// Fonction pour afficher les allocations mémoire (sans hexdump)
void show_alloc_mem()
{
    pthread_mutex_lock(&g_malloc_mutex);
    intro_print_zone(0);
    pthread_mutex_unlock(&g_malloc_mutex);
}

// Fonction pour afficher les allocations mémoire avec hexdump
void show_alloc_mem_ex(void)
{
    pthread_mutex_lock(&g_malloc_mutex);
    intro_print_zone(1);
    pthread_mutex_unlock(&g_malloc_mutex);
}
