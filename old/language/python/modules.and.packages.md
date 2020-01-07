# MODULES AND PACKAGES

In programming, a module is a piece of software that has a specific functionality. For example, when building a ping pong game, one module would be responsible for the game logic, and another module would be responsible for drawing the game on the screen. Each module is a different file, which can be edited separately.

## WRITING MODULES

Modules in python are imply Python files with a .py extension. The name of the module will be then name of the file. A Python module can have a set of functions, classes or variables defined and implemented. In the example above, we will have two files, we will have:

```
mygame/
mygame/game.py
mygame/draw.py
```

The Python script game.py will implement the game. It will use the function draw_game from the file draw.py, or in other words, the draw module, that implements the logic for drawing the game on the screen.

Modules are imported from other modules using the import command. In this example, the game.py script may look something like this:

```
import draw

def play_game():
    ...

def main():
    result = play_game()
    draw.draw_game(result)

if __name__ == '__main__':
    main()
```

The draw module may look something like this:

```
def draw_game():
    ...

def clear_screen(screen):
    ...
```

In this example, the game module imports the load module, which enables it to use function implemented in that module. The main function would use the local function play_game to run the game, and then draw the result of the game using a function implemented in the draw module called draw_game. To use the function draw_game from the draw module, we would need to specify in which module the function is implemented, using the dot operator. To reference the draw_game function from the game module, we would need to import the draw module and only then call draw.draw_game().

When the import draw directive will run, the Python interpret will look for a file in the directory which the script was executed from, by the name of the module with a .py prefix, so in our case it will try to look for draw.py. If wull find one, it will import it, if not, he will continue to look for built-in modules.

You may have noticed that when importing a module, a .pyc file appears, which is a compiled Python file. Python compiles files into Python bytecodes so that it won't have to parse the files each time modules are loaded. If a .pyc file exists, it gets loaded instead of the .py file, but this process is transparent to the user.

## IMPORT MODULE OBJECTS TO THE CURRENT NAMESPACE

We may also import the function draw_game directly into the main script's namespace, by using the from command.

```
from draw import draw_game

def main()
    result = play_game()
    draw_game(result)
```

You may have noticed that in this example, draw_game does not precede with the name of the module it is imported from, because we've specified the module name in the import command.

The advantages of using this notation is that it is easier to use the functions inside the current module because you don't need to specify which module the function comes from. However, any namespace cannot have two objects with the exact same name, so the import command may replace an existing object in the namespace.

## IMPORTING ALL OBJECTS FROM A MODULE

We may also use the import * command to import all objects from a specific module, like this:

```
from draw import *

def main()
    result = play_game()
    draw_game(result)
```

This might be a bit risky as changes in the module might affect the module which imports it, but it is shorter and also does not require you to specify which objects you wish to import from the module.


## CUSTOM IMPORT NAME

We may also load modules under any name we want. This is useful we want to import a module conditionally to use the same name in the rest of the code.

For example, if you have two draw modules with slighty different names - you may do the following:

```
if visual_mode:
    import draw_visual as draw
else
    import draw_textual as draw

def main():
    result = play_game()
    draw.draw_game(result)
```

## MODULE INITIALIZATION

The first time a module is loaded into a running Python script, it is initialized by executing the code in the module once. If another module in your code imports the same module again, it will not be loaded twice but once only - so local variables inside the module act as a "singleton" - they are initialized only once.

This is useful to know, because this means that you can rely on this behavior for initializing objects. For example:

```
def draw_game():
    clear_screen(main_screen)

def clear_screen(screen):
    ...

def Screen()
    ...

main_screen = Screen()
```

## EXTENDING MODULE LOAD PATH

There are a couple of ways we could tell the Python interpreter where to look for modules, aside from the default, which is the local directory and the built-in modules. You could either use the environment variable PYTHONPATH to specify additional directories to look for modules in, like this:

```
PYTHONPATH=/foo python game.py
```

This will execute game.py, and will enable the script to load modules frmo the foo directory as well as local directory.
Another method is the sys.path.append function. You may execute it before running an import command:

```
sys.path.append("/foo")
```

This will add the foo directory to the list of paths to look for modules in as well.

## EXPLORING BUILT-IN MODULES

Check out the full list of built-in modules in the Python standard library [here](https://docs.python.org/3/library/).

Two very important functions come in handy when exploring modules in Python - the dir and help functions.

If we want to import the module urllib, which enables use to create read data from URLs, we simply import the module:

```
import urllib

urllib.urlopen(...)
```

We can look for which functions are implemented in each module by using the dir function:

```
>>> import urllib
>>> dir(urllib)
['ContentTooShortError', 'FancyURLopener', 'MAXFTPCACHE', 'URLopener', '__all__', '__builtins__',
'__doc__', '__file__', '__name__', '__package__', '__version__', '_ftperrors', '_get_proxies',
'_get_proxy_settings', '_have_ssl', '_hexdig', '_hextochr', '_hostprog', '_is_unicode', '_localhost',
'_noheaders', '_nportprog', '_passwdprog', '_portprog', '_queryprog', '_safe_map', '_safe_quoters',
'_tagprog', '_thishost', '_typeprog', '_urlopener', '_userprog', '_valueprog', 'addbase', 'addclosehook',
'addinfo', 'addinfourl', 'always_safe', 'basejoin', 'c', 'ftpcache', 'ftperrors', 'ftpwrapper', 'getproxies',
'getproxies_environment', 'getproxies_macosx_sysconf', 'i', 'localhost', 'main', 'noheaders', 'os',
'pathname2url', 'proxy_bypass', 'proxy_bypass_environment', 'proxy_bypass_macosx_sysconf', 'quote',
'quote_plus', 'reporthook', 'socket', 'splitattr', 'splithost', 'splitnport', 'splitpasswd', 'splitport',
'splitquery', 'splittag', 'splittype', 'splituser', 'splitvalue', 'ssl', 'string', 'sys', 'test', 'test1',
'thishost', 'time', 'toBytes', 'unquote', 'unquote_plus', 'unwrap', 'url2pathname', 'urlcleanup', 'urlencode',
'urlopen', 'urlretrieve']
```

When we find the function in the module we want to use, we can red about it more using the help function, inside the Python interpreter:

```
help(urllib.urlopen)
```

## WRITING PACKAGES

Packages are namespaces which contain multiple packages and modules themselves. They are simply directories, but a twist.
Each package in Python is a directory which must contain a special file called ```__init__.py```. This file can empty, and it indicates that the directory it contains is a Python package, so it can be imported the same way a module can be imported.

If we create a directory called foo, which marks the package name, we can then create a module inside that package called bar. We also must not forget to add the ```__init__.py``` file inside the foo directory.

To use the module bar, we can import it in two ways:

```
import foo.bar
```

or

```
from foo import bar
```

In the first method, we must use the foo prefix whenever we access the module bar. In the second method. We don't, because we import the module to our module's namespace.

The ```__init__.py``` file can also decide which modules the package exports as the API, while keeping other modules internal, by overriding the ```__all__``` variable, like so:

```
__init__.py:

__all__ = ["bar"]
```

## EXERCISE

In this exercise, you will need to print an alphabetically sorted list of all functions in the re module, which contain the word find:

```
import re

find_members = []
for member in dir(re):
    if "find" in member:
        find_members.append(member)

print(sorted(find_members))
```
