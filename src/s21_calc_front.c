#include "s21_calc.h"

GtkWidget *math_calc_display;
GtkWidget *math_calc_display_x;
GtkWidget *math_calc_display_x_min;
GtkWidget *math_calc_display_x_max;
GtkWidget *math_calc_display_y_min;
GtkWidget *math_calc_display_y_max;
GtkWidget *show_err;
GtkWidget *graph_window;
GtkWidget *graph_image;
cairo_surface_t *surface;
cairo_t *cr;
cairo_text_extents_t te;
char math_calc_input_buf[255];
char math_calc_input_x_buf[255];
char math_calc_output_buf[255];
int buf_count_elemets = 0;
double result = 0.0;

int main(int argc, char **argv) {
  gtk_init(&argc, &argv);
  s21_main_window main_window;
  main_calc_widget(&main_window);
  math_calc_widget(&main_window);
  credit_calc_widget(&main_window);
  deposit_calc_widget(&main_window);
  gtk_widget_show_all(main_window.window);
  gtk_main();
  return 0;
}

void main_calc_widget(s21_main_window *main_window) {
  main_window->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(main_window->window), "SmartCalc v.1.0");
  gtk_widget_set_size_request(main_window->window, CALC_WIDHT, CALC_HEIGHT);
  gtk_container_set_border_width(GTK_CONTAINER(main_window->window),
                                 CALC_BORDER);
  g_signal_connect(G_OBJECT(main_window->window), "destroy",
                   G_CALLBACK(gtk_main_quit), NULL);
  main_window->notebook = gtk_notebook_new();
  gtk_container_add(GTK_CONTAINER(main_window->window), main_window->notebook);
}

void math_calc_widget(s21_main_window *main_window) {
  main_window->box[0] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  main_window->label[0] = gtk_label_new("Math calc");
  gtk_notebook_append_page(GTK_NOTEBOOK(main_window->notebook),
                           main_window->box[0], main_window->label[0]);
  s21_calc math_calc;
  math_calc_display = gtk_entry_new();
  gtk_editable_set_editable(GTK_EDITABLE(math_calc_display), FALSE);
  gtk_box_pack_start(GTK_BOX(main_window->box[0]), math_calc_display, TRUE,
                     TRUE, 5);
  add_buttons_math_calc(&math_calc);
  math_calc.grid = gtk_grid_new();
  gtk_grid_set_column_spacing(GTK_GRID(math_calc.grid), CALC_BORDER);
  gtk_grid_set_row_spacing(GTK_GRID(math_calc.grid), CALC_BORDER);
  gtk_grid_set_column_homogeneous(GTK_GRID(math_calc.grid), TRUE);
  gtk_grid_set_row_homogeneous(GTK_GRID(math_calc.grid), TRUE);
  gtk_box_pack_start(GTK_BOX(main_window->box[0]), math_calc.grid, TRUE, TRUE,
                     5);
  add_buttons_math_calc_to_grid(&math_calc);
  gtk_entry_set_text(GTK_ENTRY(math_calc_display), math_calc_input_buf);
  for (int i = 0; i <= 33; i++) {
    g_signal_connect(math_calc.button[i], "clicked", G_CALLBACK(calc_input),
                     NULL);
  }
}

void credit_calc_widget(s21_main_window *main_window) {
  main_window->box[1] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  s21_calc math_calc;
  main_window->label[1] = gtk_label_new("Credit calc");
  math_calc.button[0] = gtk_button_new_with_label("1");
  math_calc.button[1] = gtk_button_new_with_label("2");
  gtk_box_pack_start(GTK_BOX(main_window->box[1]), math_calc.button[0], TRUE,
                     TRUE, 20);
  gtk_box_pack_start(GTK_BOX(main_window->box[1]), math_calc.button[1], TRUE,
                     TRUE, 20);
  gtk_notebook_append_page(GTK_NOTEBOOK(main_window->notebook),
                           main_window->box[1], main_window->label[1]);
}

void deposit_calc_widget(s21_main_window *main_window) {
  main_window->box[2] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  s21_calc math_calc;
  main_window->label[2] = gtk_label_new("Deposit calc");
  math_calc.button[0] = gtk_button_new_with_label("1");
  math_calc.button[1] = gtk_button_new_with_label("2");
  gtk_box_pack_start(GTK_BOX(main_window->box[2]), math_calc.button[0], TRUE,
                     TRUE, 20);
  gtk_box_pack_start(GTK_BOX(main_window->box[2]), math_calc.button[1], TRUE,
                     TRUE, 20);
  gtk_notebook_append_page(GTK_NOTEBOOK(main_window->notebook),
                           main_window->box[2], main_window->label[2]);
}

