from bank import value

def main():
    test_hello()
    test_hello_Newman()
    test_HYD()
    test_WH()

def test_hello():
    assert value('Hello') == 0

def test_hello_Newman():
    assert value('Hello, Newman') == 0

def test_HYD():
    assert value('How you doing?') == 20

def test_WH():
    assert value("What's happening?") == 100



if __name__ == "__main__":
    main()