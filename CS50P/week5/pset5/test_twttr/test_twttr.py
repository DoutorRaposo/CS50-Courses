from twttr import shorten

def main():
    test_twttr_upper()
    test_twttr_lower()
    test_twttr_phrase1()
    test_twttr_phrase2()
    test_twttr_punct()
    test_twttr_number()

def test_twttr_upper():
    assert shorten('AEIOU') == ''

def test_twttr_lower():
    assert shorten('aeiou') == ''

def test_twttr_phrase1():
    assert shorten('Twitter') == 'Twttr'

def test_twttr_phrase2():
    assert shorten('EuTopIa') == 'Tp'

def test_twttr_punct():
    assert shorten("!.-") == "!.-"

def test_twttr_number():
    assert shorten("50") == "50"

if __name__ == "__main__":
    main()
