/**program to find closest pair of points among n points given x y coordinates of points*/

#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define N  100005

double eps = 0.00001;

typedef struct point_with_coordinates
{
    double x, y;
    int ind_of_point;
} Point;

Point src, tar;
Point a[N], b[N], c[N];

double distance_between_two_points(Point p, Point q)
{
    double x1 = p.x - q.x, y1 = p.y - q.y;
    return sqrt(x1 *x1 + y1 * y1);
}

//merge the arrays into one array
int merge_closest_pair(Point p[], Point q[], int s, int m, int t)
{
    int i, j, k;
    for (i = s, j = m + 1, k = s; i <= m && j <= t;)
    {
        if (q[i].y > q[j].y)
            p[k++] = q[j], j++;
        else
            p[k++] = q[i], i++;
    }
    while (i <= m)
        p[k++] = q[i++];
    while (j <= t)
        p[k++] = q[j++];
    memcpy(q + s, p + s, (t - s + 1) *sizeof(p[0]));
    return 0;
}

//function required for qsort library function
int compare_x(const void *p, const void *q)
{
    double temp = ((Point*)p)->x - ((Point*)q)->x;
    if (temp > 0)
        return 1;
    else if (fabs(temp) < eps)
        return 0;
    else
        return - 1;
}

//function required for qsort library function
int compare_y(const void *p, const void *q)
{
    double temp = ((Point*)p)->y - ((Point*)q)->y;
    if (temp > 0)
        return 1;
    else if (fabs(temp) < eps)
        return 0;
    else
        return - 1;
}

//find minimum of two values
double minimum_of_two_values(double value1, double value2)
{
    return (value1 > value2) ? (value2): (value1);
}

//find closest pair between two points given n points
double find_closest_pair(Point a[], Point b[], Point c[], int p, int q)
{
    //if there are only two points, return their distance
    if (q - p == 1){
        src.x = a[p].x;
        src.y = a[p].y;
        tar.x = a[q].x;
        tar.y = a[q].y;
        return distance_between_two_points(a[p], a[q]);
    }
    //if there are more than two points, return min distance between those two distances
    if (q - p == 2)
    {
        double x1 = distance_between_two_points(a[p], a[q]);
        double x2 = distance_between_two_points(a[p + 1], a[q]);
        double x3 = distance_between_two_points(a[p], a[p + 1]);
        if (x1 < x2 && x1 < x3){
            src.x = a[p].x;
            src.y = a[p].y;
            tar.x = a[q].x;
            tar.y = a[q].y;
            return x1;
        }
        else if (x2 < x3){
            src.x = a[p+1].x;
            src.y = a[p+1].y;
            tar.x = a[q].x;
            tar.y = a[q].y;
            return x2;
        }

        else{
            src.x = a[p].x;
            src.y = a[p].y;
            tar.x = a[p+1].x;
            tar.y = a[p+1].y;
            return x3;
        }
    }
    //find mid point to divide the points into two partitions
    int m = (p + q) / 2;
    int i, j, k;
    double min_distance_left, min_distance_right;

    for (i = p, j = p, k = m + 1; i <= q; i++)
    // The left half of the array c holds the left part of the partition, and is ordered for y.
        if (b[i].ind_of_point <= m)
            c[j++] = b[i];
    else
        c[k++] = b[i];
    //minimum distance in left partition
    min_distance_left = find_closest_pair(a, c, b, p, m);
    //minimum distance in right partition
    min_distance_right = find_closest_pair(a, c, b, m + 1, q);
    //minimum of closest distance in left and right partitions
    double min_distance_across_left_right_partitions = minimum_of_two_values(min_distance_left, min_distance_right);

    //The left and right parts of the array c are ordered to the y coordinate, respectively, and merged into b.
    merge_closest_pair(b, c, p, m, q);

    for (i = p, k = p; i <= q; i++)
        if (fabs(b[i].x - b[m].x) < min_distance_across_left_right_partitions)
            c[k++] = b[i];
    //Find the part that does not exceed minimum distance across left and right partitions from the dividing reference, and still order the y coordinate.
    for (i = p; i < k; i++)
    for (j = i + 1; j < k && c[j].y - c[i].y < min_distance_across_left_right_partitions; j++)
    {
        double temp = distance_between_two_points(c[i], c[j]);
        if (temp < min_distance_across_left_right_partitions){
            src.x = c[i].x;
            src.y = c[i].y;
            tar.x = c[j].x;
            tar.y = c[j].y;
            min_distance_across_left_right_partitions = temp;
        }
    }
    return min_distance_across_left_right_partitions;
}


int main()
{
    int n;
    double d;
    printf("Program for finding closest pair between n points:\n");
    printf("Enter total number of points:\n");
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        printf("\nEnter the x coordinate of point number : %d -\t",i);
        scanf("%lf", &(a[i].x));
        printf("\nEnter the y coordinate of point number : %d -\t",i);
        scanf("%lf", &(a[i].y));
    }
    qsort(a, n, sizeof(a[0]), compare_x);
    for (int i = 0; i < n; i++)
        a[i].ind_of_point = i;
    memcpy(b, a, n *sizeof(a[0]));
    qsort(b, n, sizeof(b[0]), compare_y);
    d = find_closest_pair(a, b, c, 0, n - 1);
    printf("\nThe minimum distance between two closest points are:\n");
    printf("%lf\n\n", d);
    printf("The closest points are :\n");
    printf("(%lf , %lf) and ", src.x, src.y);
    printf("(%lf, %lf)\n",tar.x, tar.y);
    printf("\nExiting....\n");
    exit(1);
    return 0;
}

