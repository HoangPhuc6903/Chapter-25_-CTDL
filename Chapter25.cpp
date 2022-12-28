#pragma warning(disable : 4996)
#pragma warning(suppress : 4996)
#include<stdio.h>
#include<ctype.h>
#include<math.h>
#include<string.h>
#include<GL/glut.h>
#include<iostream>
using namespace std;
float offset = 0.0;
bool box_clicked = false;
int temp_x, temp_y, temp_item;
bool prev_search = false;
enum color_code { RED, GREEN, BLUE };
struct node {
	int data;
	struct node* left;
	struct node* right;	
	bool lthread;
	bool rthread;
};
typedef struct node* NODE;
NODE root = NULL;
char query_string[] = "Enter an Integer to be inserted and Hit Enter : ";
char query_string2[] = "Enter an Integer to be searched and Hit Enter :";
char query_string3[] = "Enter an Integer to be deleted and Hit Enter :";
char query_string4[] = "The preorder is:";
char query_string5[] = "The inorder is:";
char query_string6[] = "The postorder is:";
char not_found[] = "Search failed!!Item Not found";
char not_found2[] = "Item cannot be deleted!! Item not Found";
float node_color[3] = { 0.419608 , 0.556863 , 0.137255 };
void display();
void backcolor()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glColor3f(0.0, 0.0, 0.0);
}
int count_digit(int n) {
	return (n == 0) ? 0 : floor(log10(n) + 1);
}
void to_string(char* s, int num) {
	int r, d;
	d = count_digit(abs(num));
	if (num == 0)
		s[0] = '0';
	if (num < 0) {
		s[0] = '-';
		d++;
	}
	s[d] = '\0';
	num = abs(num);
	while (num != 0) {
		r = num % 10;
		s[--d] = r + '0';
		num /= 10;
	}
}
void display_string(char s[], float x, float y, float z = 0.0) {
	glRasterPos3f(x, y, z);
	for (int i = 0; s[i]; i++) {

		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
	}
	glFlush();

}
void clear_input_region() {
	backcolor();
	glBegin(GL_POLYGON);
	glVertex2f(100, 630);
	glVertex2f(100, 700);
	glVertex2f(700, 650);
	glVertex2f(680, 700);
	glEnd();
	backcolor();
	glBegin(GL_POLYGON);
	glVertex2f(40, 40);
	glVertex2f(40, 100);
	glVertex2f(650, 100);
	glVertex2f(650, 40);
	glEnd();
	glFlush();
}
static int i = 0;
struct binary_search_tree {

	NODE root;
	int root_centre_x, root_centre_y;
	int node_width;
	float line_color[3];
	char data_string[10];
	NODE get_minimum(NODE temp, NODE* par) {
		if (temp->left == NULL)
			return temp;
		*par = temp;
		return get_minimum(temp->left, par);
	}

