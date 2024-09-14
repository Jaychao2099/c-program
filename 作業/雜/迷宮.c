# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# define MAXROW 1000
# define MAXCOL 1000

// 垂直移動, 水平移動
typedef struct offsets{
    int vert;
    int horiz
}offsets;

// 走過的路
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
    int sr;
    int sc;
    int er;
    int ec;
}MazeStruct;

void print_maze(MazeStruct m){
    for(int i = 1; i <= m.row_size; i++){
        for(int j = 1; j <= m.col_size; j++) printf("%d", m.maze[i][j]);
        printf("\n");
    }
}

MazeStruct GenerateMaze(const int n, const int p, int start_row, int start_col, int end_row, int end_col){
    MazeStruct m;
    m.row_size = n;
    m.col_size = p;
    m.sr = start_row;
    m.sc = start_col;
    m.er = end_row;
    m.ec = end_col;
    m.maze = malloc((n + 2) * sizeof(int *));
    for (int i = 0; i < n + 2; i++) m.maze[i] = calloc(p + 2, sizeof(int));
    srand(time(0));
    for(int i = 1; i <= m.row_size; i++)
        for(int j = 1; j <= m.col_size; j++)
            m.maze[i][j] = rand() % 2;
    return m;
}

void path(const MazeStruct m){
    offsets move[8] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    item *stack = malloc(m.row_size * m.col_size * sizeof(item));
    printf("\033[47;30;1m1 \033[47;30;0m");
    printf("0 ");
    free(stack);
}

int main(){
    int x, y;
    char mode;
    do {
        printf("Enter maze size (split by 'space'): ");
        if (scanf("%d%d", &x, &y) < 1){    // Clear input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("ERROR: invalid input. Please enter two numbers: ");
        } else if (x < 1 || x > MAXROW || y < 1 || y > MAXCOL){
            printf("ERROR: invalid number. Must be (1 ~ %d) * (1 ~ %d)\n", MAXROW, MAXCOL);
        } else break;
    } while (1);
    int sr = 1, sc = 1, er = x, ec = y;     // 0 保留作邊界
    printf("WNAT TO CHANGE the defult start point (1,1) and end point(%d,%d)? (y/n)", x, y);
    scanf("%c", &mode);
    if (mode == 'y' || mode =='Y'){
        do {
            printf("Enter start point and end point (split by 'space'): ");
            if (scanf("%d%d%d%d", &sr, &sc, &er, &ec) < 1){    // Clear input buffer
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                printf("ERROR: invalid input. Please enter four numbers: ");
            } else if (x < 1 || x > MAXROW || y < 1 || y > MAXCOL){
                printf("ERROR: invalid number. Must between (1,%d) and (1,%d)\n", x, y);
            } else break;
        } while (1);
    }
    MazeStruct M = GenerateMaze(x, y, sr, sc, er, ec);
    print_maze(M);
    path(M);

    for (int i = 0; i < y + 2; i++) free(M.maze[i]);
    free(M.maze);
    
    return 0;
}