#include "s21_calc.h"

int start_calc(char *math_calc_input_buf, double *result) {
  int exit_code = SUCCESS;
  char *polish_buf;
  polish_buf = calloc(strlen(math_calc_input_buf) * 2, sizeof(char));
  convert_to_polish(math_calc_input_buf, polish_buf);
  if (!calculate_polish(polish_buf, result)) {
    exit_code = ERROR;
  }
  free(polish_buf);
  return exit_code;
}

int convert_to_polish(char *math_calc_input_buf, char *polish_buf) {
  int exit_code = SUCCESS;
  int j = 0;
  char a;
  char *stack_buf;
  stack_buf = calloc(strlen(math_calc_input_buf), sizeof(char));
  for (int i = 0; i < strlen(math_calc_input_buf); i++) {
    a = math_calc_input_buf[i];
    int type = check_leksem_type(a);
    if (type == NUMBER) {
      polish_buf[j] = a;
      j++;
      int next_type = check_leksem_type(math_calc_input_buf[i + 1]);
      if (next_type != NUMBER) {
        polish_buf[j] = ' ';
        j++;
      }
    } else if (type == OPERATION) {
      if (a == SUB) {
        if (i == 0 || math_calc_input_buf[i - 1] == '(') {
          a = '~';
        }
      }
      sort_operation(a, &j, polish_buf, stack_buf);
    } else if (type == FUNCTION) {
      check_func_name(&a, math_calc_input_buf[i + 1], &i);
      sort_operation(a, &j, polish_buf, stack_buf);
    }
  }
  for (int i = (strlen(stack_buf) - 1); i >= 0; i--) {
    polish_buf[j] = stack_buf[i];
    j++;
  }
  free(stack_buf);
  return exit_code;
}

int check_leksem_type(char a) {
  int type;
  if ((a >= '0' && a <= '9') || a == '.' || a == 'X') {
    type = NUMBER;
  } else if (a == '(' || a == ')' || a == SUM || a == SUB || a == MUL ||
             a == DIV || a == EXP) {
    type = OPERATION;
  } else {
    type = FUNCTION;
  }
  return type;
}

void sort_operation(char a, int *j, char *polish_buf, char *stack_buf) {
  int new_operation_priority = check_priority(a);
  int long_stack = strlen(stack_buf);
  if (long_stack == 0) {
    stack_buf[0] = a;
  } else {
    for (int i = long_stack; i >= 0; i--) {
      int stack_operation_priority = 0;
      if (i != 0) {
        stack_operation_priority = check_priority(stack_buf[i - 1]);
      }
      if (stack_buf[0] == '\0') {
        stack_buf[0] = a;
      } else if (a == '(') {
        stack_buf[i] = a;
        break;
      } else if (a == ')') {
        for (int x = long_stack - 1; x >= 0; x--) {
          if (stack_buf[x] == '(') {
            stack_buf[x] = '\0';
            break;
          } else {
            polish_buf[*j] = stack_buf[x];
            stack_buf[x] = '\0';
            *j = *j + 1;
          }
        }
        break;
      } else if (new_operation_priority > stack_operation_priority) {
        stack_buf[i] = a;
        break;
      } else {
        polish_buf[*j] = stack_buf[i - 1];
        stack_buf[i - 1] = '\0';
        *j = *j + 1;
      }
    }
  }
}

int check_priority(char a) {
  int priority = 0;
  if (a == MUL || a == DIV || a == EXP || a == '~') {
    priority = 3;
  } else if (a == SUM || a == SUB) {
    priority = 2;
  } else if (a == '(' || a == ')') {
    priority = 1;
  } else if (a >= ASIN && a <= SQRT) {
    priority = 4;
  }
  return priority;
}

void check_func_name(char *a, char next, int *i) {
  if (*a == 'a') {
    if (next == 's') {
      *a = ASIN;
      *i = *i + 3;
    } else if (next == 'c') {
      *a = ACOS;
      *i = *i + 3;
    } else if (next == 't') {
      *a = ATAN;
      *i = *i + 3;
    }
  } else if (*a == 's') {
    if (next == 'i') {
      *a = SIN;
      *i = *i + 2;
    }
    if (next == 'q') {
      *a = SQRT;
      *i = *i + 3;
    }
  } else if (*a == 'c') {
    *a = COS;
    *i = *i + 2;
  } else if (*a == 'l') {
    if (next == 'n') {
      *a = LN;
      *i = *i + 1;
    } else if (next == 'o') {
      *a = LOG;
      *i = *i + 2;
    }
  } else if (*a == 't') {
    *a = TAN;
    *i = *i + 2;
  } else if (*a == 'm') {
    *a = MOD;
    *i = *i + 2;
  }
}

