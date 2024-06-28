from settings import *

# still not perfect, come back and modify


class Cube:
    def __init__(self, game):
        self.game = game
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
        self.matrixB = [[-1, -1, 1],
                        [1, -1, 1],
                        [1, 1, 1],
                        [-1, 1, 1],
                        [-1, -1, -1],
                        [1, -1, -1],
                        [1, 1, -1],
                        [-1, 1, -1]]
        self.th = 0
        self.dist = 3

    def draw2(self):
        self.th += 0.01
        mRx = [[1, 0, 0],
               [0, math.cos(self.th), math.sin(self.th)],
               [0, -math.sin(self.th), math.cos(self.th)]]
        mRy = [[math.cos(self.th), 0, -math.sin(self.th)],
               [0, 1, 0],
               [math.sin(self.th), 0, math.cos(self.th)]]
        mRz = [[math.cos(self.th), math.sin(self.th), 0],
               [-math.sin(self.th), math.cos(self.th), 0],
               [0, 0, 1]]

        i = 0
        for p in self.matrixB:
            RxPx = p[0] * mRx[0][0] + p[1] * mRx[1][0] + p[2] * mRx[2][0]
            RxPy = p[0] * mRx[0][1] + p[1] * mRx[1][1] + p[2] * mRx[2][1]
            RxPz = p[0] * mRx[0][2] + p[1] * mRx[1][2] + p[2] * mRx[2][2]

            RyPx = RxPx * mRy[0][0] + RxPy * mRy[1][0] + RxPz * mRy[2][0]
            RyPy = RxPx * mRy[0][1] + RxPy * mRy[1][1] + RxPz * mRy[2][1]
            RyPz = RxPx * mRy[0][2] + RxPy * mRy[1][2] + RxPz * mRy[2][2]

            RzPx = RyPx * mRz[0][0] + RyPy * mRz[1][0] + RyPz * mRz[2][0]
            RzPy = RyPx * mRz[0][1] + RyPy * mRz[1][1] + RyPz * mRz[2][1]
            RzPz = RyPx * mRz[0][2] + RyPy * mRz[1][2] + RyPz * mRz[2][2]

            z = 1 / (self.dist - RzPz)  # t1 scales it down and makes larger dist further instead of reverse
            # z = 1  # uncomment for orthographic projection

            pjM = [[z, 0, 0],
                   [0, z, 0]]

            x = RzPx * pjM[0][0] + RzPy * pjM[1][0]
            y = RzPx * pjM[0][1] + RzPy * pjM[1][1]
            x = int(x * SCALE + HWIDTH)
            y = int(y * SCALE + HHEIGHT)
            pg.draw.circle(self.game.screen, 'red', (x, y), 5)
            print(x)

            self.matrixAt[i][0] = x
            self.matrixAt[i][1] = y
            i += 1
        self.draw_lines()

    def draw_lines(self):
        for i in range(4):
            self.connect(i, (i + 1) % 4)
            self.connect(i + 4, (i + 1) % 4 + 4)
            self.connect(i, i + 4)
            # new concept: using modulus

    def connect(self, i, j):
        pg.draw.line(self.game.screen, 'red', (self.matrixAt[i][0], self.matrixAt[i][1]),
                     (self.matrixAt[j][0], self.matrixAt[j][1]))
