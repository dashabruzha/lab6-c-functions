```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

unsigned long long gcd_two(unsigned long long a, unsigned long long b);
unsigned long long gcd_three(unsigned long long a, unsigned long long b, unsigned long long c);
bool can_form_triangle(double x, double y, double z);
double triangle_area_heron(double x, double y, double z);
void solve_task2(double a, double b, double c, double d);
bool find_sum_of_squares(unsigned long long n, long long *x, long long *y);
long long find_k_bounds(double x, double y);
unsigned long long count_hundreds(unsigned long long n);
int sum_digits_ull(unsigned long long n);
bool check_task6(int n);
int sum_first_k_digits(unsigned long long n, int k);
unsigned long long prod_by_last_digit(unsigned long long n, unsigned long long m);
unsigned long long remove_0_and_5(unsigned long long n);
void solve_task10(long long n);
unsigned long long ackermann(unsigned int n, unsigned int m);
int count_digits_int(int x);
bool is_armstrong(int x);
void print_armstrong_2_to_4(void);
bool can_reach_n(int n, int adj[][64]);
double triangle_area_coords(double x1, double y1, double x2, double y2, double x3, double y3);
bool intersect_lines(double a1, double b1, double c1,
                     double a2, double b2, double c2,
                     double *px, double *py);
void solve_task15(double a[3], double b[3], double c[3]);
bool is_prime_int(int x);
void print_twin_primes(int n);
unsigned long long binom_coeff(int n, int k);
void print_pascal_triangle(int n);
void solve_8_queens_rec(int row, int cols, int diag1, int diag2, int pos[], int *count, bool print_all);
void merge_two_runs(int *src, int *dst, int left, int mid, int right);
void von_neumann_sort(int a[], int n);
void swap_arrays_no_temp(int x[], int y[], int size);
int filter_non_decreasing(const int arr[], int n, int out[]);
void find_all_half_fractions(void);
bool used_digits_ok(long long a, long long b, int *used_count);
void find_card_fractions_nm(unsigned long long n_num, unsigned long long m_den);

static void clear_stdin(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

unsigned long long gcd_two(unsigned long long a, unsigned long long b) {
    while (b != 0ULL) {
        unsigned long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

unsigned long long gcd_three(unsigned long long a, unsigned long long b, unsigned long long c) {
    return gcd_two(gcd_two(a, b), c);
}

bool can_form_triangle(double x, double y, double z) {
    const double eps = 1e-9;
    return (x > eps && y > eps && z > eps) &&
           (x + y > z + eps) &&
           (x + z > y + eps) &&
           (y + z > x + eps);
}

double triangle_area_heron(double x, double y, double z) {
    double p = 0.5 * (x + y + z);
    double val = p * (p - x) * (p - y) * (p - z);
    return (val > 0.0) ? sqrt(val) : 0.0;
}

void solve_task2(double a, double b, double c, double d) {
    double segs[4] = {a, b, c, d};
    const char *names[4] = {"a", "b", "c", "d"};
    int found = 0;

    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            for (int k = j + 1; k < 4; ++k) {
                if (can_form_triangle(segs[i], segs[j], segs[k])) {
                    double area = triangle_area_heron(segs[i], segs[j], segs[k]);
                    printf("Тройка (%s, %s, %s) = (%.2f, %.2f, %.2f): треугольник возможен, площадь = %.4f\n",
                           names[i], names[j], names[k], segs[i], segs[j], segs[k], area);
                    found++;
                } else {
                    printf("Тройка (%s, %s, %s) = (%.2f, %.2f, %.2f): треугольник невозможен\n",
                           names[i], names[j], names[k], segs[i], segs[j], segs[k]);
                }
            }
        }
    }
    if (found == 0) {
        printf("Ни из одной тройки отрезков нельзя построить треугольник.\n");
    }
}

bool find_sum_of_squares(unsigned long long n, long long *x, long long *y) {
    long long limit = (long long)floor(sqrt((long double)n));
    for (long long i = 0; i <= limit; ++i) {
        unsigned long long sq_i = (unsigned long long)i * (unsigned long long)i;
        if (sq_i > n) break;
        unsigned long long rem = n - sq_i;
        long long j = (long long)floor(sqrt((long double)rem));
        if ((unsigned long long)j * (unsigned long long)j == rem) {
            *x = i;
            *y = j;
            return true;
        }
    }
    return false;
}

long long find_k_bounds(double x, double y) {
    long long k = 0;
    double cur = 1.0;

    if (x >= 1.0) {
        while (cur <= x) {
            cur *= y;
            k++;
        }
    } else {
        while (cur > x) {
            cur /= y;
            k--;
        }
        k++;
    }
    return k;
}

unsigned long long count_hundreds(unsigned long long n) {
    return n / 100ULL;
}

int sum_digits_ull(unsigned long long n) {
    int s = 0;
    while (n > 0ULL) {
        s += (int)(n % 10ULL);
        n /= 10ULL;
    }
    return s;
}

bool check_task6(int n) {
    long long sq = (long long)n * (long long)n;
    int sd = sum_digits_ull((unsigned long long)n);
    return (sq - sd) == 0LL;
}

int sum_first_k_digits(unsigned long long n, int k) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%llu", n);
    int len = (int)strlen(buf);
    if (k < 1) k = 1;
    if (k > 4) k = 4;
    if (k > len) k = len;

    int sum = 0;
    for (int i = 0; i < k; ++i) {
        sum += buf[i] - '0';
    }
    return sum;
}

unsigned long long prod_by_last_digit(unsigned long long n, unsigned long long m) {
    unsigned long long last = m % 10ULL;
    return n * last;
}

unsigned long long remove_0_and_5(unsigned long long n) {
    unsigned long long digits[32];
    int cnt = 0;
    while (n > 0ULL) {
        unsigned long long d = n % 10ULL;
        if (d != 0ULL && d != 5ULL) {
            digits[cnt++] = d;
        }
        n /= 10ULL;
    }
    unsigned long long res = 0ULL;
    for (int i = cnt - 1; i >= 0; --i) {
        res = res * 10ULL + digits[i];
    }
    return res;
}

void solve_task10(long long n) {
    printf("Целые K, делящиеся на K^2 и не делящиеся на K^3 (с учётом ограничения |K| <= |N|): ");
    bool any = false;
    long long limit = llabs(n);
    for (long long k = -1; k <= 1; ++k) {
        if (llabs(k) <= limit) {
            if (k == 0) {
                printf("0 (деление на 0 не определено) ");
            } else {
                printf("%lld ", k);
                any = true;
            }
        }
    }
    if (!any) printf("нет");
    printf("\n");
}

unsigned long long ackermann(unsigned int n, unsigned int m) {
    if (n == 0U) return (unsigned long long)m + 1ULL;
    if (m == 0U) return ackermann(n - 1U, 1U);
    return ackermann(n - 1U, ackermann(n, m - 1U));
}

int count_digits_int(int x) {
    int c = 0;
    while (x > 0) {
        c++;
        x /= 10;
    }
    return (c == 0) ? 1 : c;
}

bool is_armstrong(int x) {
    int p = count_digits_int(x);
    int temp = x;
    long long sum = 0;
    while (temp > 0) {
        int d = temp % 10;
        long long term = 1;
        for (int i = 0; i < p; ++i) term *= d;
        sum += term;
        temp /= 10;
    }
    return sum == (long long)x;
}

void print_armstrong_2_to_4(void) {
    printf("Числа Армстронга (2, 3 и 4 цифры): ");
    for (int x = 10; x <= 9999; ++x) {
        if (is_armstrong(x)) {
            printf("%d ", x);
        }
    }
    printf("\n");
}

bool can_reach_n(int n, int adj[][64]) {
    if (n <= 1) return true;
    bool visited[64] = {false};
    int queue[64];
    int head = 0, tail = 0;

    visited[1] = true;
    queue[tail++] = 1;

    while (head < tail) {
        int u = queue[head++];
        if (u == n) return true;
        for (int v = 1; v <= n; ++v) {
            if (adj[u][v] && !visited[v]) {
                visited[v] = true;
                queue[tail++] = v;
            }
        }
    }
    return visited[n];
}

double triangle_area_coords(double x1, double y1, double x2, double y2, double x3, double y3) {
    return 0.5 * fabs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));
}

bool intersect_lines(double a1, double b1, double c1,
                     double a2, double b2, double c2,
                     double *px, double *py) {
    double det = a1 * b2 - a2 * b1;
    if (fabs(det) < 1e-12) return false;
    *px = (c1 * b2 - c2 * b1) / det;
    *py = (a1 * c2 - a2 * c1) / det;
    return true;
}

void solve_task15(double a[3], double b[3], double c[3]) {
    double x[3], y[3];
    bool ok01 = intersect_lines(a[0], b[0], c[0], a[1], b[1], c[1], &x[0], &y[0]);
    bool ok12 = intersect_lines(a[1], b[1], c[1], a[2], b[2], c[2], &x[1], &y[1]);
    bool ok20 = intersect_lines(a[2], b[2], c[2], a[0], b[0], c[0], &x[2], &y[2]);

    if (!ok01 || !ok12 || !ok20) {
        printf("Прямые не пересекаются попарно в трёх различных точках (треугольник не образуется).\n");
        return;
    }

    double area = triangle_area_coords(x[0], y[0], x[1], y[1], x[2], y[2]);
    if (area < 1e-12) {
        printf("Все три прямые пересекаются в одной точке — площадь треугольника равна 0.\n");
        return;
    }

    printf("Вершины треугольника: (%.4f, %.4f), (%.4f, %.4f), (%.4f, %.4f)\n",
           x[0], y[0], x[1], y[1], x[2], y[2]);
    printf("Площадь треугольника: %.4f\n", area);
}

bool is_prime_int(int x) {
    if (x < 2) return false;
    if (x == 2) return true;
    if (x % 2 == 0) return false;
    for (int d = 3; d * d <= x; d += 2) {
        if (x % d == 0) return false;
    }
    return true;
}

void print_twin_primes(int n) {
    printf("Пары простых чисел-близнецов в [%d, %d]:\n", n, 2 * n);
    int found = 0;
    for (int p = n; p + 2 <= 2 * n; ++p) {
        if (is_prime_int(p) && is_prime_int(p + 2)) {
            printf("(%d, %d)\n", p, p + 2);
            found++;
        }
    }
    if (found == 0) printf("Пар не найдено.\n");
}

unsigned long long binom_coeff(int n, int k) {
    if (k < 0 || k > n) return 0ULL;
    if (k > n - k) k = n - k;
    unsigned long long res = 1ULL;
    for (int i = 0; i < k; ++i) {
        res = res * (unsigned long long)(n - i) / (unsigned long long)(i + 1);
    }
    return res;
}

void print_pascal_triangle(int n) {
    for (int i = 0; i < n; ++i) {
        for (int sp = 0; sp < n - i - 1; ++sp) {
            printf("   ");
        }
        for (int j = 0; j <= i; ++j) {
            printf("%6llu", binom_coeff(i, j));
        }
        printf("\n");
    }
}

void solve_8_queens_rec(int row, int cols, int diag1, int diag2, int pos[], int *count, bool print_all) {
    const int N = 8;
    if (row == N) {
        (*count)++;
        if (print_all) {
            printf("#%2d: ", *count);
            for (int r = 0; r < N; ++r) {
                printf("(%d,%d)%s", r + 1, pos[r] + 1, (r + 1 < N) ? " " : "\n");
            }
        }
        return;
    }

    int free_mask = ((1 << N) - 1) & ~(cols | diag1 | diag2);
    while (free_mask != 0) {
        int bit = free_mask & -free_mask;
        int col = 0;
        while ((1 << col) != bit) col++;

        pos[row] = col;
        solve_8_queens_rec(row + 1,
                           cols | bit,
                           (diag1 | bit) << 1,
                           (diag2 | bit) >> 1,
                           pos, count, print_all);
        free_mask ^= bit;
    }
}

void merge_two_runs(int *src, int *dst, int left, int mid, int right) {
    int i = left;
    int j = mid;
    int k = left;
    while (i < mid && j < right) {
        if (src[i] <= src[j]) dst[k++] = src[i++];
        else dst[k++] = src[j++];
    }
    while (i < mid) dst[k++] = src[i++];
    while (j < right) dst[k++] = src[j++];
}

void von_neumann_sort(int a[], int n) {
    if (n <= 1) return;
    int *b = (int *)malloc((size_t)n * sizeof(int));
    if (!b) return;

    int *from_A = a;
    int *to_B = b;
    bool in_A = true;

    for (int width = 1; width < n; width *= 2) {
        for (int left = 0; left < n; left += 2 * width) {
            int mid = left + width;
            if (mid > n) mid = n;
            int right = left + 2 * width;
            if (right > n) right = n;
            merge_two_runs(from_A, to_B, left, mid, right);
        }
        int *tmp = from_A;
        from_A = to_B;
        to_B = tmp;
        in_A = !in_A;
    }

    if (!in_A) {
        memcpy(a, b, (size_t)n * sizeof(int));
    }
    free(b);
}

void swap_arrays_no_temp(int x[], int y[], int size) {
    for (int k = 0; k < size; ++k) {
        if (x[k] != y[k]) {
            x[k] ^= y[k];
            y[k] ^= x[k];
            x[k] ^= y[k];
        }
    }
}

int filter_non_decreasing(const int arr[], int n, int out[]) {
    if (n <= 0) return 0;
    int m = 0;
    out[m++] = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] >= out[m - 1]) {
            out[m++] = arr[i];
        }
    }
    return m;
}

void find_all_half_fractions(void) {
    printf("Все комбинации с 4-значным числителем и 5-значным знаменателем (все цифры 1..9 ровно по 1 разу), равные 1/2:\n");
    int count = 0;
    for (long long num = 1234; num <= 4987; ++num) {
        long long den = 2 * num;
        if (den < 10000 || den > 98765) continue;

        int used[10] = {0};
        bool ok = true;

        long long t = num;
        while (t > 0) {
            int d = (int)(t % 10);
            if (d == 0 || used[d]) { ok = false; break; }
            used[d] = 1;
            t /= 10;
        }
        if (!ok) continue;

        t = den;
        while (t > 0) {
            int d = (int)(t % 10);
            if (d == 0 || used[d]) { ok = false; break; }
            used[d] = 1;
            t /= 10;
        }
        if (!ok) continue;

        int total = 0;
        for (int d = 1; d <= 9; ++d) total += used[d];
        if (total == 9) {
            count++;
            printf("%2d) %lld / %lld = 1/2\n", count, num, den);
        }
    }
    printf("Всего комбинаций: %d\n", count);
}

bool used_digits_ok(long long a, long long b, int *used_count) {
    int used[10] = {0};
    long long t = a;
    while (t > 0) {
        int d = (int)(t % 10);
        if (d == 0 || used[d]) return false;
        used[d] = 1;
        t /= 10;
    }
    t = b;
    while (t > 0) {
        int d = (int)(t % 10);
        if (d == 0 || used[d]) return false;
        used[d] = 1;
        t /= 10;
    }
    int c = 0;
    for (int d = 1; d <= 9; ++d) c += used[d];
    *used_count = c;
    return true;
}

void find_card_fractions_nm(unsigned long long n_num, unsigned long long m_den) {
    if (n_num == 0ULL || m_den == 0ULL) {
        printf("N и M должны быть натуральными числами (> 0).\n");
        return;
    }
    unsigned long long g = gcd_two(n_num, m_den);
    unsigned long long rn = n_num / g;
    unsigned long long rm = m_den / g;

    int found = 0;
    for (unsigned long long k = 1ULL; ; ++k) {
        unsigned long long a = rn * k;
        unsigned long long b = rm * k;
        if (b > 987654321ULL) break;

        int cnt = 0;
        if (used_digits_ok((long long)a, (long long)b, &cnt)) {
            found++;
            printf("%2d) %llu / %llu (использовано карточек: %d)\n", found, a, b, cnt);
        }
    }
    if (found == 0) {
        printf("Подходящих комбинаций для дроби %llu/%llu не найдено.\n", n_num, m_den);
    }
}

int main(void) {
    int choice = -1;

    while (1) {
        printf("\n=== ЛАБОРАТОРНАЯ РАБОТА №6: ПОЛЬЗОВАТЕЛЬСКИЕ ФУНКЦИИ ===\n");
        printf("1.  НОД трёх натуральных чисел\n");
        printf("2.  Треугольник и его площадь из любых 3-х отрезков (a, b, c, d)\n");
        printf("3.  Представление N = x^2 + y^2\n");
        printf("4.  Поиск целого k: y^(k-1) <= x < y^k\n");
        printf("5.  Число сотен в натуральном N (> 99)\n");
        printf("6.  Проверка N^2 - сумма_цифр(N) == 0 (N <= 99)\n");
        printf("7.  Сумма первых K старших разрядов числа N (> 10000), K <= 4\n");
        printf("8.  Произведение n на последнюю цифру m\n");
        printf("9.  Удаление цифр 0 и 5 из числа N с сохранением порядка\n");
        printf("10. Целые K, делящиеся на K^2 и не делящиеся на K^3\n");
        printf("11. Функция Аккермана A(n, m)\n");
        printf("12. Числа Армстронга из 2, 3 и 4 цифр\n");
        printf("13. Путь из 1 в n (n=10) по дорогам (ввод до 0 0)\n");
        printf("14. Сравнение площадей двух треугольников по координатам вершин\n");
        printf("15. Пересечение трёх прямых и площадь образованного треугольника\n");
        printf("16. Простые числа-близнецы на [n, 2n] (n > 2)\n");
        printf("17. Треугольник Паскаля из N строк\n");
        printf("18. Задача о 8 ферзях (все 92 расстановки)\n");
        printf("19. Сортировка методом фон Неймана (слияние с чередованием A и B)\n");
        printf("20. Обмен элементов массивов X и Y (100 эл.) без доп. переменных\n");
        printf("21. Оставить возрастающую/неубывающую последовательность\n");
        printf("22. Карточки 1..9: 4-значный числитель и 5-значный знаменатель = 1/2\n");
        printf("23. Карточки 1..9: комбинации, равные N/M\n");
        printf("0.  Выход\n");
        printf("Выберите задание: ");

        if (scanf("%d", &choice) != 1) {
            clear_stdin();
            printf("Ошибка ввода.\n");
            continue;
        }
        if (choice == 0) break;

        switch (choice) {
            case 1: {
                unsigned long long a, b, c;
                printf("Введите три натуральных числа: ");
                if (scanf("%llu %llu %llu", &a, &b, &c) == 3 && a > 0 && b > 0 && c > 0) {
                    printf("НОД(%llu, %llu, %llu) = %llu\n", a, b, c, gcd_three(a, b, c));
                } else {
                    printf("Нужны три натуральных числа (> 0).\n");
                    clear_stdin();
                }
                break;
            }
            case 2: {
                double a, b, c, d;
                printf("Введите длины четырёх отрезков a, b, c, d: ");
                if (scanf("%lf %lf %lf %lf", &a, &b, &c, &d) == 4) {
                    solve_task2(a, b, c, d);
                } else {
                    clear_stdin();
                }
                break;
            }
            case 3: {
                unsigned long long n;
                long long x = 0, y = 0;
                printf("Введите натуральное N: ");
                if (scanf("%llu", &n) == 1 && n > 0) {
                    if (find_sum_of_squares(n, &x, &y)) {
                        printf("Найдено: %llu = %lld^2 + %lld^2\n", n, x, y);
                    } else {
                        printf("Число %llu нельзя представить в виде суммы двух квадратов целых чисел.\n", n);
                    }
                } else {
                    clear_stdin();
                }
                break;
            }
            case 4: {
                double x, y;
                printf("Введите x (x > 0) и y (y > 1): ");
                if (scanf("%lf %lf", &x, &y) == 2 && x > 0.0 && y > 1.0) {
                    long long k = find_k_bounds(x, y);
                    printf("k = %lld (выполняется %.4f^(%lld) <= %.4f < %.4f^(%lld))\n",
                           k, y, k - 1, x, y, k);
                } else {
                    printf("Некорректные значения x или y.\n");
                    clear_stdin();
                }
                break;
            }
            case 5: {
                unsigned long long n;
                printf("Введите натуральное N (> 99): ");
                if (scanf("%llu", &n) == 1 && n > 99ULL) {
                    printf("Число сотен: %llu\n", count_hundreds(n));
                } else {
                    printf("Число должно быть больше 99.\n");
                    clear_stdin();
                }
                break;
            }
            case 6: {
                int n;
                printf("Введите натуральное N (N <= 99): ");
                if (scanf("%d", &n) == 1 && n > 0 && n <= 99) {
                    printf("N^2 - сумма_цифр(N) = %lld -> %s\n",
                           (long long)n * n - sum_digits_ull((unsigned long long)n),
                           check_task6(n) ? "равно 0" : "не равно 0");
                } else {
                    printf("Число должно быть от 1 до 99.\n");
                    clear_stdin();
                }
                break;
            }
            case 7: {
                unsigned long long n;
                int k;
                printf("Введите натуральное N (> 10000) и K (1 <= K <= 4): ");
                if (scanf("%llu %d", &n, &k) == 2 && n > 10000ULL && k >= 1 && k <= 4) {
                    printf("Сумма первых %d цифр числа %llu равна %d\n", k, n, sum_first_k_digits(n, k));
                } else {
                    printf("Некорректный ввод.\n");
                    clear_stdin();
                }
                break;
            }
            case 8: {
                unsigned long long n, m;
                printf("Введите натуральные n и m: ");
                if (scanf("%llu %llu", &n, &m) == 2 && n > 0 && m > 0) {
                    printf("Результат: %llu * %llu = %llu\n", n, m % 10ULL, prod_by_last_digit(n, m));
                } else {
                    clear_stdin();
                }
                break;
            }
            case 9: {
                unsigned long long n;
                printf("Введите натуральное N: ");
                if (scanf("%llu", &n) == 1 && n > 0) {
                    printf("После удаления 0 и 5: %llu\n", remove_0_and_5(n));
                } else {
                    clear_stdin();
                }
                break;
            }
            case 10: {
                long long n;
                printf("Введите целое число N: ");
                if (scanf("%lld", &n) == 1) {
                    solve_task10(n);
                } else {
                    clear_stdin();
                }
                break;
            }
            case 11: {
                unsigned int n, m;
                printf("Введите натуральные n и m (рекомендуется n <= 3, m <= 5): ");
                if (scanf("%u %u", &n, &m) == 2) {
                    printf("A(%u, %u) = %llu\n", n, m, ackermann(n, m));
                } else {
                    clear_stdin();
                }
                break;
            }
            case 12: {
                print_armstrong_2_to_4();
                break;
            }
            case 13: {
                int n = 10;
                int adj[64][64] = {{0}};
                printf("Введите пары (i j), где i < j (n = %d). Для завершения введите 0 0:\n", n);
                while (1) {
                    int u, v;
                    if (scanf("%d %d", &u, &v) != 2) {
                        clear_stdin();
                        break;
                    }
                    if (u == 0 && v == 0) break;
                    if (u >= 1 && u <= n && v >= 1 && v <= n) {
                        adj[u][v] = 1;
                        adj[v][u] = 1;
                    }
                }
                printf("Добраться от 1 до %d %s.\n", n, can_reach_n(n, adj) ? "МОЖНО" : "НЕЛЬЗЯ");
                break;
            }
            case 14: {
                double x1, y1, x2, y2, x3, y3;
                double u1, v1, u2, v2, u3, v3;
                printf("Введите координаты 1-го треугольника (x1 y1 x2 y2 x3 y3): ");
                if (scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3) != 6) {
                    clear_stdin();
                    break;
                }
                printf("Введите координаты 2-го треугольника (x1 y1 x2 y2 x3 y3): ");
                if (scanf("%lf %lf %lf %lf %lf %lf", &u1, &v1, &u2, &v2, &u3, &v3) != 6) {
                    clear_stdin();
                    break;
                }
                double s1 = triangle_area_coords(x1, y1, x2, y2, x3, y3);
                double s2 = triangle_area_coords(u1, v1, u2, v2, u3, v3);
                printf("Площадь 1-го = %.4f, площадь 2-го = %.4f\n", s1, s2);
                if (fabs(s1 - s2) < 1e-9) printf("Площади равны.\n");
                else if (s1 > s2) printf("Большая площадь у 1-го треугольника.\n");
                else printf("Большая площадь у 2-го треугольника.\n");
                break;
            }
            case 15: {
                double a[3], b[3], c[3];
                for (int k = 0; k < 3; ++k) {
                    printf("Введите коэффициенты a%d, b%d, c%d для прямой %d: ", k + 1, k + 1, k + 1, k + 1);
                    if (scanf("%lf %lf %lf", &a[k], &b[k], &c[k]) != 3) {
                        clear_stdin();
                        k = 3;
                        break;
                    }
                }
                solve_task15(a, b, c);
                break;
            }
            case 16: {
                int n;
                printf("Введите целое число n (n > 2): ");
                if (scanf("%d", &n) == 1 && n > 2) {
                    print_twin_primes(n);
                } else {
                    printf("Число n должно быть больше 2.\n");
                    clear_stdin();
                }
                break;
            }
            case 17: {
                int n;
                printf("Введите натуральное N (количество строк треугольника Паскаля): ");
                if (scanf("%d", &n) == 1 && n > 0 && n <= 20) {
                    print_pascal_triangle(n);
                } else {
                    printf("Введите число от 1 до 20.\n");
                    clear_stdin();
                }
                break;
            }
            case 18: {
                int pos[8];
                int count = 0;
                char show;
                printf("Вывести все 92 расстановки? (y/n): ");
                clear_stdin();
                show = (char)getchar();
                bool print_all = (show == 'y' || show == 'Y');
                solve_8_queens_rec(0, 0, 0, 0, pos, &count, print_all);
                printf("Всего найдено расстановок: %d\n", count);
                break;
            }
            case 19: {
                int n;
                printf("Введите количество элементов N: ");
                if (scanf("%d", &n) == 1 && n > 0) {
                    int *arr = (int *)malloc((size_t)n * sizeof(int));
                    if (!arr) break;
                    printf("Введите %d чисел: ", n);
                    for (int i = 0; i < n; ++i) scanf("%d", &arr[i]);
                    von_neumann_sort(arr, n);
                    printf("Отсортированный массив: ");
                    for (int i = 0; i < n; ++i) printf("%d ", arr[i]);
                    printf("\n");
                    free(arr);
                } else {
                    clear_stdin();
                }
                break;
            }
            case 20: {
                const int SZ = 100;
                int x[100], y[100];
                for (int i = 0; i < SZ; ++i) {
                    x[i] = i + 1;
                    y[i] = (i + 1) * 10;
                }
                swap_arrays_no_temp(x, y, SZ);
                printf("Обмен выполнен для 100 элементов. Первые 5 элементов: X[0..4] = [%d, %d, %d, %d, %d], Y[0..4] = [%d, %d, %d, %d, %d]\n",
                       x[0], x[1], x[2], x[3], x[4], y[0], y[1], y[2], y[3], y[4]);
                break;
            }
            case 21: {
                int n;
                printf("Введите количество элементов n: ");
                if (scanf("%d", &n) == 1 && n > 0) {
                    int *arr = (int *)malloc((size_t)n * sizeof(int));
                    int *out = (int *)malloc((size_t)n * sizeof(int));
                    if (arr && out) {
                        printf("Введите %d целых чисел: ", n);
                        for (int i = 0; i < n; ++i) scanf("%d", &arr[i]);
                        int m = filter_non_decreasing(arr, n, out);
                        printf("Результирующая последовательность (%d эл.): ", m);
                        for (int i = 0; i < m; ++i) printf("%d ", out[i]);
                        printf("\n");
                    }
                    free(arr);
                    free(out);
                } else {
                    clear_stdin();
                }
                break;
            }
            case 22: {
                find_all_half_fractions();
                break;
            }
            case 23: {
                unsigned long long n_num, m_den;
                printf("Введите натуральные N и M (например, 2 3): ");
                if (scanf("%llu %llu", &n_num, &m_den) == 2) {
                    find_card_fractions_nm(n_num, m_den);
                } else {
                    clear_stdin();
                }
                break;
            }
            default:
                printf("Выберите пункт от 0 до 23.\n");
                break;
        }
    }

    return 0;
}
