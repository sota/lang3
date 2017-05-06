

from pytest import fixture
from sota.lexer import Lexer

@fixture
def lexer():
    return Lexer()

def test_ctor(lexer):
    assert isinstance(lexer, Lexer)

def test_scan(lexer):
    tokens = lexer.scan('0')
    print([token.value for token in tokens])
    assert tokens