	binary_search_tree() {
		root = NULL;
		root_centre_x = 600;
		root_centre_y = 600;
		node_width = 30;
		line_color[RED] = 0.36;
		line_color[GREEN] = 0.25;
		line_color[BLUE] = 0.20;

	}
	void draw_node(int item, int centre_x, int centre_y, bool write_value = true) {
		char data_string[10];
		glBegin(GL_POLYGON);
		glVertex2f(centre_x + node_width, centre_y + node_width);
		glVertex2f(centre_x - node_width, centre_y + node_width);
		glVertex2f(centre_x - node_width, centre_y - node_width);
		glVertex2f(centre_x + node_width, centre_y - node_width);
		glEnd();
		if (write_value) {
			to_string(data_string, item);
			glColor3f(1.0, 1.0, 0.0);
			display_string(data_string, centre_x - node_width + 10, centre_y);
		}
	}
	void draw_arrow(int par_x, int par_y, int node_x, int node_y, bool color = true) {
		if (color)
			glColor3f(line_color[RED], line_color[GREEN], line_color[BLUE]);

		glBegin(GL_LINES);
		glVertex2f(par_x, par_y - node_width);
		glVertex2f(node_x, node_y + node_width);
		glEnd();
	}
	NODE insert(int item) {
		int num_of_nodes = 1;
		int node_x = root_centre_x, node_y = root_centre_y;
		int par_x, par_y;
		node* ptr = root;
		node* par = NULL; // Parent of key to be inserted

		while (ptr != NULL)
		{
			// If key already exists, return
			if (item == (ptr->data))
			{
				printf("Duplicate Key !\n");
				return root;
			}
			num_of_nodes *= 2;
			par_x = node_x;
			par_y = node_y;
			node_y -= 100;
			par = ptr;
			// Update parent pointer
			// Moving on left subtree.
			if (item < ptr->data)
			{
				if (ptr->lthread == false)
				{
					ptr = ptr->left;
					node_x -= root_centre_x / num_of_nodes;
				}
				else
					break;
			}

			// Moving on right subtree.
			else
			{
				if (ptr->rthread == false)
				{
					ptr = ptr->right;
					node_x += root_centre_x / num_of_nodes;
					
				}
				else
					break;
			}
		}
		//num_of_nodes *= 2;
		par_x = node_x;
		par_y = node_y;
		node_y -= 100;
		par = ptr;
		// Create a new node
		node* tmp = new node;
		tmp->data = item;
		tmp->lthread = true;
		tmp->rthread = true;

		if (par == NULL)
		{
			root = tmp;
			tmp->left = NULL;
			tmp->right = NULL;
			glColor3f(node_color[RED], node_color[GREEN], node_color[BLUE]);
			draw_node(item, node_x, node_y);
		}
		else if (item < (par->data))
		{
			tmp->left = par->left;
			tmp->right = par;
			par->lthread = false;
			par->left = tmp;
			node_x -= root_centre_x / num_of_nodes;
		}
		else
		{
			tmp->left = par;
			tmp->right = par->right;
			par->rthread = false;
			par->right = tmp;
			node_x += root_centre_x / num_of_nodes;
		}
		glColor3f(node_color[RED], node_color[GREEN], node_color[BLUE]);
		draw_node(item, node_x, node_y);
		draw_arrow(par_x, par_y, node_x, node_y);
		glFlush();

		return root;

	}
	NODE search(int item) {
		int num_of_nodes = 1;
		int node_x = root_centre_x, node_y = root_centre_y;
		int par_x, par_y;
		node* ptr = root;
		node* par = NULL; // Parent of key to be inserted
		while (ptr != NULL)
		{
			// If key already exists, return
			if (item == (ptr->data))
			{
				glColor3f(1.0, 1.0, 0.0);
				display_string(not_found, 100, 650);
				return root;
			}
			num_of_nodes *= 2;
			par_x = node_x;
			par_y = node_y;
			node_y -= 100;
			par = ptr; // Update parent pointer
			// Moving on left subtree.
			if (item < ptr->data)
			{
				if (ptr->lthread == false)
				{
					ptr = ptr->left;
					node_y -= 100;
					node_x -= root_centre_x / num_of_nodes;
				}
				else
					break;
			}

			// Moving on right subtree.
			else
			{
				if (ptr->rthread == false)
				{
					ptr = ptr->right;
					node_y -= 100;
					node_x -= root_centre_x / num_of_nodes;
				}
				else
					break;
			}
		}
		glColor3f(node_color[RED], node_color[GREEN], node_color[BLUE]);
		draw_node(item, node_x, node_y);
		draw_arrow(par_x, par_y, node_x, node_y);
		glFlush();

		return root;
	}
	void pre_order(NODE temp, binary_search_tree temp_tree) {
		
		if (temp != NULL)
		{
			temp_tree.insert(temp->data);
			if(temp->lthread==false)
				pre_order(temp->left, temp_tree);
			if (temp->rthread == false)
				pre_order(temp->right, temp_tree);

		}
	}
	void delay()
	{
		for (int i = 0; i < 22000; i++)
			for (int j = 0; j < 22000; j++);
	}
	void preorder(NODE temp, binary_search_tree temp_tree) {
		if (temp != NULL) {
			temp_tree.insert(temp->data);
			delay();
			to_string(data_string, temp->data);
			glColor3f(1.0, 1.0, 0.0);
			i = i + 1;
			display_string(data_string, 300 + (i * 20), 50);
			search(temp->data);
			delay();
			i = i + 1;
			if (temp->lthread == false)
				preorder(temp->left, temp_tree);
			if (temp->rthread == false)
				preorder(temp->right, temp_tree);
		}
	}
	void inorder(NODE temp, binary_search_tree temp_tree) {
		if (temp != NULL) {
			temp_tree.insert(temp->data);
			delay();
			if (temp->lthread == false)
				inorder(temp->left, temp_tree);
			to_string(data_string, temp->data);
			glColor3f(1.0, 1.0, 0.0);
			i = i + 1;
			display_string(data_string, 300 + (i * 20), 50);
			search(temp->data);
			delay();
			i = i + 1;
			if (temp->rthread == false)
				inorder(temp->right, temp_tree);
		}
	}
	void postorder(NODE temp, binary_search_tree temp_tree) {
		if (temp != NULL) {
			temp_tree.insert(temp->data);
			if (temp->lthread == false)
				postorder(temp->left, temp_tree);
			delay();
			if (temp->rthread == false)
				postorder(temp->right, temp_tree);
			to_string(data_string, temp->data);
			glColor3f(1.0, 1.0, 0.0);
			i = i + 1;
			display_string(data_string, 300 + (i * 20), 50);
			search(temp->data);
			delay();
			i = i + 1;
		}
	}
	void draw_tree() {
		binary_search_tree temp_tree;
		display();
		pre_order(root, temp_tree);
	}
	void preordertraversal() {
		binary_search_tree temp_tree;
		display();
		display_string(query_string4, 100, 50);
		preorder(root, temp_tree);
		pre_order(root, temp_tree);
	}
	void inordertraversal() {
		binary_search_tree temp_tree;
		display();
		display_string(query_string5, 100, 50);
		inorder(root, temp_tree);
		pre_order(root, temp_tree);
	}
	void postordertraversal() {
		binary_search_tree temp_tree;
		display();
		display_string(query_string6, 100, 50);
		postorder(root, temp_tree);
		pre_order(root, temp_tree);
	}
};
binary_search_tree tree;
NODE(binary_search_tree::* operation)(int) = NULL;
class option_box {
private:
	float bottom_corner_x, bottom_corner_y;
	float bc;
	float height, width;
	float color[3];
	char option_name[20];
public:
	option_box() {
		bottom_corner_x = 0;
		bottom_corner_y = 0;
		width = 0;
		height = 0;
		color[RED] = 0.0;
		color[GREEN] = 0.0;
		color[BLUE] = 1.0;
		strcpy(option_name, "");
	}
	option_box(const char name[]) {
		bottom_corner_x = 150;
		bottom_corner_y = 700;
		width = 150;
		height = 50;
		color[RED] = 0.36;
		color[GREEN] = 0.25;
		color[BLUE] = 0.20;
		strcpy(option_name, name);
	}
	void draw_box() {
		bottom_corner_x += offset;
		bc = bottom_corner_x;
		glColor3f(color[RED], color[GREEN], color[BLUE]);
		glBegin(GL_POLYGON);
		glVertex2f(bottom_corner_x, bottom_corner_y);
		glVertex2f(bottom_corner_x + width, bottom_corner_y);
		glVertex2f(bottom_corner_x + width, bottom_corner_y + height);
		glVertex2f(bottom_corner_x, bottom_corner_y + height);
		glEnd();
		offset += 200.0;
		glColor3f(1.0, 1.0, 0.0);
		display_string(option_name, bottom_corner_x + 30.0, bottom_corner_y + 20.0);
	}
	bool clicked(int x, int y) {
		if (x >= bc && x < bc + width)
			if (y > bottom_corner_y && y < bottom_corner_y + height) {
				box_clicked = true;
				return true;
			}
		return false;
	}
};
option_box insert_box, search_box, delete_box, preorder_box, inorder_box, postorder_box;

