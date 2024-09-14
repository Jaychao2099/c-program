# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <stdbool.h>
# define MAXROW 1000
# define MAXCOL 1000

// 垂直移動, 水平移動
typedef struct offsets{
    int vert;
    int horiz;
}offsets;

// 走過的路 {row, col, way}
typedef struct item{
    int row;
    int col;
    int way;
}item;

// 迷宮結構
typedef struct MazeStruct{
    int **maze;
    int row_size;
    int col_size;
    int sr, sc; //start row, start col
    int er, ec; //end row, end col
}MazeStruct;

void print_path(const MazeStruct *m, int **mark){
    for(int i = 1; i <= m->row_size; i++){
        printf("[");
        for(int j = 1; j <= m->col_size; j++){
            if (mark[i][j] == 1) printf("\033[41;30m1 \033[0m");
            else printf("%d ", m->maze[i][j]);
        }
        printf("] %d\n", i);
    }
}

void print_maze(const MazeStruct *m){
    for(int i = 1; i <= m->row_size; i++){
        printf("[");
        for(int j = 1; j <= m->col_size; j++) printf("%d ", m->maze[i][j]);
        printf("]\n");
    }
    printf("\n");
}

void GenerateMaze(MazeStruct *m){
    m->maze = malloc((m->row_size + 2) * sizeof(int *));
    for (int i = 0; i < m->row_size + 2; i++) m->maze[i] = calloc(m->col_size + 2, sizeof(int));
    srand(time(0));
    for(int i = 1; i <= m->row_size; i++)
        for(int j = 1; j <= m->col_size; j++)
            m->maze[i][j] = rand() % 2;
    m->maze[m->sr][m->sc] = m->maze[m->er][m->ec] = 1;    // 初始化起點, 終點 = 1
    return;
}

// dir = 0_N, 1_NE, 2_E, 3_SE, 4_S, 5_SW, 6_W, 7_NW
void path(const MazeStruct *m, const int start_dir){
    int **mark= malloc((m->row_size + 2)* sizeof(int *));      // 紀錄有無走過
    for (int i = 0; i < m->row_size + 2; i++) mark[i] = calloc(m->col_size + 2, sizeof(int));
    
    offsets move[8] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};   // 設定 direction
    
    item *stack = malloc(m->row_size * m->col_size * sizeof(item));   // 製作 stack
    int top = -1;
    
    item temp = {m->sr, m->sc, start_dir};
    stack[++top] = temp;    // push 起點

    mark[m->sr][m->sc] = 1; // 起點標記為已訪問
    while (top > -1){       // stack not empty
        temp = stack[top--];
        int i = temp.row, j = temp.col, d = temp.way;
        while (d < 8){      // 往下一格移動
            int v = i + move[d].vert, h = j + move[d].horiz;
            if (v == m->er && h == m->ec) print_path(m, mark);   // 結束 印出path
            if (v > 0 && v <= m->row_size && h > 0 && h <= m->col_size && m->maze[v][h] && !mark[v][h]){   // 移動合法 + 沒有去過
                mark[v][h] = 1;
                temp.row = i; temp.col = j; temp.way = d + 1;
                stack[++top] = temp;
                i = v; j = h; d = 0;
            }
            else d++;
        }
    }
    printf("No path found\n");  // stack empty
    print_path(m, mark);   // 結束 印出path

    for (int i = 0; i < m->row_size + 2; i++) free(mark[i]);
    free(mark);
    free(stack);
    return;
}

int main(){
    MazeStruct M;
    char mode;
    do {
        printf("Enter maze size (split by 'space'): ");
        if (scanf("%d%d", &M.row_size, &M.col_size) != 2){    // Clear input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("ERROR: invalid input. Please enter two numbers: ");
        } else if (M.row_size < 1 || M.row_size > MAXROW || M.col_size < 1 || M.col_size > MAXCOL){
            printf("ERROR: invalid number. Must be (1 ~ %d) * (1 ~ %d)\n", MAXROW, MAXCOL);
        } else break;
    } while (1);
    setbuf(stdin, '\0');    //清空 stdin
    M.sr = 1, M.sc = 1, M.er = M.row_size, M.ec = M.col_size;     // 0 保留作邊界
    printf("WNAT TO CHANGE the defult start point (1,1) and end point(%d,%d)? (y/n)", M.row_size, M.col_size);
    scanf("%c", &mode);
    if (mode == 'y' || mode =='Y'){
        do {
            printf("Enter start point and end point (split by 'space'): ");
            if (scanf("%d%d%d%d", &M.sr, &M.sc, &M.er, &M.ec) != 4){    // Clear input buffer
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                printf("ERROR: invalid input. Please enter four numbers\n");
            } else if (M.sr < 1 || M.sr > M.row_size ||
                        M.sc < 1 || M.sc > M.col_size ||
                        M.er < 1 || M.er > M.row_size ||
                        M.ec < 1 || M.ec > M.col_size)
                printf("ERROR: invalid number. Must between (1,%d) and (%d,%d)\n", M.col_size, M.row_size, M.col_size);
            else break;
        } while (1);
    }
    GenerateMaze(&M);
    //print_maze(&M);
    path(&M, 2);

    for (int i = 0; i < M.row_size + 2; i++) free(M.maze[i]);
    free(M.maze);
    
    return 0;
}