from proto.structs_pb2 import Rod, Signal, RodGroup, _Color, _Rectangle, SignalShape
import random


def sine(period, amplitude=255, offset=10):
    return Signal(signalShape=SignalShape.SINE, period=period, amplitude=amplitude)


TABLET_WIDTH = 1000
TABLET_HEIGHT = 600
ROD_HEIGHT = 30
ROD_WIDTH = 3 * ROD_HEIGHT


def test_collision(rod, other_rods, x_pad, y_pad):
    for other_rod in other_rods:
        if (
            rod.rect.x - x_pad < other_rod.rect.x < rod.rect.x + rod.rect.width + x_pad
            or other_rod.rect.x - x_pad
            < rod.rect.x
            < other_rod.rect.x + other_rod.rect.width + x_pad
        ) and (
            rod.rect.y - y_pad < other_rod.rect.y < rod.rect.y + rod.rect.height + y_pad
            or other_rod.rect.y - y_pad
            < rod.rect.y
            < other_rod.rect.y + other_rod.rect.height + y_pad
        ):
            return True
    return False


def shuffle_group(
    rod_group,
    x_min=0,
    x_max=TABLET_WIDTH,
    y_min=0,
    y_max=TABLET_HEIGHT,
    x_pad=10,
    y_pad=10,
):
    rods = list(rod_group.rods)
    random.shuffle(rods)
    for i, rod in enumerate(rods):
        rod.rect.x = random.uniform(x_min, x_max - rod.rect.width - x_pad)
        rod.rect.y = random.uniform(y_min, y_max - rod.rect.height - y_pad)

        while test_collision(rod, rods[:i] + rods[i + 1 :], x_pad, y_pad):
            rod.rect.x = random.uniform(x_min, x_max - rod.rect.width - x_pad)
            rod.rect.y = random.uniform(y_min, y_max - rod.rect.height - y_pad)

        # if not x + rod.rect.width + max_x_pad < x_max:
        #     x = 0
        #     y += max_y_pad
        # rod.rect.x = x + random.uniform(min_x_pad, max_x_pad)
        # x += rod.rect.width + max_x_pad
        # rod.rect.y = y + random.uniform(0, max_y_pad - min_y_pad)
    return RodGroup(rods=rods)


WHITE = _Color(r=0xff, g=0xff, b=0xff)
RED = _Color(r=0xe6, g=0x29, b=0x37)
GREEN = _Color(r=0x00, g=0xe4, b=0x30)
PURPLE = _Color(r=0xc8, g=0x7a, b=0xff)
YELLOW = _Color(r=0xfd, g=0xf9, b=0x00)
DARK_GREEN = _Color(r=0x00, g=0x75, b=0x2c)
BLACK =  _Color(r=0, g=0, b=0)
BROWN = _Color(r=0x7f, g=0x6a, b=0x4f)
BLUE = _Color(r=0x00, g=0x79, b=0xf1)
ORANGE = _Color(r=0xff, g=0xa1, b=0x00)

COLORS = [WHITE, RED, GREEN, PURPLE, YELLOW, DARK_GREEN, BLACK, BROWN, BLUE, ORANGE]
PERIODS = [0, 10, 30, 90]

def lambda_rod():
    return  Rod(signal=Signal(signalShape=SignalShape.SINE, period=0, amplitude=255, offset=0), rect=_Rectangle(width=ROD_WIDTH, height=ROD_HEIGHT))

def make_only_periods():
    rod_group = RodGroup()
    for period in PERIODS:
        for _ in range(random.randrange(3,6)):
            rod = lambda_rod()
            rod.signal.period = period
            rod_group.rods.append(rod)
    return shuffle_group(rod_group)

def make_only_colors():
    rod_group = RodGroup()
    for color in COLORS:
        rod = lambda_rod()
        rod.color.CopyFrom(color)
        rod_group.rods.append(rod)
    return shuffle_group(rod_group)

def make_weird_signals():
    rod_group = RodGroup()

    rod = lambda_rod()
    rod.signal.offset = 1 
    rod.color.CopyFrom(BLACK)
    rod_group.rods.append(rod)


    rod = lambda_rod()
    rod.signal.period = 1
    rod.color.CopyFrom(BLUE)
    rod_group.rods.append(rod)

    rod = lambda_rod()
    rod.signal.offset = 1 
    rod.signal.period = 1
    rod.color.CopyFrom(PURPLE)
    rod_group.rods.append(rod)

    rod = lambda_rod()
    rod.signal.offset = 100
    rod.color.CopyFrom(ORANGE)
    rod_group.rods.append(rod)

    rod = lambda_rod()
    rod.signal.period = 2**16 - 1
    rod.color.CopyFrom(RED)
    rod_group.rods.append(rod)

    rod = lambda_rod()
    rod.signal.period = 1000
    rod.color.CopyFrom(GREEN)
    rod_group.rods.append(rod)


    rod = lambda_rod()
    rod.signal.period = 1000
    rod.signal.offset = 200
    rod.color.CopyFrom(DARK_GREEN)
    rod_group.rods.append(rod)

    rod = lambda_rod()
    rod.signal.signalShape = SignalShape.STEADY
    rod.signal.period = 1
    rod.color.CopyFrom(YELLOW)
    rod_group.rods.append(rod)


    return shuffle_group(rod_group)


if __name__ == "__main__":
    with open("only_periods.rg", "wb") as f:
        f.write(make_only_periods().SerializeToString())

    with open("only_colors.rg", "wb") as f:
        f.write(make_only_colors().SerializeToString())

   
    with open("weird.rg", "wb") as f:
        f.write(make_weird_signals().SerializeToString())