void init() {
	backcolor();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 1500, 0.0, 800);
}
void displayOptions() {
	option_box insert_box("Insert"), preorder_box("Preorder"), inorder_box("Inorder"), postorder_box("Postorder");
	offset = 0.0;
	insert_box.draw_box();
	preorder_box.draw_box();
	inorder_box.draw_box();
	postorder_box.draw_box();
	::insert_box = insert_box;
	::preorder_box = preorder_box;
	::inorder_box = inorder_box;
	::postorder_box = postorder_box;

}
void display() {

	glClear(GL_COLOR_BUFFER_BIT);
	displayOptions();
	glFlush();
}
void mouse(int button, int state, int x, int y) {
	y = 800 - y;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (prev_search == true) {
			glColor3f(node_color[RED], node_color[GREEN], node_color[BLUE]);
			tree.draw_node(temp_item, temp_x, temp_y);
			prev_search = false;
		}
		if (insert_box.clicked(x, y)) {
			operation = &binary_search_tree::insert;
			clear_input_region();
			glColor3f(1.0, 1.0, 0.0);
			display_string(query_string, 100, 650);
			glFlush();
		}
		if (search_box.clicked(x, y)) {
			operation = &binary_search_tree::search;
			clear_input_region();
			glColor3f(1.0, 1.0, 0.0);
			display_string(query_string2, 100, 650);
			glFlush();
		}
		if (preorder_box.clicked(x, y)) {
			tree.preordertraversal();
		}
		if (inorder_box.clicked(x, y)) {
			tree.inordertraversal();
		}
		if (postorder_box.clicked(x, y)) {
			tree.postordertraversal();
		}
	}

}
void keyboard(unsigned char key, int x, int y) {
	char s[2];
	static int digit = 0;
	static int number = 0;
	static int sign = 1;
	int l = 0;
	if (!box_clicked)
		return;
	if (digit == 0 && key == '-') {
		s[0] = key;
		s[1] = '\0';
		glColor3f(1.0, 1.0, 0.0);
		display_string(s, 570, 650);
		glFlush();
		sign = -1;
	}
	else if (key != 13 && isdigit(key)) {
		number = (number * 10) + key - '0';
		s[0] = key;
		s[1] = '\0';
		glColor3f(1.0, 1.0, 0.0);
		display_string(s, 570 + (digit * 10), 650);
		digit++;
	}
	else if (key != 13 && !isdigit(key))
		;
	else {
		digit = 0;
		clear_input_region();
		(tree.*operation)(sign * number);
		number = 0;
		sign = 1;
		box_clicked = false;
	}
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1500, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Binary Search Tree Visualization");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	init();
	glutMainLoop();
	return 0;
}
