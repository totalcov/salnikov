# include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define BIG 1000000

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
    return i*N +j;
}

void index_cord(int index, int *i, int *j){
    *i = index / N;
    *j = index % N;
}

void gl(int mat[N][N], int start_i, int start_j,int  end_i,int end_j){
    int total = N*N;
    int dist[total];
    int visit[total];
    int pred[total];
    
    int U = 50000;

    for (int i = 0; i < total; i++){
        int ii, jj;
        index_cord(i, &ii, &jj);
        if (mat[ii][jj] != BIG)
            dist[i] = U;
        else dist[i] = BIG;
        
        visit[i] = 0;
        pred[i] = -1;
   
    }
    
    int start_index = cord_index(start_i, start_j);
    if (dist[start_index] == BIG){
        printf("\nПуть не найден, на старте уже гора .... \n");
        return ;
    }
    dist[start_index] = mat[start_i][start_j];
    
    for (int count = 0; count < total; count++){
        int min = BIG;
        int u = -1;

        for (int v = 0; v < total; v++){
            if(dist[v] < min && visit[v] == 0){
                u = v;
                min = dist[v];
            }
        }
        if (u == -1) break;

        visit[u] = 1;

        int u_i, u_j;
        index_cord(u, &u_i, &u_j);
        int move[4][2] = {{-1, 0}, {1,0}, {0, -1}, {0,1}};

        for (int d = 0;  d < 4; d++){
            int v_i = u_i + move[d][0];
            int v_j = u_j + move[d][1];

            if (v_i >= 0 && v_j >= 0 && v_i <= N-1 && v_j <= N-1) {

                int v = cord_index(v_i, v_j);
                if (dist[v] != BIG){
                    if (visit[v] == 0 && dist[u] + 1 < dist[v]){
                        dist[v] = dist[u] + 1;
                        pred[v] = u;
                } }
            }
        }
    }
    int end_index = cord_index(end_i, end_j);
    if (dist[end_index] == U) {
        printf("\nПуть не найден\n");
        return ;
    }
    if (dist[end_index] == BIG) {
        printf("\n На Финале пути находится преграда, путь невозможно пройти... ( \n");
        return ;
    }

    int path[total];
    int path_l = 0;
    int n_end = end_index;

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
   int pa[total];
   for (int i = 0; i < total; i++) pa[i]= 0;

   for (int i = 0; i < path_l; i ++){
    pa[path[i]] = 1;
   }

   for (int i = 0; i < N; i++){
    printf("| ");
    for (int j = 0; j < N; j ++){
        int pp =cord_index(i,j);
        if (pa[cord_index(i, j)] ){
            printf("  X ");
        }  
        else if (mat[i][j] == BIG){
            printf("  # ");
        }
        else if (dist[pp] == U) printf("  0 ");
        else printf(" %2d ", dist[pp]);
    }
    printf(" |\n");
   }
}


int main(){
    int mat[N][N];

    for (int i = 0; i < 20; i++)
        mat[gen_rnd_int()%N][gen_rnd_int()%N] = BIG;

    for (int i = 0; i < N; i ++){
        for (int j = 0; j < N; j ++){
            if (mat[i][j] != BIG) mat[i][j] = 0;
        }
    }

    for (int i = 0; i < N; i ++){
        printf("| ");
        for (int j = 0; j < N; j ++){
            if (mat[i][j] == BIG){
                printf("# ");
            }
            else printf("%d ", mat[i][j]);
        }
        printf(" |  \n");

    }

    int start_i = gen_rnd_int() % N;
    int start_j = 0;
    int end_i = gen_rnd_int() % N;
    int end_j = N-1;
    printf("\nСтарт: элемент (%d,%d)", start_i, start_j);
    printf("\nКонец: элемент (%d,%d)", end_i, end_j);
    gl(mat, start_i, start_j, end_i, end_j);

    return 0;
    
}