void add_buttons_math_calc(s21_calc *math_calc) {
  math_calc->button[0] = gtk_button_new_with_label("0");
  math_calc->button[1] = gtk_button_new_with_label("1");
  math_calc->button[2] = gtk_button_new_with_label("2");
  math_calc->button[3] = gtk_button_new_with_label("3");
  math_calc->button[4] = gtk_button_new_with_label("4");
  math_calc->button[5] = gtk_button_new_with_label("5");
  math_calc->button[6] = gtk_button_new_with_label("6");
  math_calc->button[7] = gtk_button_new_with_label("7");
  math_calc->button[8] = gtk_button_new_with_label("8");
  math_calc->button[9] = gtk_button_new_with_label("9");
  math_calc->button[10] = gtk_button_new_with_label(".");
  math_calc->button[11] = gtk_button_new_with_label("AC");
  math_calc->button[12] = gtk_button_new_with_label("*");
  math_calc->button[13] = gtk_button_new_with_label("/");
  math_calc->button[14] = gtk_button_new_with_label("+");
  math_calc->button[15] = gtk_button_new_with_label("-");
  math_calc->button[16] = gtk_button_new_with_label("=");
  math_calc->button[18] = gtk_button_new_with_label("(");
  math_calc->button[19] = gtk_button_new_with_label(")");
  math_calc->button[20] = gtk_button_new_with_label("sqrt");
  math_calc->button[21] = gtk_button_new_with_label("mod");
  math_calc->button[22] = gtk_button_new_with_label("^");
  math_calc->button[23] = gtk_button_new_with_label("ln");
  math_calc->button[24] = gtk_button_new_with_label("log");
  math_calc->button[25] = gtk_button_new_with_label("tan");
  math_calc->button[26] = gtk_button_new_with_label("atan");
  math_calc->button[27] = gtk_button_new_with_label("sin");
  math_calc->button[28] = gtk_button_new_with_label("asin");
  math_calc->button[29] = gtk_button_new_with_label("cos");
  math_calc->button[30] = gtk_button_new_with_label("acos");
  math_calc->button[31] = gtk_button_new_with_label("graph");
  math_calc->button[32] = gtk_button_new_with_label("X");
  math_calc->button[33] = gtk_button_new_with_label("◄");
}

void add_buttons_math_calc_to_grid(s21_calc *math_calc) {
  math_calc_display_x = gtk_entry_new();
  math_calc_display_x_min = gtk_entry_new();
  math_calc_display_x_max = gtk_entry_new();
  math_calc_display_y_min = gtk_entry_new();
  math_calc_display_y_max = gtk_entry_new();

  math_calc->label[0] = gtk_label_new("Insert X:");
  math_calc->label[1] = gtk_label_new("Insert min X:");
  math_calc->label[2] = gtk_label_new("Insert max X:");
  math_calc->label[3] = gtk_label_new("Insert min Y:");
  math_calc->label[4] = gtk_label_new("Insert max Y:");
  show_err = gtk_label_new("Please, start");

  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[27], 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[28], 1, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[29], 2, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[30], 3, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[31], 4, 0, 1, 1);

  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[23], 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[24], 1, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[25], 2, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[26], 3, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[21], 4, 1, 1, 1);

  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[18], 0, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[19], 1, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[20], 2, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[22], 3, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[33], 4, 2, 1, 1);

  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[7], 0, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[8], 1, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[9], 2, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[12], 3, 3, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[11], 4, 3, 1, 2);

  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[4], 0, 4, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[5], 1, 4, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[6], 2, 4, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[13], 3, 4, 1, 1);

  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[1], 0, 5, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[2], 1, 5, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[3], 2, 5, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[14], 3, 5, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[16], 4, 5, 1, 2);

  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[32], 0, 6, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[0], 1, 6, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[10], 2, 6, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->button[15], 3, 6, 1, 1);

  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->label[0], 0, 7, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc_display_x, 1, 7, 2, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), show_err, 3, 7, 2, 1);

  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->label[1], 0, 8, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc_display_x_min, 1, 8, 1,
                  1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->label[2], 2, 8, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc_display_x_max, 3, 8, 1,
                  1);

  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->label[3], 0, 9, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc_display_y_min, 1, 9, 1,
                  1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc->label[4], 2, 9, 1, 1);
  gtk_grid_attach(GTK_GRID(math_calc->grid), math_calc_display_y_max, 3, 9, 1,
                  1);
}

