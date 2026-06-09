#include <stdio.h>

#define ROWS 25
#define COLS 50
#define MAX_SHAPES 20

char canvas[ROWS][COLS];

struct Shape
{
    int type;      // 1-Rect 2-Line 3-Triangle 4-Circle
    int a, b, c, d;
    int active;
};

struct Shape shapes[MAX_SHAPES];
int count = 0;

void clearCanvas()
{
    int i, j;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            canvas[i][j] = '_';
        }
    }
}

void printCanvas()
{
    int i, j;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}

void drawRectangle(int x, int y, int w, int h)
{
    int i, j;

    for(i = y; i < y + h && i < ROWS; i++)
    {
        for(j = x; j < x + w && j < COLS; j++)
        {
            canvas[i][j] = '*';
        }
    }
}

void drawLine(int x1, int y1, int x2, int y2)
{
    int i;

    if(y1 == y2)
    {
        if(x1 > x2)
        {
            int t = x1;
            x1 = x2;
            x2 = t;
        }

        for(i = x1; i <= x2; i++)
            canvas[y1][i] = '*';
    }
    else if(x1 == x2)
    {
        if(y1 > y2)
        {
            int t = y1;
            y1 = y2;
            y2 = t;
        }

        for(i = y1; i <= y2; i++)
            canvas[i][x1] = '*';
    }
}

void drawTriangle(int x, int y, int h)
{
    int i, j;

    for(i = 0; i < h; i++)
    {
        for(j = x - i; j <= x + i; j++)
        {
            if(j >= 0 && j < COLS && y + i < ROWS)
                canvas[y + i][j] = '*';
        }
    }
}

void drawCircle(int cx, int cy, int r)
{
    int x, y;

    for(y = 0; y < ROWS; y++)
    {
        for(x = 0; x < COLS; x++)
        {
            int dx = x - cx;
            int dy = y - cy;

            if(dx * dx + dy * dy <= r * r)
                canvas[y][x] = '*';
        }
    }
}

void redraw()
{
    int i;

    clearCanvas();

    for(i = 0; i < count; i++)
    {
        if(shapes[i].active == 0)
            continue;

        if(shapes[i].type == 1)
            drawRectangle(shapes[i].a, shapes[i].b,
                          shapes[i].c, shapes[i].d);

        else if(shapes[i].type == 2)
            drawLine(shapes[i].a, shapes[i].b,
                     shapes[i].c, shapes[i].d);

        else if(shapes[i].type == 3)
            drawTriangle(shapes[i].a, shapes[i].b,
                         shapes[i].c);

        else if(shapes[i].type == 4)
            drawCircle(shapes[i].a, shapes[i].b,
                       shapes[i].c);
    }
}

int main()
{
    int choice;

    while(1)
    {
        printf("\n--- GRAPHICS EDITOR ---\n");
        printf("1. Add Shape\n");
        printf("2. Delete Shape\n");
        printf("3. Modify Shape\n");
        printf("4. Display Picture\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 1)
        {
            int t;

            printf("\n1.Rectangle\n2.Line\n3.Triangle\n4.Circle\n");
            printf("Enter type: ");
            scanf("%d", &t);

            shapes[count].type = t;
            shapes[count].active = 1;

            if(t == 1)
            {
                printf("x y width height: ");
                scanf("%d%d%d%d",
                      &shapes[count].a,
                      &shapes[count].b,
                      &shapes[count].c,
                      &shapes[count].d);
            }

            else if(t == 2)
            {
                printf("x1 y1 x2 y2: ");
                scanf("%d%d%d%d",
                      &shapes[count].a,
                      &shapes[count].b,
                      &shapes[count].c,
                      &shapes[count].d);
            }

            else if(t == 3)
            {
                printf("center_x top_y height: ");
                scanf("%d%d%d",
                      &shapes[count].a,
                      &shapes[count].b,
                      &shapes[count].c);
            }

            else if(t == 4)
            {
                printf("center_x center_y radius: ");
                scanf("%d%d%d",
                      &shapes[count].a,
                      &shapes[count].b,
                      &shapes[count].c);
            }

            count++;
        }

        else if(choice == 2)
        {
            int n;

            printf("Shape number: ");
            scanf("%d", &n);

            if(n >= 1 && n <= count)
                shapes[n - 1].active = 0;
        }

        else if(choice == 3)
        {
            int n;

            printf("Shape number: ");
            scanf("%d", &n);

            if(n >= 1 && n <= count)
            {
                n--;

                if(shapes[n].type == 1)
                {
                    printf("New x y width height: ");
                    scanf("%d%d%d%d",
                          &shapes[n].a,
                          &shapes[n].b,
                          &shapes[n].c,
                          &shapes[n].d);
                }

                else if(shapes[n].type == 2)
                {
                    printf("New x1 y1 x2 y2: ");
                    scanf("%d%d%d%d",
                          &shapes[n].a,
                          &shapes[n].b,
                          &shapes[n].c,
                          &shapes[n].d);
                }

                else if(shapes[n].type == 3)
                {
                    printf("New center_x top_y height: ");
                    scanf("%d%d%d",
                          &shapes[n].a,
                          &shapes[n].b,
                          &shapes[n].c);
                }

                else if(shapes[n].type == 4)
                {
                    printf("New center_x center_y radius: ");
                    scanf("%d%d%d",
                          &shapes[n].a,
                          &shapes[n].b,
                          &shapes[n].c);
                }
            }
        }

        else if(choice == 4)
        {
            redraw();
            printCanvas();
        }

        else if(choice == 5)
        {
            printf("Exiting...\n");
            break;
        }
    }

    return 0;
}