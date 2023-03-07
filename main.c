/*
 * @Author: Howv.John.Young
 * @Date: 2023-03-07 10:27:07
 * @LastEditTime: 2023-03-07 13:37:36
 * @LastEditors: Howv.John.Young
 * @Description: 
 * @FilePath: \lifeGame\main.c
 * 可以输入预定的版权声明、个性签名、空行等
 */
/*
 * @Author: Howv.John.Young
 * @Date: 2023-03-07 10:27:07
 * @LastEditTime: 2023-03-07 10:42:15
 * @LastEditors: Howv.John.Young
 * @Description: 
 * @FilePath: \lifeGame\mian.c
 * 可以输入预定的版权声明、个性签名、空行等
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define CHECK_COUNT(size, x, y, tbl, cnt)    \
        if(x>=0 && x<size && y>=0 && y<size && table[x][y] != 0) \
        {cnt++;}
#define old_table(num)  table##(num?0:1)
#define new_table(num)  table##(num)


#define SIZE        70
/**
 * @description: count num of dot[index]
 * @param {int} size    
 * @param {int} index
 * @return {*}
 */
static int arroundCount(int size, int x, int y, char (*table)[SIZE]){
    int cnt = 0;

    CHECK_COUNT(size, x-1, y-1, table, cnt);
    CHECK_COUNT(size, x, y-1, table, cnt);
    CHECK_COUNT(size, x+1, y-1, table, cnt);

    CHECK_COUNT(size, x-1, y, table, cnt);
//    CHECK_COUNT(size, x, y, table, cnt);      /* don't count itself */
    CHECK_COUNT(size, x+1, y, table, cnt);

    CHECK_COUNT(size, x-1, y+1, table, cnt);
    CHECK_COUNT(size, x, y+1, table, cnt);
    CHECK_COUNT(size, x+1, y+1, table, cnt);

    return cnt;
}


/**
 * @description: 
 * @param {int} size
 * @param {char**} old
 * @param {char**} new
 * @return {*}
 */
static int interation(int size, char (*old)[SIZE], char (*new)[SIZE])
{
    int x = 0;
    int y = 0;
    int cnt = 0;

    for(x=0; x<SIZE; x++)
    {
        for(y=0; y<SIZE; y++)
        {
            cnt = arroundCount(SIZE, x, y, old);
            if(old[x][y] != 0)
            {
                if(cnt < 2 /* lonly die */ || cnt >3 /* crowed die */)
                {
                    new[x][y] = 0;
                }
                else
                {
                    new[x][y] = 1;
                }
            }
            else
            {
                if(cnt == 3){
                    new[x][y] = 1;
                }
                else
                {
                    new[x][y] = 0;
                }
            }
        }
    }
}


static void clr()
{
    system("clear");
    return;
}

static void print(int size, char (*table)[SIZE])
{
    int x = 0;
    int y = 0;
    for(x = 0; x<size; x++)
    {
        for(y = 0; y<size; y++)
        {
            if(table[x][y] == 0){
                printf(" ");
            }
            else
            {
                printf("\033[47;30m \033[40;37m");
            }
        }
        printf("\n");
    }
}

int main(){
    char table1[SIZE][SIZE] = {0};
    char table2[SIZE][SIZE] = {0};
    
    char (*old)[SIZE] = table1;
    char (*new)[SIZE] = table2;
    char (*tmp)[SIZE] = NULL;
    char in = 0;

    /* TODO: initialize & input to old*/
    clr();
    printf("@@@ ");
    while(1)
    {
        int x = 0;
        int y = 0;
        if(scanf("%d,%d", &x, &y) == 0)
        {
            break;
        }
        old[x][y] = (old[x][y]==0 ? 1:0);
        clr();
        print(SIZE, old);
        printf("@@@ ");
    }
    char c = 0;
    while((c = getchar()) != EOF && c != '\n');
    clr();
    printf("@@@ ");
    while(1)
    {
#if __DBG__
        scanf("%c", &in);
        if(in == 'q')
        {
            break;
        }
        else if(in != 'c')
        {
            continue;
        }
#else /* autorun */
    usleep(100000);

#endif
        
        interation(SIZE, old, new);
        clr();
        /* TODO: output */
        print(SIZE, new);

        /* save new to old */
        tmp = old;
        old = new;
        new = tmp;
    }

}