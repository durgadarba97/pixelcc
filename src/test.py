from __future__ import annotations

import colorsys
import random
import time

Grid = list[list[int]]
Weights = list[list[float]]

WIDTH = 40
HEIGHT = 24
SEARCH_RADIUS = 2
TIME_STEP = 1 / 30


def randfloat(start, end):
    return random.random() * (end - start) + start


def init_grid(width: int, height: int) -> Grid:
    m = []
    for y in range(height):
        m.append([])
        for x in range(width):
            m[y].append(0)

    return m


def init_weights(radius: int) -> Weights:
    size = radius * 2 + 1

    w = []
    for y in range(size):
        w.append([])
        for x in range(size):
            w[y].append(0)

    for y in range(size):
        for x in range(size):
            dist_from_center = (x - radius) ** 2 + (y - radius) ** 2
            weight = 1 / (dist_from_center) if dist_from_center > 0 else 1
            weight = weight**0.1
            w[y][x] = weight

    return w


WEIGHTS = init_weights(SEARCH_RADIUS)


def tick_cell(x: int, y: int, map: Grid) -> int:
    last_value = map[y][x]

    n = 0
    c = 0
    for u in range(-SEARCH_RADIUS, SEARCH_RADIUS + 1):
        for v in range(-SEARCH_RADIUS, SEARCH_RADIUS + 1):
            if u == 0 and v == 0:
                continue

            x2 = abs((x + u) % WIDTH)
            y2 = abs((y + v) % HEIGHT)
            last_neighb_value = map[y2][x2]

            if last_neighb_value > randfloat(0.4, 0.6):
                weight = WEIGHTS[v + SEARCH_RADIUS][u + SEARCH_RADIUS]
                c += last_neighb_value * randfloat(0.9, 1.1) * weight
                n += weight

    new_value = (last_value + c) / n if n > 0 else 1
    new_value = max(0, min(1, new_value))

    return new_value


def tick_map(grid: Grid) -> Grid:
    new_grid = init_grid(WIDTH, HEIGHT)

    for y in range(HEIGHT):
        for x in range(WIDTH):
            last_value = grid[y][x]

            if last_value <= randfloat(0.1, 0.35):
                new_value = tick_cell(x, y, grid)
            else:
                new_value = last_value * (1.0 - randfloat(0.2, 0.4) * TIME_STEP)

            new_value = max(0, min(1, new_value))
            new_grid[y][x] = new_value

    return new_grid


def clear_screen():
    print("\033[2J", end="")


def print_map(grid: Grid):
    print("\033[0;0H", end="")

    for y in range(HEIGHT):
        for x in range(WIDTH):
            v = grid[y][x]**2.0

            h = v**2 * 0.2 + 0.2
            s = 0.5 + v**2 * 0.5
            v = v**3

            r, g, b = colorsys.hsv_to_rgb(h, s, v)

            print(rgb_to_ansi(r, g, b) + "██", end="")

        print()


def rgb_to_ansi(r: int, g: int, b: int) -> str:
    r = int(r * 255)
    g = int(g * 255)
    b = int(b * 255)
    return f"\033[38;2;{r};{g};{b}m"


if __name__ == "__main__":
    g = init_grid(WIDTH, HEIGHT)
    w = init_weights(SEARCH_RADIUS)

    for y in range(HEIGHT):
        for x in range(WIDTH):
            g[y][x] = random.random()

    clear_screen()

    while True:
        g = tick_map(g)
        print_map(g)

        time.sleep(TIME_STEP)