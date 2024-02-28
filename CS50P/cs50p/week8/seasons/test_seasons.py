from seasons import convert_input
import pytest
from datetime import date

def test_1():
    assert convert_input("1993-09-10") == date(1993, 9, 10)

def test_2():
    with pytest.raises(SystemExit):
        convert_input("dez de setembro de mil novecentes e noventa e três")

def test_3():
    with pytest.raises(SystemExit):
        convert_input("1993-09-100")