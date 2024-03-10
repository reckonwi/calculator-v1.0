#ifndef S21_CALC_H
#define S21_CALC_H

#include <cairo.h>
#include <check.h>
#include <gtk/gtk.h>
#include <math.h>
#include <stdio.h>  // for my checks
#include <stdlib.h>

#define CALC_WIDHT 300
#define CALC_HEIGHT 500
#define CALC_BORDER 10

#define GRAPH_NET_NUMBER 20
#define GRAPH_BORDER 50

#define SUCCESS 1
#define ERROR 0
#define NUMBER 2
#define FUNCTION 3
#define OPERATION 4
#define BINARY_OPERATOR 5
#define UNARY_OPERATOR 6
#define TO_LEFT 7
#define TO_RIGHT 8

#define ASIN 'A'
#define ACOS 'B'
#define ATAN 'C'
#define SIN 'D'
#define COS 'E'
#define LN 'F'
#define LOG 'G'
#define TAN 'H'
#define MOD 'I'
#define SQRT 'J'
#define SUM '+'
#define SUB '-'
#define MUL '*'
#define DIV '/'
#define EXP '^'

typedef struct {
  GtkWidget *window;
  GtkWidget *notebook;
  GtkWidget *label[3];
  GtkWidget *box[3];
} s21_main_window;

typedef struct {
  GtkWidget *grid;
  GtkWidget *display[5];
  GtkWidget *button[34];
  GtkWidget *label[5];
} s21_calc;

typedef struct {
  long double *stack;
  int count_elements;
} result_struct;

typedef struct {
  const gchar *x_value_min;
  const gchar *x_value_max;
  const gchar *y_value_min;
  const gchar *y_value_max;
} range;

typedef struct {
  double x_min;
  double x_max;
  double y_min;
  double y_max;
} double_range;

void main_calc_widget(s21_main_window *main_window);
void math_calc_widget(s21_main_window *main_window);
void credit_calc_widget(s21_main_window *main_window);
void deposit_calc_widget(s21_main_window *main_window);
void add_buttons_math_calc(s21_calc *math_calc);
void add_buttons_math_calc_to_grid(s21_calc *math_calc);
void calc_input(GtkWidget *button, gpointer data);
void check_input_buf();
void add_x_to_input_buf(char *math_calc_input_x_buf, char *math_calc_input_buf);
void create_graph_window(range *range);

void show_scale(double graph_size, double scale_x, double scale_y);
void show_axis(double_range *double_range, double scale_x, double scale_y);
void show_border(double_range *double_range, double graph_size);
void show_adaptive_net(double_range *double_range, double graph_size,
                       double scale_x, double scale_y);
void show_graph(double_range *double_range, double scale_x, double scale_y,
                double graph_size);
void set_coordinate(double *x, double *y, double_range *double_range,
                    double scale_x, double scale_y);
void show_x_with_axis(double_range *double_range, double graph_size,
                      double scale_x, double graph_grid);
void show_x_without_axis(double_range *double_range, double graph_size,
                         double scale_x, double graph_grid);
void show_y_with_axis(double_range *double_range, double graph_size,
                      double scale_y, double graph_grid);
void show_y_without_axis(double_range *double_range, double graph_size,
                         double scale_y, double graph_grid);

int start_calc(char *math_calc_input_buf, double *result);
int convert_to_polish(char *math_calc_input_buf, char *polish_buf);
int check_leksem_type(char a);
void sort_operation(char a, int *j, char *polish_buf, char *stack_buf);
int check_priority(char a);
void check_func_name(char *a, char next, int *i);
int calculate_polish(char *polish_buf, double *res);
int check_polish_element_type(char a);
int use_binary_operation(result_struct *result, char a);
double s21_fmod(double x, double y);
int use_unary_operation(result_struct *result, char a);

#endif  // S21_CALC_H