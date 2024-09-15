# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
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
    int dir;
}item;

// 迷宮結構
typedef struct MazeStruct{
    int **maze;
    int row_size;
    int col_size;
    int sr, sc; //start row, start col
    int er, ec; //end row, end col
}MazeStruct;

// 選擇方向
typedef struct DirectPriority{
    int start_dir;  // 0 ~ 7
    int clockwise;  // 1 or -1
}DirectPriority;

// 設定優先的方向
DirectPriority DesideStartDir(const int sr, const int sc, const int er, const int ec){
    DirectPriority dp;
    int row_dir = er - sr;
    int col_dir = ec - sc;
    dp.clockwise = 1;       // defult is clockwise
    if (col_dir > 0){
        dp.start_dir = 2;          // end is at right
        if (row_dir < 0) dp.clockwise = -1;     // change to counterclockwise
    }
    else if (col_dir < 0){
        dp.start_dir = 6;     // end is at left
        if (row_dir > 0) dp.clockwise = -1;    // change to counterclockwise
    }
    else {
        if (row_dir > 0) dp.start_dir = 4;      // end is at down
        else dp.start_dir = 0;                  // end is at up
    }
    return dp;
}

void PrintUnsuccessPath(const MazeStruct *m, int **mark){
    for(int i = 1; i <= m->row_size; i++){
        printf("[");
        for(int j = 1; j <= m->col_size; j++){
            if (i == m->sr && j == m->sc) printf("\033[42;30m1 \033[0m");       // 起點
            else if (i == m->er && j == m->ec) printf("\033[44;30m1 \033[0m");  // 終點
            else if (mark[i][j] == 1) printf("\033[41;30m%d \033[0m", m->maze[i][j]);           // 路徑
            else printf("%d ", m->maze[i][j]);          // 非路徑
        }
        printf("] %d\n", i);
    }
}

void PrintPath(const MazeStruct *m, item *stack, int top){
    for(int i = 1; i <= m->row_size; i++){
        printf("[");
        for(int j = 1; j <= m->col_size; j++){
            if (i == m->sr && j == m->sc) printf("\033[42;30m1 \033[0m");       // 起點
            else if (i == m->er && j == m->ec) printf("\033[44;30m1 \033[0m");  // 終點
            else {
                int found = 0;
                for (int k = 0; k <= top; k++){
                    if (i == stack[k].row && j == stack[k].col) found = 1;
                }
                if (found) printf("\033[41;30m%d \033[0m", m->maze[i][j]);  // 路徑
                else printf("%d ", m->maze[i][j]);          // 非路徑
            }
        }
        printf("] %d\n", i);
    }
}

void GenerateMaze(MazeStruct *m){
    m->maze = malloc((m->row_size + 2) * sizeof(int *));
    for (int i = 0; i < m->row_size + 2; i++){
        m->maze[i] = calloc(m->col_size + 2, sizeof(int));
        if (m->maze == NULL || m->maze[i] == NULL){
            printf("ERROR: unable to allocate required memory in GenerateMaze()\n");
            exit(1);
        }
    }
    srand(time(0));
    for(int i = 1; i <= m->row_size; i++)
        for(int j = 1; j <= m->col_size; j++)
            m->maze[i][j] = rand() % 2;
    m->maze[m->sr][m->sc] = m->maze[m->er][m->ec] = 1;    // 初始化起點, 終點 = 1
    return;
}

void path(const MazeStruct *m){
    int **mark= malloc((m->row_size + 2)* sizeof(int *));      // 紀錄有無走過
    for (int i = 0; i < m->row_size + 2; i++){
        mark[i] = calloc(m->col_size + 2, sizeof(int));
        if (mark == NULL || mark[i] == NULL){
            printf("ERROR: unable to allocate required memory for mark in path()\n");
            exit(1);
        }
    }
    
    offsets move[8] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};   // 設定 direction
    
    item *stack = malloc(m->row_size * m->col_size * sizeof(item));   // 製作 stack
    if (stack == NULL){
        printf("ERROR: unable to allocate required memory for stack in path()\n");
        exit(1);
    }
    int top = -1;

    DirectPriority dp = DesideStartDir(m->sr, m->sc, m->er, m->ec);
    
    item temp = {m->sr, m->sc, dp.start_dir};
    stack[++top] = temp;    // push 起點

    mark[m->sr][m->sc] = 1; // 起點標記為已訪問
    while (top > -1){       // stack not empty
        temp = stack[top--];
        int i = temp.row, j = temp.col, d = temp.dir;
        int dir_count = 0;
        while (dir_count < 8){          // 找完8個方向都沒有 == no path found
            int v = i + move[d].vert, h = j + move[d].horiz;    // 往下一格移動
            if (v == m->er && h == m->ec){
                temp.row = i; temp.col = j; // 最後一格也 push
                stack[++top] = temp;
                PrintPath(m, stack, top);     // 結束 印出path
                for (int i = 0; i < m->row_size + 2; i++) free(mark[i]);
                free(mark);
                free(stack);
                return;
            }
            if (v > 0 && v <= m->row_size && h > 0 && h <= m->col_size && m->maze[v][h] && !mark[v][h]){   // 移動合法 + 沒有去過
                mark[v][h] = 1;
                temp.row = i; temp.col = j; temp.dir = (d + dp.clockwise + 8) % 8;  // 保留下一個方向 若之後退回來時可用 // 確保方向index為正數
                stack[++top] = temp;
                dp = DesideStartDir(v, h, m->er, m->ec);    // 每前進一格 皆校正方向
                i = v; j = h; d = dp.start_dir;     // 設為初始方向
                dir_count = 0;  // dir記數重置
            }
            else {
                d = (d + dp.clockwise + 8) % 8;    // 換下一個方向試試    // 確保方向index為正數
                dir_count++;    // dir記數++
            }
        }
    }
    printf("\033[31mNo path found\n\033[0m");   // stack empty
    PrintUnsuccessPath(m, mark);   // 結束 印出經過的 path

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
    printf("WNAT TO CHANGE the defult \033[42;30mstart point (1,1)\033[0m and \033[44;30mend point(%d,%d)\033[0m? (y/n)", M.row_size, M.col_size);
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
                printf("ERROR: invalid number. Must between (1,1) and (%d,%d)\n", M.row_size, M.col_size);
            else break;
        } while (1);
    }
    GenerateMaze(&M);
    path(&M);

    for (int i = 0; i < M.row_size + 2; i++) free(M.maze[i]);
    free(M.maze);
    
    return 0;
}