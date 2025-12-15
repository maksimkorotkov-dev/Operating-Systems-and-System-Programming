#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

typedef struct {
    double x, y, z;
    size_t line_number;
    double distance;
} PointResult;

PointResult find_farthest_point(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("fstat");
        exit(EXIT_FAILURE);
    }

    size_t filesize = st.st_size;
    char *data = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    size_t line_number = 0;
    size_t max_line = 0;
    double max_distance = -1.0;
    double x, y, z;
    char *ptr = data;
    char *end = data + filesize;

    while (ptr < end) {
        if (sscanf(ptr, "%lf %lf %lf", &x, &y, &z) == 3) {
            line_number++;
            double distance = sqrt(x*x + y*y + z*z);
            if (distance > max_distance) {
                max_distance = distance;
                max_line = line_number;
            }
        }

        // Переходим к следующей строке
        char *next_line = strchr(ptr, '\n');
        if (!next_line) break;
        ptr = next_line + 1;

        // Вывод прогресса каждые 100000 строк
        if (line_number % 1000 == 0) {
            printf("Processed %zu lines...\n", line_number);
            fflush(stdout);
        }
    }

    munmap(data, filesize);
    close(fd);

    PointResult result;
    result.line_number = max_line;
    result.distance = max_distance;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}
