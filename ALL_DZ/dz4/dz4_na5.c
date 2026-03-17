# include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define total_nodes  N*N

void init_rng() {
    time_t curtime;
    time(&curtime);
    srand((unsigned int)curtime);
    rand(); rand(); rand();
}   

int gen_rnd_int() {
    return rand() % 100 ;
}

int cord_index(int i, int j){
    return i*N + j;
}
void index_cord(int index, int *i, int *j){
    *i = index /N;
    *j = index %N;
}

void gl(int mat[N][N], int start_i, int start_j, int end_i, int end_j){
//    int total_nodes = N*N;
    int dist[total_nodes]; // минимальное растояние от стартра до точки
    int visit[total_nodes]; // проверенна яйчейка или нет
    int pred[total_nodes]; // предыдущая ершина на кратчайшем пути

    int BIG = 1000000;
    for (int i = 0; i < total_nodes; i++){
        dist[i] = BIG;
        visit[i] = 0;
        pred[i] = -1;
    }

    int start_index = cord_index(start_i, start_j);
    dist[start_index] = mat[start_i][start_j];
    
    for (int count = 0; count < total_nodes-1; count++){
        int min_dist = BIG;
        int u = -1;

        for (int v = 0; v < total_nodes; v++){
            if (visit[v] == 0 && dist[v] < min_dist){
                min_dist = dist[v];
                u = v;
            }
        }

        if (u == -1 )
            break;
        visit[u] = 1;
        // тек эл рассмотрения 
        int u_i, u_j;
        index_cord(u, &u_i, &u_j);

        int move[8][2] = {
            {-1,0},
            {1,0},
            {0,1},
            {0,-1},
            {-1,1},
            {-1,-1},
            {1,-1},
            {1,1}
        };

        for (int d = 0; d<8; d++){
            int v_i = u_i + move[d][0];
            int v_j = u_j + move[d][1];

            if (v_i >= 0 && v_i < N && v_j >= 0 &&v_j < N){

                int v = cord_index(v_i, v_j);
                if (visit[v] == 0 &&  dist[u] + mat[v_i][v_j] + 1 < dist[v]){
                    dist[v] = dist[u] + mat[v_i][v_j];
                    pred[v] = u;
                }
            }
        }
    }
    int end_index = cord_index(end_i, end_j);
    if (dist[end_index] == BIG){
        printf("\nПуть не найден\n");
        return ;
    }

    int path[total_nodes];
    int path_l = 0;
    int n_end = end_index;
    printf("\n");
    for (int i = 0; i< N; i++){
        printf("| ");
        for (int j =0; j < N; j ++){
            printf("%5d", dist[cord_index(i,j)]);}
        printf(" |  \n");
    }


    while (n_end != -1){
        path[path_l++] = n_end;
        n_end = pred[n_end];
    }
    printf("\nКратчайший путь от (%d,%d) до (%d,%d): \n", start_i, start_j, end_i, end_j);
    printf("Сумма весов: %d\n ", dist[end_index]);
    printf("Путь: ");

   
   
   
    for (int i = path_l -1; i >= 0; i--){
        int i_pos, j_pos;
        index_cord(path[i], &i_pos, &j_pos);
        printf("(%d,%d)", i_pos, j_pos);
        if (i> 0) printf(" -> ");

   }
   printf("\n");

   printf("Маршрут: \n");
   int pa[total_nodes];
   for (int i = 0; i < total_nodes; i++) pa[i]= 0;

   for (int i = 0; i < path_l; i ++){
    pa[path[i]] = 1;
   }

   for (int i = 0; i < N; i++){
    printf("| ");
    for (int j = 0; j < N; j ++){
        if (pa[cord_index(i, j)]){
            printf(" X ");
        } 
        else{
            printf("%3d", mat[i][j]);
        }
    }
    printf(" |\n");
   }
}

int main(){
    int mat[N][N];
    
    init_rng();
    printf("Матрица весов: \n");
    for (int i = 0; i< N; i++){
        printf("| ");
        for (int j =0; j < N; j ++){
            mat[i][j] = gen_rnd_int();
            printf("%3d", mat[i][j]);}
        printf(" |  \n");
    }

    int start_i = gen_rnd_int() % 10;
    int end_i = gen_rnd_int() % 10;
    int start_j = 0;
    int end_j = N-1;
    
    printf("\nСтарт: элемент (%d,%d) = %d", start_i, start_j, mat[start_i][start_j]);
    printf("\nКонец: элемент (%d,%d) = %d", end_i, end_j, mat[end_i][end_j]);

    gl(mat, start_i, start_j, end_i, end_j);

    return 0;
}