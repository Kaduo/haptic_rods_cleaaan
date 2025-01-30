from proto.structs_pb2 import Rod, Signal, RodGroup, _Color, _Rectangle, SignalShape


def sine(period, amplitude=255):
    return Signal(signalShape=SignalShape.SINE, period=period, amplitude=amplitude)


ROD_HEIGHT = 30
ROD_WIDTH = 3*ROD_HEIGHT

WHITE = _Color(r=255, g=255, b=255, a=255)

if __name__ == "__main__":
    sigs = [sine(period=20, amplitude=255), sine(period=10, amplitude=255), sine(period=30, amplitude=255), sine(period=90, amplitude=255), sine(period=90, amplitude=255)]
    rod_group = RodGroup()
    for x,sig in enumerate(sigs):
        for y in range(4):
            rod = Rod(signal=sig, rect = _Rectangle(x=2*x*ROD_WIDTH, y=2*y*ROD_HEIGHT, width=ROD_WIDTH, height=ROD_HEIGHT), color = WHITE)
            rod_group.rods.append(rod)
    with open("dummy.rg", "wb") as f:
        f.write(rod_group.SerializeToString())