void calc_input(GtkWidget *button, gpointer data) {
  const gchar *button_label;
  const gchar *x_value;
  range range;
  button_label = gtk_button_get_label(GTK_BUTTON(button));
  x_value = gtk_entry_get_text(GTK_ENTRY(math_calc_display_x));
  range.x_value_min = gtk_entry_get_text(GTK_ENTRY(math_calc_display_x_min));
  range.x_value_max = gtk_entry_get_text(GTK_ENTRY(math_calc_display_x_max));
  range.y_value_min = gtk_entry_get_text(GTK_ENTRY(math_calc_display_y_min));
  range.y_value_max = gtk_entry_get_text(GTK_ENTRY(math_calc_display_y_max));
  strcat(math_calc_input_x_buf, x_value);
  if (button_label[0] < 0) {
    math_calc_input_buf[strlen(math_calc_input_buf) - buf_count_elemets] = '\0';
    gtk_entry_set_text(GTK_ENTRY(math_calc_display), math_calc_input_buf);
  } else if (button_label[0] == 65) {
    math_calc_input_buf[0] = '\0';
    math_calc_input_x_buf[0] = '\0';
    gtk_entry_set_text(GTK_ENTRY(math_calc_display), "");
    gtk_entry_set_text(GTK_ENTRY(math_calc_display_x), "");
    gtk_entry_set_text(GTK_ENTRY(math_calc_display_x_min), "");
    gtk_entry_set_text(GTK_ENTRY(math_calc_display_x_max), "");
    gtk_entry_set_text(GTK_ENTRY(math_calc_display_y_min), "");
    gtk_entry_set_text(GTK_ENTRY(math_calc_display_y_max), "");
  } else if (button_label[0] == 61) {
    if (math_calc_input_x_buf[0] != '\0') {
      add_x_to_input_buf(math_calc_input_x_buf, math_calc_input_buf);
    }
    if (!start_calc(math_calc_input_buf, &result)) {
      sprintf(math_calc_output_buf, "%s", "CALCULATION ERROR");
      gtk_entry_set_text(GTK_ENTRY(math_calc_display), math_calc_output_buf);
      math_calc_input_buf[0] = '\0';
    } else {
      sprintf(math_calc_input_buf, "%.7lf", result);
      gtk_entry_set_text(GTK_ENTRY(math_calc_display), math_calc_input_buf);
    }

  } else if (button_label[0] == 'g') {
    create_graph_window(&range);
  } else if (math_calc_input_buf[254] == '\0') {
    buf_count_elemets = strlen(button_label);
    strcat(math_calc_input_buf, button_label);
    gtk_entry_set_text(GTK_ENTRY(math_calc_display), math_calc_input_buf);
  }

  check_input_buf();
}

void check_input_buf() {
  int flag = 0;
  const int check[19] = {40, 48, 49, 50, 51,  52,  53,  54,  55, 56,
                         57, 88, 97, 99, 105, 108, 109, 115, 116};
  for (int i = 0; i < 19; i++) {
    if (math_calc_input_buf[0] == check[i]) {
      flag = 1;
      break;
    }
  }
  if (flag == 1) {
    gtk_label_set_label(GTK_LABEL(show_err), "All good!");
  } else if (math_calc_input_buf[0] == 0) {
    gtk_label_set_label(GTK_LABEL(show_err), "Please, start");
  } else {
    gtk_label_set_label(GTK_LABEL(show_err), "Invalid input!");
  }
}

