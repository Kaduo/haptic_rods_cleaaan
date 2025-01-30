import proto.structs_pb2

if __name__ == "__main__":
    print("hi")
    rod = proto.structs_pb2.Rod()
    rod.rect.x = 0
    rod.rect.y = 0
    rod.rect.width = 20
    rod.rect.height = 50
    rod.color.r = 0
    rod.color.g = 255
    rod.color.a = 255
    with open("myRod.spec", "wb") as f:
        f.write(rod.SerializeToString())
