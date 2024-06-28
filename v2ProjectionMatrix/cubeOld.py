from settings import *
import numpy as num


class CubeOld:
    def __init__(self, game):
        self.game = game
        self.prev_time = 0
        self.Tf = 1
        self.Sx = 1
        self.Sy = 1
        self.Sz = 1
        self.Sf = 1
        self.th = -0.3
        self.mS = [[self.Sx, 0, 0],
                   [0, self.Sy, 0],
                   [0, 0, self.Sz]]
        self.mRx = [[1, 0, 0],
                    [0, math.cos(self.th), math.sin(self.th)],
                    [0, -math.sin(self.th), math.cos(self.th)]]
        self.mRy = [[math.cos(self.th), 0, -math.sin(self.th)],
                    [0, 1, 0],
                    [math.sin(self.th), 0, math.cos(self.th)]]
        self.mRz = [[math.cos(self.th), math.sin(self.th), 0],
                    [-math.sin(self.th), math.cos(self.th), 0],
                    [0, 0, 1]]
        self.matrixA = [[-1, 1, -3],
                        [1, 1, -3],
                        [1, -1, -3],
                        [-1, -1, -3],  # --
                        [-1, -1, -5],
                        [1, -1, -5],
                        [1, 1, -5],
                        [-1, 1, -5]]
        self.matrixAt = [[0, 0, 0],
                         [0, 0, 0],
                         [0, 0, 0],
                         [0, 0, 0],
                         [0, 0, 0],
                         [0, 0, 0],
                         [0, 0, 0],
                         [0, 0, 0]]
        self.transform('r')

    def update(self):
        if self.timed_event():
            self.transform('r')

    def timed_event(self):
        curr_time = pg.time.get_ticks()
        if curr_time - self.prev_time >= 200:
            self.prev_time = curr_time
            return True

    def draw(self):
        at = self.matrixAt
        for i in range(len(self.matrixA)):
            x = self.matrixA[i][0] / -self.matrixA[i][2]
            y = self.matrixA[i][1] / -self.matrixA[i][2]
            x = self.remap(x, 0)
            y = self.remap(y, 1)

            pg.draw.circle(self.game.screen, 'green',
                           (x, y), 5)
            at[i][0] = x
            at[i][1] = y
            if i + 1 < len(at):
                pg.draw.line(self.game.screen, 'white', (at[i][0], at[i][1]), (at[i + 1][0], at[i + 1][1]))
            if i < 3:
                pg.draw.line(self.game.screen, 'white', (at[i][0], at[i][1]), (at[7 - i][0], at[7 - i][1]))
        pg.draw.line(self.game.screen, 'white', (at[0][0], at[0][1]), (at[3][0], at[3][1]))
        pg.draw.line(self.game.screen, 'white', (at[4][0], at[4][1]), (at[7][0], at[7][1]))

    def remap(self, point, p):
        point = (1 + point) / 2
        if p == 0:
            point *= WIDTH
        if p == 1:
            point *= WIDTH
            point -= HEIGHT / 3  # 3....
        return point

    def transform(self, mode):
        for i in range(len(self.matrixA)):
            x = self.matrixA[i][0]
            y = self.matrixA[i][1]
            z = self.matrixA[i][2]
            ms = None

            if mode == 's':
                ms = self.mS
                # self.mS[0][0] = self.Sf
            if mode == 'r':
                ms = self.mRy

            self.matrixA[i][0] = x * ms[0][0] + y * ms[1][0] + z * ms[2][0]
            self.matrixA[i][1] = x * ms[0][1] + y * ms[1][1] + z * ms[2][1]
            self.matrixA[i][2] = x * ms[0][2] + y * ms[1][2] + z * ms[2][2]
