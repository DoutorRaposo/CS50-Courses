from plates import is_valid

def main():
    test_CS50()
    test_CS05()
    test_CS50P()
    test_pi()
    test_h()
    test_outatime()
    test_cs()
    test_c5()

def test_CS50():
    assert is_valid("CS50") == True

def test_CS05():
    assert is_valid("CS05") == False

def test_CS50P():
    assert is_valid("CS50P") == False

def test_pi():
    assert is_valid("PI3.14") == False

def test_h():
    assert is_valid("H") == False

def test_cs():
    assert is_valid("CS") == True

def test_c5():
    assert is_valid("C5") == False

def test_outatime():
    assert is_valid("OUTATIME") == False


if __name__ == "__main__":
    main()