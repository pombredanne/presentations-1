import re

from pygments import highlight
from pygments.lexers import PythonLexer
from pygments.formatters import TerminalFormatter
from pygments.filter import Filter
from pygments.token import Name
from pygments.util import get_bool_opt


class CamelCaseFilter(Filter):

    def __init__(self, **options):
        Filter.__init__(self, **options)

    def convert(self, name):
        results = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
        return re.sub('([a-z0-9])([A-Z])', r'\1_\2', results).lower()

    def filter(self, lexer, stream):
        for ttype, value in stream:
            if ttype is Name.Function or ttype is Name:
                value = self.convert(value)
            yield ttype, value


code = """
for i in range(1, 11):
    print("Hello world!")

if x and y:
    print("yes")

if x or y:
    print("dunno")

globalVariable = 42

def helloWorld():
    print("Hello world!")

helloWorld()

print(globalVariable)
"""


print(highlight(code, PythonLexer(), TerminalFormatter()))

print("-----------------------")

lexer = PythonLexer()

# pridani filtru
lexer.add_filter(CamelCaseFilter())

print(highlight(code, lexer, TerminalFormatter()))
