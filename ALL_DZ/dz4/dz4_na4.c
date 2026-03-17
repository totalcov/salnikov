# include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define NN N*N
#define B 10000
#define GOR 50000

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


int dist[NN];
int visit[NN];
void gl(int mat[N][N], int dist[NN], int visit[NN], int  start, int end ){
     init_rng();
    int move[4][2] = {{-1,0}, {1,0},{0,-1},{0,1}};

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (mat[i][j] == GOR) dist[cord_index(i,j)] = GOR;
            else dist[cord_index(i,j)] = B;
            visit[cord_index(i,j)]= 0;
        }
    }

    int start_ind = cord_index(start, 0);
    if(dist[start_ind] == GOR){
        printf(" \n В НАЧАЛЕ ПУТИ СТОИТ ПРЕПЯТСВИЕ \n");
        return ;
    }
    else dist[start_ind] = 0;

    for (int count = 0; count <  NN;  count++){
        int min = B;
        int u = -1;

        for (int v = 0; v < NN; v++){
            if (dist[v] != GOR){
            if (visit[v] == 0 && dist[v] < min){
                min = dist[v];
                u = v;
            }}
        }

        if (u == -1) break;
        visit[u] = 1;

        int u_i, u_j;

        index_cord(u, &u_i, &u_j);

        for (int d = 0; d< 4; d++){
            int v_i = u_i + move[d][0];
            int v_j = u_j + move[d][1];

            if (v_i >= 0 && v_i < N && v_j >= 0 &&v_j < N){

                int v = cord_index(v_i, v_j);
                if (visit[v] == 0 &&  (dist[u] + 1 < dist[v] && dist[v]!= GOR) ){
                    dist[v] = dist[u] + 1;
                }
            }
        }
    }
    int end_ind = cord_index(end, 9);
    if (dist[end_ind] == GOR){
        printf(" \n НА ФИНАЛЕ ПУТИ СТОИТ ГОРА \n");
        return ;
    }
    if (dist[end_ind] == B){
        printf(" \n построить маршрут невозможно \n");
        return ;
    }
    
    for (int i = 0; i < N; i ++){
        printf(" |");
        for (int j = 0; j < N; j++){
            if (dist[cord_index(i,j)] == GOR)printf("  #");
            else printf(" %2d",dist[cord_index(i,j)]);
        }
        printf("  | \n");
    }
    
    int obr[NN] = {0};
    int start_obr = end_ind;
    


}

int main(){
    int mat[N][N];
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++) mat[i][j] = 0;
    }

    for (int i = 0; i< 20; i++){
        mat[gen_rnd_int()%10][gen_rnd_int()%10] = GOR;
    }

    int start = gen_rnd_int() %10;
    int end = gen_rnd_int() %10;
    printf("СТАРТ (%d, 0) \n", start);
    printf("КОНЕЦ (%d, 9) \n", end);

    for (int i = 0; i < N; i ++){
        printf("| ");
        for (int j = 0; j < N; j ++){
            if (mat[i][j] == GOR){
                printf("# ");
            }
            else printf("%d ", mat[i][j]);
        }
        printf(" |  \n");

    }
    printf("\n");

    gl(mat, dist, visit, start, end);
    return 0;

}