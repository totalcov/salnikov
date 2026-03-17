#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define N 10
#define INF INT_MAX

void init_rng() {
    time_t curtime;
    time(&curtime);
    srand((unsigned int)curtime);
    rand(); rand(); rand();
}   

int gen_rnd_int() {
    return rand() % 100;
}

// Функция для преобразования координат в индекс вершины
int coord_to_index(int i, int j) {
    return i * N + j;
}

// Функция для преобразования индекса вершины в координаты
void index_to_coord(int index, int *i, int *j) {
    *i = index / N;
    *j = index % N;
}

// Алгоритм Дейкстры для поиска кратчайшего пути (8 направлений)
void dijkstra(int mat[N][N], int start_i, int start_j, int end_i, int end_j) {
    int total_nodes = N * N;// Всего вершин в графе
    int dist[total_nodes];// Минимальные расстояния от старта до каждой вершины
    int visited[total_nodes];// Посещенные вершины (0-не посещена, 1-посещена)
    int prev[total_nodes];// Предыдущая вершина на кратчайшем пути
    
    // Инициализация
    for (int i = 0; i < total_nodes; i++) {
        dist[i] = INF;
        visited[i] = 0;
        prev[i] = -1;
    }
    
    int start_index = coord_to_index(start_i, start_j);
    dist[start_index] = mat[start_i][start_j];
    
    for (int count = 0; count < total_nodes - 1; count++) {
        // Находим вершину с минимальным расстоянием
        int min_dist = INF;
        int u = -1;
        
        for (int v = 0; v < total_nodes; v++) {
            if (!visited[v] && dist[v] < min_dist) {
                min_dist = dist[v];
                u = v;
            }
        }
        
        if (u == -1 || u == coord_to_index(end_i, end_j)) break;
        
        visited[u] = 1;
        
        // Получаем координаты текущей вершины
        int u_i, u_j;
        index_to_coord(u, &u_i, &u_j);
        
        // 8 направлений движения: 4 основных + 4 диагональных
        int directions[8][2] = {
            {-1, 0},  // ВВЕРХ
            {1, 0},   // ВНИЗ
            {0, -1},  // ВЛЕВО
            {0, 1},   // ВПРАВО
            {-1, -1}, // ВВЕРХ-ВЛЕВО
            {-1, 1},  // ВВЕРХ-ВПРАВО
            {1, -1},  // ВНИЗ-ВЛЕВО
            {1, 1}    // ВНИЗ-ВПРАВО
        };
        
        for (int d = 0; d < 8; d++) {
            int v_i = u_i + directions[d][0];
            int v_j = u_j + directions[d][1];
            
            // Проверяем границы матрицы
            if (v_i >= 0 && v_i < N && v_j >= 0 && v_j < N) {
                int v = coord_to_index(v_i, v_j);
                
                if (!visited[v] && dist[u] != INF && 
                    dist[u] + mat[v_i][v_j] < dist[v]) {
                    dist[v] = dist[u] + mat[v_i][v_j];
                    prev[v] = u;
                }
            }
        }
    }
    
    int end_index = coord_to_index(end_i, end_j);
    
    if (dist[end_index] == INF) {
        printf("\nПуть не найден!\n");
        return;
    }
    
    // Восстанавливаем путь
    int path[total_nodes];
    int path_length = 0;
    int current = end_index;
    
    while (current != -1) {
        path[path_length++] = current;
        current = prev[current];
    }
    
    // Выводим результат
    printf("\nКратчайший путь от (%d,%d) до (%d,%d):\n", start_j, start_i, end_j, end_i);
    printf("Сумма весов: %d\n", dist[end_index]);
    printf("Путь: ");
    
    for (int i = path_length - 1; i >= 0; i--) {
        int i_pos, j_pos;
        index_to_coord(path[i], &i_pos, &j_pos);
        printf("(%d,%d)", j_pos, i_pos);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
    
    // Визуализация пути в матрице
    printf("\nМатрица с путем (X - элементы пути):\n");
    int path_cells[total_nodes];
    for (int i = 0; i < total_nodes; i++) path_cells[i] = 0;
    
    for (int i = 0; i < path_length; i++) {
        path_cells[path[i]] = 1;
    }
    
    for (int i = 0; i < N; i++) {
        printf("| ");
        for (int j = 0; j < N; j++) {
            if (path_cells[coord_to_index(i, j)]) {
                printf(" X ");
            } else {
                printf("%3d", mat[i][j]);
            }
        }
        printf(" |\n");
    }
}

int main() {
    int mat[N][N];
    
    init_rng();
    
    // Заполняем матрицу случайными числами
    printf("Матрица весов:\n");
    for (int i = 0; i < N; i++) {
        printf("| ");
        for (int j = 0; j < N; j++) {
            mat[i][j] = gen_rnd_int();
            printf("%3d", mat[i][j]);
        }
        printf(" |\n");
    }
    
    // Выбираем случайные старт и конец
    int start_i = gen_rnd_int() % N;
    int start_j = 0;  // Первый столбец
    int end_i = gen_rnd_int() % N;
    int end_j = N - 1;  // Последний столбец
    
    printf("\nСтарт: элемент (%d,%d) = %d", start_j, start_i, mat[start_i][start_j]);
    printf("\nКонец: элемент (%d,%d) = %d", end_j, end_i, mat[end_i][end_j]);
    
    // Находим кратчайший путь
    dijkstra(mat, start_i, start_j, end_i, end_j);
    
    return 0;
}