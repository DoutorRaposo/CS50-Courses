from fuel import convert, gauge
import pytest

def test_75():
    assert convert("3/4") == 75

def test_float():
    with pytest.raises(AttributeError):
        assert convert(0.75) == 75

def test_int():
    with pytest.raises(AttributeError):
        assert convert(3/4) == 75

def test_66or67():
    assert convert("2/3") == 67

def test_0():
    with pytest.raises(ZeroDivisionError):
        convert("2/0")

def test_empty():
    assert convert("0/3") == 0

def test_overload():
    with pytest.raises(ValueError):
        convert("4/3")

def test_F():
    assert gauge(100) == "F"

def test_F2():
    assert gauge(99) == "F"

def test_E():
    assert gauge(0) == "E"

def test_E2():
    assert gauge(1) == "E"

def test_67():
    assert gauge(67) == "67%"