#include <numeric>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <random>
#include <queue>

void clearScreen() {
    printf("\033[2J\033[1;1H");
}

void openCell(int r, int c, const std::vector<std::vector<int>>& field,
              std::vector<std::vector<int>>& UI, int n, int m) {
    if (UI[r][c] == 1) return;

    std::queue<std::pair<int,int>> q;
    q.push({r, c});

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        if (UI[x][y] == 1) continue;
        UI[x][y] = 1;

        if (field[x][y] == 0) {
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (dx == 0 && dy == 0) continue;
                    int nx = x + dx, ny = y + dy;
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && UI[nx][ny] == 0) {
                        q.push({nx, ny});
                    }
                }
            }
        }
    }
}

bool checkWin(const std::vector<std::vector<int>>& field,
              const std::vector<std::vector<int>>& UI, int n, int m, int mine) {
    int opened = 0;
    for (int r = 0; r < n; ++r)
        for (int c = 0; c < m; ++c)
            if (UI[r][c] == 1) ++opened;

    return opened == n * m - mine;
}

void generateMines(std::vector<int>& ground, std::vector<std::vector<int>>& field, int n, int m, int totalMines){
    std::iota(ground.begin(), ground.end(), 0);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(ground.begin(), ground.end(), g);
    for (int i = 0; i < totalMines; ++i) {
        int r = ground[i] / m;
        int c = ground[i] % m;
        field[r][c] = -1;
    }

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (field[r][c] == -1) {
                for (int dr = -1; dr <= 1; ++dr)
                    for (int dc = -1; dc <= 1; ++dc) {
                        int nr = r + dr, nc = c + dc;
                        if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
                        if (field[nr][nc] == -1) continue;
                        field[nr][nc]++;
                    }
            }
        }
    }
}

int main() {
    int n, m, minePercent;
    printf("size(n m) & min percentage(example: 10 10 10): ");
    scanf("%d %d %d", &n, &m, &minePercent);

    if(n <= 0 || m <= 0 || minePercent <= 0 || minePercent > 100) {
        printf("bad size or min percentage");
        return 1;
    }

    int totalMines = n * m * minePercent / 100;

    std::vector<int> ground(n*m);
    std::vector<std::vector<int>> field(n, std::vector<int>(m, 0));

    generateMines(ground, field, n, m, totalMines);

    std::vector<std::vector<int>> UI(n, std::vector<int>(m, 0));
    bool boom = false;

    while (!boom) {
        clearScreen();
        printf("   ");
        for (int c = 0; c < m; ++c)
            printf("%3d ", c);
        printf("\n");

        for (int r = 0; r < n; ++r) {
            printf("%2d ", r);
            for (int c = 0; c < m; ++c) {
                if (UI[r][c] == 1) {
                    if (field[r][c] == 0) {
                            printf("[0] ");
                        continue;
                    }
                    printf("[\033[32m%d\033[0m] ", field[r][c]);
                } else {
                    printf("[\033[34mX\033[0m] ");
                }
            }
            printf("\n");
        }

        int x, y;
        printf("Coordinate(example: 2 1): ");
        scanf("%d %d", &x, &y);

        if (x < 0 || x >= n || y < 0 || y >= m) continue;

        if (field[x][y] == -1) {
            boom = true;
        } else {
            openCell(x, y, field, UI, n, m);
            if (checkWin(field, UI, n, m, totalMines)) break;
        }
    }

    clearScreen();
    printf("   ");
    for (int c = 0; c < m; ++c)
        printf("%3d ", c);
    printf("\n");

    for (int r = 0; r < n; ++r) {
        printf("%2d ", r);
        for (int c = 0; c < m; ++c) {
            if (field[r][c] == -1) printf("[\033[31m*\033[0m] ");
            else printf("[\033[32m%d\033[0m] ", field[r][c]);
        }
        printf("\n");
    }

    if (boom) printf("You lose.\n");
    else printf("You win!\n");
    system("pause");
    return 0;
}
