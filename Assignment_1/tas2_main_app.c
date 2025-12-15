#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>  // Для dlopen, dlsym, dlclose

// Структура результата, совпадает с библиотекой
typedef struct {
    double x;
    double y;
    double z;
    size_t line_number;
    double distance;
} PointResult;

// Тип функции из библиотеки
typedef PointResult (*FindFarthestPointFunc)(const char *);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <shared_library.so> <input_file>\n", argv[0]);
        return 1;
    }

    const char *lib_path = argv[1];
    const char *input_file = argv[2];

    // Загружаем библиотеку
    void *handle = dlopen(lib_path, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Error loading library: %s\n", dlerror());
        return 1;
    }

    // Получаем указатель на функцию
    FindFarthestPointFunc find_farthest_point = (FindFarthestPointFunc)dlsym(handle, "find_farthest_point");
    char *error;
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "Error finding symbol: %s\n", error);
        dlclose(handle);
        return 1;
    }

    // Вызываем функцию
    PointResult result = find_farthest_point(input_file);

    // Выводим результат
    printf("Processing file: %s\n", input_file);
    printf("Farthest point found at line %zu\n", result.line_number);
    printf("Coordinates: x=%.6lf y=%.6lf z=%.6lf\n", result.x, result.y, result.z);
    printf("Distance from origin: %.6lf\n", result.distance);

    // Закрываем библиотеку
    dlclose(handle);

    return 0;
}
