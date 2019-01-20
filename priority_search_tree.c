/*
 * Given a set P of n points in the plane, implement the priority search tree data strcture to report all points in a query range of the form
 *   (-∞ : qx] X [qy : q'y] in O(logn + k) time, where k is the number of reported points.
 * Roll no: 184101046
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define null 0
#define INFTY 100000

//define a point with x and y coordinates
typedef struct point{
	float x;
	float y;
	int id; // the index of the data point in the original array
}point;

typedef struct node{
	point p;
	float ymid;
	struct node *left;
	struct node *right;
}node;

int comp_Y(const void *a, const void *b);
void display_array(point *A, int N);
void construct_pst_simple(point *A);
node *construct_node(point p, int yv);
node *construct_pst_recursive(point *A, int l, int h);
void display_tree(node *root);
void display_node(node *u);
void display_point(point p);
void search_2DRange_query(node *root, float qx, float qy, float qy1);

point *A;
int N; // the number of points
node *root;// the root of the pst tree

int main(){

    printf("Priority Search Tree implementation to report all points in a query range of the form(-∞ : qx] X [qy : q'y] in O(logn + k) time, where k is the number of reported points.\n");
    printf("\nEnter number of points in the PST:\n");
    scanf("%d",&N);

    A = (point*)malloc(N*sizeof(point));

    for(int i = 0; i < N; i++){
        printf("\nEnter x coordinate of point number : \"%d\"\n",i+1);
        scanf("%f",&A[i].x);
        printf("\nEnter y coordinate of point number : \"%d\"\n",i+1);
        scanf("%f",&A[i].y);
        A[i].id=i;
    }

	construct_pst_simple(A);
	printf("print tree:\n\n");
	display_tree(root);
	float qx, qy, qy1;
	//qx = 60; qy = 1; qy1=200;

	printf("\n");
	printf("Enter the value of qx:\n");
	scanf("%f",&qx);
	printf("Enter the value of qy:\n");
	scanf("%f",&qy);
	printf("Enter the value of q'y:\n");
	scanf("%f",&qy1);

	printf("\nquering:(%.2f,%.2f,%.2f)\n", qx, qy, qy1);
	printf("\n");
	printf("result:\n");
	search_2DRange_query(root,qx, qy, qy1);
	return 0;
}

void construct_pst_simple(point *A){
	qsort(A,N,sizeof(*A), comp_Y);
	printf("print array:\n");
	display_array(A,N);
	printf("\n");
	root = construct_pst_recursive(A,0, N-1);
}

node *construct_pst_recursive(point *A, int l, int h){
	if(h < l) return null;
	else if(h== l) return construct_node(A[l], A[l].y);
	else if(h-l == 1){
		node *u = construct_node(A[l], A[l].y);
		node *v = construct_node(A[h], A[h].y);
		if(u->p.x < v->p.x){
			u->right = v; // remember here u->y < v->y
			return u;
		}else {
			v->left = u;
			return v;
		}
	}else {
		int k = -1;
		float min  = INFTY;
		int i = l;

		// find the point of minimum x-coordinate
		for(; i <= h; i++){
			if(A[i].x < min){
				min = A[i].x;
				k = i;
			}
		}

		// put A[k] to the end of the array
		point tmp = A[k];
		int j = k+1;
		for(; j <= h; j++){
			A[j-1] = A[j];
		}
		A[h] = tmp;

		// call recursive-pst-construction
		int m = (l + h-1) >>1;
		node *v = construct_node(A[h], A[m].y);
		v->left = construct_pst_recursive(A, l, m);
		v->right  = construct_pst_recursive(A,m+1, h-1);
		return v;

	}
}

//search tree data strcture to report all points in a search_2DRange_query range of the form (-∞ : qx] X [qy : q'y] in O(logn + k) time

void search_2DRange_query(node *root, float qx, float qy, float qy1){
	if(root == null || root->p.x > qx ) return;

	if(root->p.x <= qx && root->p.y >= qy && root->p.y <= qy1){
		display_point(root->p);
	}

    search_2DRange_query(root->left, qx, qy, qy1);
    search_2DRange_query(root->right, qx, qy, qy1);
}

node *construct_node(point p, int yv){
	node *v = (node *)malloc(sizeof(node));
	v->p = p;
	v->ymid = yv;
	v->left = null;
	v->right = null;
}
int comp_Y(const void *a, const void *b){
	point *pa = (point *)a;
	point *pb = (point *)b;
	return pa->y - pb->y;
}

void display_tree(node *root){
	if(root == null) return;
	display_node(root);
	printf("left ");
	display_node(root->left);
	printf("right ");
	display_node(root->right);
	printf("\n");
	display_tree(root->left);
	display_tree(root->right);
}

void display_node(node *u){
	if(u != null) printf("(%.2f,%.2f,%.2f)\t", u->p.x, u->p.y, u->ymid);
	else printf("null\t");
}

void display_point(point p){
		printf("(%.2f,%.2f)\n",p.x,p.y);
}

void display_array(point *A, int N){
	int i = 0;
	for(i = 0; i < N; i++){
		printf("(%.2f,%.2f,%d) ", A[i].x, A[i].y, A[i].id);
	}
	printf("\n");
}