void create_graph_window(range *range) {
  GdkRectangle workarea = {0};
  gdk_monitor_get_workarea(
      gdk_display_get_primary_monitor(gdk_display_get_default()), &workarea);
  double graph_size = workarea.height < workarea.width ? workarea.height * 0.7
                                                       : workarea.width * 0.7;
  double_range double_range;
  double_range.x_min = atof(range->x_value_min);
  double_range.x_max = atof(range->x_value_max);
  double_range.y_min = atof(range->y_value_min);
  double_range.y_max = atof(range->y_value_max);
  double scale_x;
  double scale_y;
  if (double_range.x_min < 0 && double_range.x_max > 0) {
    scale_x =
        graph_size / (fabs(double_range.x_min) + fabs(double_range.x_max));
  } else {
    scale_x =
        graph_size / (fabs(double_range.x_max) - fabs(double_range.x_min));
    scale_x = scale_x > 0 ? scale_x : -scale_x;
  }
  if (double_range.y_min < 0 && double_range.y_max > 0) {
    scale_y =
        graph_size / (fabs(double_range.y_min) + fabs(double_range.y_max));
  } else {
    scale_y =
        graph_size / (fabs(double_range.y_max) - fabs(double_range.y_min));
    scale_y = scale_y > 0 ? scale_y : -scale_y;
  }
  graph_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
                                       (graph_size + GRAPH_BORDER * 2),
                                       (graph_size + GRAPH_BORDER * 2));
  cr = cairo_create(surface);
  graph_image = gtk_image_new_from_surface(surface);
  gtk_window_set_title(GTK_WINDOW(graph_window), "Graph");
  gtk_widget_set_size_request(graph_window, (graph_size + GRAPH_BORDER * 2),
                              (graph_size + GRAPH_BORDER * 2));
  g_signal_connect(G_OBJECT(graph_window), "destroy",
                   G_CALLBACK(gtk_widget_destroy), NULL);
  gtk_container_add(GTK_CONTAINER(graph_window), graph_image);
  show_graph(&double_range, scale_x, scale_y, graph_size);
  show_scale(graph_size, scale_x, scale_y);
  show_axis(&double_range, scale_x, scale_y);
  show_border(&double_range, graph_size);
  show_adaptive_net(&double_range, graph_size, scale_x, scale_y);

  gtk_widget_show_all(graph_window);
}

