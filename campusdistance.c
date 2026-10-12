#include <stdio.h>
#include <string.h>

#define MAX 20
#define INF 99999

int graph[MAX][MAX];
int distance[MAX];
int visited[MAX];
int parent[MAX];
char location[MAX][50];
int n;

void enterGraph()
{
    int i, j;

    printf("\nEnter number of locations: ");
    scanf("%d", &n);

    printf("\nEnter location names:\n");

    for (i = 0; i < n; i++)
    {
        printf("Location %d: ", i + 1);
        scanf(" %[^\n]", location[i]);
    }

    printf("\nEnter distance between locations.\n");
    printf("Enter 0 if there is no direct road.\n\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i == j)
            {
                graph[i][j] = 0;
            }
            else
            {
                printf("Distance from %s to %s: ",
                       location[i], location[j]);

                scanf("%d", &graph[i][j]);

                if (graph[i][j] == 0)
                    graph[i][j] = INF;
            }
        }
    }

    printf("\nCampus graph entered successfully!\n");
}


void displayGraph()
{
    int i, j;

    if (n == 0)
    {
        printf("\nPlease enter the campus graph first.\n");
        return;
    }

    printf("\n--- Adjacency Matrix ---\n\n");

    printf("%-20s", "");

    for (i = 0; i < n; i++)
    {
        printf("%-12d", i + 1);
    }

    printf("\n");

    for (i = 0; i < n; i++)
    {
        printf("%-20s", location[i]);

        for (j = 0; j < n; j++)
        {
            if (graph[i][j] == INF)
                printf("%-12s", "INF");
            else
                printf("%-12d", graph[i][j]);
        }

        printf("\n");
    }
}

int findMinimum()
{
    int i;
    int min = INF;
    int index = -1;

    for (i = 0; i < n; i++)
    {
        if (!visited[i] && distance[i] < min)
        {
            min = distance[i];
            index = i;
        }
    }

    return index;
}

void dijkstra(int source)
{
    int i, j;
    int current;

    for (i = 0; i < n; i++)
    {
        distance[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    distance[source] = 0;

    for (i = 0; i < n; i++)
    {
        current = findMinimum();

        if (current == -1)
            break;

        visited[current] = 1;

        for (j = 0; j < n; j++)
        {
            if (!visited[j] &&
                graph[current][j] != INF &&
                distance[current] != INF &&
                distance[current] + graph[current][j] < distance[j])
            {
                distance[j] =
                    distance[current] + graph[current][j];

                parent[j] = current;
            }
        }
    }
}

void displayPath(int vertex)
{
    if (parent[vertex] == -1)
    {
        printf("%s", location[vertex]);
        return;
    }

    displayPath(parent[vertex]);

    printf(" -> %s", location[vertex]);
}

void displayShortestPaths(int source)
{
    int i;

    printf("\n Shortest Paths from %s \n\n",
           location[source]);

    printf("%-25s %-20s %s\n",
           "Destination",
           "Shortest Distance",
           "Shortest Path");

    printf("\n");

    for (i = 0; i < n; i++)
    {
        if (i == source)
            continue;

        printf("%-25s ", location[i]);

        if (distance[i] == INF)
        {
            printf("%-20s ", "Not Reachable");
            printf("No path\n");
        }
        else
        {
            printf("%-20d ", distance[i]);

            displayPath(i);

            printf("\n");
        }
    }
}

void displayDistances(int source)
{
    int i;

    printf("\n Distance from Source \n\n");

    printf("Source Location: %s\n\n", location[source]);

    for (i = 0; i < n; i++)
    {
        if (distance[i] == INF)
            printf("%-25s : Not Reachable\n",
                   location[i]);
        else
            printf("%-25s : %d\n",
                   location[i], distance[i]);
    }
}

int main()
{
    int choice;
    int source = -1;

    n = 0;

    do
    {
        printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        printf("\n       CAMPUS SHORTEST ROUTE FINDER");
        printf("\n       Using Dijkstra's Algorithm");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

        printf("\n\n1. Enter Campus Graph");
        printf("\n2. Display Adjacency Matrix");
        printf("\n3. Select Source Location");
        printf("\n4. Find Shortest Distance");
        printf("\n5. Display Shortest Paths");
        printf("\n6. Display Distance from Source to All Locations");
        printf("\n7. Exit");

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                enterGraph();
                break;

            case 2:
                displayGraph();
                break;

            case 3:
                if (n == 0)
                {
                    printf("\nPlease enter the campus graph first.\n");
                }
                else
                {
                    printf("\nCampus Locations:\n");

                    for (int i = 0; i < n; i++)
                    {
                        printf("%d. %s\n",
                               i + 1, location[i]);
                    }

                    printf("\nEnter source location number: ");
                    scanf("%d", &source);

                    if (source < 1 || source > n)
                    {
                        printf("\nInvalid location!\n");
                        source = -1;
                    }
                    else
                    {
                        source--;

                        printf("\nSource selected: %s\n",
                               location[source]);
                    }
                }
                break;

            case 4:
                if (n == 0)
                {
                    printf("\nPlease enter the campus graph first.\n");
                }
                else if (source == -1)
                {
                    printf("\nPlease select a source location first.\n");
                }
                else
                {
                    dijkstra(source);

                    printf("\nShortest distances calculated successfully!\n");
                }
                break;

            case 5:
                if (n == 0)
                {
                    printf("\nPlease enter the campus graph first.\n");
                }
                else if (source == -1)
                {
                    printf("\nPlease select a source location first.\n");
                }
                else
                {
                    dijkstra(source);
                    displayShortestPaths(source);
                }
                break;

            case 6:
                if (n == 0)
                {
                    printf("\nPlease enter the campus graph first.\n");
                }
                else if (source == -1)
                {
                    printf("\nPlease select a source location first.\n");
                }
                else
                {
                    dijkstra(source);
                    displayDistances(source);
                }
                break;

            case 7:
                printf("\nThank you for using the program!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}
