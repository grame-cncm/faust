def main() -> None:
    x = Int32(1 > 0)
    print(reflect[type_of(x)].name())
    print(DType.bool)