void show_scale(double graph_size, double scale_x,
                double scale_y) {  // показать масштаб в виде текста
  char scale_text[20] = {"Scale 1/"};
  char scale_text_buf[20];
  sprintf(scale_text_buf, "%.2lf", (scale_x + scale_y) / 2);
  strcat(scale_text, scale_text_buf);
  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
  cairo_select_font_face(cr, "Georgia", CAIRO_FONT_SLANT_NORMAL,
                         CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size(cr, 20);
  cairo_text_extents(cr, scale_text, &te);
  cairo_move_to(cr, (graph_size - GRAPH_BORDER * 3), (GRAPH_BORDER / 1.5));
  cairo_show_text(cr, scale_text);
}

void show_axis(double_range *double_range, double scale_x,
               double scale_y) {  // показать нулевые оси
  cairo_set_source_rgb(cr, 0, 0, 0);
  cairo_set_line_width(cr, 0.5);
  if (double_range->y_min < 0 && double_range->y_max > 0) {
    cairo_move_to(
        cr, GRAPH_BORDER,
        (GRAPH_BORDER + fabs(double_range->y_max) * scale_y));  // ось Х нулевая
    cairo_line_to(
        cr,
        (GRAPH_BORDER +
         (fabs(double_range->x_min) + fabs(double_range->x_max)) * scale_x),
        (GRAPH_BORDER + fabs(double_range->y_max) * scale_y));
  }
  if (double_range->x_min < 0 && double_range->x_max > 0) {
    cairo_move_to(cr, (GRAPH_BORDER + fabs(double_range->x_min) * scale_x),
                  GRAPH_BORDER);  // ось Y нулевая
    cairo_line_to(
        cr, (GRAPH_BORDER + fabs(double_range->x_min) * scale_x),
        (GRAPH_BORDER +
         (fabs(double_range->y_min) + fabs(double_range->y_max)) * scale_y));
  }
  cairo_stroke(cr);
}

void show_border(double_range *double_range,
                 double graph_size) {  // показать границы графика
  char border_text[8];
  cairo_set_font_size(cr, 10);
  cairo_move_to(cr, GRAPH_BORDER, GRAPH_BORDER);
  cairo_line_to(cr, GRAPH_BORDER, GRAPH_BORDER + graph_size);
  cairo_move_to(cr, GRAPH_BORDER, GRAPH_BORDER);
  cairo_line_to(cr, graph_size + GRAPH_BORDER, GRAPH_BORDER);
  cairo_move_to(cr, graph_size + GRAPH_BORDER, GRAPH_BORDER + graph_size);
  cairo_line_to(cr, graph_size + GRAPH_BORDER, GRAPH_BORDER);
  cairo_move_to(cr, GRAPH_BORDER, GRAPH_BORDER + graph_size);
  cairo_line_to(cr, GRAPH_BORDER + graph_size, GRAPH_BORDER + graph_size);
  cairo_stroke(cr);

  sprintf(border_text, "%.lf", double_range->x_min);
  cairo_text_extents(cr, border_text, &te);
  cairo_move_to(cr, GRAPH_BORDER, (GRAPH_BORDER * 2 + graph_size));
  cairo_save(cr);
  cairo_rotate(cr, 200);
  cairo_show_text(cr, border_text);
  cairo_restore(cr);

  sprintf(border_text, "%.lf", double_range->y_max);
  cairo_text_extents(cr, border_text, &te);
  cairo_move_to(cr, 0, GRAPH_BORDER);
  cairo_show_text(cr, border_text);

  sprintf(border_text, "%.lf", double_range->x_max);
  cairo_text_extents(cr, border_text, &te);
  cairo_move_to(cr, GRAPH_BORDER + graph_size, (GRAPH_BORDER * 2 + graph_size));
  cairo_save(cr);
  cairo_rotate(cr, 200);
  cairo_show_text(cr, border_text);
  cairo_restore(cr);

  cairo_move_to(cr, 0, GRAPH_BORDER + graph_size);
  sprintf(border_text, "%.lf", double_range->y_min);
  cairo_text_extents(cr, border_text, &te);
  cairo_show_text(cr, border_text);
}

void show_adaptive_net(double_range *double_range, double graph_size,
                       double scale_x,
                       double scale_y) {  // показать адаптивную сетку
  double graph_grid = graph_size / GRAPH_NET_NUMBER;
  cairo_set_line_width(cr, 0.2);
  if (double_range->x_min < 0 && double_range->x_max > 0) {
    show_x_with_axis(double_range, graph_size, scale_x, graph_grid);
  } else {
    show_x_without_axis(double_range, graph_size, scale_x, graph_grid);
  }
  if (double_range->y_min < 0 && double_range->y_max > 0) {
    show_y_with_axis(double_range, graph_size, scale_y, graph_grid);
  } else {
    show_y_without_axis(double_range, graph_size, scale_y, graph_grid);
  }
}

void show_graph(double_range *double_range, double scale_x, double scale_y,
                double graph_size) {  // показать график
  double start_x = 0;
  double start_y;
  double y;
  double start_x_buf;
  cairo_set_line_width(cr, 0.8);
  for (int x = double_range->x_min; x <= double_range->x_max;
       x++) {  // находим точку старта графика (первая точка в пределах)
    char x_value_buf[10];
    char *buf = calloc(100, sizeof(char));
    strcat(buf, math_calc_input_buf);
    sprintf(x_value_buf, "%d", x);
    add_x_to_input_buf(x_value_buf, buf);
    start_calc(buf, &start_y);
    free(buf);
    if (double_range->y_min <= start_y && start_y <= double_range->y_max) {
      start_x = x;
      break;
    }
  }
  start_x_buf = start_x;
  set_coordinate(&start_x, &start_y, double_range, scale_x, scale_y);
  cairo_move_to(cr, start_x, start_y);
  for (double i = start_x_buf; i >= double_range->x_min; i--) {
    double x = i;
    char x_value_buf[10];
    char *buf = calloc(100, sizeof(char));
    strcat(buf, math_calc_input_buf);
    sprintf(x_value_buf, "%.lf", x);
    add_x_to_input_buf(x_value_buf, buf);
    start_calc(buf, &y);
    set_coordinate(&x, &y, double_range, scale_x, scale_y);
    cairo_line_to(cr, x, y);
    free(buf);
  }
  cairo_move_to(cr, start_x, start_y);
  for (double i = start_x_buf; i <= double_range->x_max; i++) {
    double x = i;
    char x_value_buf[10];
    char *buf = calloc(100, sizeof(char));
    strcat(buf, math_calc_input_buf);
    sprintf(x_value_buf, "%.lf", x);
    add_x_to_input_buf(x_value_buf, buf);
    start_calc(buf, &y);
    set_coordinate(&x, &y, double_range, scale_x, scale_y);
    cairo_line_to(cr, x, y);
    free(buf);
  }
  cairo_stroke(cr);
  cairo_set_source_rgb(cr, 255, 255, 255);
  cairo_rectangle(cr, 0, 0, graph_size + GRAPH_BORDER * 2, GRAPH_BORDER);
  cairo_rectangle(cr, 0, GRAPH_BORDER, GRAPH_BORDER, graph_size);
  cairo_rectangle(cr, 0, GRAPH_BORDER + graph_size,
                  graph_size + GRAPH_BORDER * 2, GRAPH_BORDER);
  cairo_rectangle(cr, GRAPH_BORDER + graph_size, GRAPH_BORDER, GRAPH_BORDER,
                  graph_size);
  cairo_fill(cr);
}

void set_coordinate(double *x, double *y, double_range *double_range,
                    double scale_x, double scale_y) {
  if (double_range->x_min < 0 && double_range->x_max > 0) {
    double x_buf;
    if (*x > 0) {
      x_buf = fabs(double_range->x_min) + fabs(*x);
    }
    if (*x == 0) {
      x_buf = fabs(double_range->x_min);
    }
    if (*x < 0) {
      x_buf = fabs(double_range->x_min) - fabs(*x);
    }
    *x = x_buf * scale_x + GRAPH_BORDER;
  } else {
    *x = (*x - double_range->x_min) * scale_x + GRAPH_BORDER;
  }
  if (double_range->y_min < 0 && double_range->y_max > 0) {
    double y_buf;
    if (*y > 0) {
      y_buf = fabs(double_range->y_max) - fabs(*y);
    }
    if (*y == 0) {
      y_buf = fabs(double_range->y_max);
    }
    if (*y < 0) {
      y_buf = fabs(double_range->y_max) + fabs(*y);
    }
    *y = y_buf * scale_y + GRAPH_BORDER;
  } else {
    *y = (double_range->y_max - *y) * scale_y + GRAPH_BORDER;
  }
}

void add_x_to_input_buf(char *math_calc_input_x_buf,
                        char *math_calc_input_buf) {
  int long_x_buf = strlen(math_calc_input_x_buf);
  int long_input_buf = strlen(math_calc_input_buf);
  int changing_lang = long_input_buf;
  for (int i = 0; i < changing_lang; i++) {
    if (math_calc_input_buf[i] == 'X') {
      changing_lang = long_input_buf + long_x_buf;
      for (int x = long_input_buf - 1; x > i; x--) {
        math_calc_input_buf[x + long_x_buf - 1] = math_calc_input_buf[x];
      }
      int y = i;
      for (int j = 0; j < long_x_buf; j++) {
        math_calc_input_buf[y] = math_calc_input_x_buf[j];
        y++;
      }
    }
  }
}

void show_x_with_axis(double_range *double_range, double graph_size,
                      double scale_x, double graph_grid) {
  double grid_x_name_step =
      (fabs(double_range->x_min) + fabs(double_range->x_max)) /
      GRAPH_NET_NUMBER;
  int count_x_lines = fabs(double_range->x_min) / grid_x_name_step;
  double x_start =
      fabs(double_range->x_min) * scale_x - count_x_lines * graph_grid;
  double grid_name_step_buf_x = count_x_lines * grid_x_name_step;
  grid_name_step_buf_x = -grid_name_step_buf_x;
  for (double i = x_start; i < graph_size;
       i = i + graph_grid) {  // вертикальные линии
    char vertical_line_name[10];
    cairo_move_to(cr, GRAPH_BORDER + i, GRAPH_BORDER);
    cairo_line_to(cr, GRAPH_BORDER + i, GRAPH_BORDER + graph_size);
    if (grid_x_name_step < 1) {
      sprintf(vertical_line_name, "%.1lf", grid_name_step_buf_x);
    } else {
      sprintf(vertical_line_name, "%.lf", grid_name_step_buf_x);
    }
    grid_name_step_buf_x = grid_name_step_buf_x + grid_x_name_step;
    cairo_text_extents(cr, vertical_line_name, &te);
    cairo_move_to(cr, GRAPH_BORDER + i, (GRAPH_BORDER * 2 + graph_size));
    cairo_save(cr);
    cairo_rotate(cr, 200);
    cairo_show_text(cr, vertical_line_name);
    cairo_restore(cr);
  }
  cairo_stroke(cr);
}

void show_y_with_axis(double_range *double_range, double graph_size,
                      double scale_y, double graph_grid) {
  double grid_y_name_step =
      (fabs(double_range->y_min) + fabs(double_range->y_max)) /
      GRAPH_NET_NUMBER;
  int count_y_lines = fabs(double_range->y_max) / grid_y_name_step;
  double y_start =
      fabs(double_range->y_max) * scale_y - count_y_lines * graph_grid;
  double grid_name_step_buf_y = count_y_lines * grid_y_name_step;
  for (double i = y_start; i < graph_size;
       i = i + graph_grid) {  // горизонтальные линии
    char horizontal_line_name[10];
    cairo_move_to(cr, GRAPH_BORDER, GRAPH_BORDER + i);
    cairo_line_to(cr, GRAPH_BORDER + graph_size, GRAPH_BORDER + i);
    if (grid_y_name_step < 1) {
      sprintf(horizontal_line_name, "%.1lf", grid_name_step_buf_y);
    } else {
      sprintf(horizontal_line_name, "%.lf", grid_name_step_buf_y);
    }
    cairo_text_extents(cr, horizontal_line_name, &te);
    cairo_move_to(cr, 0, GRAPH_BORDER + i);
    cairo_show_text(cr, horizontal_line_name);
    grid_name_step_buf_y = grid_name_step_buf_y - grid_y_name_step;
  }
  cairo_stroke(cr);
}

void show_x_without_axis(double_range *double_range, double graph_size,
                         double scale_x, double graph_grid) {
  double grid_x_name_step =
      (double_range->x_max - double_range->x_min) / GRAPH_NET_NUMBER;
  double grid_name_step_buf_x = fabs(grid_x_name_step) + double_range->x_min;
  for (double i = graph_grid; i < graph_size; i = i + graph_grid) {
    char vertical_line_name[10];
    cairo_move_to(cr, GRAPH_BORDER + i, GRAPH_BORDER);
    cairo_line_to(cr, GRAPH_BORDER + i, GRAPH_BORDER + graph_size);
    if (grid_x_name_step < 1) {
      sprintf(vertical_line_name, "%.1lf", grid_name_step_buf_x);
    } else {
      sprintf(vertical_line_name, "%.lf", grid_name_step_buf_x);
    }
    grid_name_step_buf_x = grid_name_step_buf_x + fabs(grid_x_name_step);
    cairo_text_extents(cr, vertical_line_name, &te);
    cairo_move_to(cr, GRAPH_BORDER + i, (GRAPH_BORDER * 2 + graph_size));
    cairo_save(cr);
    cairo_rotate(cr, 200);
    cairo_show_text(cr, vertical_line_name);
    cairo_restore(cr);
  }
  cairo_stroke(cr);
}

void show_y_without_axis(double_range *double_range, double graph_size,
                         double scale_y, double graph_grid) {
  double grid_y_name_step =
      (double_range->y_max - double_range->y_min) / GRAPH_NET_NUMBER;
  // int count_y_lines = fabs(double_range->y_max) / grid_y_name_step;
  // double y_start = fabs(double_range->y_max) * scale_y - count_y_lines *
  // graph_grid;
  double grid_name_step_buf_y = double_range->y_max - grid_y_name_step;
  for (double i = graph_grid; i < graph_size; i = i + graph_grid) {
    char horizontal_line_name[10];
    cairo_move_to(cr, GRAPH_BORDER, GRAPH_BORDER + i);
    cairo_line_to(cr, GRAPH_BORDER + graph_size, GRAPH_BORDER + i);
    if (grid_y_name_step < 1) {
      sprintf(horizontal_line_name, "%.1lf", grid_name_step_buf_y);
    } else {
      sprintf(horizontal_line_name, "%.lf", grid_name_step_buf_y);
    }
    cairo_text_extents(cr, horizontal_line_name, &te);
    cairo_move_to(cr, 0, GRAPH_BORDER + i);
    cairo_show_text(cr, horizontal_line_name);
    grid_name_step_buf_y = grid_name_step_buf_y - grid_y_name_step;
  }
  cairo_stroke(cr);
}