int calculate_polish(char *polish_buf, double *res) {
  int exit_code = SUCCESS;
  int long_polish = strlen(polish_buf);
  result_struct result;
  result.stack = calloc(long_polish, sizeof(double));
  result.count_elements = 0;
  char *char_to_double_buf;
  int j = 0;
  char_to_double_buf = calloc(long_polish, sizeof(char));
  for (int i = 0; i < long_polish; i++) {
    char a = polish_buf[i];
    if (a == ' ') {
      continue;
    }
    int type = check_polish_element_type(a);
    if (type == NUMBER) {
      int next_type = check_polish_element_type(polish_buf[i + 1]);
      char_to_double_buf[j] = a;
      j++;
      if (next_type != NUMBER) {
        result.stack[result.count_elements] = atof(char_to_double_buf);
        result.count_elements = result.count_elements + 1;
        memset(char_to_double_buf, '\0', long_polish);
        char_to_double_buf[0] = '\0';
        j = 0;
      }
    } else if (type == BINARY_OPERATOR) {
      if (!use_binary_operation(&result, a)) {
        exit_code = ERROR;
        break;
      }
    } else if (type == UNARY_OPERATOR) {
      if (!use_unary_operation(&result, a)) {
        exit_code = ERROR;
      }
    }
  }
  *res = result.stack[0];
  free(result.stack);
  free(char_to_double_buf);
  return exit_code;
}

int check_polish_element_type(char a) {
  int type;
  if ((a >= '0' && a <= '9') || a == '.' || a == 'X') {
    type = NUMBER;
  } else if (a == MOD || (check_leksem_type(a) == OPERATION && a != '~')) {
    type = BINARY_OPERATOR;
  } else if (a == '~') {
    type = UNARY_OPERATOR;
  } else {
    type = UNARY_OPERATOR;
  }
  return type;
}

int use_binary_operation(result_struct *result, char a) {
  int exit_code = SUCCESS;
  if (result->count_elements < 2) {
    exit_code = ERROR;
  } else {
    int top_stack = result->count_elements - 1;
    double x = result->stack[top_stack - 1];
    double y = result->stack[top_stack];
    double operation_result = 0;
    switch (a) {
      case SUM:
        operation_result = x + y;
        break;
      case SUB:
        operation_result = x - y;
        break;
      case MUL:
        operation_result = x * y;
        break;
      case DIV:
        if (y == 0) {
          exit_code = ERROR;
          break;
        } else {
          operation_result = x / y;
        }
        break;
      case EXP:
        operation_result = pow(x, y);
        break;
      case MOD:
        operation_result = s21_fmod(x, y);
        break;
    }
    result->stack[top_stack - 1] = operation_result;
    result->stack[top_stack] = 0;
    result->count_elements = result->count_elements - 1;
  }
  return exit_code;
}

double s21_fmod(double x, double y) {
  double fmod_x;
  long long int div;
  div = floor(x / y);
  fmod_x = x - (div * y);
  return fmod_x;
}

int use_unary_operation(result_struct *result, char a) {
  int exit_code = SUCCESS;
  if (result->count_elements < 1) {
    exit_code = ERROR;
  } else {
    int top_stack = result->count_elements - 1;
    double x = result->stack[top_stack];
    double operation_result = 0;
    switch (a) {
      case ASIN:
        operation_result = asin(x);
        break;
      case ACOS:
        operation_result = acos(x);
        break;
      case ATAN:
        operation_result = atan(x);
        break;
      case SIN:
        operation_result = sin(x);
        break;
      case COS:
        operation_result = cos(x);
        break;
      case LN:
        operation_result = log(x);
        break;
      case LOG:
        operation_result = log10(x);
        break;
      case TAN:
        operation_result = tan(x);
        break;
      case SQRT:
        operation_result = sqrt(x);
        break;
      case '~':
        operation_result = -x;
    }
    result->stack[top_stack] = operation_result;
  }
  return exit_code;
}
