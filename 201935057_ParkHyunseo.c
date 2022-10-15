#include <stdio.h>
#include <math.h>

double dot[30][2]; // save the location of dots
double interval[30][30] = { 0, }; // save the interval between the dots
double sort_inte[406] = { 0, }; // sort the interval value
int sort_ind[406][2] = { 0, }; // index value of sort inteval value's dots
double sum = 0; // the cost of ink
void cal_func(int n); // function to calculate the interval between dots
void sort(int n, int temp); // function to sort the interval value
void kruskal(int n, int temp); // function to find the minimum cost by kruskal algorithm
int check(int i, int n, int temp); // function to check the connection between the dots

struct edge { // structure to save the line drawing
    double start[2]; // save the position of dot's location
    struct edge* parent; // save the parent node
};

struct edge node[30]; // node with maximum number of dots

int main() {
    int N; // the number of dots
    printf("input the number of dots\n");
    scanf_s("%d", &N); // 0 < N < 30

    for (int i = 0; i < N; i++) { // roop by number of dots
        scanf_s("%lf %lf", &dot[i][0], &dot[i][1]);
    }

    cal_func(N); // function to calculate the interval between dots

    for (int i = 0; i < N; i++) { // roop by number of dots for save the dot's point at its node
        node[i].start[0] = dot[i][0];
        node[i].start[1] = dot[i][1];
        node[i].parent = NULL; // initialize the address of parent node to NULL
    }

    int temp = 0; // calculate the number of interval
    for (int i = 1; i < N; i++) // roop by ( number of dots - 1 )
        temp += i; // number of interval

    sort(N, temp); // function to sort the interval value

    kruskal(N, temp); // function to find the minimum cost by kruskal algorithm

    printf("%.2lf", sum); // printf the minimum cost

    return 0;
}

void cal_func(int n) { // function to calculate the interval between dots
    for (int i = 0; i < n; i++) { // roop by number of dots for calculate the interval between dots
        for (int j = i + 1; j < n; j++) { // roop by number of dots
            double temp = 0; // temporary variable
            double a = dot[i][0] - dot[j][0]; // x position difference
            double b = dot[i][1] - dot[j][1]; // y position difference
            a = a * a; // squared of difference value
            b = b * b; // squared of difference value
            temp = a + b; // plus the squared value
            interval[i][j] = sqrt(temp); // the root by Pythagoras
        }
    }
}

void sort(int n, int temp) { // function to sort the interval value
    for (int k = 0; k < temp; k++) { // roop by number of interval
        double min = 1000000; // minimum variable
        int ind_i = 0, ind_j = 0; // save the index of minimum
        for (int i = 0; i < n; i++) { // roop by number of dots for find the minimum interval
            for (int j = i + 1; j < n; j++) { // roop by number of dots
                if (min > interval[i][j] && interval[i][j] != -1) { // minimum value what it isn't -1
                    min = interval[i][j];
                    ind_i = i;
                    ind_j = j;
                }
            }
        }
        sort_inte[k] = min; // store the minimum value
        sort_ind[k][0] = ind_i; // store the index
        sort_ind[k][1] = ind_j; // store the index
        interval[ind_i][ind_j] = -1; // initialize what I used
    }
}

void kruskal(int n, int temp) { // function to find the minimum cost by kruskal algorithm
    for (int i = 0; i < temp; i++) { // roop by number of interval value
        if (i == 0) { // when the minimum interval value
            node[sort_ind[i][1]].parent = &node[sort_ind[i][0]]; // store the parent node of minimum node
            sum += sort_inte[i]; // sum the cost of ink
        }
        else {
            if (check(i, n, temp)) { // if not connected between the start node and end node of minimum of extra interval, when I can connect the new node
                node[sort_ind[i][1]].parent = &node[sort_ind[i][0]]; // store the parent node of new node
                sum += sort_inte[i]; // sum the cost of ink
            }
            else { // if connected between the start node and end node of minimum of extra interval, when I don't need to connect
                continue;
            }
        }
    }
}

int check(int i, int n, int temp) {
    struct edge temp_node; // temporary node to save the parent node

    if (node[sort_ind[i][0]].parent == NULL && node[sort_ind[i][1]].parent == NULL) // When two nodes have no parent both.
        return 1; // if not connected between the start node and end node of minimum of extra interval, when I can connect the new node
    else if (node[sort_ind[i][0]].parent != NULL && node[sort_ind[i][1]].parent == NULL) { // when only one node has the parent node, the other's parent node is NULL value
        temp_node = node[sort_ind[i][0]]; // initialize the temporary node to node what have the parent node
        while (temp_node.parent != NULL) { // if the parent node is not NULL value
            if (temp_node.parent == &node[sort_ind[i][1]]) // When the parent node is the same as another node
                return 0; // if connected between the start node and end node of minimum of extra interval, when I don't need to connect
            temp_node = *temp_node.parent; // If not, initialize the temporary node to parent node
        }
    }
    else if (node[sort_ind[i][0]].parent == NULL && node[sort_ind[i][1]].parent != NULL) { // when only one node has the parent node, the other's parent node is NULL value
        temp_node = node[sort_ind[i][1]]; // initialize the temporary node to node what have the parent node
        while (temp_node.parent != NULL) { // if the parent node is not NULL value
            if (&node[sort_ind[i][0]] == temp_node.parent) // When the parent node is the same as another node
                return 0; // if connected between the start node and end node of minimum of extra interval, when I don't need to connect
            temp_node = *temp_node.parent; // If not, initialize the temporary node to parent node
        }
    }
    else { // when their parent node is not NULL value
        if (node[sort_ind[i][0]].parent == node[sort_ind[i][1]].parent) // when when their parent node is the same
            return 0; // if connected between the start node and end node of minimum of extra interval, when I don't need to connect
        temp_node = node[sort_ind[i][0]]; // initialize the temporary node to one node of the two nodes of the minimum interval value
        while (temp_node.parent != NULL) { // if the parent node is not NULL value
            if (temp_node.parent == &node[sort_ind[i][1]]) // When the parent node is the same as another node
                return 0; // if connected between the start node and end node of minimum of extra interval, when I don't need to connect
            temp_node = *temp_node.parent; // If not, initialize the temporary node to parent node
        }
        struct edge temp_node2 = node[sort_ind[i][1]]; // second temporary node to save the parent node, and initialize the node to the other node
        while (temp_node2.parent != NULL) { // if the parent node is not NULL value
            if (&node[sort_ind[i][0]] == temp_node2.parent) // When the parent node is the same as another node
                return 0; // if connected between the start node and end node of minimum of extra interval, when I don't need to connect
            temp_node2 = *temp_node2.parent; // If not, initialize the temporary node to parent node
        }
        if (temp_node.start[0] == temp_node2.start[0] && temp_node.start[1] == temp_node2.start[1]) // when their head nodes are the same
            return 0; // if connected between the start node and end node of minimum of extra interval, when I don't need to connect
    }

    return 1; // if not connected between the start node and end node of minimum of extra interval, when I can connect the new node
}