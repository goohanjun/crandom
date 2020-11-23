if __name__ == "__main__":
    print("import safeRandom")
    from safe_random import safeRandom

    for i in range(10):
        print(f"Generated Random Number: {safeRandom.uniform()}")

    print("set seed 0")
    safeRandom.seed(0)

    for i in range(10):
        print(f"Generated Random Number: {safeRandom.uniform()}")
