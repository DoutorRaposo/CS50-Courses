from numb3rs import validate

def test_valid_IP_1():
    assert validate("127.0.0.1") is True

def test_valid_IP_2():
    assert validate("255.255.255.255") is True

def test_invalid_IP_1():
    assert validate("512.512.512.512") is False

def test_invalid_IP_2():
    assert validate("1.2.3.400") is False

def test_invalid_IP_3():
    assert validate("1.2.300.4") is False

def test_invalid_IP_4():
    assert validate("1.256.3.4") is False

def test_invalid_IP_5():
    assert validate("256.2.3.4") is False

def test_invalid_IP_6():
    assert validate("cat") is False